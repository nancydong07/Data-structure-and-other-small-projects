from cs50 import get_string
from sys import argv, exit
import csv

if len(argv) != 3:
    print("wrong")
    exit(0)

f1 = open(argv[1], "r")
f2 = open(argv[2], "r")

txtRead = f2.read()

#with open(argv[1], "r") as csvfile:
reader = csv.DictReader(f1,delimiter=",")

data = list(reader)

for d in data:
    for i,u in d.items():
        if (i != "name"):
            d[i] = int(d[i])

#print(data)
"""
for row in reader:
    for k,v in row.items():
        if(k != "name"):
            row[k] = int(v)
    print(row)
"""
code = set()

for row in data:
    for key, val in row.items():
        code.add(key)
code.discard('name')


max2 = 0
next = 0
myDict = {key: [0] for key in code}


for c in code:
    for i in range(len(txtRead)):
        if(len(txtRead[i:len(c)+i]) != len(c)):
            break
        if(txtRead[i:len(c)+i] == c):
            myDict[c][next]+=1
            i+=len(c)
            if(txtRead[i:len(c)+i] != c):
                myDict[c].append(0)
                next+=1
    next = 0
for c in code:
    myDict[c] = max(myDict[c])

check = True
for i in data:
    for k,v in i.items():
        if(k != "name"):
            if(not v in myDict.values()):
                check = False
                break
    if(check):
        print(i['name'])
    check = True
                

