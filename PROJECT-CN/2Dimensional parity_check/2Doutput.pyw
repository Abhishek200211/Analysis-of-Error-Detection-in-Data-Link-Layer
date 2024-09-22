from tkinter import *
from tkinter import filedialog

def btn_clicked():
    f = open('2D_output.txt', 'r+')
    f.seek(0) 
    f.truncate(0)
    f.close()


def openFile():
    tf = filedialog.askopenfilename(
        initialdir="2D_output.txt", 
        title="Open Text file", 
        filetypes=(("Text Files", "*.txt"),)
        )
    pathh.insert(END, tf)
    tf = open(tf)  # or tf = open(tf, 'r')
    data = tf.read()
    txtarea.insert(END, data)
    tf.close()
    

def delete_text():
    txtarea.delete("1.0", "end")    
ws = Tk()
ws.title("TWO DIMENSIONAL OUTPUT")
ws.geometry("700x580")
ws['bg']='#fb0'
canvas = Canvas(
    ws,
    bg = "#ffffff",
    height = 790,
    width = 1119,
    bd = 0,
    highlightthickness = 0,
    relief = "ridge")
canvas.place(x = 0, y = 0)#background.png
background_img = PhotoImage(file = f"bg.png")
background = canvas.create_image(
    765.5, 540.5,
    image=background_img)

txtarea = Text(ws,wrap=WORD,bg="lightgray",fg="black",bd=0, width=80, height=30)
filename='2D_output.txt'
file = open(filename,'r')
f = file.read()
txtarea.insert(END,f)
txtarea.pack(pady=20)

pathh = Entry(ws,bg="#000000",fg="#ffffff",bd=3)
pathh.pack(side=LEFT, expand=True, fill=X, padx=20)

Button(
    ws, 
    text="Open File", 
    command=openFile,
    bg="#E0E066",
    fg="black",
    activebackground="orange",
    activeforeground="black",
    borderwidth=2,
    ).pack(side=RIGHT, expand=True, fill=X, padx=20)

Button(
    text="Reset File",
    bg="#E0E066",
    fg="black",
    activebackground="orange",
    activeforeground="black",
    borderwidth=2,
    command = (btn_clicked)).pack(side=RIGHT,expand=True,fill=X,padx=20)
Button(
    text="Clear Frame",
    bg="#E0E066",
    fg="black",
    activebackground="orange",
    activeforeground="black",
    borderwidth=2,
    command = (delete_text)).pack(side=RIGHT,expand=True,fill=X,padx=20)


Label(ws,text="<- PATH",bg="#000000",fg="#ffffff").pack(side=LEFT,padx=5)
ws.resizable(False, False)
ws.mainloop()
