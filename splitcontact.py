#!/bin/sh
#encoding: utf-8

import re
import os


inputPath = "f:\\contact.txt"
outputPath = "f:\\data.txt"


def createOutputFile(outputPath):
	try:
		if os.path.exists(outputPath):
			os.remove(outputPath)

		return open(outputPath, "w+")
	except Exception as err:
		return None


def openInputFile(inputPath):
	try:
		if os.path.exists(inputPath):
			return open(inputPath, "r")
		else:
			return None
	except Exception as err:
		return None


#"splc10": ["107", "405"],
def setBranchList(inputPath):
	splcList = ""
	m = re.compile("([0-9]{3}){1}")
	line = inputPath.readline()
	index = 0

	while line:
		if m.match(line.strip()):
			tmp = line.split('\t')
			splc = tmp[0].strip()

			if index == 0:
				splcList += "\"" + splc + "\""
				index += 1
			else:
				splcList += ", \"" + splc + "\""

		line = inputPath.readline()

	return splcList


#{"splc10": "107", "addr": ["kristd@live.cn", "kristd@live.cn"]}, 
def setSplcAddr(inputPath, outputPath):
	splc10 = "\"splc10\": \"[splcNo]\", \"addr\":["
	addrList = ""
	buff = []
	m = re.compile("([0-9]{3}){1}")
	line = inputPath.readline()

	while not m.match(line.strip()):
		line = inputPath.readline()

	while line:
		if m.match(line.strip()):
			buff.append(line)
			line = inputPath.readline()

			while not m.match(line.strip()):
				buff.append(line)

			for i in range(len(buff)):
				if i == 0:
					tmp = line.split('\t')
					splc = tmp[0].strip()
					addr = tmp[1].strip()

					splc10.replace("[splcNo]", splc)

					if addr != "":
						addrList += "\"" + addr + "\""
				else:
					if addr == "":
						continue
					else:
						if addrList != "":
							addrList += ", \"" + addr + "\""
						else:
							addrList += "\"" + addr + "\""

			splc10 += addrList + "]\n"
			outputPath.writelines(splc10)
		else:
			line = inputPath.readline()


if __name__ == '__main__':
	splcListHead = "\"splc10\":["
	src =  openInputFile(inputPath)
	data = createOutputFile(outputPath)
	
	if src != None:
		splcList = setBranchList(src)

	if data != None:
		splcListHead += splcList + "]"
		data.writelines(splcListHead)
		data.writelines("\n\n")
		setSplcAddr(src, data)

