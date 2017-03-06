#!/bin/bash
g++ -Wall --std=c++11 -o bin/srrip-config1 example/srrip.cc lib/config1.a
g++ -Wall --std=c++11 -o bin/srrip-config2 example/srrip.cc lib/config2.a
g++ -Wall --std=c++11 -o bin/srrip-config3 example/srrip-8MB.cc lib/config3.a
g++ -Wall --std=c++11 -o bin/srrip-config4 example/srrip-8MB.cc lib/config4.a
#g++ -Wall --std=c++11 -o bin/srrip-config5 example/srrip-8MB.cc lib/config5.a
#g++ -Wall --std=c++11 -o bin/srrip-config6 example/srrip-8MB.cc lib/config6.a
