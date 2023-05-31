# TODO 
from cs50 import get_string, get_int

while True:
    x = get_string("Card Number: ")
    y = x
    if len(x) == 16 or 13 or 15:
        
        #VALIDATION ALGORITHM
        first = []
        second = []
        while int(x) > 0:
            lastdigit = int(x) % 10 #gets last digit
            x = int(x)//10 # divides card number by 10
            seconddigit = int(x) % 10 #gets last digit again
            x = x//10 # divides card by 10
            first.append(lastdigit)
            second.append(seconddigit)
        second = [i * 2 for i in second]
        for k in range(len(second)):
            l = second[k]
            if l >= 10: 
                lastdigit = l % 10
                seconddigit = l // 10
                l = lastdigit + seconddigit
                second[k] = l
        l = sum(second)+sum(first)
        if l%10 == 0:
            if len(y) == 16:
                if int(y[:2]) in [51,52,53,54,55]:
                    print("MASTERCARD")
                elif int(y[:1]) == 4:
                    print("VISA")
                break
            elif len(y) == 15:
                if int(y[:2]) in [34,37]:
                    print("AMEX")
                break
            elif len(y) == 13:
                if int(y[:1]) == 4:
                    print("VISA")
                break
        else:
            print("INVALID")
            break
            #VALIDATION ALGORITHM ENDS


       