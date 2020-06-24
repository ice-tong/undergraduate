#  Kian Farsany 55375951 and Muyuan He 72301773.  ICS 31 Lab sec 8.  Lab asst 4.

from collections import namedtuple
#
# Part (c)
#
print('Part (c)\n')

# Part (c.1)
def test_number(n:int, s:str) -> bool:
    '''Return if an int equivalent to what the string describes'''
    if s == 'positive' and n > 0:
        return True
    if s == 'negative' and n < 0:
        return True
    if s == 'odd' and n%2 == 1:
        return True
    if s == 'even' and n%2 == 0:
        return True
    return False
assert test_number(14, 'even')
assert not test_number(100, 'odd')
assert test_number(33, 'positive')
assert not test_number(100, 'negative')

#Part (c.2)

def display() -> None:
    '''Print each character of a user input'''
    s = input('Enter a word: ')
    for i in s:
        print(i)
display()

# Part (c.3)
def square_list(L: list) -> None:
    '''Print the square of each number in a list of int'''
    for i in L:
        print(i ** 2)
square_list([2, 3, 4, 10])

print()

# Part (c.4)
def match_first_letter(s: str, L: list) -> None:
    '''Print the strings that begin with the character'''
    for i in L:
        if i[0] == s:
            print(i)
match_first_letter('I', ['Iron Man', 'Iron Man 2', 'The Avengers', 'Superman', 'I am Legend'])

print()

# Part (c.5)
def match_area_code(area_codes: list, phone_nums: list) -> None:
    '''Print the phone numbers with the area codes given'''
    for p in phone_nums:
        for a in area_codes:
            if a[1:4] == p:
                print(a)
match_area_code(['949', '714'], ['(714)824-1234', '(419)312-8732', '(949)555-1234'])

print()

# Part (c.6)
def matching_area_codes(area_codes: list, phone_nums: list) -> list:
    '''Return a list of phone numbers with the area code given'''
    result = []
    for p in phone_nums:
        for a in area_codes:
            if a == p[1:4]:
                result.append(p)
    return result
assert matching_area_codes(['949', '714'], ['(714)824-1234', '(419)312-8732', '(949)555-1234']) == ['(714)824-1234', '(949)555-1234']

#
# Part (d)
#
print('\nPart (d)\n')

# Part (d.1)
def is_vowel(s: str) -> bool:
    '''Return if a character is a vowel'''
    if s in 'aeiouAEIOU':
        return True
    return False
assert is_vowel('a') == True
assert is_vowel('D') == False
assert is_vowel('U') == True

#Part (d.2)
def print_nonvowels(s: str) -> None:
    '''Print the nonvowels in a string'''
    for i in s:
        if not is_vowel(i):
            print(i)
print_nonvowels('Hello')
print_nonvowels('WOW')

# Part (d.3)
def nonvowels(s: str) -> str:
    '''Return a string of the nonvowels of the given string (this includes non-letters)'''
    result = ''
    for i in s:
        if not is_vowel(i):
            result += i
    return result
assert nonvowels('Hello') == 'Hll'
assert nonvowels('WOW') == 'WW'
assert nonvowels('aeiouAEIOU123') == '123'

# Part (d.4)
def consonants(s: str) -> str:
    '''Return a string of the consonants of the given string (this only includes letters)'''
    result = ''
    for i in s:
        if i.isalpha() and not is_vowel(i):
            result += i
    return result
assert consonants('Hello') == 'Hll'
assert consonants('WOW') == 'WW'
assert consonants('aeiouAEIOU123#$%@why') == 'why'

# Part (d.5)
def select_letters(s1: str, s2: str) -> str:
    '''If s1 is 'v', return s2's vowels.
    If s1 is 'c', return s2's consonants.
    Otherwise, return an empty string'''
    result = ''
    if s1 == 'v':
        for i in s2:
            if is_vowel(i):
                result += i
        return result
    if s1 == 'c':
        return consonants(s2)
    return ''
assert select_letters('c', 'facetiously') == 'fctsly'
assert select_letters('v', 'facetiously') == 'aeiou'
assert select_letters('h', 'facetiously') == ''
        
# Part (d.6)
def hide_vowels(s: str) -> str:
    '''Replace all vowels in a string with hyphens'''
    result = ''
    for i in s:
        if is_vowel(i):
            result += '-'
        else:
            result += i
    return result
assert hide_vowels('Welp, this is one') == 'W-lp, th-s -s -n-'
assert hide_vowels('why') == 'why'
assert hide_vowels('AeIioU') == '------'

#
# Part (e)
#

Restaurant = namedtuple('Restaurant', 'name cuisine phone dish price')
def Restaurant_change_price(r: Restaurant, n: float) -> Restaurant:
    '''Return the Restaurant given with the given number added to the price'''
    return r._replace(price = r.price + n)
assert Restaurant_change_price(Restaurant('name', 'cuisine', 'phone', 'dish', 14.00), 2) == Restaurant('name', 'cuisine', 'phone', 'dish', 16.00)

#
# Part (f)
#
print('\nPart (f)\n')

