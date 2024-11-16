import random

i=1
t=0

while i!=0:
    a=(random.randint(1,6))
    b=(random.randint(1,6))
    c=(random.randint(1,6))
    d=(random.randint(1,6))
    e=(random.randint(1,6))
    print(a,b,c,d,e)
    t=t+1
    if(a==b==c==d==e):
        break
print("YAHTZEE!")
print("Total attempts: ",t)
input("Press to exit")
