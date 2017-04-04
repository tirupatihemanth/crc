#!/bin/bash
./bin/srrip-config1 -traces trace/bzip2_10M.trace.gz > stats/srrip-config1-${1-def}.txt
#./bin/srrip-config2 -traces trace/bzip2_10M.trace.gz > stats/srrip-config2-${1-def}.txt 
#./bin/srrip-config3 -traces trace/bzip2_10M.trace.gz trace/libquantum_10M.trace.gz trace/mcf_10M.trace.gz trace/graph_analytics_10M.trace.gz > stats/srrip-config3-${1-def}.txt
#./bin/srrip-config4 -traces trace/bzip2_10M.trace.gz trace/libquantum_10M.trace.gz trace/mcf_10M.trace.gz trace/graph_analytics_10M.trace.gz > stats/srrip-config4-${1-def}.txt
