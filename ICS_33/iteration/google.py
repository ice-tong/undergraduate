# Submitter: kfarsany(Farsany, Kian)

import prompt 
from goody       import safe_open,irange
from collections import defaultdict # Use defaultdict for prefix and query


def all_prefixes(fq : (str,)) -> {(str,)}:
    return {fq[:i] for i in irange(len(fq))}


def add_query(prefix : {(str,):{(str,)}}, query : {(str,):int}, new_query : (str,)) -> None:
    for new_prefix in all_prefixes(new_query):
        prefix[new_prefix].add(new_query)
    query[new_query] += 1


def read_queries(open_file : open) -> ({(str,):{(str,)}}, {(str,):int}):
    prefix_dict = defaultdict(set)
    query_dict = defaultdict(int)
    for line in open_file:
        query = tuple(line.strip('\n').split())
        add_query(prefix_dict, query_dict, query)
    return (prefix_dict, query_dict)
    

def dict_as_str(d : {None:None}, key : callable=None, reverse : bool=False) -> str:
    result = ""
    for k in sorted(d.keys(), key=key, reverse=reverse):
        result += f'  {k} -> {d[k]}\n'
    return result


def top_n(a_prefix : (str,), n : int, prefix : {(str,):{(str,)}}, query : {(str,):int}) -> [(str,)]:
    if a_prefix in prefix:
        return sorted([q for q in prefix[a_prefix]], key = lambda x: (-query[x], x))[:n]
    return []


# Script

if __name__ == '__main__':
    # Write script here
    prefix_dict, query_dict = read_queries(safe_open('Type some file name storing the full query',
                                                     'r', 'Error opening file')) 
    while True:    
        print('\nPrefix dictionary:')
        print(dict_as_str(prefix_dict, key = lambda x: (len(x), x)))
        
        print('Query dictionary:')
        print(dict_as_str(query_dict, key = lambda x: (-query_dict[x], x)))
        
        user_prefix = prompt.for_string('Type some prefix sequence (or just quit)')
        if user_prefix == 'quit':
            break
        user_prefix = user_prefix.replace(' ', '')
        print('  Up to 3 (best) matching full queries =',
              top_n(tuple(user_prefix), 3, prefix_dict, query_dict))
        
        user_query = prompt.for_string('\nType some full query sequence (or just quit)')
        if user_query == 'quit':
            break
        user_query = user_query.replace(' ', '')
        add_query(prefix_dict, query_dict, tuple(user_query))
    # For running batch self-tests
    print()
    import driver
    driver.default_file_name = "bsc5.txt"
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
