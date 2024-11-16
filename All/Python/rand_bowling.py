# -*- coding: utf-8 -*-
"""Random Bowling"""

import random as rand
i=int()
while i<9:
  First=rand.randint(0,10)
  Sec=rand.randint(0,(10-First))
  if First==10:
    First="X"
    Sec=" "
  elif Sec==10-First:
    Sec="/"
  elif Sec==0:
    Sec="-"
  print(First,Sec,end="  ")
  i=i+1

First=rand.randint(0,10)
if First==10:
  First="X"
  Sec=rand.randint(0,10)
  if Sec==10:
    Sec="X"
    Third=rand.randint(0,10)
    if Third==10:
      Third="X"
  else:
    Third=rand.randint(0,10-Sec)
    if Third==10-Sec:
      Third="/"
    elif Third==0:
      Third="-"
else:
  Sec=rand.randint(0,(10-First))
  if Sec==10-First:
    Sec="/"
    Third=rand.randint(0,10)
    if Third==10:
      Third="X"
  elif Sec==0:
    Sec="-"
    Third=""
  else:
    Third=""

print(First,Sec,Third)

