#!/bin/sh
# -*- encoding: utf-8 -*-

import re
import os


def open_outfile(destfile):
    if os.path.exists(destfile):
        os.remove(destfile)

    return open(destfile, "w+")


def open_infile(srcfile):
    if os.path.exists(srcfile):
        return open(srcfile, "r")
    else:
        return None


# "splc10": ["107", "405"],
def set_branch_list(srcfile, destfile):
    first_line = True
    branch_list = ""
    branch_header = '"splc10":['
    m = re.compile("([0-9]{3})")

    for line in srcfile:
        if m.match(line.strip()):
            tmp = line.split(":")

            if first_line:
                branch_list += "\"" + tmp[0].strip() + "\""
                first_line = False
            else:
                branch_list += ", \"" + tmp[0].strip() + "\""

    branch_header += branch_list + "]"
    destfile.writelines(branch_header)
    print "set_branch_list() finish."


# {"splc10": "107", "addr": ["kristd@live.cn", "kristd@live.cn"]},
def set_branch_address(srcfile, destfile):
    first_line = True
    address_list = ""
    branch_header = '"splc10": "[splcNo]", "addr":['
    m = re.compile("([0-9]{3})")

    for line in srcfile:
        if len(line.strip()) == 0:
            continue

        if m.match(line.strip()):
            if not first_line:
                branch_header += address_list + "]"
                destfile.writelines(branch_header)
                destfile.writelines("\n")

            first_line = True
            address_list = ""
            branch_header = '"splc10": "[splcNo]", "addr":['
            tmp = line.split(":")
            branch_header = branch_header.replace("[splcNo]", tmp[0].strip())

            if len(tmp[1].strip()) != 0:
                address_list += "\"" + tmp[1].strip() + "\""
        else:
            if address_list != "":
                address_list += ", \"" + line.strip() + "\""
            else:
                address_list += "\"" + line.strip() + "\""

    branch_header += address_list + "]\n"
    destfile.writelines(branch_header)
    print "set_branch_address() finish."


# combine the two functions
def format_data(srcfile, destfile):
    first_line = True
    address_list = ""
    address_header = ""

    branch_list = ""
    branch_header = '"splc10":['
    m = re.compile("([0-9]{3})")

    for line in srcfile:
        if len(line.strip()) == 0:
            continue

        if m.match(line.strip()):
            if not first_line:
                address_header += address_list + "]},"
                destfile.writelines(address_header)
                destfile.writelines("\n")

            address_list = ""
            address_header = '{"splc10": "[splcNo]", "addr":['
            tmp = line.split(":")
            branch = tmp[0].strip()
            address = tmp[1].strip()
            address_header = address_header.replace("[splcNo]", branch)

            if first_line:
                branch_list += '"' + branch + '"'
            else:
                branch_list += ', "' + branch + '"'

            if len(address) != 0:
                address_list += '"' + address + '"'

            first_line = False
        else:
            if address_list != "":
                address_list += ', "' + line.strip() + '"'
            else:
                address_list += '"' + line.strip() + '"'

    branch_header += branch_list + "]"
    address_header += address_list + "]}"
    destfile.writelines(address_header)
    destfile.writelines("\n\n")
    destfile.writelines(branch_header)
    destfile.writelines("\n")


if __name__ == '__main__':
    srcfile = "f:\\contact3.txt"
    destfile = "f:\\output.txt"

    src = open_infile(srcfile)
    dest = open_outfile(destfile)

    format_data(src, dest)
    src.close()
    dest.close()
    print "finish!\n"
