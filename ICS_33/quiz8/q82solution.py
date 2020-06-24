import cProfile
from graph_goody import random_graph, spanning_tree
import pstats

# Put script below to generate data for Problem #2
# In case you fail, the data appears in sample8.pdf in the helper folder

graph1 = random_graph(5000, lambda n : 10*n)
graph2 = random_graph(10000, lambda n: 10*n)

cProfile.run('spanning_tree(graph1)', 'profile5K')
p1 = pstats.Stats('profile5K')
p1.strip_dirs().sort_stats('calls').print_stats()

cProfile.run('spanning_tree(graph2)', 'profile10K')
p2 = pstats.Stats('profile10K')
p2.strip_dirs().sort_stats('time').print_stats()