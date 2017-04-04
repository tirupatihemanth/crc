////////////////////////////////////////////
//                                        //
//        DO NOT CHANGE THIS FILE         //
//                                        //
//      ChampSim interface for CRC-2      //
//     Jinchun Kim, cienlux@tamu.edu      //
//                                        //
////////////////////////////////////////////

#ifndef CHAMPSIM_CRC2_H
#define CHAMPSIM_CRC2_H

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <iostream>
#include <string>

// CACHE ACCESS TYPE
#define LOAD      0
#define RFO       1
#define PREFETCH  2
#define WRITEBACK 3
#define NUM_TYPES 4

using namespace std;

class BLOCK {
  public:
    bool valid,
         dirty;
    uint64_t address,
             full_addr,
             tag,
             data,
             cpu;

    // DO NOT USE THIS LRU VARIABLE
    uint32_t lru;

    BLOCK() {
        valid = false;
        dirty = false;

        address = 0;
        full_addr = 0;
        tag = 0;
        data = 0;
        cpu = 0;

        lru = 0;
    };
};

void InitReplacementState(),
     UpdateReplacementState(uint32_t cpu, uint32_t set, uint32_t way, uint64_t paddr, uint64_t PC, uint64_t victim_addr, uint32_t type, uint8_t hit),
     PrintStats_Heartbeat(),
     PrintStats();

uint32_t GetVictimInSet(uint32_t cpu, uint32_t set, const BLOCK *current_set, uint64_t PC, uint64_t paddr, uint32_t type);
uint64_t get_cycle_count(),
         get_instr_count(uint32_t cpu),
         get_config_number();

#endif
