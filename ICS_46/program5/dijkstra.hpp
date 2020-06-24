//Submitter: kfarsany(Farsany,Kian)

#ifndef DIJKSTRA_HPP_
#define DIJKSTRA_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>                    //Biggest int: std::numeric_limits<int>::max()
#include "array_queue.hpp"
#include "array_stack.hpp"
#include "heap_adjustable_hash_priority_queue.hpp"
#include "hash_graph.hpp"


namespace ics {


class Info {
  public:
    Info() { }

    Info(std::string a_node) : node(a_node) { }

    bool operator==(const Info &rhs) const { return node == rhs.node && cost == rhs.cost && from == rhs.from; }

    bool operator!=(const Info &rhs) const { return !(*this == rhs); }

    friend std::ostream &operator<<(std::ostream &outs, const Info &i) {
      outs << "Info[" << i.node << "," << i.cost << "," << i.from << "]";
      return outs;
    }

    //Public instance variable definitions
    std::string node = "?";
    int cost = std::numeric_limits<int>::max();
    std::string from = "?";
  };


  bool gt_info(const Info &a, const Info &b) { return a.cost < b.cost; }
  int hash_string(const std::string& s) {std::hash<std::string> str_hash; return str_hash(s);}
  int hash_int(const int& i) {std::hash<int> int_hash; return int_hash(i);}

  //Write the following for hashing Info (using hash_string and hash_int)
  int hash_info(const Info& i) {return hash_string(i.node)*hash_int(i.cost);}

  typedef ics::HashGraph<int>                   DistGraph;
  typedef ics::HeapAdjustableHashPriorityQueue<Info, gt_info, hash_info> CostPQ;
  typedef ics::HashMap<std::string, Info, hash_string>       CostMap;
  typedef ics::pair<std::string, Info>          CostMapEntry;


//Return the final_map as specified in the lecture-note description of
//  extended Dijkstra algorithm
  CostMap extended_dijkstra(const DistGraph &g, std::string start_node) {
      CostMap answer_map;

      CostMap info_map;
      for (auto &node : g.all_nodes())
          info_map.put(node.first, Info(node.first));
      info_map[start_node].cost = 0;

      CostPQ info_pq;
      for (auto &node : info_map)
          info_pq.enqueue(node.second);

      while (!info_map.empty()) {
          Info min_info = info_pq.dequeue();
          if (min_info.cost == std::numeric_limits<int>::max())
              break;

          std::string min_node = min_info.node;
          int min_cost = min_info.cost;
          answer_map.put(min_node, info_map.erase(min_node));

          for (auto &d : g.out_nodes(min_node))
              if (!answer_map.has_key(d)) {
                  Info d_info = info_map[d];
                  int calc_cost = min_cost + g.edge_value(min_node, d);
                  if (d_info.cost == std::numeric_limits<int>::max() || d_info.cost > calc_cost) {
                      info_map[d].cost = calc_cost;
                      info_map[d].from = min_node;
                      info_pq.update(d_info, info_map[d]);
                  }
              }
      }

      return answer_map;
  }


//Return a queue whose front is the start node (implicit in answer_map) and whose
//  rear is the end node
  ArrayQueue <std::string> recover_path(const CostMap &answer_map, std::string end_node) {
      ArrayStack<std::string> stack;
      stack.push(end_node);
      while (answer_map[end_node].from != "?") {
          stack.push(answer_map[end_node].from);
          end_node = answer_map[end_node].from;
      }
      return ArrayQueue<std::string>(stack);
  }


}

#endif /* DIJKSTRA_HPP_ */
