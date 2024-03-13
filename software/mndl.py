iteratorLimit = 15
largestNumber = 0

def largestNumberCheck(input):
    global largestNumber
    if (input > largestNumber):
        largestNumber = input
    return None

def mandel(cx,cy):
    returnValue = 0
    # Ideally, 3.5 for true -2 to 2 range
    cx = cx
    cy = cy
    zx = cx
    zy = cy

    for iterator in range(iteratorLimit):
        tmp = zx
        # zx = zx*zx - zy*zy + cx
        zx = zx*zx
        zySquare = zy*zy
        zx = zx-zySquare
        zx = zx + cx
        # zy = 2*tmp*zy + cy
        tmp = tmp+tmp # 2*tmp
        zy = tmp*zy
        zy = zy + cy
        if ((zx*zx + zy*zy) > 4):
            # Outside Set
            returnValue = 1
            break
    return returnValue

# Range doesn't include stop number!
# range of -4 to 3 to map onto Byte
for y in range(-4,4):
    for x in range(-4,4):
        res = mandel(x,y)
        if (res):
            print('#', end='')
        else:
            print(".", end='')
    print()