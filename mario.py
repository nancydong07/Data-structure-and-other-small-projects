from cs50 import get_int


height = get_int("Enter height: ")

while (height < 1 or height > 8):
    height = get_int("Enter again: ")

for i in range(1, height+1):
    j = height - i
    while j > 0:
        print(" ", end = "")
        j -= 1
    for t in range(i):
        print("#" , end = "")
    print("  ", end = "")
    print("#" * i)
    
        
