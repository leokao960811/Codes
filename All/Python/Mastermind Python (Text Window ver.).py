import random
import tkinter as tk
import tkinter.messagebox as tmsg
#Button Clicked
def ButtonClick():
    #Getting Input
    b=editbox1.get()

    #Determining if 4 digit number or not
    isok=False
    if len(b)!=4:
        tmsg.showerror("Error","Enter a 4 digit number")
    else:
        kazuok=True
        for i in range(4):
            if (b[i]<"0")or(b[i]>"9"):
                tmsg.showerror("Error","Not a number")
                kazuok=False
                break
        if kazuok:
            isok=True
    if isok:
        #When input a 4 digit number:
        #Determining Hits
        hit=0
        for i in range(4):
            if a[i]==int(b[i]):
                hit=hit+1
        #Determining Blows
        blow=0
        for j in range(4):
            for i in range(4):
                if int(b[j])==a[i]and(a[i]!=int(b[i]))and(a[j]!=int(b[j])):
                    blow=blow+1
                    break
        #Finish when Hit=4
        if hit==4:
            tmsg.showinfo("Correct","Congrats!")
            #Finish
            root.destroy()
        else:
            rirekibox.insert(tk.END,b+"/H:"+str(hit)+" B:"+str(blow)+"\n")

#Main code
#Preparing Numbers            
a=[random.randint(0,9),
   random.randint(0,9),
   random.randint(0,9),
   random.randint(0,9)]

#Window
root=tk.Tk()
root.geometry("600x400")
root.title("Mastermind Python")

#Recorder
rirekibox=tk.Text(root,font=("TF2 Secondary",14))
rirekibox.place(x=400,y=0,width=200,height=400)

#Label
label1=tk.Label(root,text="Input Number",font=("TF2 Secondary",14))
label1.place(x=20,y=20)

#Text
editbox1=tk.Entry(width=4,font=("TF2 Secondary",28))
editbox1.place(x=120,y=60)

#Button
button1=tk.Button(root, text="Confirm",font=("TF2 Secondary",14),command=ButtonClick)
button1.place(x=220,y=60)

#Window
root.mainloop()
