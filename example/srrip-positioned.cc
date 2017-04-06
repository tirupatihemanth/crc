////////////////////////////////////////////
//                                        //
//     SRRIP [Jaleel et al. ISCA' 10]     //
//     Jinchun Kim, cienlux@tamu.edu      //
//                                        //
////////////////////////////////////////////
//
#include "../inc/champsim_crc2.h"
#include <map>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pair>

#define NUM_CORE 1
#define LLC_SETS NUM_CORE*2048
#define LLC_WAYS 16
#define MAX_RRPV 7
#define MAX_INS_POS 8
#define EPOCH_SIZE 2048 //TODO: Parameter Tuning
#define AGING_PROB 32 //TODO: Parameter Tuning
#define PROMOTION_PROB 64 //TODO: Parameter Tuning
#define SKIP_BYPASS_PROB 10 //TODO: Parameter Tuning
#define DEBUG_ENABLED //Comment this out to remove debugging information

#ifdef DEBUG_ENABLED
#define DEBUG(X) do {std:: cerr << X;} while(0)
#else
#define DEBUG(X)
#endif

typedef uint64_t SIG; //TODO: Appropriately typedef SIG to sufficient size ater getSignature implementation

uint8_t SRRIP_STATUS=1;
uint8_t RAND_AGING=1;
uint8_t RAND_PROMOTION=1;
uint8_t RAND_BYPASS=1;
uint8_t ABANDON_RAND_BYPASS=1;

//Seeds for Random Number Generators
uint32_t AGING_SEED;
uint32_t PROMOTION_SEED;
uint32_t SKIP_BYPASS_SEED;

//Counters
uint64_t NUM_FILLS=0;
uint64_t NUM_HITS=0;
uint64_t NUM_BYPASS=0;

//Thresholds
float SRRIP_THRESHOLD = 1/4.0;

uint8_t rrpv[LLC_SETS][LLC_WAYS];
SIG sig[LLC_SETS][LLC_WAYS];

class ACCESS_STATS{
  public:
    uint64_t fills; //Total No. of blocks brought by that Signature
    uint64_t hits; //Total No. of hits obtained by the blocks brought by that Signature
    uint8_t INS_POS;

    ACCESS_STATS(){
      fills=0;
      hits=0;
      INS_POS = MAX_RRPV-1; //Defaulted to distant SRRIP insertion position
    };
};

//Access Trend Table
map<SIG, ACCESS_STATS*> ATD;

/*
* VARIOUS AUXIALLIARY FUNCTIONS NECESSARY
*/

map<int, pair<int,int> > hitFillStats;
void printAccessStats(){
  int fills=0, hits=0;
  for(map<SIG, ACCESS_STATS*>::iterator it = ATD.begin(); it!= ATD.end();it++){
    cout<<"SIG: "<< it->first <<" hits: "<< it->second->hits<<" fills: "<<it->second->fills<<" hits/fills: "<<(int)round((it->second->hits+1)/(it->second->fills+1))<<endl;
    fills+=it->second->fills;
    hits+=it->second->hits;
    hitFillStats[(int)round((it->second->hits+1)/(it->second->fills+1))]+=1;
  }
  cout<<"FILLS: "<<fills<<" HITS: "<<hits<<endl;
  cout<<"HITS/FILLS STATS: MAP_SIZE: "<<hitFillStats.size()<<endl;
  for(map<int, int>::iterator it=hitFillStats.begin();it!=hitFillStats.end();it++){
    cout<<it->first<<" "<<it->second<<endl;
  }
  cout<<"END HITS/FILLS STATS. CLEARING MAPS..."<<endl;
  hitFillStats.clear();
}

void removeDeadSignatures(){
  //Removing the dead SIGNATURES for next EPOCH
  DEBUG("SIZE OF ATD WITH DEAD SIGS: "<<ATD.size()<<endl);
  map<SIG, ACCESS_STATS*>::iterator it = ATD.begin();
  while(it!= ATD.end()){
    if(it->second->fills==0 && it->second->hits==0){
      //TODO: Figure out why enabling this crashes code in printAccessStats
      //For now disabling dead signature removal
      it = ATD.erase(it);
    }
    else{
        it++;
    }
  }
  DEBUG("SIZE OF ATD WITHOUT DEAD SIGS: "<<ATD.size()<<endl);
}

void epochReset(){

  //Resetting Fills for next EPOCH
  NUM_FILLS=0;
  NUM_HITS=0;

  //Resetting ACCESS_STATS for the next EPOCH
  for(map<SIG, ACCESS_STATS*>::iterator it = ATD.begin();it!=ATD.end();it++){
    it->second->fills=0;
    it->second->hits=0;
  }

}

void setPolicyForNextEpoch(){
  if(NUM_HITS < SRRIP_THRESHOLD*NUM_HITS){
    SRRIP_STATUS=1;
  }
  else{
    SRRIP_STATUS=0;
  }
}

void calculateInsPositions(){
  int hits, fills;
  for(map<SIG, ACCESS_STATS*>::iterator it = ATD.begin(); it!= ATD.end();it++){
    hits = it->second->hits;
    fills = it->second->fills;
    if(hits==0 && fills!=0){
      //RAND_BYPASS for all blocks with no hits
      it->second->INS_POS = MAX_INS_POS;
    }

  }
}

void updateEpochState(){
  //Called on every EPOCH
  //TODO: Remember to smooth FILLS and HITS for various STATS
  //TODO: Understand the patterns through various stats stored in blah.txt and blah_err.txt to write this function
  DEBUG("END OF AN EPOCH. CRUCHING STATS..."<<endl);
  //Removing Dead Signatures
  removeDeadSignatures();
  printAccessStats();
  //TODO: Code to detect if we should go with SRRIP or POSITIONED-SRRIP for next EPOCH
  setPolicyForNextEpoch();
  SRRIP_STATUS=1;
  if(SRRIP_STATUS==0){
    calculateInsPositions();
  }
  static int temp = 0;
  temp++;
  if(temp == 16)exit(0);
  epochReset();
}

