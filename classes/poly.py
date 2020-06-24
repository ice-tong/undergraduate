# Submitter: kfarsany(Farsany, Kian)

from inspect import stack


class Poly:
    def __init__(self, *args):
        powers = []
        self.terms = dict()
        for a in args:
            assert type(a) == tuple and len(a) == 2, str(a)+' is not a 2-tuple'
            assert type(a[0]) in {int,float}, 'illegal coefficient in term: '+str(a)
            assert type(a[1]) == int and a[1] >= 0, 'illegal power in term: '+str(a)
            if a[0] != 0:
                assert a[1] not in self.terms, 'powers not in decreasing order'
                powers.append(a[1])
                self.terms[a[1]] = a[0]
        assert powers == sorted(powers, reverse=True), 'powers not in decreasing order'
        
    def __repr__(self):
        return f"Poly({str([term for term in self]).strip('[]')})"
    
    def __str__(self):
        if len(self.terms) == 0:
            return '0'
        result = ''
        for c,p in self:
            if p >= 2:
                result += f'{c}x^{p} + '
            elif p == 1:
                result += f'{c}x + '
            elif p == 0:
                result += f'{c} + '
        return result[:-3].replace('+ -','- ').replace('1x','x').replace('1.0x','x')
        
    
    def __bool__(self):
        return self.__str__() != '0'
    
    def __len__(self):
        if not self:
            return 0
        return max(self.terms)
    
    def __call__(self, x):
        return sum([c*(x**p) for p,c in self.terms.items()])
    
    def __iter__(self):
        def gen(poly):
            for p,c in sorted(poly.items(), reverse=True):
                yield (c, p)
        return gen(dict(self.terms))
    
    def __getitem__(self, p):
        if type(p) != int or p < 0:
            raise TypeError(f'item {p} not valid power')
        
        if p not in self.terms:
            return 0
        return self.terms[p]
    
    def __setitem__(self, p, c):
        if type(p) != int or p < 0:
            raise TypeError(f'item {p} not valid power')
        
        if c == 0:
            if p in self.terms:
                del self.terms[p]
        else:
            self.terms[p] = c
            
    def __delitem__(self, p):
        if type(p) != int or p < 0:
            raise TypeError(f'item {p} not valid power')
        
        if p in self.terms:
            del self.terms[p]
            
    def _add_term(self, c, p):
        if type(p) != int or p < 0:
            raise TypeError(f'arg {p} not valid power')
        if type(c) not in {int,float}:
            raise TypeError(f'arg {c} not valid coefficient')
        
        if p not in self.terms:
            if c != 0:
                self.terms[p] = c
        else:
            self.terms[p] += c
            if self.terms[p] == 0:
                del self.terms[p] 
            
    def __pos__(self):
        return Poly(*(term for term in self))
    
    def __neg__(self):
        return Poly(*((-c, p) for c,p in self))
    
    def __abs__(self):
        return Poly(*((abs(c), p) for c,p in self))
    
    def differentiate(self):
        return Poly(*((c*p, p-1) for c,p in self if p >= 1))
    
    def integrate(self, c=0):
        return Poly(*( (c/(p+1), p+1) for c,p in self ), (c, 0))
    
    def def_integrate(self, v1, v2):
        integ_poly = self.integrate()
        return integ_poly(v2) - integ_poly(v1)
    
    def __add__(self, i):
        if type(i) not in {Poly, int, float}:
            raise TypeError(f"unsupported operand type(s) for +: 'Poly' and '{type(i)}'")
        result = Poly()
        if type(i) in {int, float}:
            i = Poly((i, 0))
        for c,p in i:
            result._add_term(c,p)
        for c,p in self:
            result._add_term(c,p)
        return result
    
    def __radd__(self, i):
        return Poly.__add__(self, i)
    
    def __sub__(self, i):
        if type(i) not in {Poly, int, float}:
            raise TypeError(f"unsupported operand type(s) for -: 'Poly' and '{type(i)}'")
        return Poly.__add__(self, -i)
    
    def __rsub__(self, i):
        if type(i) not in {Poly, int, float}:
            raise TypeError(f"unsupported operand type(s) for -: 'Poly' and '{type(i)}'")
        return Poly.__add__(-self, i)
    
    def __mul__(self, i):
        if type(i) not in {Poly, int, float}:
            raise TypeError(f"unsupported operand type(s) for *: 'Poly' and '{type(i)}'")
        result = Poly()
        if type(i) in {float, int}:
            i = Poly((i, 0))
        for c1, p1 in self:
            for c2, p2 in i:
                result._add_term(c1*c2, p1+p2)
        return result
    
    def __rmul__(self, i):
        return Poly.__mul__(self, i)
    
    def __pow__(self, i):
        if type(i) != int or i < 0:
            raise TypeError(f"unsupported operand type(s) for **: 'Poly' and '{type(i)}'")
        if i == 0:
            return Poly((1,0))
        elif i == 1:
            return Poly.__pos__(self)
        result = Poly.__mul__(self, self)
        for p in range(i-2):
            result = Poly.__mul__(result, self)
        return result
    
    def __eq__(self, i):
        if type(i) not in {Poly, int, float}:
            raise TypeError(f"unsupported operand type(s) for ==: 'Poly' and '{type(i)}'")
        if type(i) in {int, float}:
            i = Poly((i,0))
        return self.terms == i.terms
    
    def __lt__(self, i):
        if type(i) not in {Poly, int, float}:
            raise TypeError(f"< not supported between instances of 'Poly' and '{type(i)}'")
        if type(i) in {int, float}:
            i = Poly((i,0))
        if len(self) == len(i):
            return self[len(self)] < i[len(i)]
        return len(self) < len(i)
    
    def __gt__(self, i):
        if type(i) not in {Poly, int, float}:
            raise TypeError(f"> not supported between instances of 'Poly' and '{type(i)}'")
        if type(i) in {int,float}:
            i = Poly((i,0))
        return Poly.__lt__(i, self)
    
    def __le__(self, i):
        if type(i) not in {Poly, int, float}:
            raise TypeError(f"<= not supported between instances of 'Poly' and '{type(i)}'")
        if type(i) in {int, float}:
            i = Poly((i,0))
        if len(self) == len(i):
            return self[len(self)] <= i[len(i)]
        return len(self) <= len(i)
    
    def __ge__(self, i):
        if type(i) not in {Poly, int, float}:
            raise TypeError(f">= not supported between instances of 'Poly' and '{type(i)}'")
        if type(i) in {int,float}:
            i = Poly((i,0))
        return Poly.__le__(i, self)
    
    def __setattr__(self, name, value):
        calling = stack()[1]
        assert calling.function == '__init__', 'class Poly is immutable'
        assert calling.frame.f_code is Poly.__dict__['__init__'].__code__, 'class Poly is immutable'
        self.__dict__[name] = value
        
if __name__ == '__main__':
    #Simple tests before running driver
    #Put your own test code here to test Poly before doing bsc tests

    """print('Start of simple tests')
    p = Poly((3,2),(-2,1),(4,0))
    print('  For Polynomial: 3x^2 - 2x + 4')
    print('  str(p):',p)
    print('  repr(p):',repr(p))
    print('  len(p):',len(p))
    print('  p(2):',p(2))
    print('  list collecting the iterator results:', [t for t in p])
    print('  p+p:',p+p)
    print('  p+2:',p+2)
    print('  p*p:',p*p)
    print('  p*2:',p*2)
    print('End of simple tests\n\n')"""
    
    import driver
    driver.default_file_name = 'bscp22W18.txt'
#     driver.default_show_exception= True
#     driver.default_show_exception_message= True
#     driver.default_show_traceback= True
    driver.driver()     
