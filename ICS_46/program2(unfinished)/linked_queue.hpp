//Submitter: kfarsany(Farsany,Kian)

#ifndef LINKED_QUEUE_HPP_
#define LINKED_QUEUE_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"


namespace ics {


template<class T> class LinkedQueue {
  public:
    //Destructor/Constructors
    ~LinkedQueue();

    LinkedQueue          ();
    LinkedQueue          (const LinkedQueue<T>& to_copy);
    explicit LinkedQueue (const std::initializer_list<T>& il);

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    explicit LinkedQueue (const Iterable& i);


    //Queries
    bool empty      () const;
    int  size       () const;
    T&   peek       () const;
    std::string str () const; //supplies useful debugging information; contrast to operator <<


    //Commands
    int  enqueue (const T& element);
    T    dequeue ();
    void clear   ();

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    int enqueue_all (const Iterable& i);


    //Operators
    LinkedQueue<T>& operator = (const LinkedQueue<T>& rhs);
    bool operator == (const LinkedQueue<T>& rhs) const;
    bool operator != (const LinkedQueue<T>& rhs) const;

    template<class T2>
    friend std::ostream& operator << (std::ostream& outs, const LinkedQueue<T2>& q);



  private:
    class LN;

  public:
    class Iterator {
      public:
        //Private constructor called in begin/end, which are friends of LinkedQueue<T>
        ~Iterator();
        T           erase();
        std::string str  () const;
        LinkedQueue<T>::Iterator& operator ++ ();
        LinkedQueue<T>::Iterator  operator ++ (int);
        bool operator == (const LinkedQueue<T>::Iterator& rhs) const;
        bool operator != (const LinkedQueue<T>::Iterator& rhs) const;
        T& operator *  () const;
        T* operator -> () const;
        friend std::ostream& operator << (std::ostream& outs, const LinkedQueue<T>::Iterator& i) {
          outs << i.str(); //Use the same meaning as the debugging .str() method
          return outs;
        }
        friend Iterator LinkedQueue<T>::begin () const;
        friend Iterator LinkedQueue<T>::end   () const;

      private:
        //If can_erase is false, current indexes the "next" value (must ++ to reach it)
        LN*             prev = nullptr;  //if nullptr, current at front of list
        LN*             current;         //current == prev->next (if prev != nullptr)
        LinkedQueue<T>* ref_queue;
        int             expected_mod_count;
        bool            can_erase = true;

        //Called in friends begin/end
        Iterator(LinkedQueue<T>* iterate_over, LN* initial);
    };


    Iterator begin () const;
    Iterator end   () const;


  private:
    class LN {
      public:
        LN ()                      {}
        LN (const LN& ln)          : value(ln.value), next(ln.next){}
        LN (T v,  LN* n = nullptr) : value(v), next(n){}

        T   value;
        LN* next = nullptr;
    };


    LN* front     =  nullptr;
    LN* rear      =  nullptr;
    int used      =  0;            //Cache the count of nodes in the linked list
    int mod_count =  0;            //Allows the sensing of concurrent modification

    //Helper methods
    void delete_list(LN*& front);  //Deallocate all LNs, and set front's argument to nullptr;
};





////////////////////////////////////////////////////////////////////////////////
//
//LinkedQueue class and related definitions

//Destructor/Constructors

template<class T>
LinkedQueue<T>::~LinkedQueue() {
    delete_list(front);
}


template<class T>
LinkedQueue<T>::LinkedQueue() {
}


template<class T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& to_copy)
: used(to_copy.used) {
    if (used == 0)
        return;
    front = new LN(to_copy.front->value, to_copy.front->next);
    rear = front;
    for (LN* p = to_copy.front->next; p != nullptr; rear = rear->next, p = p->next)
        rear->next = new LN(p->value, p->next);
}


template<class T>
LinkedQueue<T>::LinkedQueue(const std::initializer_list<T>& il) {
    for (const T& i : il)
        enqueue(i);
}


template<class T>
template<class Iterable>
LinkedQueue<T>::LinkedQueue(const Iterable& i) {
    for (const T& e : i) {
        enqueue(e);
    }
}


////////////////////////////////////////////////////////////////////////////////
//
//Queries

template<class T>
bool LinkedQueue<T>::empty() const {
    return front == nullptr;
}


template<class T>
int LinkedQueue<T>::size() const {
    return used;
}


