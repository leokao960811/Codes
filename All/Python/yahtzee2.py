import random
tries=1

def show_rolls(dice):
    print("The dice rolls are ",end=" ")
    for d in dice:
        print(str(d)+" ",end=" ")


while True:
    input("Press to roll ")
    dice=[]
    for d in range(5):
        dice.append(random.randint(1,6))

    show_rolls(dice)

    while tries!=3:
        reroll=input("Which dice to reroll? ")
        reroll=reroll.split()
        for index, ch in enumerate(reroll):
            reroll[index]=int(ch)-1

        for index in reroll:
            dice[index]=random.randint(1,6)

        show_rolls(dice)
        tries=tries+1

    print("All tries over, now you need to score")
    tries=1
