#  Kian Farsany 55375951 and Carina Javalera 51817757.  ICS 31 Lab sec 8.  Lab asst 5.

from collections import namedtuple

#
# Part (c)
#
print('Part (c)\n')

# Part (c.1)
Dish = namedtuple('Dish', 'name price calories')
d1 = Dish('burger', 2.50, 1000)
d2 = Dish('pizza', 10.00, 750)
d3 = Dish('burger', 5.99, 1000)

# Part (c.2)
def Dish_str(d: Dish) -> str:
    '''Return a string with the dish's fields'''
    return d.name + ' ($' + str(d.price) + '): ' + str(d.calories) + ' cal'
assert Dish_str(d1) == 'burger ($2.5): 1000 cal'
assert Dish_str(d2) == 'pizza ($10.0): 750 cal'

# Part (c.3)
def Dish_same(d1: Dish, d2: Dish) -> bool:
    '''Return True if both dished have the same name and calories'''
    if d1.name == d2.name and d1.calories == d2.calories:
        return True
    return False
assert Dish_same(d1, d3)
assert not Dish_same(d1, d2)
assert not Dish_same(d2, d3)

# Part (c.4)
def Dish_change_price(d: Dish, n: float) -> Dish:
    '''Return the same dish with the price changed by the given percentage'''
    return d._replace(price=d.price+((n*0.01)*d.price))
assert Dish_change_price(d1, -50) == d1._replace(price=1.25)
assert Dish_change_price(d2, 200) == d2._replace(price=30.00)
assert Dish_change_price(d1, 100) == d1._replace(price=5.00)
assert Dish_change_price(d2, -100) == d2._replace(price=0)
assert Dish_change_price(d2, -75) == d2._replace(price=2.50)
assert Dish_change_price(d3, 0) == d3

# Part (c.5)
def Dish_is_cheap(d: Dish, n: float) -> bool:
    '''Return if the given price is greater than the Dish's price'''
    if d.price < n:
        return True
    return False
assert Dish_is_cheap(d1, 3)
assert not Dish_is_cheap(d2, 10.00)
assert not Dish_is_cheap(d3, 5.98)

# Part (c.6)
DL = [Dish('burger', 2.50, 1000),
      Dish('pizza', 10.00, 750),
      Dish('burger', 5.99, 1000),
      Dish('kabob', 12.50, 400),
      Dish('steak', 25.00, 725)]

DL2 = [Dish('crab', 45.99, 560),
       Dish('sandwich', 3.00, 200),
       Dish('yogurt', 1.50, 120),
       Dish('soup', 7.99, 460)]

DL.extend(DL2)

def Dishlist_display(L: 'list of Dish') -> str:
    '''Return a large string of all of the Dishes in the list given'''
    result = ''
    for i in L:
        result = result + Dish_str(i) + '\n'
    return result
assert Dishlist_display(DL2[0: 2]) == 'crab ($45.99): 560 cal\nsandwich ($3.0): 200 cal\n'
assert Dishlist_display([d1, d3]) == 'burger ($2.5): 1000 cal\nburger ($5.99): 1000 cal\n'

print(Dishlist_display(DL))

# Part (c.7)
def Dishlist_all_cheap(L: 'list of Dish', n: float) -> bool:
    '''Return True if all Dish prices are less than the price given'''
    for i in L:
        if not Dish_is_cheap(i, n):
            return False
    return True
assert Dishlist_all_cheap(DL, 50)
assert not Dishlist_all_cheap(DL, 5.60)

# Part (c.8)
def Dishlist_change_price(L: 'list of Dish', n: float) -> 'list of Dish':
    '''Return the list given with all Dishes' prices changed by percent given'''
    result = []
    for i in L:
        result += [Dish_change_price(i, n)]
    return result
assert Dishlist_change_price([d1, d2], -50) == [d1._replace(price=1.25),
                                                d2._replace(price=5.00)]
assert Dishlist_change_price([d1, d3], 100) == [d1._replace(price=5.00),
                                                d3._replace(price=11.98)]

# Part (c.9)
def Dishlist_prices(L: 'list of Dish') -> 'list of float':
    '''Return a list of the prices of the Dishes given'''
    result = []
    for i in L:
        result += [i.price]
    return result
assert Dishlist_prices(DL2) == [45.99, 3.00, 1.50, 7.99]
assert Dishlist_prices(DL[0:2]) == [2.50, 10.00]
    
