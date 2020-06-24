import prompt
from helpers import primes, hide, nth, mini_Backwardable_test, Backwardable_test



def running_count(iterable,p):
    count = 0
    for i in iterable:
        if p(i):
            count += 1
        yield count
        
            
def stop_when(iterable,p):
    for i in iterable:
        if p(i):
            break
        yield i


def yield_and_skip(iterable):
    i = iter(iterable)
    try:
        while True:
            n = next(i)
            yield n
            if type(n) == int:
                for _ in range(n):
                    next(i)
    except StopIteration:
        pass
        

def windows(iterable,n,m=1):
    i = iter(iterable)
    try:
        result = [next(i) for _ in range(n)]
        while True:
            yield result
            result = result[m:]
            for _ in range(m):
                result.append(next(i))
    except StopIteration:
        pass


def alternate(*iterables):
    try:
        _hiddens = [iter(i) for i in iterables]
        while True:
            for _hidden in _hiddens:
                yield next(_hidden)
    except StopIteration:
        pass


def myzip(*iterables):
    _hiddens = [iter(i) for i in iterables]
    while True:
        result = []
        for _hidden in _hiddens:
            try:
                result.append(next(_hidden))
            except StopIteration:
                result.append(None)
        if result == len(_hiddens)*[None]:
            break
        yield tuple(result)
            

class Backwardable:
    def __init__(self,iterable):
        self._iterable = iterable
            
    def __iter__(self):
        class B_iter:
            def __init__(self,iterable):
                self._all      = []
                self._iterator = iter(iterable)
                self._index    = -1 # index of just returned value from __next__ or __prev__
        
            def __str__(self):
                return '_all={}, _index={}'.format(self._all,self._index)
        
            def __next__(self):
                if self._index + 1 == len(self._all):
                    self._all.append(next(self._iterator))
                    self._index += 1
                    return self._all[self._index]
                self._index += 1
                return self._all[self._index]
                
            def __prev__(self):
                assert self._index > 0
                self._index -= 1
                return self._all[self._index]
                
                
            
        return B_iter(self._iterable)

def prev(x): return x.__prev__()





if __name__ == '__main__':
    
    # Test running_count; you can add your own test cases
    print('\nTesting running_count')
    for i in running_count('bananastand',lambda x : x in 'aeiou'): # is vowel
        print(i,end=' ')
    print()
    
    for i in running_count(hide('bananastand'),lambda x : x in 'aeiou'): # is vowel
        print(i,end=' ')
    print()
    
    print(nth(running_count(primes(),lambda x : x%10 == 3),1000))
    
    
    # Test stop_when; you can add your own test cases
    print('\nTesting stop_when')
    for c in stop_when('abcdefghijk', lambda x : x >='d'):
        print(c,end='')
    print()

    for c in stop_when(hide('abcdefghijk'), lambda x : x >='d'):
        print(c,end='')
    print('\n')

    print(nth(stop_when(primes(),lambda x : x > 100000),100))


    # Test group_when; you can add your own test cases
    print('\nTesting yield_and_skip')
    for i in yield_and_skip([1, 2, 1, 3, 'a', 'b', 2, 5, 'c', 1, 2, 3, 8, 'x', 'y', 'z', 2]):
        print(i,end=' ')
    print()
    
    for i in yield_and_skip(hide([1, 2, 1, 3, 'a', 'b', 2, 5, 'c', 1, 2, 3, 8, 'x', 'y', 'z', 2])):
        print(i,end=' ')
    print()

    print(nth(yield_and_skip(primes()),5))
    
    
    # Test windows; you can add your own test cases
    print('\nTesting windows')
    for i in windows('abcdefghijk',4,2):
        print(i,end=' ')
    print()
    
    print('\nTesting windows on hidden')
    for i in windows(hide('abcdefghijk'),4,2):
        print(i,end=' ')
    print()
    
    print(nth(windows(primes(),10,5),20))
    

    # Test alternate; add your own test cases
    print('\nTesting alternate')
    for i in alternate('abcde','fg','hijk'):
        print(i,end='')
    print()
       
    for i in alternate(hide('abcde'), hide('fg'),hide('hijk')):
        print(i,end='')
    print()
       
    for i in alternate(primes(20), hide('fghi'),hide('jk')):
        print(i,end='')
    print()

    print(nth(alternate(primes(),primes()),50))


    # Test myzip; add your own test cases
    print('\nTesting myzip')
    for i in myzip('abcde','fg','hijk'):
        print(i,end='')
    print()
       
    for i in myzip(hide('abcde'), hide('fg'),hide('hijk')):
        print(i,end='')
    print()
       
    for i in myzip(primes(20), hide('fghi'),hide('jk')):
        print(i,end='')
    print('\n')
       
    print(nth(myzip(primes(),primes()),50))

    
       
    
    # Test Backwardable; add your own test cases
    print('\nTesting Backwardable')
    s = 'abcde'
    i = iter(Backwardable(s))
    print(i)
    print(next(i),i) #a
    print(next(i),i) #b
    print(next(i),i) #c
    print(prev(i),i) #b
    print(prev(i),i) #a
    try:
        print(prev(i),i)
    except AssertionError:
        print('Tried to prev before first value')
    print(next(i),i) #b
    print(next(i),i) #c
    print(next(i),i) #d
    print(next(i),i) #d
    try:
        print(next(i),i)
    except StopIteration:
        print('Correctly raised StopIteration')

    # See the mini_Backwardable_test code, which allows you to call
    #  interleaved sequences of next and prev, or quit
    mini_Backwardable_test(iter(Backwardable('abc')))
    mini_Backwardable_test(iter(Backwardable([0,1,2,3,4])))
    mini_Backwardable_test(iter(Backwardable(primes())))
    
    
    import driver
    driver.default_file_name = 'bscq4W18.txt'
#     driver.default_show_exception=True
#     driver.default_show_exception_message=True
#     driver.default_show_traceback=True
    driver.driver()
    
    
