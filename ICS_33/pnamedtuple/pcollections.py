# Submitter: kfarsany(Farsany, Kian)

import re, traceback, keyword

def pnamedtuple(type_name, field_names, mutable=False):
    def show_listing(s):
        for aline,its_text in enumerate(s.split('\n'), 1):
            print(f' {aline: >3} {its_text.rstrip()}')

    # put your code here
    legal_name = re.compile('^[a-zA-Z]\w*$')
    if type_name in keyword.kwlist:
        raise SyntaxError('Class name cannot be Python keyword')
    if type(type_name) is not str or re.match(legal_name, type_name) == None:
        raise SyntaxError('Class name does not match proper format')
    
    def unique(iterable):
        iterated = set()
        for i in iterable:
            if i not in iterated:
                iterated.add(i)
                yield i
    
    if type(field_names) not in {str, list}:
        raise SyntaxError('field names must be placed in str or list')
    if type(field_names) is str:
        field_names = field_names.replace(',', ' ').strip().split()
    filtered_fields = []
    for name in unique(field_names):
        if name in keyword.kwlist:
            raise SyntaxError(f'{name} cannot be Python keyword')
        if re.match(legal_name, name) == None:
            raise SyntaxError(f'{name} does not match proper format')
        filtered_fields.append(name)
    field_names = filtered_fields

    def gen_init(fields: [str]) -> str:
        result = "def __init__(self"
        for field in fields:
            result += f', {field}'
        result += '):\n        '
        for field in fields:
            result += f'self.{field} = {field}\n        '
        result += f'self._fields = {fields}\n        '
        result += f'self._mutable = {mutable}\n'
        return result
    
    def gen_repr(fields: [str]) -> str:
        result = "def __repr__(self):\n        "
        result += f"return '{type_name}("
        result += ','.join([field+'={'+field+'}'  for field in fields]) + ")'.format("
        result += ','.join([f'{field}=self.{field}' for field in fields]) + ')\n'
        return result
    
    def gen_getters(fields: [str]) -> str:
        result = ""
        for field in fields:
            result += f'def get_{field}(self):\n        '
            result += f'return self.{field}\n\n    '
        return result[:-5]
    
    
    # bind class_definition (used below) to the string constructed for the class
    class_definition = f'''\
class {type_name}:
    {gen_init(field_names)}
    
    {gen_repr(field_names)}
    
    {gen_getters(field_names)}
    
    def __getitem__(self, value):
        if type(value) is int:
            if value >= len(self._fields):
                raise IndexError
            return eval('self.get_' + self._fields[value] + '()')
        elif type(value) is str:
            if value not in self._fields:
                raise IndexError
            return eval('self.get_' + value + '()')
        raise IndexError
        
    def __eq__(self, i):
        if type(i) == type(self) and i._fields == self._fields:
            for x in range(len(i._fields)):
                if self.__getitem__(x) != i.__getitem__(x):
                    return False
            return True
        return False
        
    def _replace(self, **kargs):
        for k in kargs:
            if k not in self._fields:
                raise TypeError
        if self._mutable:
            for k,v in kargs.items():
                self.__dict__[k] = v
            return None
        else:
            result = dict()
            for field in self._fields:
                if field in kargs:
                    result[field] = kargs[field]
                else:
                    result[field] = eval('self.get_' + field + '()')
            return {type_name}(**result)'''
    
        

    # For initial debugging, remove comment to show the source code for the clas
    # show_listing(class_definition)
    
    # Execute the class_definition string in a local name space; later, bind the
    #   source_code name in its dictionary to the class_defintion; return the
    #   class object created; if there is a syntax error, list the class and
    #   also show the error
    name_space = dict(__name__ =  f'pnamedtuple_{type_name}')
    try:
        exec(class_definition,name_space)
        name_space[type_name].source_code = class_definition
    except [TypeError, SyntaxError]:
        show_listing(class_definition)
        traceback.print_exc()
    return name_space[type_name]


    
if __name__ == '__main__':
    # Test pnamedtuple in script below using Point = pnamedtuple('Point', 'x y')

    #driver tests
    import driver
    driver.default_file_name = 'bscp3W18.txt'
#     driver.default_show_exception= True
#     driver.default_show_exception_message= True
#     driver.default_show_traceback= True
    driver.driver()
