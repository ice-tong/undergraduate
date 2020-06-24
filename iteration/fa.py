# Submitter: kfarsany(Farsany, Kian)

import goody


def read_fa(file : open) -> {str:{str:str}}:
    fa = dict()
    for line in file:
        line_split = line.strip('\n').split(';')
        key_value_pairs = list(zip(line_split[1::2], line_split[2::2]))
        fa[line_split[0]] = dict(key_value_pairs)
    return fa
        
        
def fa_as_str(fa : {str:{str:str}}) -> str:
    result = ""
    for state in sorted(fa):
        result += f'  {state} transitions: {sorted(list(fa[state].items()))}\n'
    return result

    
def process(fa : {str:{str:str}}, state : str, inputs : [str]) -> [None]:
    result = [state]
    for inp in inputs:
        try:
            transitions_dict = fa[state]
            state = transitions_dict[inp]
            result.append((inp, state))
        except KeyError:
            result.append((inp, None))
    return result
        

def interpret(fa_result : [None]) -> str:
    result = 'Start state = ' + str(fa_result[0]) + '\n'
    for transition in fa_result[1:]:
        if transition[1] == None:
            result += f'  Input = {transition[0]}; illegal input: simulation terminated\n'
            result += 'Stop state = None\n'
            return result
        else:
            result += f'  Input = {transition[0]}; new state = {transition[1]}\n'
    result += f'Stop state = {fa_result[-1][1]}\n'
    return result


if __name__ == '__main__':
    # Write script here
    fa = read_fa(goody.safe_open('Type some file name storing a finite automaton', 
                                 'r', 'Error opening file'))
    print('The Description of read Finite Automaton') 
    print(fa_as_str(fa))
    
    fa_input_file = goody.safe_open('Type some file name storing a start-state with its inputs',
                               'r', 'Error opening file')
    for line in fa_input_file:
        split_line = line.strip('\n').split(';')
        print('Begin tracing a new FA simulation')
        print(interpret(process(fa, split_line[0], split_line[1:]))) 
    # For running batch self-tests
    print()
    import driver
    driver.default_file_name = "bsc3.txt"
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
