import os
#INPUT_PATH="/home/hemanth/btp/code2/crc/ChampSim_CRC2/input/";
#BIN_PATH="/home/hemanth/btp/code2/crc/ChampSim_CRC2/bin/";
#TRACE_PATH="/home/hemanth/btp/code2/crc/ChampSim_CRC2/trace/";
OUTPUT_PATH="/home/hemanth/btp/code2/crc/ChampSim_CRC2/output/";
ERR_PATH="/home/hemanth/btp/code2/crc/ChampSim_CRC2/err/";

files = os.listdir(OUTPUT_PATH);

benchmarks = ["GemsFDTD", "lbm", "mcf", "omnetpp", "namd", "soplex", "bzip2", "gcc", "leslie3d", "hmmer", "h264ref"]

missDict = {};

for benchmark in benchmarks:
	print "ANALYZING BENCHMARK: "+benchmark;
	for f in files:
		with open(OUTPUT_PATH+benchmark+"/"+f) as fo:
			print "f: "+f;
			content = fo.readlines();
			content = content[len(content)-5].strip();
			content = content.split(" ");
			content = [i for i in content if i != ''];
			missDict[f] = int(content[7]);
	fo = open("perfStats_"+benchmark+".txt", "w");
	sortedList = sorted(missDict.items(), key=lambda (_,x):x)
	for key, value in sortedList:
		fo.write("file: "+key+" misses: "+str(value)+"\n");
	fo.close();
	missDict = {};

