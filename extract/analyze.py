# File Name: Analyze.py
# Author : S R Swamy Saranam

#!/usr/bin/python
import re
import sys
#from numpy import ndarray
import numpy as np
class Analyze:
	file_name=""
	content = []
	#set_replace = ndarray((2048,),int)
	set_replace = np.zeros((2048,),int)
	set_hits = np.zeros((2048,),int)
	set_fills = np.zeros((2048,),int)

	def __init__(self,name):
		Analyze.file_name = name

	# Read File to be analyzed
	def readFile(self):
		inFile = open(Analyze.file_name, "r")
		Analyze.content = inFile.readlines()
		Analyze.content = [x.strip() for x in Analyze.content]
		#print content
		inFile.close()

	def extract(self):
		for i in range(len(Analyze.content)):
			line = Analyze.content[i];
			if line == "" or "Reached" in line or "Warmup" in line :
				continue;
			line = re.split(r'\t+', line)
			#print line
			index = int(line[3]);
			Analyze.set_replace[index] = Analyze.set_replace[index] + 1;
			if int(line[15])==0:
				Analyze.set_fills[index] = Analyze.set_fills[index]+1;
			else:
				Analyze.set_hits[index] = Analyze.set_hits[index]+1;


	def total(self):
		val = 0
		for i in range(len(Analyze.set_replace)):
			val += Analyze.set_replace[i]
		print val
		print len(Analyze.content)

	# Write Output to the File
	def writeFile(self, out_name):
		#out_name = Analyze.file_name + "_out.txt"
		outFile = open(out_name, "w")
		for i in range(len(Analyze.set_replace)):
			outFile.write(str(i))
			outFile.write("\t")
			outFile.write(str(Analyze.set_replace[i]))
			outFile.write("\t")
			outFile.write(str(Analyze.set_hits[i]))
			outFile.write("\t")
			outFile.write(str(Analyze.set_fills[i]))
			outFile.write("\n")
		outFile.close()

file1 = Analyze(sys.argv[1])
file1.readFile()
file1.extract()
file1.writeFile(sys.argv[2])
#file1.total()
