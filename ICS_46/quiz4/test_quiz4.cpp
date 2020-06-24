#include <string>
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include <vector>
#include <algorithm>    // std::random_shuffle
#include "q4solution.hpp"

class SetTest : public ::testing::Test {
protected:
    virtual void SetUp()    {}
    virtual void TearDown() {}
};


TEST_F(SetTest, is_BST) {
  int bt0_values[] = {};
  TPN<int>* bt0 = nullptr;
  build_bt(bt0, bt0_values, 0);
  ASSERT_EQ(true,is_bst(bt0));

  int bt1_values[] = {4,4, 2,2, 5,5, 1,1, 3,3};
  TPN<int>* bt1 = nullptr;
  build_bt(bt1, bt1_values, 10);
  ASSERT_EQ(true,is_bst(bt1));

  int bt2_values[] = {4,4, 2,2, 5,5, 3,1, 1,3};
  TPN<int>* bt2 = nullptr;
  build_bt(bt2, bt2_values, 10);
  ASSERT_EQ(false,is_bst(bt2));

  int bt3_values[] = {8,8, 4,4, 2,2, 1,1, 3,3, 6,6, 5,5, 7,7, 12,12, 10,10, 9,9, 11,11, 14,14, 13,13, 15,15};
  TPN<int>* bt3 = nullptr;
  build_bt(bt3, bt3_values, 30);
  ASSERT_EQ(true,is_bst(bt3));

  int bt4_values[] = {8,8, 4,4, 2,2, 1,1, 3,3, 6,6, 5,5, 16,7, 12,12, 10,10, 9,9, 11,11, 14,14, 13,13, 15,15};
  TPN<int>* bt4 = nullptr;
  build_bt(bt4, bt4_values, 30);
  ASSERT_EQ(false,is_bst(bt4));

  int bt5_values[] = {8,8, 4,4, 2,2, 1,1, 3,3, 6,6, 5,5, 7,7, 12,12, 10,10, 9,9, 11,11, 14,14, 13,15};
  TPN<int>* bt5 = nullptr;
  build_bt(bt5, bt5_values, 28);
  ASSERT_EQ(false,is_bst(bt5));
}


TEST_F(SetTest, merge) {
  int load1[]  = {1};
  int load1a[] = {2};
  int load2[]  = {2,3};
  int load4[]  = {4,5,6,7};

  TPN<int>* dlcl_0 = nullptr, *dlcl_1, *dlcl_1a, *dlcl_2, *dlcl_4, *dlcl;

  std::ostringstream s1, s2, s3, s4, s5, s6, s7, s8;

  dlcl = merge(dlcl_0,dlcl_0);
  print_dlcl(dlcl,s1);
  ASSERT_EQ("empty\n",s1.str());

  dlcl_0 = nullptr;
  build_dlcl(dlcl_1, load1,1);
  dlcl = merge(dlcl_0,dlcl_1);
  print_dlcl(dlcl,s2);
  ASSERT_EQ("1<->circular to first node\n",s2.str());

  dlcl_0 = nullptr;
  build_dlcl(dlcl_1, load1,1);
  dlcl = merge(dlcl_1,dlcl_0);
  print_dlcl(dlcl,s3);
  ASSERT_EQ("1<->circular to first node\n",s3.str());

  build_dlcl(dlcl_1,  load1,1);
  build_dlcl(dlcl_1a, load1a,1);
  dlcl = merge(dlcl_1,dlcl_1a);
  print_dlcl(dlcl,s4);
  ASSERT_EQ("1<->2<->circular to first node\n",s4.str());

  build_dlcl(dlcl_1, load1,1);
  build_dlcl(dlcl_2, load2,2);
  dlcl = merge(dlcl_1,dlcl_2);
  print_dlcl(dlcl,s5);
  ASSERT_EQ("1<->2<->3<->circular to first node\n",s5.str());

  build_dlcl(dlcl_1, load1,1);
  build_dlcl(dlcl_2, load2,2);
  dlcl = merge(dlcl_2,dlcl_1);
  print_dlcl(dlcl,s6);
  ASSERT_EQ("2<->3<->1<->circular to first node\n",s6.str());

  build_dlcl(dlcl_2, load2,2);
  build_dlcl(dlcl_4, load4,4);
  dlcl = merge(dlcl_2,dlcl_4);
  print_dlcl(dlcl,s7);
  ASSERT_EQ("2<->3<->4<->5<->6<->7<->circular to first node\n",s7.str());

  build_dlcl(dlcl_2, load2,2);
  build_dlcl(dlcl_4, load4,4);
  dlcl = merge(dlcl_4,dlcl_2);
  print_dlcl(dlcl,s8);
  ASSERT_EQ("4<->5<->6<->7<->2<->3<->circular to first node\n",s8.str());
}


TEST_F(SetTest, bt_to_dlcl) {
  int bt0_values[] = {};
  int bt1_values[] = {4,4, 2,2, 5,5, 1,1, 3,3};
  int bt2_values[] = {4,4, 2,2, 5,5, 3,1, 1,3};
  int bt3_values[] = {8,8, 4,4, 2,2, 1,1, 3,3, 6,6, 5,5, 7,7, 12,12, 10,10, 9,9, 11,11, 14,14, 13,13, 15,15};
  int bt4_values[] = {8,8, 4,4, 2,2, 1,1, 3,3, 6,6, 5,5, 16,7, 12,12, 10,10, 9,9, 11,11, 14,14, 13,13, 15,15};
  int bt5_values[] = {8,8, 4,4, 2,2, 1,1, 3,3, 6,6, 5,5, 7,7, 12,12, 10,10, 9,9, 11,11, 14,14, 13,15};

  TPN<int>* bt0 = nullptr,* bt1 = nullptr,* bt2 = nullptr,* bt3 = nullptr,* bt4 = nullptr,* bt5 = nullptr;
  std::ostringstream s0,s1,s2,s3,s4,s5;

  bt0 = nullptr;
  build_bt(bt0, bt0_values, 0);
  print_dlcl(bt_to_dlcl(bt0),s0);
  ASSERT_EQ("empty\n",s0.str());

  bt1 = nullptr;
  build_bt(bt1, bt1_values, 10);
  print_dlcl(bt_to_dlcl(bt1),s1);
  ASSERT_EQ("1<->2<->3<->4<->5<->circular to first node\n",s1.str());

  bt2 = nullptr;
  build_bt(bt2, bt2_values, 10);
  print_dlcl(bt_to_dlcl(bt2),s2);
  ASSERT_EQ("3<->2<->1<->4<->5<->circular to first node\n",s2.str());

  bt3 = nullptr;
  build_bt(bt3, bt3_values, 30);
  print_dlcl(bt_to_dlcl(bt3),s3);
  ASSERT_EQ("1<->2<->3<->4<->5<->6<->7<->8<->9<->10<->11<->12<->13<->14<->15<->circular to first node\n",s3.str());

  bt4 = nullptr;
  build_bt(bt4, bt4_values, 30);
  print_dlcl(bt_to_dlcl(bt4),s4);
  ASSERT_EQ("1<->2<->3<->4<->5<->6<->16<->8<->9<->10<->11<->12<->13<->14<->15<->circular to first node\n",s4.str());

  bt5 = nullptr;
  build_bt(bt5, bt5_values, 28);
  print_dlcl(bt_to_dlcl(bt5),s5);
  ASSERT_EQ("1<->2<->3<->4<->5<->6<->7<->8<->9<->10<->11<->12<->14<->13<->circular to first node\n",s5.str());
}





int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
