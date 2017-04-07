import os

filenum=1;
for EPOCH_SIZE in [1024, 2048, 4096]:
	for SRRIP_THRESHOLD in [0.125, 0.5, 1]:
		for SKIP_BYPASS_PROB in [4, 8, 16, 32]:
			for AGING_PROB in [16, 32, 64, 128, 256, 512]:
				for PROMOTION_PROB in [16, 32, 64, 128, 256, 512]:
					for RAND_PROMOTION in [0,1,2]:
						for RAND_AGING in [0,1,2]:
							for ABANDON_RAND_AGING in [0, 1]:
								fo = open("../input/gridSearchInFile"+str(filenum)+".txt", "w");
								fo.write(str(EPOCH_SIZE)+"\n"+str(SRRIP_THRESHOLD)+"\n"+str(SKIP_BYPASS_PROB)+"\n"+str(AGING_PROB)+"\n"+str(PROMOTION_PROB)+"\n"+str(RAND_PROMOTION)+"\n"+str(RAND_AGING)+"\n"+str(ABANDON_RAND_AGING)+"\n");
								fo.close();
								filenum = filenum+1;
fo = open("../input/fileStats.txt", "w");
fo.write(str(filenum-1));
fo.close();
