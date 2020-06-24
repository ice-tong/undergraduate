//// Submitter: kfarsany(Farsany, Kian)
//
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <limits>                    //Biggest int: std::numeric_limits<int>::max()
//#include "ics46goody.hpp"
//#include "array_queue.hpp"
//#include "array_priority_queue.hpp"
//#include "array_set.hpp"
//#include "array_map.hpp"
//
//
//typedef ics::ArrayQueue<std::string>              CandidateQueue;
//typedef ics::ArraySet<std::string>                CandidateSet;
//typedef ics::ArrayMap<std::string,int>            CandidateTally;
//
//typedef ics::ArrayMap<std::string,CandidateQueue> Preferences;
//typedef ics::pair<std::string,CandidateQueue>     PreferencesEntry;
//typedef ics::ArrayPriorityQueue<PreferencesEntry> PreferencesEntryPQ; //Must supply gt at construction
//
//typedef ics::pair<std::string,int>                TallyEntry;
//typedef ics::ArrayPriorityQueue<TallyEntry>       TallyEntryPQ;
//
//
//
////Read the open file stating voter preferences (each line is (a) a voter
////  followed by (b) all the candidates the voter would vote for, in
////  preference order (from most to least preferred candidate, separated
////  by semicolons), and return a Map of preferences: a Map whose keys are
////  voter names and whose values are a queue of candidate preferences.
//Preferences read_voter_preferences(std::ifstream &file) {
//    Preferences pref;
//    std::string line;
//    while (getline(file, line)) {
//        std::vector<std::string> ballot = ics::split(line,";");
//        for (int i = 1; i < ballot.size(); ++i)
//            pref[ballot[0]].enqueue(ballot[i]);
//    }
//    file.close();
//    return pref;
//}
//
//
////Print a label and all the entries in the preferences Map, in alphabetical
////  order according to the voter.
////Use a "->" to separate the voter name from the Queue of candidates.
//void print_voter_preferences(const Preferences& preferences) {
//    std::cout << "\nName of Voter -> Preferences queue" << std::endl;
//    PreferencesEntryPQ pq(preferences,
//            [](const PreferencesEntry& a, const PreferencesEntry& b) {return a.first < b.first;});
//    for (const auto& entry : pq)
//        std::cout << entry.first << " -> " << entry.second << std::endl;
//    std::cout << "\n";
//}
//
//
////Print the message followed by all the entries in the CandidateTally, in
////  the order specified by has_higher_priority: i is printed before j, if
////  has_higher_priority(i,j) returns true: sometimes alphabetically by candidate,
////  other times by decreasing votes for the candidate.
////Use a "->" to separate the candidat name from the number of votes they
////  received.
//void print_tally(std::string message, const CandidateTally& tally, bool (*has_higher_priority)(const TallyEntry& i,const TallyEntry& j)) {
//    CandidateSet candidates;
//    TallyEntryPQ pq(tally, has_higher_priority);
//    for (const auto& kv : tally)
//        candidates.insert(kv.first);
//    std::cout << message << candidates << std::endl;
//    for (const auto& entry : pq)
//        std::cout << entry.first << " -> " << entry.second << std::endl;
//    std::cout << "\n";
//}
//
//
////Return the CandidateTally: a Map of candidates (as keys) and the number of
////  votes they received, based on the unchanging Preferences (read from the
////  file) and the candidates who are currently still in the election (which changes).
////Every possible candidate should appear as a key in the resulting tally.
////Each voter should tally one vote: for their highest-ranked candidate who is
////  still in the the election.
//CandidateTally evaluate_ballot(const Preferences& preferences, const CandidateSet& candidates) {
//    CandidateTally result;
//    for (const auto& entry : preferences) {
//        for (const auto& voted_cand : entry.second) {
//            if (candidates.contains(voted_cand)) {
//                ++result[voted_cand];
//                break;
//            }
//        }
//    }
//    return result;
//}
//
//
////Return the Set of candidates who are still in the election, based on the
////  tally of votes: compute the minimum number of votes and return a Set of
////  all candidates receiving more than that minimum; if all candidates
////  receive the same number of votes (that would be the minimum), the empty
////  Set is returned.
//CandidateSet remaining_candidates(const CandidateTally& tally) {
//    CandidateSet result;
//    TallyEntryPQ pq(tally,
//                    [](const TallyEntry& a, const TallyEntry& b) {return a.second < b.second;});
//    int min;
//    if (!pq.empty()) {
//        min = pq.peek().second;
//        for (const auto &entry : pq) {
//            if (entry.second != min)
//                result.insert(entry.first);
//        }
//    }
//    return result;
//}
//
//
////Prompt the user for a file, create a voter preference Map, and print it.
////Determine the Set of all the candidates in the election, from this Map.
////Repeatedly evaluate the ballot based on the candidates (still) in the
////  election, printing the vote count (tally) two ways: with the candidates
////  (a) shown alphabetically increasing and (b) shown with the vote count
////  decreasing (candidates with equal vote counts are shown alphabetically
////  increasing); from this tally, compute which candidates remain in the
////  election: all candidates receiving more than the minimum number of votes;
////  continue this process until there are less than 2 candidates.
////Print the final result: there may 1 candidate left (the winner) or 0 left
////   (no winner).
//int main() {
//  try {
//      std::ifstream file;
//      ics::safe_open(file, "Choose a file representing voter preferences", "votepref1.txt");
//
//      Preferences pref = read_voter_preferences(file);
//      print_voter_preferences(pref);
//
//      int ballot_count;
//      CandidateSet candidates;
//      for (const auto& entry : pref) {
//          for (const auto &cand : entry.second)
//              candidates.insert(cand);
//          break;
//      }
//
//      while (candidates.size() >= 2) {
//          std::string ballot_str = std::to_string(++ballot_count);
//          CandidateTally tally = evaluate_ballot(pref, candidates);
//
//          print_tally("Vote count on ballot #" + ballot_str +
//          "(in alphabetical order) remaining candidates = ", tally,
//          (bool (*)(const TallyEntry& a, const TallyEntry& b)) {[](const TallyEntry& a, const TallyEntry& b)
//          {return a.first < b.first;}});
//
//          print_tally("Vote count on ballot #" + ballot_str +
//          "(in numerical order) remaining candidates = ", tally,
//          (bool (*)(const TallyEntry& a, const TallyEntry& b)) {[](const TallyEntry& a, const TallyEntry& b)
//          {return (a.second == b.second ? a.first < b.first : a.second > b.second);}});
//
//          candidates = remaining_candidates(tally);
//          int cand_size = candidates.size();
//          if (cand_size == 0)
//              std::cout << "No identifiable winner: election is a tie among the candidates who remain on the last ballot" << std::endl;
//          else if (cand_size == 1)
//              for (const auto& cand : candidates)
//                  std:: cout << "Winner is " << cand << std::endl;
//      }
//
//  } catch (ics::IcsError& e) {
//    std::cout << e.what() << std::endl;
//  }
//  return 0;
//}
