#!//bin/bash
echo "./bin/lru-config1 -traces trace/bzip2_10M.trace.gz > stats/lru-config1-${1-def}.txt"
./bin/lru-config1 -traces trace/bzip2_10M.trace.gz > stats/lru-config1-${1-def}.txt
echo "./bin/lru-config2 -traces trace/bzip2_10M.trace.gz > stats/lru-config2-${1-def}.txt"
./bin/lru-config2 -traces trace/bzip2_10M.trace.gz > stats/lru-config2-${1-def}.txt 
echo "./bin/lru-config3 -traces trace/bzip2_10M.trace.gz trace/libquantum_10M.trace.gz trace/mcf_10M.trace.gz trace/graph_analytics_10M.trace.gz > stats/lru-config3-${1-def}.txt"
./bin/lru-config3 -traces trace/bzip2_10M.trace.gz trace/libquantum_10M.trace.gz trace/mcf_10M.trace.gz trace/graph_analytics_10M.trace.gz > stats/lru-config3-${1-def}.txt
echo "./bin/lru-config4 -traces trace/bzip2_10M.trace.gz trace/libquantum_10M.trace.gz trace/mcf_10M.trace.gz trace/graph_analytics_10M.trace.gz > stats/lru-config4-${1-def}.txt"
./bin/lru-config4 -traces trace/bzip2_10M.trace.gz trace/libquantum_10M.trace.gz trace/mcf_10M.trace.gz trace/graph_analytics_10M.trace.gz > stats/lru-config4-${1-def}.txt
