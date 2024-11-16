import random

a=[random.randint(0,9),
   random.randint(0,9),
   random.randint(0,9),
   random.randint(0,9)]
#print(str(a[0])+str(a[1])+str(a[2])+str(a[3]))

while True:
    isok=False
    while isok == False:
        b=input("Imput a Number ")
        if len(b)!=4:
            print("Imput a 4 digit number")
        else:
            kazuok=True
            for i in range(4):
                if (b[i]<"0")or(b[i]>"9"):
                    print("Not a number")
                    kazuok=False
                    break
                if kazuok:
                    isok=True

    hit=0
    for i in range(4):
        if a[i]==int(b[i]):
            hit=hit+1

    blow=0
    for j in range(4):
        for i in range(4):
            if int(b[j])==a[i]and(a[i]!=int(b[i]))and(a[j]!=int(b[j])):
                blow=blow+1
                break

    print("Hit "+str(hit))
    print("Blow "+str(blow))

    if hit==4:
        print("Correct!")
        break
    
            
    
