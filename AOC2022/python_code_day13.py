#import re
#import string

#def helloworld():
#    print("Hello from Python!")

def CompareRightOrder(l,r):
    if (type(l) == int and type(r) == int):
        return l-r # if negative, order is correct
    
    if (type(l) == int and type(r) != int):
        return CompareRightOrder([l],r)
    elif (type(l) != int and type(r) == int):
        return CompareRightOrder(l,[r])

    for (e1,e2) in zip(l,r):
        result = CompareRightOrder(e1,e2)
        if result != 0:
            return result
    return len(l)-len(r)

def GetInput(filename):
    with open(filename) as f:
        lines = f.readlines()
    
    i=0
    inputpairs=[]
    fullinput=[]
    while i<len(lines):
        line1 = eval(lines[i].replace('\n',''))
        line2 = eval(lines[i+1].replace('\n',''))
        i+=3
        inputpairs.append([line1,line2])
        fullinput.append(line1)
        fullinput.append(line2)

    return inputpairs, fullinput

def Solve():
    inputpairs, fullinput = GetInput("day13_input.txt")    

    countsum = 0
    for i, line  in enumerate(inputpairs):
        check = CompareRightOrder(line[0],line[1])
        print('line',i,'result',check)
        if check < 0:
            countsum += i+1
    print(countsum,'\n')

    fullinput.append([[2]])
    fullinput.append([[6]])
    swaptookplace = True
    while swaptookplace:
        swaptookplace = False
        i=0
        while i<len(fullinput)-1:
            check = CompareRightOrder(fullinput[i],fullinput[i+1])
            swap = check > 0
            if swap:
                temp = fullinput[i]
                fullinput[i] = fullinput[i+1]
                fullinput[i+1] = temp
                swaptookplace = True
            i+=1

    for i, elem in enumerate(fullinput):
        if (elem == [[2]]):
            firstindex = i+1
        if (elem == [[6]]):
            secondindex = i+1
        print(elem,i)

    print(firstindex,' x ',secondindex,'=',firstindex*secondindex)
