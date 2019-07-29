#!/usr/bin/python
# -*- coding: UTF-8 -*-

import MySQLdb
import base64
import json
import time
from datetime import datetime

def execSql(sql):
    db = MySQLdb.connect(host="183.36.122.55", port=6302, user="yymusic", passwd="123qwe", db="tlovedata", charset='utf8')
    cursor = db.cursor();
    cursor.execute(sql)
    db.commit()
    db.close()

#时间转换为 23:59:59
for i in range (1, 31):
	tbl = "entpay_daybill_201903{:0>2d}"
	tbl = tbl.format(i)
	print tbl

# file_object = open('.txt','r')
# sql = "insert IGNORE into tlove_budaka (uid, anchor_id, num, last_issue_time) values "
# num = 0
# for line in file_object:
# 	line=line.strip()
# 	line2=line.split('\t')
# 	#print line2
# 	if line2[0] == 'uid':
# 		continue
# 	if num != 0:
# 		sql += ","
# 	sql += '(' + line2[0] + ',' + line2[1] + ',' + line2[2] + ', \'2019-02-21 00:00:00\')'
# 	num = num + 1
# 	if num == 1000:
# 		sql += ";"
# 		#print sql
# 		execSql(sql)
# 		sql = "insert IGNORE into tlove_budaka (uid, anchor_id, num, last_issue_time) values "
# 		num = 0

# print num
# if num > 0 :
# 	sql += ";"
# 	#print sql
# 	execSql(sql)
