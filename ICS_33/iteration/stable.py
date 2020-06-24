#Submitter: kfarsany(Farsany, Kian)

import prompt
import goody
from copy import deepcopy
# Use these global variables to index the list associated with each name in the dictionary.
# e.g., if men is a dictionary, men['m1'][match] is the woman who matches man 'm1', and 
# men['m1'][prefs] is the list of preference for man 'm1'.
# It would seems that this list might be better represented as a named tuple, but the
# preference list it contains is mutated, which is not allowed in a named tuple. 

match = 0   # Index 0 of list associate with name is match (str)
prefs = 1   # Index 1 of list associate with name is preferences (list of str)


def read_match_preferences(open_file : open) -> {str:[str,[str]]}:
    result = dict()
    for line in open_file:
        split_line = line.strip('\n').split(';')
        result[split_line[0]] = [None, split_line[1:]]
    return result


def dict_as_str(d : {str:[str,[str]]}, key : callable=None, reverse : bool=False) -> str:
    result = ""
    for person in sorted(d.keys(), key=key, reverse=reverse):
        result += '  ' + person + ' -> ' + str(d[person]) + '\n'
    return result

def who_prefer(order : [str], p1 : str, p2 : str) -> str:
    return [p for p in order if p == p1 or p == p2][0]


def extract_matches(men : {str:[str,[str]]}) -> {(str,str)}:
    return {(m, men[m][match]) for m in men}


def make_match(men : {str:[str,[str]]}, women : {str:[str,[str]]}, trace : bool = False) -> {(str,str)}:
    men_copy = deepcopy(men)
    unmatched_men = set(men_copy.keys())
    if trace:
        print('Women Preferences (unchanging)')
        print(dict_as_str(women))
    while len(unmatched_men) != 0:
        if trace:
            print('Men Preferences (current)')
            print(dict_as_str(men))
            print('unmatched men =', unmatched_men, '\n')
        m = unmatched_men.pop()
        w = men_copy[m][prefs].pop(0)
        w_match = women[w][match]
        if w_match == None:
            men_copy[m][match] = w
            women[w][match] = m
            if trace: 
                print(f'{m} proposes to {w}, who is unmatched and accepts the proposal\n')
        else:
            preference = who_prefer(women[w][prefs], m, w_match)
            if preference == m:
                unmatched_men.add(w_match)
                men_copy[w_match][match] = None
                women[w][match] = m
                men_copy[m][match] = w
                if trace:
                    print(f'{m} proposes to {w}, who is matched and accepts the proposal, rejecting match with {w_match}\n')
            else:
                unmatched_men.add(m)
                if trace:
                    print(f'{m} proposes to {w}, who is matched and rejects the proposal (likes current match better)\n')
    result = extract_matches(men_copy)
    if trace:
        print('algorithm halted: matches =', result)
    return result
    
       
    
if __name__ == '__main__':
    # Write script here
    men_file = goody.safe_open('Type some file name storing preferences of men', 'r',
                               'Error opening file')
    women_file = goody.safe_open('Type some file name storing preferences of women', 'r',
                                 'Error opening file')
    
    men = read_match_preferences(men_file)
    women = read_match_preferences(women_file)
    
    print('Men preferences\n', dict_as_str(men), sep='')
    print('Women preferences\n', dict_as_str(women), sep='')
    
    trace = prompt.for_bool('Trace this Algorithm', default = True)
    matches = make_match(men, women, trace)
    print('matches =', matches)
    
    # For running batch self-tests
    print()
    import driver
    driver.default_file_name = "bsc2.txt"
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
