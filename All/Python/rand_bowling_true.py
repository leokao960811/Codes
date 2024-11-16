# -*- coding: utf-8 -*-
"""Professional Player Simulation"""

import random as rand
i=int()
shot_list= [0] * 1 + [1] * 1 + [2] * 1 + [3] * 1 + [4] * 2 + [5] * 3 + [6] * 5 + [7] * 8 + [8] * 8 + [9] * 10 + [10] * 60
SpareChance_list=[0] * 1 + [1]* 3
while i<9:
  First=rand.choice(shot_list)
  Sec=rand.choice(SpareChance_list)
  if First==10:
    First="X"
    Sec=" "
  elif Sec==1:
    Sec="/"
  else:
    Sec=rand.randint(0,(10-First)-1)
    if Sec==0:
      Sec="-"
  print(First,Sec,end="  ")
  i=i+1

First=rand.choice(shot_list)
if First==10:
  First="X"
  Sec=rand.choice(shot_list)
  if Sec==10:
    Sec="X"
    Third=rand.choice(shot_list)
    if Third==10:
      Third="X"

  else:
    Third=rand.choice(SpareChance_list)
    if Third==1:
      Third="/"
    else:
      Third=rand.randint(0,(10-Sec)-1)
      if Third==0:
        Third="-"

else:
  Sec=rand.choice(SpareChance_list)
  if Sec==1:
    Sec="/"
    Third=rand.choice(shot_list)
    if Third==10:
      Third="X"
  else:
    Sec=rand.randint(0,(10-First)-1)
    if Sec==0:
      Sec="-"
      Third=""
    else:
      Third=""

print(First,Sec,Third)
