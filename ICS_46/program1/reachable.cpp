//// Submitter: kfarsany(Farsany, Kian)
//
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include "ics46goody.hpp"
//#include "array_queue.hpp"
//#include "array_priority_queue.hpp"
//#include "array_set.hpp"
//#include "array_map.hpp"
//
//
//typedef ics::ArraySet<std::string>          NodeSet;
//typedef ics::pair<std::string,NodeSet>      GraphEntry;
//
//bool graph_entry_gt (const GraphEntry& a, const GraphEntry& b)
//{return a.first<b.first;}
//
//typedef ics::ArrayPriorityQueue<GraphEntry,graph_entry_gt> GraphPQ;
//typedef ics::ArrayMap<std::string,NodeSet>  Graph;
//
//
////Read the open file of edges (node names separated by semicolons, with an
////  edge going from the first node name to the second node name) and return a
////  Graph (Map) of each node name associated with the Set of all node names to
////  which there is an edge from the key node name.
//Graph read_graph(std::ifstream &file) {
//	Graph graph;
//	std::string line;
//	while (getline(file, line)) {
//	    std::vector<std::string> nodes = ics::split(line, ";");
//	    graph[nodes[0]].insert(nodes[1]);
//	}
//	file.close();
//	return graph;
//}
//
//
////Print a label and all the entries in the Graph in alphabetical order
////  (by source node).
////Use a "->" to separate the source node name from the Set of destination
////  node names to which it has an edge.
//void print_graph(const Graph& graph) {
//    std::cout << "Graph: any node -> set[all that node's destination nodes]" << std::endl;
//    GraphPQ pq(graph);
//    for (const auto& entry : pq)
//        std::cout << entry.first << "->" << entry.second << std::endl;
//}
//
//
////Return the Set of node names reaching in the Graph starting at the
////  specified (start) node.
////Use a local Set and a Queue to respectively store the reachable nodes and
////  the nodes that are being explored.
//NodeSet reachable(const Graph& graph, std::string start) {
//    NodeSet reached;
//    ics::ArrayQueue<std::string> nodes({start});
//    while(!nodes.empty()) {
//        std::string test_node = nodes.dequeue();
//        reached.insert(test_node);
//        if (graph.has_key(test_node)) {
//            for (const auto& des_node : graph[test_node]) {
//                if (!reached.contains(des_node))
//                    nodes.enqueue(des_node);
//            }
//        }
//    }
//    return reached;
//}
//
//
//
//
//
////Prompt the user for a file, create a graph from its edges, print the graph,
////  and then repeatedly (until the user enters "quit") prompt the user for a
////  starting node name and then either print an error (if that the node name
////  is not a source node in the graph) or print the Set of node names
////  reachable from it by using the edges in the Graph.
//int main() {
//  try {
//      std::ifstream text_file;
//      ics::safe_open(text_file, "Choose the file name representing the graph", "graph1.txt");
//
//      Graph graph = read_graph(text_file);
//      print_graph(graph);
//
//      std::string start;
//      while (start != "quit") {
//          std::cout << "Choose the start node (or choose quit): ";
//          std::cin >> start;
//          if (graph.has_key(start))
//              std::cout << "Starting from " << start << " the nodes reachable are "
//                        << reachable(graph, start) << std::endl;
//          else if (start != "quit")
//              std::cout << start << " is not a source node in the graph" << std::endl;
//      }
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
