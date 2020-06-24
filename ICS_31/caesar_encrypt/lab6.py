#  Kian Farsany 55375951 and Jasper Van 81766836.  ICS 31 Lab sec 8.  Lab asst 6.

#
# Part (c)
#
print("-----Part (c)-----\n")

# Part (c.1)
def contains(s1: str, s2: str) -> bool:
    '''Return True if s2 occurs in s1'''
    return s2 in s1
assert contains('banana', 'ana')
assert not contains('racecar', 'ck')
assert contains('12345', '234')
assert not contains('[][]1D192%', '[][]1d192%')

# Part (c.2)
print('-----Part (c.2)-----')
def sentence_stats(s: str) -> None:
    '''Print the stats of the given string'''
    remove_punct_table = str.maketrans('.,?!:;"*', '        ')
    no_punct = s.translate(remove_punct_table)
    total = 0
    print('Characters:  ', len(no_punct))
    print('Words:  ', len(no_punct.split()))
    for i in no_punct.split():
        total += len(i)
    print('Average word length:  ', total/len(no_punct.split()))
sentence_stats('I love UCI')
print()
sentence_stats('***The ?! quick brown fox:  jumps over the lazy dog.')

print()

# Part (c.3)
def initials(s: str) -> str:
    '''Return the initials of the name given in capital letters'''
    result = ''
    words = s.split()
    for i in words:
        result += i[0].upper()
    return result
assert initials('Bill Cody') == 'BC'
assert initials('Guido van Rossum') == 'GVR'
assert initials('alan turing') == 'AT'
    
#
# Part (d)
#
print("\n-----Part (d)-----\n")
from random import randrange

# Part (d.1)
print('-----Part (d.1)-----')
for i in range(0, 50):
    print(randrange(0, 11), end = ' ')
    
print()

for i in range(0, 50):
    print(randrange(1,7), end = ' ')

print()

# Part (d.2)
print('-----Part (d.2)-----')
def roll2dice() -> int:
    '''Return the result of two randomly tossed dice'''
    return randrange(1, 7) + randrange(1,7)
for i in range(0,50):
    print(roll2dice(), end = ' ')

print()

# Part (d.3)
print('-----Part (d.3)-----')
def distribution_of_rolls(n: int) -> None:
    '''Prints a histogram that shows the distribution of 2 dice being rolled'''
    print('Distribution of dice rolls')
    results = [0] * 11
    for i in range(n):
        results[roll2dice()-2] += 1
    for i in range(0, 11):
        times = results[i]
        percent = (times/float(n)) * 100
        stars = times * '*'
        print('{:2d}: {:5d} ({:4.1f}%)  {}'.format(i+2, times, percent, stars))
    print('-----------------------')
    print('{:10d} rolls'.format(n))
distribution_of_rolls(200)

print()

#
# Part (e)
#
ALPHABET = 'abcdefghijklmnopqrstuvwxyz'
def rotate_alphabet(n: int) -> str:
    '''Rotates the letter by the given number'''
    result = ALPHABET + ALPHABET[0:n]
    return result[n:]
assert rotate_alphabet(2) == 'cdefghijklmnopqrstuvwxyzab'
assert rotate_alphabet(4) == 'efghijklmnopqrstuvwxyzabcd'

def Caesar_encrypt(s: str, n: int) -> str:
    '''Encrypts plaintext with a Caesar cipher'''
    table_lower = str.maketrans(ALPHABET, rotate_alphabet(n%26))
    table_upper = str.maketrans(ALPHABET.upper(), rotate_alphabet(n%26).upper())
    s = s.translate(table_lower)
    return s.translate(table_upper)
assert Caesar_encrypt('hello123$^$%^@', 2) == 'jgnnq123$^$%^@'
assert Caesar_encrypt('WOw', 5) == 'BTb'
assert Caesar_encrypt('WOw', 31) == 'BTb'

def Caesar_decrypt(s: str, n: int) -> str:
    '''Decrypts ciphertext with a Caesar cipher'''
    table_lower = str.maketrans(rotate_alphabet(n%26), ALPHABET)
    table_upper = str.maketrans(rotate_alphabet(n%26).upper(), ALPHABET.upper())
    s = s.translate(table_lower)
    return s.translate(table_upper)
assert Caesar_decrypt('jgnnq123$^$%^@', 2) == 'hello123$^$%^@'
assert Caesar_decrypt('BtB', 5) == 'WoW'
assert Caesar_decrypt('BtB', 31) == 'WoW'

#
# Part (f)
#
print('\n-----Part (f)-----\n')

# Part (f.1)
print('-----Part (f.1)-----')
def print_line_numbers(L: list) -> None:
    '''Prints each string in the list preceded by a line number.'''
    for i in range(len(L)):
        print('{:5d}:  {}'.format(i+1, L[i]))
print_line_numbers([ "Four score and seven years ago, our fathers brought forth on",
                     "this continent a new nation, conceived in liberty and dedicated",
                     "to the proposition that all men are created equal.  Now we are",
                     "   engaged in a great 		civil war, testing whether that nation, or any",
                     "nation so conceived and so dedicated, can long endure.        " ])
print()
print_line_numbers(['Hello',
                    'good',
                    'bye',
                    'wow',
                    'indeed',
                    'AMAZING',
                    'clever',
                    'd2f2f2d32',
                    '       Arduino           ',
                    'ok then'])
print()

# Part (f.2)
print('-----Part (f.2)-----')
def stats(L: list) -> None:
    '''Prints the stats for the strings in the list'''
    lines = len(L)
    empty_lines = 0
    characters = 0
    for s in L:
        if s.isspace() or s == '':
            empty_lines += 1
        characters += len(s)
    print('{:5d}   lines in the list'.format(lines))
    print('{:5d}   empty lines'.format(empty_lines))
    print('{:7.1f} average characters per line'.format(characters/lines))
    print('{:7.1f} average characters per non-empty line'.format(characters/(lines-empty_lines)))    
stats([ "Four score and seven years ago, our fathers brought forth on",
        "this continent a new nation, conceived in liberty and dedicated",
        "to the proposition that all men are created equal.  Now we are",
        "   engaged in a great 		civil war, testing whether that nation, or any",
        "nation so conceived and so dedicated, can long endure.        " ])
print()
stats(['Hello',
       'good',
       'bye',
       'wow',
       '',
       'AMAZ     ING',
       'clever',
       'd2f 2f2d 32',
       '                  ',
       'ok then'])

# Part (f.3)
def list_of_words(L: list) -> list:
    '''Returns a list of the words in a list of strings with punctuation and whitespace removed'''
    result = []
    remove_punct = str.maketrans('.,?!:;*', '       ')
    for s in L:
        result.extend(s.translate(remove_punct).split())
    return result
assert list_of_words(['Hello   hello', '        ', 'This, is a line with , commas!']) == ['Hello', 'hello', 'This',
                                                                                          'is', 'a', 'line', 'with',
                                                                                          'commas']