# Part (c.10)
def Dishlist_average(L: 'list of Dish') -> float:
    '''Return the average price of the Dishes given'''
    total = 0
    for i in Dishlist_prices(L):
        total += i
    return total/len(L)
assert Dishlist_average(DL[0: 5]) == 11.198
assert Dishlist_average([DL[0]]) == 2.50

# Part (c.11)
def Dishlist_keep_cheap(L: 'list of Dish', n: float) -> 'list of Dish':
    '''Return a list of the dishes whose prices are less than the number given'''
    result = []
    for i in L:
        if Dish_is_cheap(i, n):
            result += [i]
    return result
assert Dishlist_keep_cheap(DL, 3) == [DL[0], DL[7]]
assert Dishlist_keep_cheap(DL, 50) == DL
    
# Part (c.12)
DL_big = [Dish('burger', 2.50, 1000),
          Dish('pizza', 10.00, 750),
          Dish('burger', 5.99, 1000),
          Dish('kabob', 12.50, 400),
          Dish('steak', 25.00, 725),
          Dish('crab', 45.99, 560),
          Dish('sandwich', 3.00, 200),
          Dish('yogurt', 1.50, 120),
          Dish('soup', 7.99, 460),
          Dish('rice', 1.25, 75),
          Dish('macaroni', 2.00, 330),
          Dish('chicken', 11.99, 620),
          Dish('fries', 0.99, 400),
          Dish('eggs', 4.99, 450),
          Dish('pancakes', 6.00, 370),
          Dish('waffles', 6.50, 500),
          Dish('salad', 2.99, 40),
          Dish('salmon', 16.00, 200),
          Dish('cake', 4.75, 560),
          Dish('sandwich', 0.99, 100),
          Dish('soup', 4.99, 390),
          Dish('crab', 39.99, 510),
          Dish('pancakes', 2.50, 250),
          Dish('pizza', 14.99, 830),
          Dish('cake', 3.99, 540)]
def before_and_after() -> None:
    '''Print the Dishlist_display for the list before and after the price change'''
    percent = float(input('Enter a number: '))
    print('List before price change:\n')
    print(Dishlist_display(DL_big))
    print('List after price change:\n')
    print(Dishlist_display(Dishlist_change_price(DL_big, percent)))
before_and_after()

print()

#
# Part (e)
#
Restaurant = namedtuple('Restaurant', 'name cuisine phone menu')
r1 = Restaurant('Thai Dishes', 'Thai', '334-4433', [Dish('Mee Krob', 12.50, 500),
                                                    Dish('Larb Gai', 11.00, 450)])
r2 = Restaurant('Taillevent', 'French', '01-44-95-15-01', 
				[Dish('Homard Bleu', 45.00, 750),
				 Dish('Tournedos Rossini', 65.00, 950),
				 Dish("Selle d'Agneau", 60.00, 850)])	
# Part (e.1)
r3 = Restaurant('Pascal', 'French', '940-752-0107', [Dish('Escargot', 12.95, 250),
                                                     Dish('Poached Salmon', 18.50, 550),
                                                     Dish('Rack of Lamb', 24.00, 850),
                                                     Dish('Marjolaine Cake', 8.50, 950)])
# Part (e.2)
def Restaurant_first_dish_name(r: Restaurant) -> str:
    '''Return the first dish in a Restaurant's menu'''
    if len(r.menu) == 0:
        return ''
    return r.menu[0].name
assert Restaurant_first_dish_name(Restaurant('Name', 'Cuisine', 'Phone', [])) == ''
assert Restaurant_first_dish_name(r3) == 'Escargot'
assert Restaurant_first_dish_name(r1) == 'Mee Krob'

# Part (e.3)
def Restaurant_is_cheap(r: Restaurant, n: float) -> bool:
    '''Return True if the Restaurant's menu's average price is less than the price given'''
    if Dishlist_average(r.menu) < n:
        return True
    return False
assert Restaurant_is_cheap(r3, 16)
assert not Restaurant_is_cheap(r3, 15.90)
assert not Restaurant_is_cheap(r1, 0)

# Part (e.4)
Collection = [r1, r2, r3]
def Dish_raise_price(d: Dish) -> Dish:
    '''Raise a dish's price by $2.50'''
    return Dish(d.name, d.price + 2.50, d.calories)
assert Dish_raise_price(d1) == Dish(d1.name, 5, d1.calories)
assert Dish_raise_price(d2) == Dish(d2.name, 12.50, d2.calories)

