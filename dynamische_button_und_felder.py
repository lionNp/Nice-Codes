from email.policy import strict
from operator import truediv
from tkinter import *
from turtle import left, window_height
from time import *
from re import *

#dynamic structures
dynamic_pic_box = []
dynamic_del_button = []
dynamic_text_box = []



#button functions

#reset values of dynamic elements
def dynamic_grid_cleanup():
    for i in range(len(dynamic_del_button)):
        dynamic_del_button[i].grid(row =i*2, column = 4)
        dynamic_pic_box[i].grid(row =i*2, column = 5)
        dynamic_text_box[i].grid(row = i*2+1, column = 5)

    return

#function to delete last dynamic block
def del_dynamic_at_index(button):
    index = dynamic_del_button.index(button)

    dynamic_del_button[index].destroy()
    dynamic_pic_box[index].destroy()
    dynamic_text_box[index].destroy()

    del dynamic_del_button[index]
    del dynamic_pic_box[index]
    del dynamic_text_box[index]

    dynamic_grid_cleanup()

    return

#create dynmic button, append to list
def new_dyn_button(name, index):
    button = Button(window, text=name, command= lambda: del_dynamic_at_index(button))
    button.grid(row=index, column=4)
    dynamic_del_button.append(button)

    return

#create dynamic textbox, append to list
def  new_dyn_text_box(index):
    text_box = Entry(window, width=20)
    text_box.grid(row=index, column=5)
    dynamic_text_box.append(text_box)

    return

#create dynamic picture filed, append to list
def new_dyn_scan_field(index):
    label = Label(window, text='hier das Bild')
    label.grid(row=index, column=5)
    dynamic_pic_box.append(label)

    return

#create new block
def new_pos():
    dynamic_struct_counter = len(dynamic_del_button)
    new_dyn_button('del', dynamic_struct_counter*2)
    new_dyn_scan_field(dynamic_struct_counter*2)
    new_dyn_text_box(dynamic_struct_counter*2+1)

    return

def add_to_file():
    str = text_box_ergebnis.get()

    f = open('gescanntes.txt', 'a+')
    f.write(str)

    text_box_ergebnis.delete(0, END)
    text_box_ergebnis.insert(END, 'alles gesichert')


#create window
window = Tk()
window.title('Screen Scanner')
window.geometry('850x580')


#create window assets
button_neue_position = Button(window, text='Neue Position', command=new_pos)
button_neue_position.grid(row=0, columnspan=2, sticky='NE')

#worttrennung
label_worttrennung = Label(window, text='Worttrennung')
label_worttrennung.grid(row=1)

string_worttrennung = StringVar(window)
text_box_worttrennung = Entry(window, width = 10, textvariable=string_worttrennung)
text_box_worttrennung.grid(row=1, column=1)
text_box_worttrennung.insert(END, '_')
#text_box_worttrennung.bind("<Return>", btn_func)

#scantrennung
label_scantrennung = Label(window, text='Scantrennung')
label_scantrennung.grid(row=2)

string_scantrennung = StringVar(window)
text_box_scantrennung = Entry(window, width = 10, textvariable=string_scantrennung)
text_box_scantrennung.grid(row=2, column=1)
text_box_scantrennung.insert(END, '_')


#ergebnis
text_box_ergebnis = Entry(window, width = 24)
#text_box_ergebnis.pack(expand=1)
text_box_ergebnis.grid(row=3, columnspan=2, sticky='NW')  #NW für North West


#savetofile
button_add_to_file = Button(window, text='als Datei speichern', command=add_to_file)
button_add_to_file.grid(row=4, columnspan=2, sticky='NE')

window.mainloop()
