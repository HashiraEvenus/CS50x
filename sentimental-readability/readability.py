# TODO
from cs50 import get_string

text = get_string("Text: ")
letters = 0
words = 0
sentences = 0
#AVG  LETTERS/100 WORDS

#AVG SENTENCES/100 WORDS


for k in text:
    #LETTERS COUNT
    if k.isalpha():
        letters+=1
     #SENTENCES COUNT
    elif k == "!" or k=="?" or k==".":
        sentences += 1
    # WORDS COUNT
    if k == " ":
        
        words += 1
    if letters >= 1 and words == 0:
        words = 1  
   
        

L = (letters/words)*100
S = (sentences*100/words)
result = 0.0588 * L - 0.296 * S - 15.8

if result < 1:
    print("Before Grade 1")
elif result > 16:
    print("Grade 16+") 
elif result > 1:
    print("Grade ",round(result))


#print(result)