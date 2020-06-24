#  Kian Farsany 55375951 and Jasper Van 81766836.  ICS 31 Lab sec 8.  Lab asst 6g.

#
# Part (g)
#

# RESTAURANT COLLECTION PROGRAM
# ICS 31, UCI, David G. Kay, Fall 2015

# Implement Restaurant as a namedtuple, collection as a list

##### MAIN PROGRAM (CONTROLLER)

def restaurants():  # nothing -> interaction
    """ Main program
    """
    print("Welcome to the restaurants program!")
    our_rests = Collection_new()
    our_rests = handle_commands(our_rests)
    print("\nThank you.  Good-bye.")

MENU = """
Restaurant Collection Program --- Choose one
 a:  Add a new restaurant to the collection
 r:  Remove a restaurant from the collection
 s:  Search the collection for selected restaurants
 p:  Print all the restaurants
 e:  Remove (erase) all the restaurants from the collection
 c:  Change prices for the dishes served
 t:  Search for the restaurants with a type of cuisine
 d:  Search for the restaurants with a certain dish
 q:  Quit
"""

def handle_commands(C: list) -> list:
    """ Display menu, accept and process commands.
    """
    while True:
        response = input(MENU)
        if response=="q":
            return C
        elif response=='a':
            r = Restaurant_get_info()
            C = Collection_add(C, r)
        elif response=='r':
            n = input("Please enter the name of the restaurant to remove:  ")
            C = Collection_remove_by_name(C, n)
        elif response=='p':
            print(Collection_str(C))
        elif response=='s':
            n = input("Please enter the name of the restaurant to search for:  ")
            for r in Collection_search_by_name(C, n):
                print(Restaurant_str(r))
        elif response=='e':
            C = Collection_new()
        elif response=='c':
            n = float(input("Please enter the percentage you want to change the prices by:  "))
            C = Collection_change_prices(C, n)
        elif response=='t':
            n = input("Please enter the type of cuisine:  ")
            for r in Collection_search_cuisine(C, n):
                print(Restaurant_str(r))
        elif response=='d':
            n = input("Please enter the type of dish:  ")
            for r in Collection_search_dish(C, n):
                print(Restaurant_str(r))
        else:
            invalid_command(response)

def invalid_command(response):  # string -> interaction
    """ Print message for invalid menu command.
    """
    print("Sorry; '" + response + "' isn't a valid command.  Please try again.")




##### Restaurant
from collections import namedtuple
Restaurant = namedtuple('Restaurant', 'name cuisine phone menu')
# Constructor:   r1 = Restaurant('Taillevent', 'French', '01-11-22-33-44', 'Escargots', 23.50)

def Restaurant_str(self: Restaurant) -> str:
    return (
        "Name:     " + self.name + "\n" +
        "Cuisine:  " + self.cuisine + "\n" +
        "Phone:    " + self.phone + "\n" +
        "Menu:     " + Menu_str(self.menu) + "\n" +
        "Average price:  ${:5.2f}.  Average calories:  {:5.1f}".format(Menu_average_price(self.menu), Menu_average_calories(self.menu)) + "\n")

def Restaurant_get_info() -> Restaurant:
    """ Prompt user for fields of Restaurant; create and return.
    """
    return Restaurant(
        input("Please enter the restaurant's name:  "),
        input("Please enter the kind of food served:  "),
        input("Please enter the phone number:  "),
        Menu_enter())

def Restaurant_change_price(r: Restaurant, n: float) -> Restaurant:
    '''Raise the Restaurant's prices by the percentage given'''
    return Restaurant(r.name, r.cuisine, r.phone, Menu_change_price(r.menu, n))


#### COLLECTION
# A collection is a list of restaurants

def Collection_new() -> list:
    ''' Return a new, empty collection
    '''
    return [ ]

def Collection_str(C: list) -> str:
    ''' Return a string representing the collection
    '''
    s = ""
    for r in C:
        s = s + Restaurant_str(r)
    return s

def Collection_search_by_name(C: list, name: str) -> list:
    """ Return list of Restaurants in input list whose name matches input string.
    """
    result = [ ]
    for r in C:
        if r.name == name:
            result.append(r)
    return result

def Collection_add(C: list, R: Restaurant) -> list:
    """ Return list of Restaurants with input Restaurant added at end.
    """
    C.append(R)
    return C

def Collection_remove_by_name(C: list, name: str) -> list:
    """ Given name, remove all Restaurants with that name from collection.
    """
    result = [ ]
    for r in C:
        if r.name != name:
            result.append(r)
    return result

def Collection_change_prices(C: list, n: float) -> list:
    '''Return the list given with all Restaurants' prices changed by percent given'''
    result = []
    for i in C:
        result += [Restaurant_change_price(i, n)]
    return result

def Collection_search_cuisine(C: list, s: str) -> list:
    '''Return the list of Restaurants with the cuisine specified'''
    result = []
    for r in C:
        if r.cuisine == s:
            result += [r]
    return result

def Collection_search_dish(C: list, s: str) -> list:
    '''Return the list of Restaurants with Menus that contain the given Dish'''
    result = []
    for r in C:
        for d in r.menu:
            if s in d.name:
                result += [r]
    return result

            
#### DISH
Dish = namedtuple('Dish', 'name price calories')
def Dish_str(d: Dish) -> str:
    '''Return a string with the dish's fields'''
    return d.name + ' ($' + str(d.price) + '): ' + str(d.calories) + ' cal'

def Dish_get_info() -> Dish:
    '''Prompt user for fields of Dish; create and return.'''
    return Dish(
        input("Please enter the dish's name:  "),
        float(input("Please enter the price of the dish:  ")),
        float(input("Please enter the number of calories:  ")))

def Dish_change_price(d: Dish, n: float) -> Dish:
    '''Return the same dish with the price changed by the given percentage'''
    return d._replace(price=d.price+((n*0.01)*d.price))


#### MENU
# A Menu is a list of Dishes

def Menu_enter() -> list:
    '''Prompts user for more dishes, then returns Menu'''
    result = []
    while True:
        response = input('Type yes if you want to add a dish to the menu, type no if you do not:  ')
        if response == 'no':
            return result
        elif response == 'yes':
            result += [Dish_get_info()]

def Menu_str(m: list) -> str:
    '''Return a string with Menu's dishes'''
    result = ''
    for d in m:
        result = result + Dish_str(d) + '\n          '
    return result

def Menu_change_price(m: list, n: float) -> list:
    '''Raise a Menu's prices by the percentage given'''
    result = []
    for d in m:
        result += [Dish_change_price(d, n)]
    return result

def Menu_average_price(m: list) -> float:
    '''Return the average price of the Menu'''
    total = 0
    for d in m:
        total += d.price
    return total/len(m)

def Menu_average_calories(m: list) -> float:
    '''Return the average calories of the Menu'''
    total = 0
    for d in m:
        total += d.calories
    return total/len(m)


restaurants()
