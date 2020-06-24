#  Kian Farsany 55375951 and Guohao Liang 78838097.  ICS 31 Lab sec 8.  Lab Asst 2.

hours = int(input('How many hours?'))
print('This many hours:', hours)
rate = float(input('How many dollars per hour?'))
print('This many dollars per hour:  $', rate)
print('Weekly salary:  $', hours * rate)

name = str(input("Hello. What is your name? "))
print("Hello,", name)
print("It's nice to meet you.")
age = int(input("How old are you? "))
print("Next year you will be", age + 1, "years old.")
print("Good-bye!")

KRONE_PER_EURO = 7.46
KRONE_PER_POUND = 8.60
KRONE_PER_DOLLAR = 6.62
print("Please provide this information:")
name = str(input("Business name: "))
euro = float(input("Number of euros: "))
pound = float(input("Number of pounds: "))
dollar = float(input("Number of dollars: "))
print()
print("Copenhagen Chamber of Commerce")
print("Business name:", name)
print(euro, "euros is", KRONE_PER_EURO * euro, "krone.")
print(pound, "pounds is", KRONE_PER_POUND * pound, "krone.")
print(dollar, "dollars is", KRONE_PER_DOLLAR * dollar, "krone.")
print("Total krone: ", (KRONE_PER_EURO * euro) +
                        (KRONE_PER_POUND * pound)+
                        (KRONE_PER_DOLLAR * dollar))

from collections import namedtuple
Book = namedtuple('Book', 'title author year price')
favorite = Book('Adventures of Sherlock Holmes',
                'Arthur Conan Doyle', 1892, 21.50)
another = Book('Memoirs of Sherlock Holmes', 
               'Arthur Conan Doyle', 1894, 23.50)
still_another = Book('Return of Sherlock Holmes',
                     'Arthur Conan Doyle', 1905, 25.00)
booklist = [favorite, another, still_another]
print(still_another.title)
print(another.price)
print((favorite.price + another.price + still_another.price) / 3)
print(favorite.year < 1900)
temp1 = Book(still_another.title, still_another.author, still_another.year, 26.00)
still_another = temp1
print(still_another.price)
temp2 = Book(still_another.title, still_another.author, still_another.year, still_another.price * 1.20)
still_another = temp2
print(still_another.price)

Animal = namedtuple('Animal', 'name species age weight food')
elephant = Animal('Jumbo', 'elephant', 50, 1000.0, 'peanuts')
platypus = Animal('Perry', 'platypus', 7, 1.7, 'shrimp')
print(elephant.weight == platypus.weight)

print(booklist[0].price < booklist[1].price)
print(booklist[0].year > booklist[-1].year)

Restaurant = namedtuple('Restaurant', 'name cuisine phone dish price')
# Restaurant attributes: name, kind of food served, phone number, best dish, price of that dish
RC = [
    Restaurant("Thai Dishes", "Thai", "334-4433", "Mee Krob", 12.50),
    Restaurant("Nobu", "Japanese", "335-4433", "Natto Temaki", 5.50),
    Restaurant("Nonna", "Italian", "355-4433", "Stracotto", 25.50),
    Restaurant("Jitlada", "Thai", "324-4433", "Paht Woon Sen", 15.50),
    Restaurant("Nola", "New Orleans", "336-4433", "Jambalaya", 5.50),
    Restaurant("Noma", "Modern Danish", "337-4433", "Birch Sap", 35.50),
    Restaurant("Addis Ababa", "Ethiopian", "337-4453", "Yesiga Tibs", 10.50) ]
print(RC[2].name)
print(RC[0].cuisine == RC[3].cuisine)
print(RC[-1].price)
RC.sort()
print(RC)
RC.sort()
print(RC[-1].dish)
RC.sort()
print([RC[0], RC[1], RC[-2], RC[-1]])

import tkinter              # Load the library; do this just once per program

my_window = tkinter.Tk()    # Create the graphics window

my_canvas = tkinter.Canvas(my_window, width=500, height=500)  # Create a 500x500 canvas to draw on
my_canvas.pack()            # Put the canvas into the window

my_canvas.create_line(100, 100, 100, 300, fill='black')
my_canvas.create_line(100, 300, 300, 300, fill='black')
my_canvas.create_line(300, 300, 300, 100, fill='black')
my_canvas.create_line(300, 100, 100, 100, fill='black')

my_canvas.create_line(200, 100, 100, 200, fill='black')
my_canvas.create_line(100, 200, 200, 300, fill='black')
my_canvas.create_line(200, 300, 300, 200, fill='black')
my_canvas.create_line(300, 200, 200, 100, fill='black')

my_canvas.create_line(300, 100, 300, 300, fill='black')
my_canvas.create_line(300, 300, 500, 300, fill='black')
my_canvas.create_line(500, 300, 500, 100, fill='black')
my_canvas.create_line(500, 100, 300, 100, fill='black')
my_canvas.create_line(300, 100, 400, 0, fill='black')
my_canvas.create_line(500, 100, 400, 0, fill='black')
my_canvas.create_line(370, 300, 370, 220, fill='black')
my_canvas.create_line(430, 300, 430, 220, fill='black')
my_canvas.create_line(370, 220, 430, 220, fill='black')
my_canvas.create_line(330, 130, 330, 180, fill='black')
my_canvas.create_line(330, 180, 380, 180, fill='black')
my_canvas.create_line(380, 180, 380, 130, fill='black')
my_canvas.create_line(380, 130, 330, 130, fill='black')

my_canvas.create_oval(100, 350, 300, 450, fill='white')
my_canvas.create_oval(150, 360, 250, 440, fill='blue')
my_canvas.create_oval(185, 385, 215, 415, fill='black')

tkinter.mainloop()          # Combine all the elements and display the window

