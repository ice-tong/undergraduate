# Kian Farsany 55375951 and Candice Kim 41855902.   ICS 31 Lab sec 8.  Lab asst 3.

# Part (c)
# Part (c.1)
def abbreviate(s: str) -> str:
    '''Return a month's three-letter abbreviation'''
    return s[0:3]
assert abbreviate('January') == 'Jan'
assert abbreviate('abril') == 'abr'

print()

# Part (c.2)
def find_area_square(n:int) -> int:
    '''Return the area of a square with length n'''
    return n ** 2
assert find_area_square(1) == 1
assert find_area_square(5) == 25

print()

# Part (c.3)
def find_area_circle(n: int) -> float:
    '''Return area of a circle with radius n'''
    return 3.14159 * n ** 2
assert find_area_circle(1) == 3.14159
assert find_area_circle(5) == 78.53975

print()

# Part (c.4)
def print_even_numbers(L: list):
    '''Print the even numbers of a list'''
    for i in L:
        if i % 2 == 0:
            print(i)

print()

# Part (c.5)
def calculate_shipping(n: float) -> float:
    '''Return price for shipping'''
    if n < 2:
        return 2
    if n >= 2 and n < 10:
        return 5
    if n >= 10:
        return 5 + (1.5 * (n-10))
assert calculate_shipping(1.5) == 2.00
assert calculate_shipping(7) == 5.00
assert calculate_shipping(15) == 12.50

print()

# Part (c.6&7)
import tkinter              # Load the library; do this just once per program

my_window = tkinter.Tk()    # Create the graphics window

my_canvas = tkinter.Canvas(my_window, width=500, height=500)  # Create a 500x500 canvas to draw on
my_canvas.pack()            # Put the canvas into the window


def create_square(x: int, y: int, n: int):
    '''Draw a square with coordinates (x,y) and side length n'''
    my_canvas.create_rectangle(x,y,x+n,y+n)

create_square(200,200,200)

def create_circle(x: int, y: int, d: int):
    '''Draw a circle with coordinates (x,y) and diameter length d'''
    my_canvas.create_oval(x,y,x+d,y+d)

create_circle(200,200,200)

    
# Part (d)
# Part (d.1)
from collections import namedtuple
Restaurant = namedtuple('Restaurant', 'name cuisine phone dish price')
RC = [
    Restaurant("Thai Dishes", "Thai", "334-4433", "Mee Krob", 12.50),
    Restaurant("Nobu", "Japanese", "335-4433", "Natto Temaki", 5.50),
    Restaurant("Nonna", "Italian", "355-4433", "Stracotto", 25.50),
    Restaurant("Jitlada", "Thai", "324-4433", "Paht Woon Sen", 15.50),
    Restaurant("Nola", "New Orleans", "336-4433", "Jambalaya", 5.50),
    Restaurant("Noma", "Modern Danish", "337-4433", "Birch Sap", 35.50),
    Restaurant("Addis Ababa", "Ethiopian", "337-4453", "Yesiga Tibs", 10.50) ]

def restaurant_price(r: Restaurant) -> float:
    '''Return the value of the price for the restaurant'''
    return r.price
assert restaurant_price(RC[0]) == 12.50
assert restaurant_price(RC[-1]) == 10.50

print()

# Part (d.2)
print('Part (d.2)')
RC.sort(key=restaurant_price)
print(RC)

print()

# Part (d.3)
print('Part (d.3)')
def costliest(L:list) -> str:
    '''Return the restaurant name with the highest priced dish'''
    L.sort(key=restaurant_price)
    return L[-1].name
print(costliest(RC))

print()

# Part (d.4)
print('Part (d.4)')

RC = [
    Restaurant("Thai Dishes", "Thai", "334-4433", "Mee Krob", 12.50),
    Restaurant("Nobu", "Japanese", "335-4433", "Natto Temaki", 5.50),
    Restaurant("Nonna", "Italian", "355-4433", "Stracotto", 25.50),
    Restaurant("Jitlada", "Thai", "324-4433", "Paht Woon Sen", 15.50),
    Restaurant("Nola", "New Orleans", "336-4433", "Jambalaya", 5.50),
    Restaurant("Noma", "Modern Danish", "337-4433", "Birch Sap", 35.50),
    Restaurant("Addis Ababa", "Ethiopian", "337-4453", "Yesiga Tibs", 10.50) ]

