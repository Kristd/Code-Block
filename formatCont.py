#!/bin/sh
# -*- encoding: utf-8 -*-

import re
import os


def openOutputFile(destfile):
    try:
        if os.path.exists(destfile):
            os.remove(destfile)

        return open(destfile, "w+")
    except Exception as err:
        return None


def openInputFile(srcfile):
    try:
        if os.path.exists(srcfile):
            return open(srcfile, "r")
        else:
            return None
    except Exception as err:
        return None


#"splc10": ["107", "405"],
def setBranchList(srcfile, destfile):
    flag = False
    splcList = ""
    splcHead = "\"splc10\":["
    m = re.compile("([0-9]{3}){1}")

    for line in srcfile:
        if m.match(line.strip()):
            tmp = line.split('\t')

            if not flag:
                splcList += "\"" + tmp[0].strip() + "\""
                flag = True
            else:
                splcList += ", \"" + tmp[0].strip() + "\""

    splcHead += splcList + "]"
    destfile.writelines(splcHead)
    print "setBranchList finish."


#{"splc10": "107", "addr": ["kristd@live.cn", "kristd@live.cn"]}, 
def setSplcAddr(srcfile, destfile):
    flag = False
    addrList = ""
    splcHeader = "\"splc10\": \"[splcNo]\", \"addr\":["
    m = re.compile("([0-9]{3}){1}")

    for line in srcfile:
        if len(line.strip()) == 0:
            continue

        if m.match(line.strip()):
            if flag:
                splcHeader += addrList + "]"
                destfile.writelines(splcHeader)
                destfile.writelines("\n")

            flag = True
            addrList = ""
            splcHeader = "\"splc10\": \"[splcNo]\", \"addr\":["
            tmp = line.split('\t')
            splcHeader = splcHeader.replace("[splcNo]", tmp[0].strip())

            if len(tmp[1].strip()) != 0:
                addrList += "\"" + tmp[1].strip() + "\""
        else:
            if addrList != "":
                addrList += ", \"" + line.strip() + "\""
            else:
                addrList += "\"" + line.strip() + "\""

    splcHeader += addrList + "]\n"
    destfile.writelines(splcHeader)
    print "setSplcAddr finish."


#combine the two functions
def formatData(srcfile, destfile):
    flag = False
    addrList = ""
    addrHeader = "{\"splc10\": \"[splcNo]\", \"addr\":["

    splcList = ""
    splcHeader = "\"splc10\":["
    m = re.compile("([0-9]{3}){1}")

    for line in srcfile:
        if len(line.strip()) == 0:
            continue

        if m.match(line.strip()):
            if flag:
                addrHeader += addrList + "]},"
                destfile.writelines(addrHeader)
                destfile.writelines("\n")

            addrList = ""
            addrHeader = "{\"splc10\": \"[splcNo]\", \"addr\":["
            tmp = line.split('\t')
            splc = tmp[0].strip()
            addr = tmp[1].strip()
            addrHeader = addrHeader.replace("[splcNo]", splc)

            if not flag:
                splcList += "\"" + splc + "\""
            else:
                splcList += ", \"" + splc + "\""

            if len(addr) != 0:
                addrList += "\"" + addr + "\""

            flag = True
        else:
            if addrList != "":
                addrList += ", \"" + line.strip() + "\""
            else:
                addrList += "\"" + line.strip() + "\""

    splcHeader += splcList + "]"
    addrHeader += addrList + "]}"
    destfile.writelines(addrHeader)
    destfile.writelines("\n\n")
    destfile.writelines(splcHeader)
    destfile.writelines("\n")


if __name__ == '__main__':
    srcfile = "contact.txt"
    destfile = "output.txt"

    src = openInputFile(srcfile)
    dest = openOutputFile(destfile)

    formatData(src1, dest)
    src.close()
    dest.close()
    print "finish!\n"
