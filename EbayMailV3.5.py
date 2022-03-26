from operator import truediv
from tkinter import *
from turtle import window_height
from time import *
from re import *
import requests

EMAIL_REGEX = r'([a-zA-Z0-9+._-]+@[a-zA-Z0-9._-]+\.[a-zA-Z0-9_-]+)'

def btn_func(event):
    url_string = url.get()
    html_str = requests.get(url=url_string).text

    for re_match in findall(EMAIL_REGEX, html_str):
        mails.insert(END, re_match + '; ')

    return

def btn_func_html(event):
    html_str = htmls.get()

    for re_match in findall(EMAIL_REGEX, html_str):
        mails.insert(END, re_match + '; ')

    return

window = Tk()
window.title('Mail Reader')
window.geometry('1400x800')

label = Label(window, text='URL')
label.grid(row=0)

label = Label(window, text='URL')
label.grid(row=1)

label2 = Label(window, text='Emails')
label2.grid(row=2)


url_str = StringVar(window)
url = Entry(window, width = 200, textvariable=url_str)
url.grid(row=0, column=1)
url.insert(END, 'Hier die URL reinkopieren')
url.bind("<Return>", btn_func)

html_str = StringVar(window)
htmls = Entry(window, width = 200, textvariable=html_str)
htmls.grid(row=1, column=1)
htmls.insert(END, 'Alternativ hier Html reinkopieren')
htmls.bind("<Return>", btn_func_html)

mails = Entry(window, width = 200)
mails.grid(row=2, column=1)



window.mainloop()
