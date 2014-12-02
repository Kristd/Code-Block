#!/bin/sh
#encoding: utf-8

import re
import os


inputPath = "f:\\contact.txt"
outputPath = "f:\\data.txt"


def createOutputFile(outputPath):
	if os.path.exists(outputPath):
		os.remove(outputPath)
		
	return open(outputPath, "w+")


def openInputFile(inputPath):
	if os.path.exists(inputPath):
		return open(inputPath, "r")
	else:
		return None


def setBranchList():
	return


def setSplcAddr():
	return



def classify(inputObj, outputObj):    
	splclist = "\"splc10\": ["          #"splc10": ["107", "405"],
	splcaddr = "{\"splc10\": "        #{"splc10": "107", "addr": ["kristd@live.cn", "kristd@live.cn"]}, 

	m = re.compile("([0-9]{3}){1}")
	line = inputObj.readline()
	
	while line:
		addrList = []
		while not m.match(line.strip()):
			line = inputObj.readline()

		addrList.append(line.strip())
		line = inputObj.readline()
		
		while not m.match(line.strip()):
			if len(line.strip()):
				addrList.append(line)
			line = inputObj.readline()
		
		for i in range(len(addrList)):
			if line != None:    #still have next line
				if i == 0:
					tmp = line.split('\t')
					splc = tmp[0].strip()
					addr = tmp[1].strip()

					splclist += "\"" + splc + "\","         #deal with splc list
					
					if len(addrList) > 1 or len(addr.strip()) != 0:
						splcaddr += "\"" + splc + "\", \"addr\":[" + "\"" + addr + "\","
				else:
					if len(addr.strip()) != 0:
						splcaddr += "\"" + addr + "\","
				#end if
			else:               #it is eof already
				if i == 0:
					tmp = line.split('\t')
					splc = tmp[0].strip()
					addr = tmp[1].strip()

					splclist += "\"" + splc + "\"]"         #deal with splc list
					
					if len(addrList) > 1 or len(addr.strip()) != 0:
						splcaddr += "\"" + splc + "\", \"addr\":[" + "\"" + addr + "\"]"
				else:
					if len(addr.strip()) != 0:
						splcaddr += "\"" + addr + "\"]"
				#end if
			#end if
		#end for
		outputObj.writelines(splcaddr + "\n")
	#end while
	outputObj.writelines(splclist)


if __name__ == '__main__':
	src =  openInputFile(inputPath)
	data = createOutputFile(outputPath)
	
	if data != None and src != None:
		classify(src, data)
