import random as rd
import time

Drivers = ["1 Wood", "3 Wood", "5 Wood", "Star"]
Irons = ["3 Hybrid", "4 Hybird", "5 Hybrid", "6 Iron", "7 Iron", "Star"]
Wedges = ["8 Iron", "9 Iron", "Pitching Wedge", "Approach Wedge", "Sand Wedge", "Star"]
Wedges_alt = ["8 Iron", "9 Iron", "Pitching Wedge", "Approach Wedge", "Sand Wedge"]
Star = ["Star"]
roll = "no"

d=rd.randint(3,8)
e=rd.randint(3,7)
f=rd.randint(1,3)
g=rd.randint(2,6)
h=rd.randint(2,5)
i=rd.randint(1,4)

print("Club Slots")

roll = input("Roll for clubs? (Y/N)")

while roll == "yes" or roll == "y" or roll == "Yes" or roll == "Y":
    print("\nRolling clubs for next hole...")
    time.sleep(1)
          
    a=rd.choices(Drivers, weights=[d,e,g,i],k=1)
    b=rd.choices(Irons, weights=[f,g,d,e,h,i],k=1)
    c=rd.choices(Wedges, weights=[f,d,h,g,e,i],k=1)
    l=rd.choices(Wedges_alt, weights=[f,d,h,g,e],k=1)
    s=rd.choices(Wedges, weights=[f,d,h,g,e,10000],k=1)
    print("The clubs are:",*a," "," ")
    time.sleep(0.5)
    print("The clubs are:",*a,*b," ")
    time.sleep(0.5)
    if a == b:
        time.sleep(1)
        print("The clubs are:",*a,*b,*s)
    else:
        print("The clubs are:",*a,*b,*l)
    
    if a == b == s:
        time.sleep(0.75)
        print("JACKPOT! All clubs are avalible next hole.") 
    
    roll = input("Roll again? (Y/N)")
