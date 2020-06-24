# Submitter: kfarsany(Farsany, Kian)

import prompt
from goody       import safe_open
from math        import ceil 
from collections import defaultdict


def read_graph(open_file : open) -> {str:{str}}:
    graph = defaultdict(set)
    for line in open_file:
        split_line = line.strip('\n').split(';')
        node = split_line[0]
        if len(split_line) != 1:
            friend = split_line[1]
            graph[node].add(friend)
            graph[friend].add(node)
        else:
            graph[node] = set()
    return graph
    

def graph_as_str(graph : {str:{str}}) -> str:
    result = ""
    for node in sorted(graph.keys()):
        result += '  ' + node + ' -> ' + str(sorted(list(graph[node]))) + '\n'
    return result


def find_influencers(graph : {str:{str}}, trace : bool = False) -> {str}:
    infl_dict = dict()
    for node in graph:
        friends = len(graph[node])
        if friends == 0:
            infl_dict[node] = [-1, 0, node]
        else:
            infl_dict[node] = [friends-ceil(friends / 2), 
                            friends, node]
    while True:
        infl_list = [tuple(node_list) for node_list in infl_dict.values() if node_list[0] >= 0]
        if len(infl_list) == 0:
            if trace:
                print('influencer dictionary =', infl_dict)
                print('removal candidates    = []\n')
            return set(infl_dict.keys())
        node = min(infl_list)[2]
        if trace:
            print('influencer dictionary =', infl_dict)
            print('removal candidates    =', infl_list)
            print(min(infl_list), 'is the smallest candidate')
            print('Removing', node, 
                  "as key from influencer dictionary; decreasing friend's values there\n")
        del infl_dict[node]
        for friend in graph[node]:
            if friend in infl_dict:
                infl_dict[friend][0] -= 1
                infl_dict[friend][1] -= 1
    

def all_influenced(graph : {str:{str}}, influencers : {str}) -> {str}:
    infl_dict = {node: node in influencers for node in graph}
    while True:
        influencers_changed = False
        for node in infl_dict: 
            if not infl_dict[node] and len(graph[node]) != 0:
                if len(graph[node])/2 <= len([friend for friend in graph[node] if infl_dict[friend]]):
                    infl_dict[node] = True
                    influencers_changed = True
        if not influencers_changed:
            return set([node for node in infl_dict if infl_dict[node]])
        
        
def in_proper_format(user_str: str, graph: {str:{str}}) -> bool:
    if user_str.strip().startswith('{') and user_str.strip().endswith('}'):
        nodes = user_str.strip().replace("'",'').lstrip('{').rstrip('}').split(',')
        for node in nodes:
            if node.strip() not in graph:
                return False
        return True
    return False
            
    
if __name__ == '__main__':
    # Write script here
    file = safe_open('Type some file name storing a friendship graph',
                     'r', 'Error reading file')
    graph = read_graph(file)
    
    print('Graph: node -> list of all its friend nodes\n',
          graph_as_str(graph))
    
    trace = prompt.for_bool('Trace this Algorithm', default=True)
    influencers = find_influencers(graph, trace)
    print('Influencers set is', influencers, '\n')
    
    while True:
        infl_set = prompt.for_string('Type some influencers set (or just quit)',
                                     default=str(influencers), 
                                     is_legal=lambda x : x == 'quit' or in_proper_format(x, graph))
        if infl_set == 'quit':
            break
        else:
            nodes_infl = all_influenced(graph, infl_set)
            print('Nodes Influenced ({}% of graph)= {}'.format(
                100*len(nodes_infl)/len(graph), nodes_infl))
        
    # For running batch self-tests
    print()
    import driver
    driver.default_file_name = "bsc1.txt"
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()

