#ifndef SOLUTION_HPP_
#define SOLUTION_HPP_

#include <string>
#include <iostream>
#include <fstream>
#include <math.h>            /* for atan2 and sqrt */
#include "ics46goody.hpp"
#include "ics_exceptions.hpp"
#include "array_queue.hpp"
#include "array_priority_queue.hpp"
#include "array_map.hpp"


class Point {
public:
  Point() : x(0), y(0) {} // Needed for pair
  Point(int x_val, int y_val) : x(x_val), y(y_val) {}
  friend bool operator == (const Point& p1, const Point& p2) {
    return p1.x == p2.x && p1.y == p2.y;
  }
  friend std::ostream& operator << (std::ostream& outs, const Point& p) {
    outs << "(" << p.x << "," << p.y << ")";
    return outs;
  }

  int x;
  int y;
};


//Helper Functions (you decide what is useful)
//Hint: I used helpers for sort_yo, sort_angle, points, and first_quad
bool gt_sort_yo (const ics::pair<int,Point>& p1, const ics::pair<int,Point>& p2) {
    if (p1.second.y < p2.second.y)
        return true;
    if (p1.second.y == p2.second.y)
        if (p1.first >= p2.first)
            return true;
    return false;
}

bool gt_distance (const Point& p1, const Point& p2) {
    double dist1 = sqrt(pow(p1.x, 2) + pow(p1.y, 2));
    double dist2 = sqrt(pow(p2.x, 2) + pow(p2.y, 2));
    return  dist1 > dist2;
}

bool gt_ordinal (const ics::pair<int,Point>& p1, const ics::pair<int,Point>& p2) {
    return p1.first < p2.first;
}

bool gt_angle (const ics::pair<int,Point>& p1, const ics::pair<int,Point>& p2) {
    return atan2(p1.second.y,p1.second.x) < atan2(p2.second.y,p2.second.x);
}


//Problem #1a and #1b
template<class KEY,class T>
void swap (ics::ArrayMap<KEY,T>& m, KEY key1, KEY key2) {
    m[key1] = m.put(key2, m[key1]);
}


template<class KEY,class T>
void values_set_to_queue (const ics::ArrayMap<KEY,ics::ArraySet<T>>& m1,
                          ics::ArrayMap<KEY,ics::ArrayQueue<T>>&     m2) {
    for (const auto& kv : m1)
        m2[kv.first].enqueue_all(kv.second);
}


//Problem #2a, #2b, #2c, and #2d
ics::ArrayQueue<ics::pair<int,Point>> sort_yo (const ics::ArrayMap<int,Point>& m) {
    ics::ArrayPriorityQueue<ics::pair<int,Point>,gt_sort_yo> pq(m);
    ics::ArrayQueue<ics::pair<int,Point>> result(pq);
    return result;
}


ics::ArrayQueue<Point> sort_distance (const ics::ArrayMap<int,Point>& m) {
    ics::ArrayPriorityQueue<Point, gt_distance> pq;
    for (const auto& kv : m)
        pq.enqueue(kv.second);
    ics::ArrayQueue<Point> result(pq);
    return result;
}


ics::ArrayQueue<Point> points (const ics::ArrayMap<int,Point>& m) {
    ics::ArrayPriorityQueue<ics::pair<int,Point>, gt_ordinal> pq(m);
    ics::ArrayQueue<Point> result;
    for (const auto& pair : pq)
        result.enqueue(pair.second);
    return result;
}


ics::ArrayQueue<ics::pair<int,double>> angles (const ics::ArrayMap<int,Point>& m) {
    ics::ArrayPriorityQueue<ics::pair<int,Point>, gt_angle> pq(m);
    ics::ArrayQueue<ics::pair<int,double>> result;
    for (const auto& p : pq)
        result.enqueue(ics::pair<int,double>(p.first,
                atan2(p.second.y,p.second.x)));
    return result;
}


//Problem #3
ics::ArrayMap<char,ics::ArraySet<char>> follows(const std::string word) {
    ics::ArrayMap<char,ics::ArraySet<char>> result;
    for (int i = 0; i < word.size()-1; ++i)
        result[word[i]].insert(word[i+1]);
    return result;
}


//Problem #4a and #4b
ics::ArrayMap<std::string,int> got_called(const  ics::ArrayMap<std::string,ics::ArrayMap<std::string,int>>& calls) {
    ics::ArrayMap<std::string,int> result;
    for (const auto& outer_map : calls)
        for (const auto& inner_map : outer_map.second)
            result[inner_map.first] += inner_map.second;
    return result;
}


  ics::ArrayMap<std::string,ics::ArrayMap<std::string,int>> invert (const ics::ArrayMap<std::string,ics::ArrayMap<std::string,int>>& calls) {
    ics::ArrayMap<std::string,ics::ArrayMap<std::string,int>> result;
    for (const auto& outer_map_pair : calls)
        for (const auto& inner_map_pair : outer_map_pair.second)
            result[inner_map_pair.first].put(outer_map_pair.first, inner_map_pair.second);
    return result;
}
#endif /* SOLUTION_HPP_ */


