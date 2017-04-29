import os

filenum=1;
for EPOCH_SIZE in [2048, 4096]:
	for SRRIP_THRESHOLD in [0.5]:
		for SKIP_BYPASS_PROB in [16, 32]:
			for AGING_PROB in [32, 64, 128]:
				for PROMOTION_PROB in [1, 16, 32, 64]:
					for RAND_PROMOTION in [0,1,2]:
						for RAND_AGING in [0,1,2,3]:
							for RAND_BYPASS in [0, 1]:
								fo = open("../input/"+str(EPOCH_SIZE)+"/gridSearchInFile"+str(filenum)+".txt", "w");
								fo.write(str(EPOCH_SIZE)+"\n"+str(SRRIP_THRESHOLD)+"\n"+str(SKIP_BYPASS_PROB)+"\n"+str(AGING_PROB)+"\n"+str(PROMOTION_PROB)+"\n"+str(RAND_PROMOTION)+"\n"+str(RAND_AGING)+"\n"+str(RAND_BYPASS)+"\n");
								fo.close();
								filenum = filenum+1;
