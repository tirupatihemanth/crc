#!/bin/bash

#DEFAULT_DIRS
PIN_ROOT="/home/hemanth/btp/code1/crc/pin-3.0-76991-gcc-linux"
TRACER_ROOT="/home/hemanth/btp/code1/crc/ChampSim_CRC2/trace/obj-intel64"
BENCHMARKS_ROOT="/home/hemanth/btp/benchmarks/SPEC2006/SPEC2006_X86"
TRACE_ROOT="/home/hemanth/btp/code1/crc/ChampSim_CRC2/trace"
CHAMPSIM_ROOT="/home/hemanth/btp/code1/crc/ChampSim_CRC2"

cd $BENCHMARKS_ROOT/binaries
$PIN_ROOT/pin -t $TRACER_ROOT/champsim_tracer.so -o $TRACE_ROOT/$1.trace -s 100000 -t 100000000 -- $BENCHMARKS_ROOT/binaries/$1 $2
cd $CHAMPSIM_ROOT
gzip $TRACE_ROOT/$1.trace
mv $TRACE_ROOT/$1.trace.gz $TRACE_ROOT/$1_100M.trace.gz
