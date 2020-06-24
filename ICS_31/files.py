#  Kian Farsany 55375951 and Meme Trinh 61748479.  ICS 31 Lab sec 8.  Lab asst 7.

#
# Part (c)
#
from random import randrange

surnames_file = open('surnames.txt', 'r')
femalenames_file = open('femalenames.txt', 'r')
malenames_file = open('malenames.txt', 'r')

surnames = surnames_file.read().split('\n')
femalenames = femalenames_file.read().split('\n')
malenames = malenames_file.read().split('\n')

surnames_file.close()
femalenames_file.close()
malenames_file.close()

def pick_random_name(L: list) -> str:
    '''Picks one random name from a large list of names'''
    index = randrange(0, len(L))
    name = L[index].split()[0]
    return name[0].upper() + name[1:].lower()

def single_random_name() -> str:
    '''Return a single random name with first and last name'''
    choice = randrange(0, 2)
    if choice == 0:
        return pick_random_name(surnames) + ', ' + pick_random_name(femalenames)
    return pick_random_name(surnames) + ', ' + pick_random_name(malenames)

def random_names(n: int) -> list:
    '''Return a list of n random names'''
    result = []
    for i in range(0, n):
        result += [single_random_name()]
    return result

#
# Part (d)
#
ALPHABET = 'abcdefghijklmnopqrstuvwxyz'

wordlist_file = open('wordlist.txt', 'r')
dictionary = wordlist_file.read()
wordlist_file.close()

def rotate_alphabet(n: int) -> str:
    '''Rotates the letter by the given number'''
    result = ALPHABET + ALPHABET[0:n]
    return result[n:]
assert rotate_alphabet(2) == 'cdefghijklmnopqrstuvwxyzab'
assert rotate_alphabet(26) == 'abcdefghijklmnopqrstuvwxyz'

def Caesar_decrypt(s: str, n: int) -> str:
    '''Decrypts ciphertext with a Caesar cipher'''
    table_lower = str.maketrans(rotate_alphabet(n%26), ALPHABET)
    table_upper = str.maketrans(rotate_alphabet(n%26).upper(), ALPHABET.upper())
    s = s.translate(table_lower)
    return s.translate(table_upper)
assert Caesar_decrypt('jgnnq123$^$%^@', 2) == 'hello123$^$%^@'
assert Caesar_decrypt('BtB', 5) == 'WoW'
assert Caesar_decrypt('BtB', 31) == 'WoW'

def strip_punct(s: str) -> str:
    '''Strips whitespace and punctuation from the string'''
    result = ''
    punct = "',.?!:;-()_[]/{}<> "
    for i in s:
        if i not in punct:
            result += i
    return result
assert strip_punct('Hello!?') == 'Hello'
assert strip_punct(',.?!:;-()_[]/{}<> ') == ''
       
def Caesar_break(s: str) -> str:
    '''Deciphers a Caesar ciphertext without the key being provided'''
    ciphers = s.split()
    for i in range(len(ciphers)):
        ciphers[i] = strip_punct(ciphers[i])
    
    highest = 0
    key = 0
    for i in range(26):
        count = 0
        for word in ciphers:
            if Caesar_decrypt(word, i) in dictionary:
                count += 1
        if count >= highest:
            highest = count
            key = i
    return Caesar_decrypt(s, key)
assert Caesar_break('Uijt jt b tfoufodf.') == 'This is a sentence.'
assert Caesar_break('Pdulr nduw lv ixq!!!') == 'Mario kart is fun!!!'

#
# Part (e)
#
print('-----Part (e)-----\n')
def line_numbers(L: list) -> list:
    '''Return the list of lines with numbers added to the front'''
    result = []
    for i in range(len(L)):
        result += '{:5d}:  {}'.format(i+1, L[i])
    return result

def find_start_line(L: list) -> int:
    """Returns the first line index with '*** START' """
    for i in range(len(L)):
        if '*** START' in L[i]:
            return i
    return -1
assert find_start_line(['*** START words', '*** START', '*** start']) == 0
assert find_start_line(['*** start words', '*** START', '*** END']) == 1

def find_end_line(L: list) -> int:
    """Returns the first line index with '*** 'END' """
    for i in range(len(L)):
        if '*** END' in L[i]:
            return i
    return -1
assert find_end_line(['*** END words', '*** END', '*** end']) == 0
assert find_end_line(['*** end words', '*** END', '*** START']) == 1

def stats(L: list) -> str:
    '''Prints the stats for the strings in the list'''
    result = ''
    lines = len(L)
    empty_lines = 0
    characters = 0
    for s in L:
        if s.isspace() or s == '':
            empty_lines += 1
        characters += len(s)
    result += '{:5d}   lines in the file\n'.format(lines)
    result += '{:5d}   empty lines\n'.format(empty_lines)
    result += '{:7.1f} average characters per line\n'.format(characters/lines)
    result += '{:7.1f} average characters per non-empty line'.format(characters/(lines-empty_lines))
    return result

def copy_file(s: str) -> None:
    infile_name = input("Please enter the name of the file to copy: ")
    infile = open(infile_name, 'r', encoding='utf8')
    outfile_name = input("Please enter the name of the new copy:  ")
    outfile = open(outfile_name, 'w', encoding='utf8')

    infile_lines = infile.read().split('\n')
    
    if s == 'line numbers':
        for i in range(len(infile_lines)):
            outfile.write('{:5d}:  {}\n'.format(i+1, infile_lines[i]))
    elif s == 'gutenburg trim':
        start = find_start_line(infile_lines)
        end = find_end_line(infile_lines)
        for line in infile_lines[start+1: end]:
            outfile.write(line + '\n')
    elif s == 'statistics':
        for line in infile_lines:
            outfile.write(line + '\n')
        outfile.write(stats(infile_lines))
        print(stats(infile_lines))
    else:
        for line in infile_lines:
            outfile.write(line + '\n')
    infile.close()
    outfile.close()

copy_file('line numbers')
copy_file('gutenburg trim')
copy_file('statistics')
