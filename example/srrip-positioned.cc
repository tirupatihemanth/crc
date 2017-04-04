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

#define NUM_CORE 1
#define LLC_SETS NUM_CORE*2048
#define LLC_WAYS 16
#define MAX_RRPV 7
#define MAX_INS_POS 8
#define EPOCH_SIZE 1024 //TODO: Parameter Tuning
#define AGING_PROB 256 //TODO: Parameter Tuning
#define PROMOTION_PROB 256 //TODO: Parameter Tuning
#define DEBUG_ENABLED

#ifdef DEBUG_ENABLED
#define DEBUG(X) do {std:: cerr << X;} while(0)
#else
#define DEBUG(X)
#endif

typedef uint64_t SIG; //TODO: Appropriately typedef SIG to sufficient size ater getSignature implementation

uint8_t SRRIP_STATUS=1;
uint8_t RAND_AGING=1;
uint8_t RAND_PROMOTION=1;

uint32_t AGING_SEED;
uint32_t PROMOTION_SEED;
uint64_t NUM_FILLS=0;
uint64_t NUM_HITS=0;

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

void printAccessStats(){
  int temp=0, temp1=0;
  for(map<SIG, ACCESS_STATS*>::iterator it = ATD.begin(); it!= ATD.end();it++){
    cout<<"SIG: "<< it->first <<" hits: "<< it->second->hits<<" fills: "<<it->second->fills<<endl;
    temp+=it->second->fills;
    temp1+=it->second->hits;
  }
  cout<<temp<<" "<<temp1<<endl;
}

void epochReset(){
  //Changing from SRRIP to POSITIONED SRRIP
  if(SRRIP_STATUS)  SRRIP_STATUS=0;

  //Resetting Fills for next EPOCH
  NUM_FILLS=0;
  NUM_HITS=0;
  //Resetting ACCESS_STATS and removing the dead SIGNATURES for next EPOCH
  DEBUG("SIZE OF ATD WITH DEAD SIGS: "<<ATD.size()<<endl);
  map<SIG, ACCESS_STATS*>::iterator it = ATD.begin();
  while(it!= ATD.end()){
    if(it->second->fills==0 && it->second->hits==0){
      //Programming crashing if uncommented
      //For now disabling dead signature removal
      //it = ATD.erase(it);
      //continue;
    }
    else{
      it->second->fills=0;
      it->second->hits=0;
    }
    it++;
  }
  DEBUG("SIZE OF ATD WITHOUT DEAD SIGS: "<<ATD.size()<<endl);
}

void updateEpochState(){
  //Called on every EPOCH
  //TODO: Remember to smooth FILLS and HITS for various STATS
  DEBUG("END OF AN EPOCH. CRUCHING STATS"<<endl);
  printAccessStats();
  static int temp = 0;
  temp++;
  if(temp == 16)exit(0);
  epochReset();
  SRRIP_STATUS=1;
}

void stepHitPromotion(uint32_t set, uint32_t way){
  // STEP HIT PROMOTION POLICY

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
      ATD[sig[set][way]]->hits++;
      //Particularly useful when clearing the dead signatures on EPOCH BOUNDARY
      // if(ATD[sig[set][way]]!=NULL){
      //     ATD[sig[set][way]] = new ACCESS_STATS;
      //     ATD[sig[set][way]]->hits++;
      // }
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
    PROMOTION_SEED = AGING_SEED+1;
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
    if(ATD[getSignature(PC)]!=NULL && ATD[getSignature(PC)]->INS_POS == MAX_INS_POS){
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
    if(NUM_FILLS == EPOCH_SIZE){
      updateEpochState();
    }
    DEBUG("NUM_FILLS: "<<NUM_FILLS<<" NUM_HITS: "<<NUM_HITS<<endl);
}

// use this function to print out your own stats on every heartbeat
void PrintStats_Heartbeat()
{

}

// use this function to print out your own stats at the end of simulation
void PrintStats()
{

}
