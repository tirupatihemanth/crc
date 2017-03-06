#!/bin/bash
g++ -Wall --std=c++11 -o bin/lru-config1 example/lru.cc lib/config1.a
g++ -Wall --std=c++11 -o bin/lru-config2 example/lru.cc lib/config2.a
g++ -Wall --std=c++11 -o bin/lru-config3 example/lru-8MB.cc lib/config3.a
g++ -Wall --std=c++11 -o bin/lru-config4 example/lru-8MB.cc lib/config4.a
#g++ -Wall --std=c++11 -o bin/lru-config5 example/lru-8MB.cc lib/config5.a
#g++ -Wall --std=c++11 -o bin/lru-config6 example/lru-8MB.cc lib/config6.a
