#!/bin/bash
./bin/$1-config1 -simulation_instructions 10000000 -traces trace/bzip2_10M.trace.gz > output/$1_bzip2_out.txt
./bin/$1-config1 -simulation_instructions 10000000 -traces trace/libquantum_10M.trace.gz > output/$1_libquantum_out.txt
./bin/$1-config1 -simulation_instructions 10000000 -traces trace/gcc_10M.trace.gz > output/$1_gcc_out.txt
./bin/$1-config1 -simulation_instructions 10000000 -traces trace/GemsFDTD_10M.trace.gz > output/$1_GemsFDTD_out.txt
./bin/$1-config1 -simulation_instructions 10000000 -traces trace/lbm_10M.trace.gz > output/$1_lbm_out.txt
./bin/$1-config1 -simulation_instructions 10000000 -traces trace/h264ref_10M.trace.gz > output/$1_h264ref_out.txt
./bin/$1-config1 -simulation_instructions 10000000 -traces trace/leslie3d_10M.trace.gz > output/$1_leslie3d_out.txt
./bin/$1-config1 -simulation_instructions 10000000 -traces trace/omnetpp_10M.trace.gz > output/$1_omnetpp_out.txt
./bin/$1-config1 -simulation_instructions 10000000 -traces trace/soplex_10M.trace.gz > output/$1_soplex_out.txt
./bin/$1-config1 -simulation_instructions 10000000 -traces trace/namd_10M.trace.gz > output/$1_namd_out.txt
#./bin/srrip-config2 -traces trace/bzip2_10M.trace.gz > stats/srrip-config2-${1-def}.txt 
#./bin/srrip-config3 -traces trace/bzip2_10M.trace.gz trace/libquantum_10M.trace.gz trace/mcf_10M.trace.gz trace/graph_analytics_10M.trace.gz > stats/srrip-config3-${1-def}.txt
#./bin/srrip-config4 -traces trace/bzip2_10M.trace.gz trace/libquantum_10M.trace.gz trace/mcf_10M.trace.gz trace/graph_analytics_10M.trace.gz > stats/srrip-config4-${1-def}.txt
