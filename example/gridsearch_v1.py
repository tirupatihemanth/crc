import os
from subprocess import Popen
INPUT_PATH="/home1/phd/cs14d403/ChampSim_CRC2/input/";
BIN_PATH="/home1/phd/cs14d403/ChampSim_CRC2/bin/";
TRACE_PATH="/home1/phd/cs14d403/ChampSim_CRC2/trace/";
OUTPUT_PATH="/home1/phd/cs14d403/ChampSim_CRC2/output/";
ERR_PATH="/home1/phd/cs14d403/ChampSim_CRC2/err/";
waitObjects=[];
outObjects=[];
errObjects=[];
inObjects=[];


count=0;
def waitForFinish():
	global waitObjects, outObjects, errObjects, inObjects
	for i in range(len(waitObjects)):
		waitObjects[i].wait();
		outObjects[i].close();
		errObjects[i].close();
		inObjects[i].close();
	waitObjects=[];
	outObjects=[];
	errObjects=[];
	inObjects=[];

benchmarks = ["libquantum", "GemsFDTD", "lbm", "mcf", "omnetpp", "namd", "soplex", "bzip2", "gcc", "leslie3d", "h264ref"]
#benchmarks = ["bzip2"]

for benchmark in benchmarks:
	print "CURR RUNNING BENCHMARK: "+benchmark;
	for epoch in ["2048/", "4096/"]:
		files = os.listdir(INPUT_PATH+epoch);
		for file in files:
			count = count+1;
			#print "CUR FILE: "+file+" count: "+str(count);
			inFO = open(INPUT_PATH+epoch+file, "r");
			outFO = open(OUTPUT_PATH+benchmark+"/out_"+file, "w");
			errFO = open(ERR_PATH+benchmark+"/err_"+file, "w");
			wo = Popen([BIN_PATH+"srrip-positioned_v3-config1", "-hide_heartbeat", "-warmup_instructions", "100000000", "-simulation_instructions", "150000000", "-traces", TRACE_PATH+benchmark+"_250M.trace.gz"], stdin=inFO, stdout=outFO, stderr=errFO);
			waitObjects.append(wo);
			outObjects.append(outFO);
			errObjects.append(errFO);
			inObjects.append(inFO);
			if count==16:
				waitForFinish();
				count=0;
		waitForFinish();
		count=0;
#	os.system("mkdir "+OUTPUT_PATH+benchmark);
#	os.system("mv "+OUTPUT_PATH+"*.txt "+OUTPUT_PATH+benchmark); 
#	os.system("mkdir "+ERR_PATH+benchmark);
#	os.system("mv "+ERR_PATH+"*.txt "+OUTPUT_PATH+benchmark); 