template<class T>
T& LinkedQueue<T>::peek () const {
    if (this->empty())
        throw EmptyError("LinkedQueue::peek");
    return front->value;
}


template<class T>
std::string LinkedQueue<T>::str() const {
    std::ostringstream result;
    result << "linked_queue[";
    if (used != 0) {
        for (LN* p = front; p != nullptr; p = p->next) {
            if (p != rear)
                result << p->value << "->";
            else
                result << p->value;
        }
        result << "](used=" << used << ",front=" << front << ",rear=" << rear
        << ",mod_count=" << mod_count << ")";
    }
    return result.str();
}


////////////////////////////////////////////////////////////////////////////////
//
//Commands

template<class T>
int LinkedQueue<T>::enqueue(const T& element) {
    if (used != 0) {
        rear->next = new LN(element);
        rear = rear->next;
    }
    else {
        front = new LN(element);
        rear = front;
    }
    ++used;
    ++mod_count;
    return 1;
}


template<class T>
T LinkedQueue<T>::dequeue() {
    if (this->empty())
        throw EmptyError("LinkedQueue::dequeue");
    LN* to_del = front;
    T result = to_del->value;
    front =  front->next;
    delete to_del;
    --used;
    ++mod_count;
    return result;
}


template<class T>
void LinkedQueue<T>::clear() {
    LN* to_del = front;
    front = nullptr;
    rear = nullptr;
    used = 0;
    ++mod_count;
    delete_list(to_del);
}


