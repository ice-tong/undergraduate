#include <fstream>
#include <initializer_list>
#include <string>
#include "gtest/gtest.h"
#include "q5solution.hpp"

class Quiz5Test : public ::testing::Test {
protected:
  virtual void SetUp()    {}
  virtual void TearDown() {}
};



TEST_F(Quiz5Test, nary_tree_maximum) {
  int load1[] = {8,0};
  int at = 0;
  ASSERT_EQ(8, maximum(build_NTN_tree(load1,at)));
  int load2[] = {1,2,5,3,6,0,4,0,2,0,7,3,4,0,10,0,3,0};
  at = 0;
  ASSERT_EQ(10, maximum(build_NTN_tree(load2,at)));
  int load3[] = {1,2,12,3,6,0,4,0,2,0,7,3,4,0,6,0,3,0};
  at = 0;
  ASSERT_EQ(12, maximum(build_NTN_tree(load3,at)));
}

TEST_F(Quiz5Test, digital_tree_longest_word) {
  //Testing longest_word
//adding anteater
//longest word = anteater
//adding anthem
//longest word = anteater
//adding anthebellum
//longest word = antebellum
//adding anteatersforics46
  DTN root;
  add_a_word(root,"ante");
  ASSERT_EQ("ante", longest_word(root));
  add_a_word(root,"anteater");
  ASSERT_EQ("anteater", longest_word(root));
  add_a_word(root,"anthem");
  ASSERT_EQ("anteater", longest_word(root));
  add_a_word(root,"antebellum");
  ASSERT_EQ("antebellum", longest_word(root));
  add_a_word(root,"anteatersforics46");
  ASSERT_EQ("anteatersforics46", longest_word(root));
  add_a_word(root,"foment");
  ASSERT_EQ("anteatersforics46", longest_word(root));
}

TEST_F(Quiz5Test, digital_tree_longest_word_dictionary) {
  DTN root;
  std::ifstream file("dict3.txt");
  std::string word;
  while (getline(file, word))
    add_a_word(root, word);
  ASSERT_EQ(15, longest_word(root).size());  //my function returned "inconsequential"
}


TEST_F(Quiz5Test, digital_tree_stats) {
  DTN root;
  add_a_word(root,"anteater");
  ASSERT_EQ(ics::make_pair(9, 1), stats(root));
  add_a_word(root,"ant");
  ASSERT_EQ(ics::make_pair(9, 2), stats(root));
  add_a_word(root,"ante");
  ASSERT_EQ(ics::make_pair(9, 3), stats(root));
  add_a_word(root,"anthem");
  ASSERT_EQ(ics::make_pair(12, 4), stats(root));
  add_a_word(root,"animal");
  ASSERT_EQ(ics::make_pair(16, 5), stats(root));
  add_a_word(root,"foment");
  ASSERT_EQ(ics::make_pair(22, 6), stats(root));
}

TEST_F(Quiz5Test, digital_tree_stats_dictionary) {
  DTN root;
  std::ifstream file("dict3.txt");
  std::string word;
  while (getline(file, word))
    add_a_word(root, word);
  ASSERT_EQ(ics::make_pair(61616, 19911), stats(root));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}