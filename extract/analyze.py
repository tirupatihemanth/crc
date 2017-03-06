# File Name: Analyze.py
# Author : S R Swamy Saranam

#!/usr/bin/python
import re
#from numpy import ndarray
import numpy as np
class Analyze:
	file_name=""
	content = []
	#set_replace = ndarray((2048,),int)
	set_replace = np.zeros((2048,),int)
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
			line = re.split(r'\t+',Analyze.content[i])
			#print line[0]
			index = int(line[0]);
			Analyze.set_replace[index] = Analyze.set_replace[index] + 1;

	def total(self):
		val = 0
		for i in range(len(Analyze.set_replace)):
			val += Analyze.set_replace[i]
		print val
		print len(Analyze.content)
	# Write Output to the File
	def writeFile(self):
		out_name = Analyze.file_name + "_out.txt"
		outFile = open(out_name, "w")
		np.sort(Analyze.set_replace)
		for i in range(len(Analyze.set_replace)):
			outFile.write(str(i))
			outFile.write("\t")
			outFile.write(str(Analyze.set_replace[i]))
			outFile.write("\n")
		outFile.close()

file1 = Analyze("bzip2")
file1.readFile()
file1.extract()
file1.writeFile()
#file1.total()
