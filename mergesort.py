# !/usr/bin/env python
# -*-encoding:utf-8-*-

def merge_sort(list):
    mid = int(len(list) / 2)
    if len(list) <= 1:
        return list
    return merge(merge_sort(list[:mid]), merge_sort(list[mid:]))


def merge(l1, l2):
    final = []
    l1 = sorted(l1)
    l2 = sorted(l2)
    while l1 and l2:
        if l1[0] <= l2[0]:
            final.append(l1.pop(0))
        else:
            final.append(l2.pop(0))
    return final + l1 + l2


# --------

def merge_sort(lst):
    if len(lst) <= 1:
        return lst
    left = merge_sort(lst[:len(lst) / 2])
    right = merge_sort(lst[len(lst) / 2:len(lst)])
    result = []

    while len(left) > 0 and len(right) > 0:
        if left[0] > right[0]:
            result.append(right.pop(0))
        else:
            result.append(left.pop(0))

    if len(left) > 0:
        result.extend(merge_sort(left))
    else:
        result.extend(merge_sort(right))
    return result


def main():
    L = [22, 11, 55, 33, 66]
    print merge_sort(L)
