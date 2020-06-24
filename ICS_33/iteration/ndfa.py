# Submitter: kfarsany(Farsany, Kian)

import goody
from collections import defaultdict

def read_ndfa(file : open) -> {str:{str:{str}}}:
    ndfa = dict()
    for line in file:
        line_split = line.strip('\n').split(';')
        key_value_pairs = list(zip(line_split[1::2], line_split[2::2]))
        ndfa[line_split[0]] = defaultdict(set)
        for pair in key_value_pairs:
            ndfa[line_split[0]][pair[0]].add(pair[1])
        ndfa[line_split[0]] = dict(ndfa[line_split[0]])
    return ndfa


def ndfa_as_str(ndfa : {str:{str:{str}}}) -> str:
    result = ""
    for state in sorted(ndfa):
        transitions = [(inp, sorted(list(ndfa[state][inp]))) for inp in ndfa[state]]
        result += f'  {state} transitions: {sorted(transitions)}\n'
    return result
       
def process(ndfa : {str:{str:{str}}}, state : str, inputs : [str]) -> [None]:
    result = [state]
    current_states = ndfa[state][inputs[0]]
    result.append((inputs[0], current_states))
    for inp in inputs[1:]:
        new_states = []
        for test_state in current_states:
            if inp in ndfa[test_state]:
                new_states.extend(ndfa[test_state][inp])
        result.append((inp, set(new_states)))
        if len(set(new_states)) == 0:
            return result
        current_states = set(new_states)
    return result


def interpret(result : [None]) -> str:
    result_str = 'Start state = ' + result[0] + '\n'
    for transition in result[1:]:
        result_str += f'  Input = {transition[0]}; new possible states = {sorted(transition[1])}\n'
    result_str += f'Stop state(s) = {sorted(list(result[-1][1]))}\n'
    return result_str



if __name__ == '__main__':
    # Write script here
    ndfa = read_ndfa(goody.safe_open('Type some file name storing a non-deterministic finite automaton', 
                                     'r', 'Error opening file'))
    print('\nThe Description of read Non-Deterministic Finite Automaton') 
    print(ndfa_as_str(ndfa))
    
    ndfa_input_file = goody.safe_open('Type some file name storing a start-state with its inputs',
                                      'r', 'Error opening file')
    print()
    for line in ndfa_input_file:
        split_line = line.strip('\n').split(';')
        print('Begin tracing a new NDFA simulation')
        print(interpret(process(ndfa, split_line[0], split_line[1:])))           
    # For running batch self-tests
    print()
    import driver
    driver.default_file_name = "bsc4.txt"
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
