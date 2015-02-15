#!/usr/bin/env python

import re


def init_branch_list():
    infile = open('f:\\messages.txt', 'r')
    branch_list = []

    for line in infile:
        flag = True
        mat = re.search('\[splc10\]: \d{3}(\(1\))*', line)
        if mat:
            branch = mat.group().split(':')[1].strip()
            if len(branch) != 0:
                for elem in branch_list:
                    if elem.find(branch) != -1:
                        flag = False
                        break

                if flag:
                    branch_list.append(branch)

    infile.close()
    return branch_list


if __name__ == '__main__':
    branches = init_branch_list()
    print(len(branches))
