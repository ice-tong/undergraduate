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
//typedef ics::ArraySet<std::string>                     States;
//typedef ics::ArrayQueue<std::string>                   InputsQueue;
//typedef ics::ArrayMap<std::string,States>              InputStatesMap;
//
//typedef ics::ArrayMap<std::string,InputStatesMap>       NDFA;
//typedef ics::pair<std::string,InputStatesMap>           NDFAEntry;
//
//bool gt_NDFAEntry (const NDFAEntry& a, const NDFAEntry& b)
//{return a.first<b.first;}
//
//typedef ics::ArrayPriorityQueue<NDFAEntry,gt_NDFAEntry> NDFAPQ;
//
//typedef ics::pair<std::string,States>                   Transitions;
//typedef ics::ArrayQueue<Transitions>                    TransitionsQueue;
//
//
////Read the open file describing the non-deterministic finite automaton (each
////  line starts with a state name followed by pairs of transitions from that
////  state: (input followed by a new state, all separated by semicolons), and
////  return a Map whose keys are states and whose associated values are another
////  Map with each input in that state (keys) and the resulting set of states it
////  can lead to.
//const NDFA read_ndfa(std::ifstream &file) {
//    NDFA ndfa;
//    std::string line;
//    while (getline(file, line)) {
//        std::vector<std::string> items = ics::split(line, ";");
//        int size = items.size();
//        if (size > 1) {
//            for (int i = 1; i < size; i += 2)
//                ndfa[items[0]][items[i]].insert(items[i + 1]);
//        }
//        else {
//            ndfa[items[0]] = InputStatesMap();
//        }
//    }
//  return ndfa;
//}
//
//
////Print a label and all the entries in the finite automaton Map, in
////  alphabetical order of the states: each line has a state, the text
////  "transitions:" and the Map of its transitions.
//void print_ndfa(const NDFA& ndfa) {
//    std::cout << "The Description of the chosen Non-Deterministic Finite Automaton" << std::endl;
//    NDFAPQ pq(ndfa, gt_NDFAEntry);
//    for (const auto& kv : pq) {
//        std::cout << "  " << kv.first << " transitions: " << kv.second << std::endl;
//    }
//    std::cout << std::endl;
//}
//
//
////Return a queue of the calculated transition pairs, based on the non-deterministic
////  finite automaton, initial state, and queue of inputs; each pair in the returned
////  queue is of the form: input, set of new states.
////The first pair contains "" as the input and the initial state.
////If any input i is illegal (does not lead to any state in the non-deterministic finite
////  automaton), ignore it.
//TransitionsQueue process(const NDFA& ndfa, std::string state, const InputsQueue& inputs) {
//    TransitionsQueue result;
//    States states({state});
//    result.enqueue(Transitions("", states));
//    for (const auto& input : inputs) {
//        States new_states;
//        for (const auto& s : states)
//            if (ndfa[s].has_key(input))
//                new_states.insert_all(ndfa[s][input]);
//        states.clear();
//        states.insert_all(new_states);
//        result.enqueue(Transitions(input, states));
//    }
//    return result;
//}
//
//
////Print a TransitionsQueue (the result of calling process) in a nice form.
////Print the Start state on the first line; then print each input and the
////  resulting new states indented on subsequent lines; on the last line, print
////  the Stop state.
//void interpret(TransitionsQueue& tq) {  //or TransitionsQueue or TransitionsQueue&&
//    std::cout << "Start state = " << tq.peek().second << std::endl;
//    States end;
//    for (const auto& transition : tq) {
//        if (!transition.first.empty()) {
//            std::cout << "  Input = " << transition.first << "; ";
//            std::cout << "new states possible = " << transition.second << std::endl;
//            end = transition.second;
//        }
//    }
//    std::cout << "Stop state(s) = " << end << "\n" << std::endl;
//}
//
//
//
////Prompt the user for a file, create a finite automaton Map, and print it.
////Prompt the user for a file containing any number of simulation descriptions
////  for the finite automaton to process, one description per line; each
////  description contains a start state followed by its inputs, all separated by
////  semicolons.
////Repeatedly read a description, print that description, put each input in a
////  Queue, process the Queue and print the results in a nice form.
//int main() {
//  try {
//      std::ifstream ndfa_file;
//      ics::safe_open(ndfa_file,
//              "Choose the file name representing the non-deterministic finite automaton",
//              "ndfaendin01.txt");
//
//      NDFA ndfa = read_ndfa(ndfa_file);
//      print_ndfa(ndfa);
//
//      std::ifstream input_file;
//      ics::safe_open(input_file,
//              "Choose the file name representing the start-states and their inputs",
//              "ndfainputendin01.txt");
//
//      std::string line;
//      while (getline(input_file, line)) {
//          std::cout << "\nBegin tracing the next NDFA simulation: " << line << std::endl;
//
//          std::vector<std::string> items = ics::split(line, ";");
//          std::string start_state = items[0];
//
//          InputsQueue inputs;
//          TransitionsQueue t;
//          for (int i = 1; i < items.size(); ++i)
//              inputs.enqueue(items[i]);
//          t = process(ndfa, start_state, inputs);
//          interpret(t);
//      }
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
