//Submitter: kfarsany(Farsany,Kian)

#ifndef Q6SOLUTION_HPP_
#define Q6SOLUTION_HPP_


#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <algorithm>                 // std::swap
#include "ics46goody.hpp"
#include "array_queue.hpp"
#include "q6utility.hpp"


////////////////////////////////////////////////////////////////////////////////

//Problem 1

//Write this function
template<class T>
void selection_sort(LN<T>* l) {
    for (LN<T>* to_change = l; to_change != nullptr; to_change = to_change->next)
        for (LN<T>* cursor = to_change->next; cursor != nullptr; cursor = cursor->next)
            if (cursor->value < to_change->value) {
                T temp = cursor->value;
                cursor->value = to_change->value;
                to_change->value = temp;
            }
}


////////////////////////////////////////////////////////////////////////////////

//Problem 2

//Write this function
template<class T>
void merge(T a[], int left_low,  int left_high,
           int right_low, int right_high) {
    T temp[right_high+1];
    int left = left_low; int right = right_low;
    for (int i = left_low; i < right_high+1; ++i) {
        if (left > left_high)
            temp[i] = a[right++];
        else if(right > right_high)
            temp[i] = a[left++];
        else if (a[left] <= a[right])
            temp[i] = a[left++];
        else
            temp[i] = a[right++];
    }

    for (int i = left_low; i <= right_high; ++i)
        a[i] = temp[i];
}


////////////////////////////////////////////////////////////////////////////////

//Problem 3

int select_digit (int number, int place)
{return number/place % 10;}


//Write this function
void radix_sort(int a[], int length) {
    ics::ArrayQueue<int> buckets[10];
    for (int place = 1; place < 1000000; place = place*10) {

        for (int i = 0; i < length; ++i)
            buckets[select_digit(a[i], place)].enqueue(a[i]);

        int j = 0;
        for (int i = 0; i <= 9; ++i)
            while (!buckets[i].empty())
                a[j++] = buckets[i].dequeue();
    }
}


////////////////////////////////////////////////////////////////////////////////

//Problem 4

//Write this function

//Test how well a partition function (choose_pivot_index: e.g., last and median_3) works.
//Test is on an array of the the values 0..length-1, randomly shuffled, num_tests times
//Returns the average size of the larger of the left and right partition sizes.
//At best the array is cut in half, yield the biggest side as 0.5 (50%)
double test_partition(int length, int num_tests, int (*choose_pivot_index) (int a[], int low, int high)) {
    int test[length];
    for (int i = 0; i < length; ++i)
        test[i] = i;

    int sum = 0;
    for (int i = 0; i < num_tests; ++i) {
        shuffle(test, length);
        int pivot = choose_pivot_index(test, 0, length-1);
        pivot = partition(test, 0, length-1, pivot);
        if (pivot >= length-pivot-1)
            sum += pivot;
        else
            sum += length-pivot-1;
    }

    return double(sum/num_tests) / length;
}


#endif /* Q6SOLUTION_HPP_ */
