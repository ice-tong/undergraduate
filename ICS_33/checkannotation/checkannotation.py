# Submitter: kfarsany(Farsany, Kian)

from goody import type_as_str
import inspect

class Check_All_OK:
    """
    Check_All_OK class implements __check_annotation__ by checking whether each
      annotation passed to its constructor is OK; the first one that
      fails (by raising AssertionError) prints its problem, with a list of all
      annotations being tried at the end of the check_history.
    """
       
    def __init__(self,*args):
        self._annotations = args
        
    def __repr__(self):
        return 'Check_All_OK('+','.join([str(i) for i in self._annotations])+')'

    def __check_annotation__(self, check, param, value,check_history):
        for annot in self._annotations:
            check(param, annot, value, check_history+'Check_All_OK check: '+str(annot)+' while trying: '+str(self)+'\n')


class Check_Any_OK:
    """
    Check_Any_OK implements __check_annotation__ by checking whether at least
      one of the annotations passed to its constructor is OK; if all fail 
      (by raising AssertionError) this classes raises AssertionError and prints
      its failure, along with a list of all annotations tried followed by the
      check_history.
    """
    
    def __init__(self,*args):
        self._annotations = args
        
    def __repr__(self):
        return 'Check_Any_OK('+','.join([str(i) for i in self._annotations])+')'

    def __check_annotation__(self, check, param, value, check_history):
        failed = 0
        for annot in self._annotations: 
            try:
                check(param, annot, value, check_history)
            except AssertionError:
                failed += 1
        if failed == len(self._annotations):
            assert False, repr(param)+' failed annotation check(Check_Any_OK): value = '+repr(value)+\
                         '\n  tried '+str(self)+'\n'+check_history                 



class Check_Annotation:
    # setting the class attribute on the next line to True allows checking to occue
    checking_on = True
  
    # self._checking_on must be True too, for function checking to occur 
    def __init__(self, f):
        self._f = f
        self._checking_on = True
        
    # Check whether param's annot is correct for value, adding to check_history
    #    if recurs; defines many local function which use it parameters.  
    def check(self,param,annot,value,check_history=''):
        generic_assert = "{} failed annotation check(wrong type): value = {}\n"
        generic_assert += "  was type {} ...should be type {}"
        
        # Define local functions for checking, list/tuple, dict, set/frozenset,
        #   lambda/functions, and str (str for extra credit)
        def check_list_tuple():
            assert isinstance(value, type(annot)), \
            generic_assert.format(repr(param), repr(value),
                                  type_as_str(value), type_as_str(annot)) + '\n' + check_history
            
            if len(annot) == 1:
                for i in range(len(value)):
                    self.check(param, annot[0], value[i], 
                               check_history + f'{type_as_str(value)}[{i}] check: {annot[0]}\n')      
            else:
                assert len(annot) == len(value), \
                f"{repr(param)} failed annotation check(wrong number of elements): value = {value}\n\
  annotation had {len(annot)} elements{annot}\n" + check_history
                for i in range(len(annot)):
                    self.check(param, annot[i], value[i], 
                               check_history + f'{type_as_str(value)}[{i}] check: {annot[i]}\n')
                    
        def check_dict():
            assert isinstance(value, dict), \
            generic_assert.format(repr(param), repr(value),
                                  type_as_str(value), 'dict') + '\n' + check_history
            assert len(annot) == 1, \
            f"{repr(param)} annotation inconsistency: dict should have 1 item but had {len(annot)}\n\
  annotation = {annot}\n" + check_history 
            
            for k,v in value.items():
                annot_k, annot_v = list(annot.items())[0]
                self.check(param, annot_k, k,
                           check_history + f'dict key check: {annot_k}')
                self.check(param, annot_v, v,
                           check_history + f'dict value check: {annot_v}')
        
        def check_set():
            assert isinstance(value, type(annot)), \
            generic_assert.format(repr(param), repr(value),
                                  type_as_str(value), type_as_str(annot)) +'\n' + check_history
            assert len(annot) == 1, \
            f"{repr(param)} annotation inconsistency: {type_as_str(annot)} should have 1 value but had {len(annot)}\n\
  annotation = {annot}\n" + check_history
                 
            for v in value:
                annot_v = list(annot)[0]
                self.check(param, annot_v, v,
                           check_history + f'{type_as_str(annot)} value check: {annot_v}')
        
        def check_lambda():
            params = annot.__code__.co_varnames
            assert len(params) == 1, \
            f"{repr(param)} annotation inconsistency: predicate should have 1 parameter but had {len(params)}\n\
  predicate = {annot}\n" + check_history
            try:
                annot(value)
            except Exception as error:
                raise AssertionError(f"{repr(param)} annotation predicate({annot}) raised exception\n\
  exception = {type_as_str(error)}: {error}\n" + check_history)
            else:
                assert annot(value) != False, \
                f"{repr(param)} failed annotation check: value = {value}\n  predicate = {annot}\n" + check_history

            
        # Decode function's annotation below; check it against arguments
        if annot == None:
            pass
        elif type(annot) is type:
            assert isinstance(value, annot), \
            generic_assert.format(repr(param), repr(value),
                                  type_as_str(value), str(annot)[8:-2]) + '\n' + check_history  
        elif isinstance(annot, list) or isinstance(annot, tuple):
            check_list_tuple()
        elif isinstance(annot, dict):
            check_dict()
        elif isinstance(annot, set) or isinstance(annot, frozenset):
            check_set()
        elif inspect.isfunction(annot):
            check_lambda()
        else:
            try:
                annot.__check_annotation__()
            except AttributeError:
                raise AssertionError(f"{repr(param)} annotation undecipherable: {repr(annot)}\n" + check_history)
            except:
                raise AssertionError()
                
            
    # Return result of calling decorated function call, checking present
    #   parameter/return annotations if required
    def __call__(self, *args, **kargs):
        
        # Return a dictionary of the parameter/argument bindings (actually an
        #    ordereddict, whose parameters are in the function header, in order)
        def param_arg_bindings():
            f_signature  = inspect.signature(self._f)
            bound_f_signature = f_signature.bind(*args,**kargs)
            for param in f_signature.parameters.values():
                if not (param.name in bound_f_signature.arguments):
                    bound_f_signature.arguments[param.name] = param.default
            return bound_f_signature.arguments

        # If annotation checking is turned off at the class or function level
        #   just return the result of calling the decorated function
        if not (self._checking_on or Check_Annotation.checking_on):
            return self._f(*args, **kargs)
        
        # Otherwise do all the annotation checking
        try:
            param_dict = param_arg_bindings()
            # Check the annotation for every parameter (if there is one)
            for p,v in param_dict.items():
                self.check(p, self._f.__annotations__[p], v)
            
            # Compute/remember the value of the decorated function
            result = self._f(*args, **kargs)
            
            # If 'return' is in the annotation, check it
            if 'return' in self._f.__annotations__:
                param_dict['_return'] = result
                self.check('return', self._f.__annotations__['return'], result)
                
            # Return the decorated answer
            return result
            
        # On first AssertionError, print the source lines of the function and reraise 
        except AssertionError:
        #     print(80*'-')
        #     for l in inspect.getsourcelines(self._f)[0]: # ignore starting line #
        #     print(l.rstrip())
        #     print(80*'-')
            raise




  
if __name__ == '__main__':     
        
    import driver
    
    #driver.default_show_exception = True
    #driver.default_show_exception_message = True
    #driver.default_show_traceback = True
    
    driver.driver()
    
    
