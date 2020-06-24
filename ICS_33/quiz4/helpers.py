from predicate import is_prime
import prompt
import traceback

# primes is used to test code you write below
def primes(max=None):
    p = 2
    while max == None or p <= max:
        if is_prime(p):
            yield p
        p += 1
         
# Generators must be able to iterate through any iterable.
# hide is present and called to ensure that your generator code works on
#   general iterable parameters (not just a string, list, etc.)
# For example, although we can call len(string) we cannot call
#   len(hide(string)), so the generator functions you write should not
#   call len on their parameters
# Leave hide in this file and add code for the other generators.

def hide(iterable):
    for v in iterable:
        yield v


# A function to return the nth yielded value in iterable (1sth, 2nd, ..etc)
# returns None if the iterable doesn't have n values
# Interesting when iterable is infinite
def nth(iterable, n):
    for i,v in enumerate(iterable,1):
        if i == n:
            return v
    return None


def prev(x): return x.__prev__() # for both tests

def mini_Backwardable_test(i):
    print('\n\nmini_Backwardable_test: enter sequences of next/prev operations (or quit)')
    while True:
        print('\ni =',i)
        command = prompt.for_char('Enter 1-character Command: [n]ext, [p]rev, or [q]uit', legal= 'npq')
        try:
            if command == 'n':
                print(' ',next(i))
            elif command == 'p':
                print(' ',prev(i))
            else:
                break;
        except:
            # Error message may make it look like you cannot continue entering commands, but you can
            print('  command raised exception')
            traceback.print_exc()
 
 
def Backwardable_test(i,seq):
    answer = ''
    for command in seq:
        try:
            if command == 'n':
                answer += str(next(i))
            elif command == 'p':
                answer += str(prev(i))
        except:
            answer += '^'
    return answer       