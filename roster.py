from cs50 import SQL
from sys import argv, exit
import csv

db = SQL("sqlite:///students.db")

if len(argv) != 2:
    print("wrong")
    exit(0)

data = db.execute("SELECT first, middle, last, birth FROM students WHERE house =? ORDER BY last, first", argv[1])

counter = 0
ll = []
for rows in data:
    for i,u in rows.items():
        ll.append(rows[i])
        counter = counter + 1
        if (rows[i] == rows["birth"]):
            if (rows["middle"] == None):
                print(ll[0], ll[2], end = "")
                print(", born", ll[3])
            else:
                print(ll[0], ll[1], ll[2], end = "")
                print(", born", ll[3])
            ll = []
