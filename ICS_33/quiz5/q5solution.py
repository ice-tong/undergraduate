def compare(a,b):
    if a == '' and b != '':
        return '<'
    if a != '' and b == '':
        return '>'
    if a == '' and b == '':
        return '='
    else:
        if a[0] == b[0]:
            return compare(a[1:], b[1:])
        elif a[0] > b[0]:
            return '>'
        else:
            return '<'


def get_assoc(assoc : ((object,object),), key : object) -> object:
    if assoc == ():
        raise KeyError
    elif assoc[0][0] == key:
        return assoc[0][1]
    else:
        return get_assoc(assoc[1:], key)


def del_assoc(assoc : ((object,object),), key : object) -> ((object,object),):
    if assoc == ():
        raise KeyError
    elif assoc[0][0] == key:
        return assoc[1:]
    else:
        return assoc[:1] + del_assoc(assoc[1:], key)
    

def set_assoc(assoc : ((object,object),), key : object, value: object) -> ((object,object),):
    if assoc == ():
        return ((key, value),)
    elif assoc[0][0] == key:
        return ((key, value),) + assoc[1:]
    else:
        return assoc[:1] + set_assoc(assoc[1:], key, value)
    


def immutify(a : 'an int, str, tuple, list, set, frozenset or dict') -> 'an int, str, tuple, or forzenset':
    if type(a) in {int, str, frozenset}:
        return a
    elif type(a) is set:
        return frozenset(a)
    elif type(a) is dict:
        return tuple([(k,immutify(v)) for k,v in sorted(a.items())])
    elif type(a) in {list, tuple}:
        if len(a) == 0:
            return ()
        else:
            return (immutify(a[0]),) + immutify(a[1:])
    else:
        raise TypeError

        
    



if __name__=="__main__":
    import driver
    
    print('Testing compare')
    print('',      compare('',''),          '')
    print('',      compare('','abc'),       'abc')
    print('abc',   compare('abc',''),       '')
    print('abc',   compare('abc','abc'),    'abc')
    print('bc',    compare('bc','abc'),     'abc')
    print('abc',   compare('abc','bc'),     'bc')
    print('aaaxc', compare('aaaxc','aaabc'), 'aaabc')
    print('aaabc', compare('aaabc','aaaxc'), 'aaaxc')
     
    print('\nTesting get_assoc')
    assoc = ( ('a',1), ('c',3), ('d',4), ('b',2) )
    print(get_assoc(assoc, 'a'))
    print(get_assoc(assoc, 'b'))
    print(get_assoc(assoc, 'c'))
    print(get_assoc(assoc, 'd'))
    try:
        print(get_assoc(assoc, 'x'))
    except KeyError:
        print('Correctly raised exception on bad key')

    print('\nTesting del_assoc')
    assoc = ( ('a',1), ('c',3), ('d',4), ('b',2) )
    assoc = del_assoc(assoc,'b')
    print('assoc now =', assoc)
    try:
        assoc = del_assoc(assoc, 'x')
    except KeyError:
        print('Correctly raised exception on bad key')
    assoc = del_assoc(assoc,'a')
    print('assoc now =', assoc)
    assoc = del_assoc(assoc,'c')
    print('assoc now =', assoc)
    assoc = del_assoc(assoc,'d')
    print('assoc now =', assoc)

    print('\nTesting set_assoc')
    assoc = ()
    assoc = set_assoc(assoc,'b', 2)
    print('assoc now =', assoc)
    assoc = set_assoc(assoc,'a',1)
    print('assoc now =', assoc)
    assoc = set_assoc(assoc,'c',3)
    print('assoc now =', assoc)
    assoc = set_assoc(assoc,'d',4)
    print('assoc now =', assoc)
    assoc = set_assoc(assoc,'b',102)
    print('assoc now =', assoc)
    assoc = set_assoc(assoc,'c',103)
    print('assoc now =', assoc)
    assoc = set_assoc(assoc,'d',104)
    print('assoc now =', assoc)

    print('\nTesting immutify')
    print( immutify(1) )
    print( immutify('a') )
    print (immutify( (1, 2, 3)) )
    print (immutify( frozenset([1, 2, 3])) )
    print( immutify( [1, 2, 3, 4, 5, 6]) )
    print( immutify( [1, 2, [3, [4], 5], 6]) )
    print( immutify( [1, 2, (3, [4], 5), 6]) )
    print( immutify( [{1,2}, {3,frozenset([4,5])}, {6,7}]))
    print( immutify( [{1,2}, {3,frozenset([4,5])}, [{5,6}]]))
    print( immutify( {'b' : [1,2], 'a' : {'ab': {1,2}, 'aa' : (1,2)}}) )
    

    driver.default_file_name = 'bscq5W18.txt'
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
    
