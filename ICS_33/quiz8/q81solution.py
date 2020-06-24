from performance import Performance
from graph_goody import random_graph,spanning_tree

# Put script below to generate data for Problem #1
# In case you fail, the data appears in sample8.pdf in the helper folder

def create_random(size: int) -> 'Graph':
    return random_graph(size, lambda n: 10*n)
    
graph = None

size = 1
while size <= 128:
    graph = create_random(size*1000)
    p = Performance(lambda: spanning_tree(graph), title=f'Spanning Tree of size {size*1000}')
    p.evaluate()
    p.analyze()
    print()
    size *= 2