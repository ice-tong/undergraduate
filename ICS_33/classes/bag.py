# Submitter: kfarsany(Farsany, Kian)

from collections import defaultdict

class Bag:
    def __init__(self, i=[]):
        self.bag = defaultdict(int)
        for key in i:
            self.bag[key] += 1

    def __repr__(self):
        info = []
        for k,v in self.bag.items():
            info.extend(v*[k])
        return f'Bag({info})'

    def __str__(self):
        info = ''
        for k,v in self.bag.items():
            info += f'{k}[{v}],'
        return f'Bag({info[:-1]})'
    
    def __len__(self):
        return sum(self.bag.values())
    
    def unique(self):
        return len(self.bag)
    
    def __contains__(self, i):
        return i in self.bag
    
    def count(self, i):
        if i not in self:
            return 0
        return self.bag[i]
    
    def add(self, i):
        if i in self:
            self.bag[i] += 1
        else:
            self.bag[i] = 1
            
    def __add__(self, i):
        if type(i) != Bag:
            raise TypeError
        info = []
        for k,v in self.bag.items():
            info.extend(v*[k])
        for k,v in i.bag.items():
            info.extend(v*[k])
        return Bag(info)
    
    def remove(self, i):
        if i not in self:
            raise ValueError(str(i)+' not in '+repr(self))
        self.bag[i] -= 1
        if self.bag[i] == 0:
            del self.bag[i]
            
    def __eq__(self, i):
        if type(i) != Bag:
            return False
        return self.bag == i.bag
    
    def __iter__(self):
        def gen(bag):
            for k,v in bag.items():
                for char in k*v:
                    yield char
        return gen(dict(self.bag))
            
    
    
if __name__ == '__main__':
    #driver tests
    import driver
    driver.default_file_name = 'bscp21W18.txt'
#     driver.default_show_exception= True
#     driver.default_show_exception_message= True
#     driver.default_show_traceback= True
    driver.driver()