def Menu_raise_prices(m: list) -> list:
    '''Raise a menu's dishes' prices by $2.50'''
    result = []
    for d in m:
        result += [Dish_raise_price(d)]
    return result
assert Menu_raise_prices([d1, d2]) == [Dish(d1.name, 5, d1.calories),
                                       Dish(d2.name, 12.50, d2.calories)]

def Restaurant_raise_prices(r: Restaurant) -> Restaurant:
    '''Raise a Restaurant's dishes' prices by $2.50'''
    return Restaurant(r.name, r.cuisine, r.phone, Menu_raise_prices(r.menu))
assert Restaurant_raise_prices(r1) == Restaurant('Thai Dishes', 'Thai', '334-4433', [Dish('Mee Krob', 15.00, 500),
                                                                                     Dish('Larb Gai', 13.50, 450)])

def Collection_raise_prices(C: list) -> list:
    '''Raise every dish's price by $2.50 in each Restaurant in the Collection'''
    result = []
    for r in C:
        result += [Restaurant_raise_prices(r)]
    return result
assert Collection_raise_prices([r1, r2]) == [Restaurant('Thai Dishes', 'Thai', '334-4433', [Dish('Mee Krob', 15.00, 500),
                                                                                            Dish('Larb Gai', 13.50, 450)]),
                                             Restaurant('Taillevent', 'French', '01-44-95-15-01', [Dish('Homard Bleu', 47.50, 750),
                                                                                                   Dish('Tournedos Rossini', 67.50, 950),
                                                                                                   Dish("Selle d'Agneau", 62.50, 850)])]

def Menu_change_price(m: list, n: float) -> list:
    '''Raise a Menu's prices by the percentage given'''
    result = []
    for d in m:
        result += [Dish_change_price(d, n)]
    return result
assert Menu_change_price([d1, d2], 100) == [Dish(d1.name, 5, d1.calories),
                                            Dish(d2.name, 20, d2.calories)]

def Restaurant_change_price(r: Restaurant, n: float) -> Restaurant:
    '''Raise the Restaurant's prices by the percentage given'''
    return Restaurant(r.name, r.cuisine, r.phone, Menu_change_price(r.menu, n))
assert Restaurant_change_price(r1, -50) == Restaurant('Thai Dishes', 'Thai', '334-4433', [Dish('Mee Krob', 6.25, 500),
                                                                                          Dish('Larb Gai', 5.50, 450)])

def Collection_change_price(C: list, n: float) -> list:
    '''Return the Collection with all Dish prices changed by the percentage given'''
    result = []
    for r in C:
        result += [Restaurant_change_price(r, n)]
    return result
assert Collection_change_price([r1, r2], 100) == [Restaurant('Thai Dishes', 'Thai', '334-4433', [Dish('Mee Krob', 25, 500),
                                                                                                 Dish('Larb Gai', 22, 450)]),
                                                  Restaurant('Taillevent', 'French', '01-44-95-15-01', [Dish('Homard Bleu', 90, 750),
                                                                                                   Dish('Tournedos Rossini', 130, 950),
                                                                                                   Dish("Selle d'Agneau", 120, 850)])]
                      
# Part (e.5)
def Collection_select_cheap(C: list, n: float) -> list:
    '''Return a list of Restaurants whose average price of Dishes is less than the number given'''
    result = []
    for r in C:
        if Restaurant_is_cheap(r, n):
            result += [r]
    return result
assert Collection_select_cheap(Collection, 100) == Collection
assert Collection_select_cheap(Collection, 40) == [r1, r3]

#
# Part (g)
#
Count = namedtuple('Count', 'letter number')
def single_count(s: str, char: str) -> Count:
    '''Return a Count with the single character's occurences in the message'''
    return Count(char, s.count(char))
assert single_count('hello', 'l') == Count('l', 2)
assert single_count('This \n is \n white \n space.', '\n') == Count('\n', 3)

def letter_count(s: str, code: str) -> list:
    '''Return a list of Counts that show the number of occurences of each character in the message'''
    result = []
    for i in code:
        result += [single_count(s, i)]
    return result
assert letter_count('The cabbage has baggage', 'abcd') == [Count('a',5),
                                                           Count('b',3),
                                                           Count('c',1),
                                                           Count('d',0)]
assert letter_count('AAAAAAaaaaaa', 'Aa') == [Count('A',6),
                                              Count('a',6)]
        
    
    
    
