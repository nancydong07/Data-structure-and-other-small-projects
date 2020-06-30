from cs50 import SQL 
from sys import argv, exit
import csv

if len(argv) != 2:
    print("wrong")
    exit(0)
    
#open(f"students.db", "a").close()

file = open(argv[1], "a")
db = SQL("sqlite:///students.db")

with open(argv[1], "r") as potterChar: 
    reader = csv.DictReader(potterChar)
    for row in reader:
        names = row["name"].split(" ")
        house = row["house"]
        birth = row["birth"]
        if (len(names) == 2):
            db.execute("INSERT INTO students (first, last, house, birth) VALUES(?,?, ?, ?)", names[0], names[1], house, birth)
        else: 
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", names[0], names[1], names[2], house, birth)
        