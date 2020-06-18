from cs50 import get_string

card = get_string("enter: ")

if (len(card) % 2 == 0):
    i = 0;
else: i = 1;

first = 0;
sumfirst = 0;
while(i < len(card)):
    first = 2*int(card[i])
    first = str(first)
    i+=2
    if (len(first)>1):
        sumfirst += int(first[0]) + int(first[1])
    else:
        sumfirst += int(first)

if (len(card) % 2 == 0):
    i = 1;
else: i = 0;

while(i < len(card)):
    sumfirst += int(card[i])
    i += 2
if (sumfirst % 10 != 0):
    print("INVALID")
    exit(0)


if (card[0] == "4"): 
    print("VISA")
elif (card[0] == "3" and (card[1] == "7" or card[1] == "4") and len(card) == 15):
    print("AMEX")
else: 
    print("MASTERCARD")
