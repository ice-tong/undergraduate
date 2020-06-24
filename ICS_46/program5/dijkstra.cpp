//Submitter: kfarsany(Farsany,Kian)

#include <string>
#include <iostream>
#include <fstream>
#include "array_queue.hpp"
#include "dijkstra.hpp"



std::string get_node_in_graph(const ics::DistGraph& g, std::string prompt, bool allow_QUIT) {
  std::string node;
  for(;;) {
    node = ics::prompt_string(prompt + " (must be in graph" + (allow_QUIT ? " or QUIT" : "") + ")");
    if ( (allow_QUIT && node == "QUIT") || g.has_node(node) )
      break;
  }
  return node;
}


int main() {
  try {
    std::ifstream file;
    ics::safe_open(file, "Enter graph file name", "flightcost.txt");

    ics::DistGraph graph;
    graph.load(file, ";");
    std::cout << graph << std::endl;

    std::string start = ics::prompt_string("Enter start node (must be in graph)");
    ics::CostMap answer_map = ics::extended_dijkstra(graph, start);
    std::cout << answer_map << std::endl << std::endl;

    while (true) {
      std::string stop = get_node_in_graph(graph, "Enter stop node", true);
      if (stop == "QUIT")
        break;
      std::cout << "Cost is " << answer_map[stop].cost << "; ";
      std::cout << "path is " << ics::recover_path(answer_map, stop) << std::endl << std::endl;
    }

  } catch (ics::IcsError& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