void stepHitPromotion(uint32_t set, uint32_t way){
  //Consider applying the PROMOTION and AGING POLICIES on FILL Boundaries
  // or Consider the other possibilites here

  //ABANDON RAND_BYPASS POLICY
  //TODO: Determine what to follow ABANDON RAND_BYPASS policy with very less SKIP_BYPASS_PROB or
  //ABANDON ABANDON_RAND_BYPASS and just proceed with some greater SKIP_BYPASS_PROB for that EPOCH
  if(ABANDON_RAND_BYPASS==1 && ATD[sig[set][way]]->INS_POS == MAX_INS_POS){
    ATD[sig[set][way]]->INS_POS = MAX_RRPV-1; //TODO: Parameter Tuning Required. MAX_RRPV?
  }

  // STEP HIT PROMOTION POLICY
  //TODO: Think about multiple HIT PROMOTION POLICIES
  if(RAND_PROMOTION && rand_r(&PROMOTION_SEED)%PROMOTION_PROB==1){
    if(rrpv[set][way]>0){
      rrpv[set][way]--;
    }
  }

  //STEP HIT AGING POLICY
  if(RAND_AGING && rand_r(&AGING_SEED)%AGING_PROB==1){
    for(int i=0;i<LLC_WAYS;i++){
      if(rrpv[set][i] == rrpv[set][way]-1){
        rrpv[set][i]++;
        assert(rrpv[set][i]<MAX_INS_POS);
        break;
      }
    }
  }
}

void positionedInsertion(SIG sig, uint32_t set, uint32_t way){
    // POSITIONED INSERTION POLICY
    // On each fill we insert based on the INS_POS calculated from the previous EPOCH for this sig
    assert(ATD[sig]->INS_POS < MAX_INS_POS);
    rrpv[set][way] = ATD[sig]->INS_POS;
}

SIG getSignature(uint64_t PC){
  // TODO: Implement Better Signature Scheme.
  return PC;
}

void updateAccessStats(uint32_t set, uint32_t way, uint8_t hit){
    // Called on each Cache Hit, Fill
    if(hit){
      //Check required when clearing the dead signatures on EPOCH BOUNDARY
      if(ATD[sig[set][way]]==NULL){
          ATD[sig[set][way]] = new ACCESS_STATS;
      }
      ATD[sig[set][way]]->hits++;
    }
    else{
      ATD[sig[set][way]]->fills++;
    }
}

// initialize replacement state
void InitReplacementState()
{
    cout << "Initialize SRRIP state" << endl;
    //initializing the seed for RANDOM NUMBER GENERATORS
    AGING_SEED = time(NULL);
    //Helping Arch for parallelization :xD :xD
    PROMOTION_SEED = AGING_SEED+1;
    SKIP_BYPASS_SEED = AGING_SEED+2;

    for (int i=0; i<LLC_SETS; i++) {
        for (int j=0; j<LLC_WAYS; j++) {
            rrpv[i][j] = MAX_RRPV;
        }
    }
}

// find replacement victim
// return value should be 0 ~ 15 or 16 (bypass)
uint32_t GetVictimInSet (uint32_t cpu, uint32_t set, const BLOCK *current_set, uint64_t PC, uint64_t paddr, uint32_t type)
{

    //Cache Bypassing
    if(SRRIP_STATUS==0 && RAND_BYPASS==1 && rand_r(&SKIP_BYPASS_SEED)%SKIP_BYPASS_PROB!=1 && ATD[getSignature(PC)]!=NULL && ATD[getSignature(PC)]->INS_POS == MAX_INS_POS){
      DEBUG("BYPASSING CACHE FOR SIG: " << getSignature(PC) << endl);
      return LLC_WAYS;
    }
    // look for the MAX_RRPV line
    while (1)
    {
        for (int i=0; i<LLC_WAYS; i++)
            if (rrpv[set][i] == MAX_RRPV)
                return i;

        for (int i=0; i<LLC_WAYS; i++)
            rrpv[set][i]++;
    }

    // WE SHOULD NOT REACH HERE
    assert(0);
    return 0;
}

// called on every cache hit and cache fill
void UpdateReplacementState (uint32_t cpu, uint32_t set, uint32_t way, uint64_t paddr, uint64_t PC, uint64_t victim_addr, uint32_t type, uint8_t hit)
{
    DEBUG("PC: "<<PC<<" CACHE HIT STATUS: "<<(int)hit<<endl);
    if (hit){
      NUM_HITS++;
      if(SRRIP_STATUS){
        rrpv[set][way] = 0;
      }
      else{
        stepHitPromotion(set, way);
      }
    }
    else{
      NUM_FILLS++;
      if(ATD[getSignature(PC)] == NULL){
        ATD[getSignature(PC)] = new ACCESS_STATS;
      }
      sig[set][way] = getSignature(PC);
      if(SRRIP_STATUS){
        rrpv[set][way] = MAX_RRPV-1;
      }
      else{
        positionedInsertion(getSignature(PC), set, way);
      }
    }
    updateAccessStats(set, way, hit);
    DEBUG("NUM_FILLS: "<<NUM_FILLS<<" NUM_HITS: "<<NUM_HITS<<endl);
    if(NUM_FILLS == EPOCH_SIZE){
      updateEpochState();
    }
}

// use this function to print out your own stats on every heartbeat
void PrintStats_Heartbeat()
{

}

// use this function to print out your own stats at the end of simulation
void PrintStats()
{

}
