#!/bin/sh
#encoding: utf-8

import re

def test():
    m = re.compile(r'([0-9]{3}){1}')
    for line in open("contact.txt"):
        line.strip()
        
        if m.match(line):
            str1 = line.split('\t')
            print "branch:", str1[0], ", email:", str1[1]
        else:
            line.strip()
            print "not match:", line.strip()

if __name__=='__main__':
    test()