template<class T>
template<class Iterable>
int LinkedQueue<T>::enqueue_all(const Iterable& i) {
    int result = 0;
    for (const T& v : i)
        result += enqueue(v);
    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//Operators

template<class T>
LinkedQueue<T>& LinkedQueue<T>::operator = (const LinkedQueue<T>& rhs) {
    if (this == &rhs)
        return *this;

    LN* this_p = front;
    LN* rhs_p = rhs.front;
    for (; this_p != nullptr || rhs_p != nullptr; this_p = this_p->next, rhs_p = rhs_p->next) {
        if (this_p == nullptr) {
            enqueue(rhs_p->value);
            --mod_count;
            this_p = rear;
        }
        else if (rhs_p->next == nullptr && this_p->next != nullptr) {
            this_p->value = rhs_p->value;
            rear = this_p;
            delete_list(rear->next);
            break;
        } else
            this_p->value = rhs_p->value;
    }
    ++mod_count;
    used = rhs.used;
    return *this;
}


template<class T>
bool LinkedQueue<T>::operator == (const LinkedQueue<T>& rhs) const {
    if (this == &rhs)
        return true;
    if (used != rhs.used)
        return false;

    LN* p1 = front;
    LN* p2 = rhs.front;
    for (; p1 != nullptr; p1 = p1->next, p2 = p2->next)
        if (p1->value != p2->value)
            return false;
    return true;
}


template<class T>
bool LinkedQueue<T>::operator != (const LinkedQueue<T>& rhs) const {
    return !(*this == rhs);
}


template<class T>
std::ostream& operator << (std::ostream& outs, const LinkedQueue<T>& q) {
    outs << "queue[";

    if (!q.empty()) {
        outs << q.front->value;
        typename LinkedQueue<T>::LN* node = q.front->next;
        for (; node != nullptr; node = node->next)
            outs << "," << node->value;
    }

    outs << "]:rear";
    return outs;
}


////////////////////////////////////////////////////////////////////////////////
//
//Iterator constructors

template<class T>
auto LinkedQueue<T>::begin () const -> LinkedQueue<T>::Iterator {
    return Iterator(const_cast<LinkedQueue<T>*>(this), front);
}

template<class T>
auto LinkedQueue<T>::end () const -> LinkedQueue<T>::Iterator {
    return Iterator(const_cast<LinkedQueue<T>*>(this), nullptr);
}


////////////////////////////////////////////////////////////////////////////////
//
//Private helper methods

template<class T>
void LinkedQueue<T>::delete_list(LN*& front) {
    if (front == nullptr)
        return;
    else {
        LN* to_del = front;
        front = front->next;
        delete to_del;
        delete_list(front);
    }
}





////////////////////////////////////////////////////////////////////////////////
//
//Iterator class definitions

template<class T>
LinkedQueue<T>::Iterator::Iterator(LinkedQueue<T>* iterate_over, LN* initial)
: current(initial), ref_queue(iterate_over), expected_mod_count(ref_queue->mod_count){
}


template<class T>
LinkedQueue<T>::Iterator::~Iterator()
{}


template<class T>
T LinkedQueue<T>::Iterator::erase() {
    if (expected_mod_count != ref_queue->mod_count)
        throw ConcurrentModificationError("LinkedQueue::Iterator::erase");
    if (!can_erase)
        throw CannotEraseError("LinkedQueue::Iterator::erase Iterator cursor already erased");

    can_erase = false;
    T result = current->value;

    LN* to_del = current;
    current = current->next;
    if (to_del == ref_queue->front)
        ref_queue->front = ref_queue->front->next;
    else if (to_del == ref_queue->rear) {
        ref_queue->rear = prev;
        prev->next = nullptr;
    }
    else
        prev->next = current;
    delete to_del;
    --ref_queue->used;
    ++ref_queue->mod_count;

    expected_mod_count = ref_queue->mod_count;
    return result;
}


template<class T>
std::string LinkedQueue<T>::Iterator::str() const {
    std::ostringstream result;
    result << ref_queue->str() << "(current=" << current << ",expected_mod_count=" << expected_mod_count << ",can_erase=" << can_erase << ")";
    return result.str();
}


template<class T>
auto LinkedQueue<T>::Iterator::operator ++ () -> LinkedQueue<T>::Iterator& {
    if (expected_mod_count != ref_queue->mod_count)
        throw ConcurrentModificationError("LinkedQueue::Iterator::operator ++");

    if (current == nullptr)
        return *this;

    if (can_erase) {
        prev = current;
        current = current->next;
    }
    else
        can_erase = true;

    return *this;
}


template<class T>
auto LinkedQueue<T>::Iterator::operator ++ (int) -> LinkedQueue<T>::Iterator {
    if (expected_mod_count != ref_queue->mod_count)
        throw ConcurrentModificationError("LinkedQueue::Iterator::operator ++");

    if (current == nullptr)
        return *this;

    Iterator result(*this);
    if (can_erase) {
        prev = current;
        current = current->next;
    }
    else
        can_erase = true;

    return result;
}


template<class T>
bool LinkedQueue<T>::Iterator::operator == (const LinkedQueue<T>::Iterator& rhs) const {
    const Iterator* rhsI = dynamic_cast<const Iterator*>(&rhs);
    if (rhsI == 0)
        throw IteratorTypeError("LinkedQueue::Iterator::operator ==");
    if (expected_mod_count != ref_queue->mod_count)
        throw ConcurrentModificationError("LinkedQueue::Iterator::operator ==");
    if (ref_queue != rhsI->ref_queue)
        throw ComparingDifferentIteratorsError("LinkedQueue::Iterator::operator ==");

    return current == rhsI->current;
}


template<class T>
bool LinkedQueue<T>::Iterator::operator != (const LinkedQueue<T>::Iterator& rhs) const {
    const Iterator* rhsI = dynamic_cast<const Iterator*>(&rhs);
    if (rhsI == 0)
        throw IteratorTypeError("LinkedQueue::Iterator::operator !=");
    if (expected_mod_count != ref_queue->mod_count)
        throw ConcurrentModificationError("LinkedQueue::Iterator::operator !=");
    if (ref_queue != rhsI->ref_queue)
        throw ComparingDifferentIteratorsError("LinkedQueue::Iterator::operator !=");

    return current != rhsI->current;
}


template<class T>
T& LinkedQueue<T>::Iterator::operator *() const {
    if (expected_mod_count != ref_queue->mod_count)
        throw ConcurrentModificationError("LinkedQueue::Iterator::operator *");
    if (!can_erase) {
        std::ostringstream where;
        where << current
              << " when front = " << ref_queue->front
              << " and rear = " << ref_queue->rear;
        throw IteratorPositionIllegal("LinkedQueue::Iterator::operator * Iterator illegal: " + where.str());
    }

    return current->value;
}


template<class T>
T* LinkedQueue<T>::Iterator::operator ->() const {
    if (expected_mod_count != ref_queue->mod_count)
        throw ConcurrentModificationError("LinkedQueue::Iterator::operator ->");
    if (!can_erase) {
        std::ostringstream where;
        where << current
              << " when front = " << ref_queue->front
              << " and rear = " << ref_queue->rear;
        throw IteratorPositionIllegal("LinkedQueue::Iterator::operator -> Iterator illegal: "+where.str());
    }

    return &current->value;
}


}

#endif /* LINKED_QUEUE_HPP_ */
