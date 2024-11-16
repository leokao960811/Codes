#coding:utf:8
import tkinter as tk
import tkinter.messagebox as tmsg

root=tk.Tk()
root.geometry("600x225")
root.title("from 資訊社")

def click():
    label=tk.Label(root,text="祝高三學長姊包高中！",font=("Helvetica", 30))
    label.place (x=115,y=150)

button=tk.Button(root, text="請點我",font=("Helvetica", 25),command=click)
button.place(x=230,y=60)
