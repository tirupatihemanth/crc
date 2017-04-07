import os
from subprocess import Popen

inObject = open("in.txt", "r");
outObject = open("out1.txt", "w");
wo = [];
waiting = Popen(["./a.out"], stdin=inObject, stdout=outObject, stderr=outObject);
wo.append(waiting);
waiting = Popen(["./a.out"], stdin=inObject, stdout=outObject, stderr=outObject);
wo.append(waiting);
print len(wo);
if wo[0]!=wo[1]:
	print "I am screwed";
wo[0].wait();
wo[1].wait();

