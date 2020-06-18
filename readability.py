from cs50 import get_string
import re

sentence = get_string("enter sentence: ")

numOfLetters = sum(c.isalpha() for c in sentence)
numOfWords = len(sentence.split())
numOfSentences = len(re.split('[.?!]', sentence)) - 1

L = (numOfLetters/numOfWords) * 100
S = (numOfSentences/ numOfWords) * 100 
index =round( 0.0588 * L - 0.296 * S - 15.8)

if(index < 1):
    print("Before Grade 1")
elif(index > 16):
    print("Grade 16+")
else:
    print("Grade ", index)