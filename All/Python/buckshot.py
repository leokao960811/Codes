import random as rand

def load(list):
    list.append(rand.randint(0,1))

##def playerMove():
    
##def opponentMove():


a = []
b = 0
l = 0
shell = rand.randint(2,8)
for i in range(0,shell):
    load(a)

for i in range(0,shell):
    if a[i]==1:
        l += 1
        #print(l)
    else:
        b += 1
        #print(b)

if(l==0):
    a.insert(rand.randint(0,shell), 1)
    l += 1
    shell += 1
elif(b==0):
    a.insert(rand.randint(0,shell), 0)
    b += 1
    shell += 1

#print(a)
print(l,"lives,",b,"blanks")

shot = 0
while shot<shell:
    ans=eval(input("You(0) or Him(1)? "))
    if ans==0:
        if(a[shot]==1):
            print("You shot yourself.")
            l -= 1
        else:
            print("You are safe.")
            b -= 1
    else:
        if(a[shot]==1):
            print("You shot him.")
            l -= 1
        else:
            print("It's a blank.")
            b -= 1
    shot += 1
    #print(shot)
    if(shot<shell):
        choice=rand.randint(0,1)

        if(l>b):
            print("Opponent shoots you.")
            if(a[shot]==1):
                print("He shot you.")
                l -= 1
            else:
                print("It's a blank.")
                b -= 1
        elif(l<b):
            print("Opponent shoots himself.")
            if(a[shot]==1):
                print("Opponent shot himself.")
                l -= 1
            else:
                print("Opponent is safe.")
                b -= 1
        else:
            if(choice==1):
                print("Opponent shoots you.")
                if(a[shot]==1):
                    print("He shot you.")
                    l -= 1
                else:
                    print("It's a blank.")
                    b -= 1
            else:
                print("Opponent shoots himself.")
                if(a[shot]==1):
                    print("Opponent shot himself.")
                    l -= 1
                else:
                    print("Opponent is safe.")
                    b -= 1
        shot += 1
        #print(shot)