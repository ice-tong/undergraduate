from goody import irange
from collections import defaultdict


# List Node class and helper functions (to set up problem)

class LN:
    def __init__(self,value,n=None):
        self.value = value
        self.next  = n

def list_to_ll(l):
    if l == []:
        return None
    front = rear = LN(l[0])
    for v in l[1:]:
        rear.next = LN(v)
        rear = rear.next
    return front

def str_ll(ll):
    answer = ''
    while ll != None:
        answer += str(ll.value)+'->'
        ll = ll.next
    return answer + 'None'



# Tree Node class and helper functions (to set up problem)

class TN:
    def __init__(self,value,left=None,right=None):
        self.value = value
        self.left  = left
        self.right = right

def list_to_tree(alist):
    if alist == None:
        return None
    else:
        return TN(alist[0],list_to_tree(alist[1]),list_to_tree(alist[2])) 
    
def str_tree(atree,indent_char ='.',indent_delta=2):
    def str_tree_1(indent,atree):
        if atree == None:
            return ''
        else:
            answer = ''
            answer += str_tree_1(indent+indent_delta,atree.right)
            answer += indent*indent_char+str(atree.value)+'\n'
            answer += str_tree_1(indent+indent_delta,atree.left)
            return answer
    return str_tree_1(0,atree) 


# Define pair_sum ITERATIVELY

def pair_sum(ll):
    if ll == None or ll.next == None:
        return None
    
    front = rear = LN(ll.value + ll.next.value)
    while ll.next.next != None:
        ll = ll.next.next
        if ll.next == None:
            break
        else:
            rear.next = LN(ll.value + ll.next.value)
        rear = rear.next
    return front


# Define pair_sum_r RECURSIVELY

def pair_sum_r(ll):
    if ll == None or ll.next == None:
        return None
    else:
        return LN(ll.value + ll.next.value, 
                  pair_sum_r(ll.next.next))


# Define count RECURSIVELY

def count(t,value):
    if t == None:
        return 0
    else:
        if t.value == value:
            return 1 + count(t.left, value) + count(t.right, value)
        else:
            return count(t.left, value) + count(t.right, value)


# Define the derived bidict using the dict base class

class bidict(dict):
    objects = []
    
    def __init__(self, initial = [], **kargs):
        bidict.objects = initial
        self._rdict = defaultdict(set)
        
        def hashable(o):
            if type(o) is str:
                pass
            elif not hasattr(o, '__hash__') or o.__hash__ == None:
                raise ValueError            
            elif hasattr(o, '__iter__'):
                for i in o:
                    hashable(i)
        for k,v in kargs.items():
            hashable(k)
            hashable(v)
            dict.__setitem__(self, k, v)
            self._rdict[v].add(k)
            
        bidict.objects.append(self)
    
    def __setitem__(self, key, value):
        for v in self._rdict.values():
            if key in v:
                v.remove(key)
        
        temp = self._rdict
        self._rdict = dict()
        for k,v in temp.items():
            if v != set():
                self._rdict[k] = v
        self._rdict[value].add(key)
        dict.__setitem__(self, key, value)
    
    def __delitem__(self, key):
        for v in self._rdict.values():
            if key in v:
                v.remove(key)
        
        temp = self._rdict
        self._rdict = dict()
        for k,v in temp.items():
            if v != set():
                self._rdict[k] = v
        dict.__delitem__(self,key)
                
    def __call__(self, value):
        return dict(self._rdict)[value]
    
    def clear(self):
        dict.clear(self)
        self._rdict.clear()
        
    @staticmethod
    def all_objects():
        return bidict.objects
    
    @staticmethod
    def forget(o):
        bidict.objects.remove(o)
        
        
# Testing Script

if __name__ == '__main__':
    print('Testing pair_sum')
    ll = list_to_ll([])
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(pair_sum(ll)))
    print('original list              = ',str_ll(ll))
    
    ll = list_to_ll([1])
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(pair_sum(ll)))
    print('original list              = ',str_ll(ll))
    
    ll = list_to_ll([1,2])
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(pair_sum(ll)))
    print('original list              = ',str_ll(ll))
    
    ll = list_to_ll([1,2,3,4,5,6,7,8])
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(pair_sum(ll)))
    print('original list              = ',str_ll(ll))
    
    ll = list_to_ll([1,2,3,4,5,6,7,8,9])
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(pair_sum(ll)))
    print('original list              = ',str_ll(ll))
    
    
    # Put in your own tests here


    print('\n\nTesting pair_sum_r')
    ll = list_to_ll([])
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(pair_sum_r(ll)))
    print('original list              = ',str_ll(ll))
    
    ll = list_to_ll([1])
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(pair_sum_r(ll)))
    print('original list              = ',str_ll(ll))
    
    ll = list_to_ll([1,2])
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(pair_sum_r(ll)))
    print('original list              = ',str_ll(ll))
    
    ll = list_to_ll([1,2,3,4,5,6,7,8])
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(pair_sum_r(ll)))
    print('original list              = ',str_ll(ll))
    
    ll = list_to_ll([1,2,3,4,5,6,7,8,9])
    print('\noriginal list              = ',str_ll(ll))
    print('resulting list             = ',str_ll(pair_sum_r(ll)))
    print('original list              = ',str_ll(ll))

    # Put in your own tests here


    print('\n\nTesting count')
    tree = list_to_tree(None)
    print('\nfor tree = \n',str_tree(tree))
    for i in [1]:
        print('count(tree,'+str(i)+') = ', count(tree,i))
          
    tree = list_to_tree([1, [2, None, None], [3, None, None]])
    print('\nfor tree = \n',str_tree(tree))
    for i in irange(1,3):
        print('count(tree,'+str(i)+') = ', count(tree,i))
          
    tree = list_to_tree([3, [2, None, [3, None, None]], [1, [3, None, None], None]])
    print('\nfor tree = \n',str_tree(tree))
    for i in irange(1,3):
        print('count(tree,'+str(i)+') = ', count(tree,i))
          
    tree = list_to_tree([3, [2, [3, None, [2, None, None]], [3, None, None]], [1, [3, None, None], None]])
    print('\nfor tree = \n',str_tree(tree))
    for i in irange(1,3):
        print('count(tree,'+str(i)+') = ', count(tree,i))
          
    # Put in your own tests here


    print('\n\nTesting bidict')
    b1 = bidict(a=1,b=2,c=1)
    print(b1, b1._rdict)
    b1['a']= 2
    print(b1, b1._rdict)
    b1['d']= 2
    print(b1, b1._rdict)
    b1['c']= 2
    print(b1, b1._rdict)
    
    b1.clear()
    print(b1, b1._rdict)
    
    b2 = bidict(a=1,b=2,c=1,d=2)
    del b2['a']
    print(b2, b2._rdict)
    del b2['b']
    print(b2, b2._rdict)
    del b2['c']
    print(b2, b2._rdict)
    del b2['d']
    print(b2, b2._rdict)
    print(b2._rdict)
    
    b3 = bidict(a=1,b=2,c=1,d=2)
    print(b3(1))
    print(b3(2))
    
    print(bidict.all_objects())
    bidict.forget(b2)
    print(bidict.all_objects())
    bidict.forget(b3)
    print(bidict.all_objects())
    bidict.forget(b1)
    print(bidict.all_objects())

    # Put in your own tests here

   
    import driver
    driver.default_file_name = 'bscq6W18.txt'
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    print('\n\n')
    driver.driver()
    
