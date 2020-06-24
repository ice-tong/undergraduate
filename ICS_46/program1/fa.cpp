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
//typedef ics::ArrayQueue<std::string>                InputsQueue;
//typedef ics::ArrayMap<std::string,std::string>      InputStateMap;
//
//typedef ics::ArrayMap<std::string,InputStateMap>    FA;
//typedef ics::pair<std::string,InputStateMap>        FAEntry;
//
//bool gt_FAEntry (const FAEntry& a, const FAEntry& b)
//{return a.first<b.first;}
//
//typedef ics::ArrayPriorityQueue<FAEntry,gt_FAEntry> FAPQ;
//
//typedef ics::pair<std::string,std::string>          Transition;
//typedef ics::ArrayQueue<Transition>                 TransitionQueue;
//
//
////Read the open file describing the finite automaton (each line starts with
////  a state name followed by pairs of transitions from that state: (input
////  followed by new state, all separated by semicolons), and return a Map
////  whose keys are states and whose associated values are another Map with
////  each input in that state (keys) and the resulting state it leads to.
//const FA read_fa(std::ifstream &file) {
//    FA fa;
//    std::string line;
//    while (getline(file, line)) {
//        std::vector<std::string> items = ics::split(line, ";");
//        for (int i = 1; i < items.size(); i += 2)
//            fa[items[0]].put(items[i], items[i + 1]);
//    }
//    return fa;
//}
//
//
////Print a label and all the entries in the finite automaton Map, in
////  alphabetical order of the states: each line has a state, the text
////  "transitions:" and the Map of its transitions.
//void print_fa(const FA& fa) {
//    std::cout << "The Description of the chosen Finite Automaton" << std::endl;
//    FAPQ fapq(fa, gt_FAEntry);
//    for (const auto& kv : fapq)
//        std::cout << "  " << kv.first << " transitions: " << kv.second << std::endl;
//    std::cout << std::endl;
//}
//
//
////Return a queue of the calculated transition pairs, based on the finite
////  automaton, initial state, and queue of inputs; each pair in the returned
////  queue is of the form: input, new state.
////The first pair contains "" as the input and the initial state.
////If any input i is illegal (does not lead to a state in the finite
////  automaton), then the last pair in the returned queue is i,"None".
//TransitionQueue process(const FA& fa, std::string state, const InputsQueue& inputs) {
//    TransitionQueue result;
//    Transition t("", state);
//    result.enqueue(t);
//    for (const auto& input : inputs) {
//        if (fa[state].has_key(input)) {
//            std::string new_state = fa[state][input];
//            t.first = input; t.second = new_state;
//            result.enqueue(t);
//            state = new_state;
//        }
//        else {
//            t.first = input; t.second = "None";
//            result.enqueue(t);
//            break;
//        }
//    }
//    return result;
//}
//
//
////Print a TransitionQueue (the result of calling the process function above)
//// in a nice form.
////Print the Start state on the first line; then print each input and the
////  resulting new state (or "illegal input: terminated", if the state is
////  "None") indented on subsequent lines; on the last line, print the Stop
////  state (which may be "None").
//void interpret(TransitionQueue& tq) {  //or TransitionQueue or TransitionQueue&&
//    std::cout << "Start state = " << tq.peek().second << std::endl;
//    std::string end;
//    for (const auto& transition : tq) {
//        if (transition.second == "None") {
//            std::cout << "  Input = " << transition.first << "; ";
//            std::cout << "illegal input: simulation terminated" << std::endl;
//            end = transition.second;
//            break;
//        }
//        else if (transition.first != "") {
//            std::cout << "  Input = " << transition.first << "; ";
//            std::cout << "new state = " << transition.second << std::endl;
//            end = transition.second;
//        }
//    }
//    std::cout << "Stop state = " << end << "\n" << std::endl;
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
//      std::ifstream fa_file;
//      ics::safe_open(fa_file, "Choose the file name representing the finite automaton", "faparity.txt");
//
//      FA fa = read_fa(fa_file);
//      print_fa(fa);
//
//      std::ifstream input_file;
//      ics::safe_open(input_file, "Choose the file name representing the start-states and their inputs", "fainputparity.txt");
//
//      std::string line;
//      while (getline(input_file, line)) {
//          std::cout << "\nBegin tracing the next FA simulation: " << line << std::endl;
//
//          std::vector<std::string> items = ics::split(line, ";");
//          std::string start_state = items[0];
//
//          InputsQueue inputs;
//          TransitionQueue t;
//          for (int i = 1; i < items.size(); ++i)
//              inputs.enqueue(items[i]);
//          t = process(fa, start_state, inputs);
//          interpret(t);
//      }
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//
//  return 0;
//}