R1 = Restaurant("Taillevent", "French", "343-3434", "Escargots", 24.50)
R2 = Restaurant("La Tour D'Argent", "French", "343-3344", "Ris de Veau", 48.50)
R3 = Restaurant("Pascal", "French", "333-4444", "Bouillabaisse", 32.00)
R4 = Restaurant("Thai Touch", "Thai", "444-3333", "Mee Krob", 10.95)
R5 = Restaurant("Thai Dishes", "Thai", "333-4433", "Paht Woon Sen",  8.50)
R6 = Restaurant("Thai Spoon", "Thai", "334-3344", "Mussamun", 9.00)
R7 = Restaurant("McDonald's", "Burgers", "333-4443", "Big Mac", 3.95)
R8 = Restaurant("Burger King", "Burgers", "444-3344", "Whopper", 3.75)
R9 = Restaurant("Wahoo's", "Fish Tacos", "443-4443", "Mahi Mahi Burrito", 7.50)
R10 = Restaurant("In-N-Out Burger", "Burgers", "434-3344", "Cheeseburger", 2.50)
R11 = Restaurant("The Shack", "Burgers", "333-3334", "Hot Link Burger", 4.50)
R12 = Restaurant("Gina's", "Pizza", "334-4433", "Combo Pizza", 12.95)
R13 = Restaurant("Peacock, Room", "Indian", "333-4443", "Rogan Josh", 12.50)
R14 = Restaurant("Gaylord", "Indian", "333-3433", "Tandoori Chicken", 13.50)
R15 = Restaurant("Mr. Chow", "Chinese", "222-3333", "Peking Duck", 24.50)
R16 = Restaurant("Chez Panisse", "California", "222-3322", "Grilled Duck Breast", 25.00)
R17 = Restaurant("Spago", "California", "333-2222", "Striped Bass", 24.50)
R18 = Restaurant("Sriped Bass", "Seafood", "333-2233", "Cedar Plank Salmon", 21.50)
R19 = Restaurant("Golden Pagoda", "Chinese", "232-3232", "Egg Foo Young", 8.50)
R20 = Restaurant("Langer's", "Delicatessen", "333-2223", "Pastrami Sandwich", 11.50)
R21 = Restaurant("Nobu", "Japanese", "335-4433", "Natto Temaki", 5.50)
R22 = Restaurant("Nonna", "Italian", "355-4433", "Stracotto", 25.50)
R23 = Restaurant("Jitlada", "Thai", "324-4433", "Paht Woon Sen", 15.50)
R24 = Restaurant("Nola", "New Orleans", "336-4433", "Jambalaya", 5.50)
R25 = Restaurant("Noma", "Modern Danish", "337-4433", "Birch Sap", 35.50)
R26 = Restaurant("Addis Ababa", "Ethiopian", "337-4453", "Yesiga Tibs", 10.50) 


RL = [R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15, R16,
	R17, R18, R19, R20, R21, R22, R23, R24, R25, R26]

# Part (f.1)
def alphabetical(L: list) -> list:
    '''Return the sorted list of Restauarant in alphabetical order by name'''
    return sorted(L)
assert alphabetical(RL) == sorted(RL)
assert alphabetical(RL[0: 2]) == [R2, R1]

# Part (f.2)
def alphabetical_names(L: list) -> list:
    '''Return a list of the name of each Restaurant in alphabetical order'''
    result = []
    L = alphabetical(L)
    for i in L:
        result = result + [i.name]
    return result
assert alphabetical_names(RL[0: 3]) == ["La Tour D'Argent", 'Pascal', 'Taillevent']
assert alphabetical_names(RL[0:2]) == ["La Tour D'Argent", 'Taillevent']

# Part (f.3)
def all_Thai(L: list) -> list:
    '''Return the list of Restaurants that have Thai cuisine'''
    result = []
    for i in L:
        if i.cuisine == 'Thai':
            result = result + [i]
    return result
assert all_Thai(RL) == [R4, R5, R6, R23]
assert all_Thai(RL[0: 3]) == []

# Part (f.4)
def select_cuisine(L: list, s: str) -> list:
    '''Return a list of the Restaurants that have the given cuisine'''
    result = []
    for i in L:
        if i.cuisine == s:
            result = result + [i]
    return result
assert select_cuisine(RL, 'Thai') == all_Thai(RL)
assert select_cuisine(RL, 'French') == [R1, R2, R3]
assert select_cuisine(RL, 'Ethiopian') == [R26]

# Part (f.5)
def select_cheaper(L: list, f: float) -> list:
    '''Returns a list of Restaurants whose price is less than the number given'''
    result = []
    for i in L:
        if i.price < f:
            result = result + [i]
    return result
assert select_cheaper(RL, 100) == RL
assert select_cheaper(RL, 1.50) == []
assert select_cheaper(RL, 7.50) == [R7, R8, R10, R11, R21, R24]
            
# Part (f.6)
def average_price(L: list) -> float:
    '''Returns the average price of the dishes at all the Restaurants given'''
    sum = 0
    for i in L:
        sum += i.price
    return sum / len(L)
assert average_price([RL[0]]) == 24.50
assert average_price(RL[0: 3]) == 35
assert average_price(RL[0: 5]) == 24.89
    
# Part (f.7)
print(average_price(select_cuisine(RL, 'Indian')))

print()

# Part (f.8)
print(average_price(select_cuisine(RL, 'Chinese') + select_cuisine(RL, 'Thai')))

print()

# Part (f.9)
print(alphabetical_names(select_cheaper(RL, 15.00)))

print()

#
# Part (g)
#
import tkinter              # Load the library; do this just once per program

my_window = tkinter.Tk()    # Create the graphics window

my_canvas = tkinter.Canvas(my_window, width=500, height=500)  # Create a 500x500 canvas to draw on
my_canvas.pack()            # Put the canvas into the window

def create_rectangle_from_center(x: int, y: int, w: int, h: int) -> None:
    '''Create a rectangle with center (x, y), width w, and height h'''
    my_canvas.create_rectangle(x - (w/2), y - (h/2), x + (w/2), y + (w/2))

create_rectangle_from_center(250, 250, 400, 400) 

tkinter.mainloop()          # Combine all the elements and display the window