def costliest2(L:list) -> str:
    '''Return the restaurant name with the highest priced dish without side effect'''
    L1 = sorted(L, key=restaurant_price)
    return L1[-1].name
print(costliest2(RC))

print()

# Part (e)
print('Part (e.1)')
Book = namedtuple('Book', 'author title genre year price instock')
BSI = [
    Book("J.R.R. Tolkien", "The Lord of the Rings", "fantasy", 1954, 20.00, 150),
    Book("James Patterson", "The Black Book", "adventure", 2017, 16.80, 300),
    Book("Mary H. Clark", "All By Myself, Alone", "fiction", 2016, 16.19, 100),
    Book("William H. McRaven", "Make Your Bed", "advice", 2012, 11.56, 200),
    Book("James Dean", "Big Easter Adventure", "children", 2014, 9.99, 175),
    Book("J.K. Rowling", "Harry Potter and the Sorcerer's Stone", "fantasy", 1999, 7.04, 500),
        ]
for i in BSI:
    print(i.title)

print()
print('Part (e.2)')
def book_title(B:Book) -> str:
    '''Return the title of the book'''
    return B.title
temp = sorted(BSI, key=book_title)
for i in temp:
    print(i.title)

print()
print('Part (e.3)')
for i in range(len(BSI)):
    BSI[i] = BSI[i]._replace(price = BSI[i].price * 1.10)
print(BSI)


print()
print('Part (e.4)')
for i in BSI:
    if i.genre == 'Technology':
        print(i.title)

print()
print('Part (e.5)')
before=[]
after=[]
for i in range(len(BSI)):
    if BSI[i].year<2000:
        before.append(BSI[i].title)
    else:
        after.append(BSI[i].title)
print(before)
print(after)
if len(before)>len(after):
    print('More titles before 2000 (',len(before),'vs.',len(after),')')
else:
    print('More titles 2000 or later (',len(after),'vs.',len(before),')')

print()
print('Part (e.6)')
def inventory_value(B:Book)->float:
    ''' Returns inventory of the Book'''
    return B.instock*B.price

def top_value(L:list)->Book:
    ''' Returns highest value inventory'''
    L.sort(key=inventory_value)

    return L[-1]
print('The highest-value book is',top_value(BSI).title, 'by', top_value(BSI).author, 'at a value of $', inventory_value(top_value(BSI)))

print()

# Part (f)

def draw_eye(x:int, y:int, d1:int, d2:int, color:str):
    '''Draw an eye with coordinated (x,y)'''
    my_canvas.create_oval(x,y,x+d1,y+d2,fill='white')
    my_canvas.create_oval(x+d1/2-d2/2,y,x+d1/2+d2/2,y+d2,fill=color)
    my_canvas.create_oval(x+d1/2-d2/5,y+3*d2/10,x+d1/2+d2/5,y+7*d2/10,fill='black')
def draw_nose(x:int,y:int,l1:int,l2:int):
    '''Draw a nose'''
    my_canvas.create_polygon(x,y,x+l1,y+l2,x-l1,y+l2,fill='pink')
def draw_mouth(x:int,y:int,d1:int,d2:int):
    '''Draw a mouth'''
    my_canvas.create_oval(x,y,x+d1,y+d2,fill='red')
    
def draw_face(x:int, y:int, d1:int, d2:int, color:str):
    '''Draw a face with coordinates (x,y)'''
    my_canvas.create_oval(x,y,x+d1,y+d2)
    draw_eye((2*x+d1)/2+(d1/10),y+(2*d2/5),3*d1/10,3*d2/25,color)
    draw_eye((2*x+d1)/2-(d1/10)-3*d1/10,y+(2*d2/5),3*d1/10,3*d2/25,color)
    draw_nose((2*x+d1)/2,y+(2.3*d2/5),3*d1/40,4*d2/25)
    draw_mouth((2*x+d1)/2-3*d1/40,y+0.7*d2,3*d1/20,3*d2/25)

my_window = tkinter.Tk()    # Create the graphics window

my_canvas = tkinter.Canvas(my_window, width=500, height=500)  # Create a 500x500 canvas to draw on
my_canvas.pack()            # Put the canvas into the window
draw_face(100,100,200,250,'brown')

my_window = tkinter.Tk()    # Create the graphics window

my_canvas = tkinter.Canvas(my_window, width=500, height=500)  # Create a 500x500 canvas to draw on
my_canvas.pack()            # Put the canvas into the window
draw_face(50,50,400,400,'blue')

tkinter.mainloop()          # Combine all the elements and display the window












