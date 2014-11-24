#!/bin/sh
#encoding: utf-8

import re
import os

def test():
    m = re.compile("([0-9]{3}){1}")
    src = open("contact.txt", "r")

    if os.path.exists("data.txt"):
        os.remove("data.txt")
        
    data = open("data.txt", "w+")
    splclist = "\"splc10\": ["
    splcaddr = ""

    line = src.readline()
#"splc10": ["107"],
#{"splc10": "107", "addr": ["kristd@live.cn", "kristd@live.cn"]}, 
    while line:
        line.strip()
        
        if m.match(line):
            tmparry = line.split('\t')
            splc = tmparry[0].strip()
            addr = tmparry[1].strip()
            line = src.readline()

            if len(addr) != 0:
                continue

            if not m.match(line.strip()) && len(line.strip()) != 0:
                splcaddr = "{\"splc10\": \"" + splc + "\", \"addr\": [\"" + addr + "\","
            else:
                splcaddr = "{\"splc10\": \"" + splc + "\", \"addr\": [\"" + addr + "\"]"
                data.write(splcaddr)
                splcaddr = ""
            
            if line:
                splclist += "\"" + splc + "\", "
            else:
                splclist += "\"" + splc + "\"]"

        else:
            line.strip()
            print "not match:", line.strip()
            line = src.readline()

    data.write(splclist)

    if src:
        src.close()

    if data:
        data.close()


if __name__ == '__main__':
    test()
