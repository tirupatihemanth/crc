import os
#INPUT_PATH="/home/hemanth/btp/code2/crc/ChampSim_CRC2/input/";
#BIN_PATH="/home/hemanth/btp/code2/crc/ChampSim_CRC2/bin/";
#TRACE_PATH="/home/hemanth/btp/code2/crc/ChampSim_CRC2/trace/";
OUTPUT_PATH="/home/hemanth/btp/code2/crc/ChampSim_CRC2/output/";
ERR_PATH="/home/hemanth/btp/code2/crc/ChampSim_CRC2/err/";

files = os.listdir(OUTPUT_PATH);

missDict = {};
for file in files:
	with open(OUTPUT_PATH+file) as fo:
		content = fo.readlines();
		content = content[len(content)-5].strip();
		content = content.split(" ");
		content = [i for i in content if i != ''];
		missDict[file] = int(content[7])

fo = open("perfStats.txt", "w");
sortedList = sorted(missDict.items(), key=lambda (_,x):x)
for key, value in sortedList:
	fo.write("file: "+file+" misses: "+str(value)+"\n");
fo.close();
