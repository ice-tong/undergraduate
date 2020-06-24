#ifndef SOLUTION_HPP_
#define SOLUTION_HPP_

#include <string>
#include <iostream>
#include <fstream>


template<class T>
class LN {
  public:
    LN ()                        : next(nullptr){}
    LN (const LN<T>& ln)         : value(ln.value), next(ln.next){}
    LN (T v, LN<T>* n = nullptr) : value(v), next(n){}
    T      value;
    LN<T>* next;
};


//Simple way to print linked lists (useful for driver and debugging)
template<class T>
std::ostream& operator << (std::ostream& outs, LN<T>* l) {
  for (LN<T>* p = l; p!=nullptr; p=p->next)
    outs << p->value << "->";
  outs << "nullptr";
  return outs;
}


//Simple way to print linked lists given first node
//  (useful for driver and debugging)
template<class T>
std::ostream& operator << (std::ostream& outs, LN<T> l) {
  outs << l.value << "->";
  for (LN<T>* p = l.next; p!=nullptr; p=p->next)
    outs << p->value << "->";
  outs << "nullptr";
  return outs;
}


char relation (const std::string& s1, const std::string& s2) {
    if (s1 == "" and s2 == "")
        return '=';
    else if (s1 == "")
        return '<';
    else if (s2 == "")
        return '>';
    else if (s1[0] < s2[0])
        return '<';
    else if (s1[0] > s2[0])
        return '>';
    else
        return relation(s1.substr(1), s2.substr(1));
}


template<class T>
void remove_ascending_i (LN<T>*& l) {
    if (l == nullptr)
        return;
    LN<T>* prev = nullptr;
    for (LN<T>* c = l; c != nullptr && c->next != nullptr; ) {
        if (prev == nullptr) {
            if (c->value < c->next->value) {
                LN<T>* to_del = c;
                c = c->next;
                l = l->next;
                delete to_del;
            } else {
                prev = c;
                c = c->next;
            }
        } else {
            if (c->value < c->next->value) {
                LN<T>* to_del = c;
                c = c->next;
                prev->next = c;
                delete to_del;
            } else {
                prev = c;
                c = c->next;
            }
        }
    }
}

template<class T>
void remove_ascending_r (LN<T>*& l) {
    if (l == nullptr || l->next == nullptr)
        return;
    else if (l->value >= l->next->value)
        remove_ascending_r(l->next);
    else {
        LN<T>* to_del = l;
        l = l->next;
        delete to_del;
        remove_ascending_r(l);
    }
}



#endif /* SOLUTION_HPP_ */
