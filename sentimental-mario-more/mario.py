# TODO
from cs50 import get_int

height = get_int("Height: ")
while height > 8 or height < 1:
    height = get_int("Height: ")
for i in range(height):
        #PRINT HASHES
        print((height-i-1)*" "+(i+1)*"#", end="")
        #PRINT GAPS
        print("  ", end="")
        #PRINT HASHES OF OTHER 
        print((i+1)*"#")