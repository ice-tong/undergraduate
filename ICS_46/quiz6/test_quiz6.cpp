#include "q6solution.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <random>
#include <vector>

template<class T, class I>
LN<T> *make_list(I begin, I end) {
  LN<T> *h = nullptr, **x = &h;
  for (; begin != end; ++begin)
    x = &(*x = new LN<T>(*begin))->next;
  return h;
}

template <class T>
std::vector<T> make_vector(const LN<T> *x) {
  std::vector<T> v;
  for(; x != nullptr; x = x->next)
    v.push_back(x->value);
  return v;
}

template<class T>
void merge_sort(T a[], const int low, const int high) {
  if (high - low < 1)
    return;
  const int mid = low + (high - low)/2;
  merge_sort(a, low, mid);
  merge_sort(a, mid+1, high);
  merge(a, low, mid, mid+1, high);
}

class Quiz6Test : public ::testing::Test {};

TEST_F(Quiz6Test, selection_sort_random) {
  std::vector<int> values = {1,2,3,4,5,6,7,8,9,10,12}; // 11 is missing
  for (int rep = 0; rep < 100; rep++) {
    std::random_shuffle(values.begin(), values.end());
    auto list = make_list<int>(values.begin(), values.end());
    selection_sort(list);
    std::sort(values.begin(), values.end());
    ASSERT_EQ(values, make_vector(list));
  }
}

TEST_F(Quiz6Test, merge) {
  const int length = 10;

  int array1[length] = {1,2,5,8,10,  3,4,6,7,9};
  std::vector<int> values(array1, array1+length);
  merge(array1, 0, 4, 5, 9);
  std::sort(values.begin(), values.end());
  ASSERT_EQ(values, std::vector<int>(array1, array1+length));

  int array2[length] = {9,2,5,8,10,  3,4,6,7,1};
  values.assign(array2, array2+length);
  merge(array2, 1, 4, 5, 8);
  std::sort(values.begin()+1, values.end()-1);
  ASSERT_EQ(values, std::vector<int>(array2, array2+length));
}

TEST_F(Quiz6Test, merge_random) {
  const int length = 51;
  int array[length];
  std::default_random_engine gen;
  std::uniform_int_distribution<int> dist(0, 100);
  for (int rep = 0; rep < 100; rep++) {
    for (int i = 0; i < length; i++)
      array[i] = dist(gen);
    std::sort(array, array+length/2);
    std::sort(array+length/2, array+length);
    merge(array, 0, length/2-1, length/2, length-1);
    std::vector<int> values(array, array+length);
    std::sort(values.begin(), values.end());
    ASSERT_EQ(values, std::vector<int>(array, array+length));
  }
}

TEST_F(Quiz6Test, merge_sort_random) {
  const int length = 64;
  int array[length] = {1,2,3,4,5,6,7,8,9,10,1,2,3,8,9,10};
  for (int rep = 0; rep < 100; rep++) {
    std::random_shuffle(array, array+length);
    std::vector<int> values(array, array+length);
    merge_sort(array, 0, length-1);
    std::sort(values.begin(), values.end());
    ASSERT_EQ(values, std::vector<int>(array, array+length));
  }
}

TEST_F(Quiz6Test, radix_sort_random) {
  const int length = 31;
  int array[length];
  std::default_random_engine gen;
  std::uniform_int_distribution<int> dist(0, 1000*1000);
  for (int i = 0; i < length; i++)
    array[i] = dist(gen);
  for (int rep = 0; rep < 100; rep++) {
    std::random_shuffle(array, array+length);
    std::vector<int> values(array, array+length);
    radix_sort(array, length);
    std::sort(values.begin(), values.end());
    ASSERT_EQ(values, std::vector<int>(array, array+length));
  }
}

TEST_F(Quiz6Test, test_partition_last) {
  double delta = .01;
  double d = test_partition(100, 100000, last);
  ASSERT_GE(d, .745 - delta);
  ASSERT_LE(d, .745 + delta);
}

TEST_F(Quiz6Test, test_partition_3) {
  double delta = .01;
  double d = test_partition(100, 100000, median_3);
  ASSERT_GE(d, .68 - delta);
  ASSERT_LE(d, .68 + delta);
}

TEST_F(Quiz6Test, test_partition_5) {
  double delta = .01;
  double d = test_partition(100, 100000, median_5);
  ASSERT_GE(d, .65 - delta);
  ASSERT_LE(d, .65 + delta);
}

TEST_F(Quiz6Test, test_partition_median) {
  double delta = .01;
  double d = test_partition(100,100001,median);
  ASSERT_GE(d,.5-delta);
  ASSERT_LE(d,.5+delta);
}

//TEST_F(Quiz6Test, test_partition) {
//  double delta = .01;
//  double d = test_partition(100, 100000, last);
//  ASSERT_GE(d, .745 - delta);
//  ASSERT_LE(d, .745 + delta);
//
//  d = test_partition(100, 100000, median_3);
//  ASSERT_GE(d, .68 - delta);
//  ASSERT_LE(d, .68 + delta);
//
//  d = test_partition(100, 100000, median_5);
//  ASSERT_GE(d, .65 - delta);
//  ASSERT_LE(d, .65 + delta);
//
//  d = test_partition(100,100001,median);
//  ASSERT_GE(d,.5-delta);
//  ASSERT_LE(d,.5+delta);
//}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
