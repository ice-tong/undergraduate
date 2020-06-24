//Submitter: kfarsany(Farsany,Kian)

#ifndef HEAP_ADJUSTABLE_HASH_PRIORITY_QUEUE_HPP_
#define HEAP_ADJUSTABLE_HASH_PRIORITY_QUEUE_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include <utility>              //For std::swap function
#include "array_stack.hpp"      //See operator <<
#include "hash_map.hpp"


namespace ics {


#ifndef undefinedgtdefined
#define undefinedgtdefined
template<class T>
bool undefinedgt (const T& a, const T& b) {return false;}
#endif /* undefinedgtdefined */

//Instantiate the templated class supplying tgt(a,b): true, iff a has higher priority than b.
//If tgt is defaulted to undefinedgt in the template, then a constructor must supply cgt.
//If both tgt and cgt are supplied, then they must be the same (by ==) function.
//If neither is supplied, or both are supplied but different, TemplateFunctionError is raised.
//The (unique) non-undefinedgt value supplied by tgt/cgt is stored in the instance variable gt.
//Because of adjustability, also allow thash to be specified in the template, as it was in Hashmap.
template<class T, bool (*tgt)(const T& a, const T& b) = undefinedgt<T>, int (*thash)(const T& a) = undefinedhash<T>> class HeapAdjustableHashPriorityQueue {
  public:
    typedef bool (*gtfunc)   (const T& a, const T& b);
    typedef int  (*hashfunc) (const T& a);

    //Destructor/Constructors
    ~HeapAdjustableHashPriorityQueue();

    HeapAdjustableHashPriorityQueue(bool (*cgt)(const T& a, const T& b) = undefinedgt<T>, double the_load_threshold = 1.0, int (*chash)(const T& a) = undefinedhash<T>);
    explicit HeapAdjustableHashPriorityQueue(int initial_length, bool (*cgt)(const T& a, const T& b) = undefinedgt<T>, double the_load_threshold = 1.0, int (*chash)(const T& a) = undefinedhash<T>);
    HeapAdjustableHashPriorityQueue(const HeapAdjustableHashPriorityQueue<T,tgt,thash>& to_copy, bool (*cgt)(const T& a, const T& b) = undefinedgt<T>, double the_load_threshold = 1.0, int (*chash)(const T& a) = undefinedhash<T>);
    explicit HeapAdjustableHashPriorityQueue(const std::initializer_list<T>& il, bool (*cgt)(const T& a, const T& b) = undefinedgt<T>, double the_load_threshold = 1.0, int (*chash)(const T& a) = undefinedhash<T>);

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    explicit HeapAdjustableHashPriorityQueue (const Iterable& i, bool (*cgt)(const T& a, const T& b) = undefinedgt<T>, double the_load_threshold = 1.0, int (*chash)(const T& a) = undefinedhash<T>);


    //Queries
    bool empty      () const;
    int  size       () const;
    T&   peek       () const;
    std::string str () const; //supplies useful debugging information; contrast to operator <<


    //Commands
    int  enqueue (const T& element);
    T    dequeue ();
    void update  (const T& old_element, const T& new_element);
    void clear   ();

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    int enqueue_all (const Iterable& i);


    //Operators
    HeapAdjustableHashPriorityQueue<T,tgt,thash>& operator = (const HeapAdjustableHashPriorityQueue<T,tgt,thash>& rhs);
    bool operator == (const HeapAdjustableHashPriorityQueue<T,tgt,thash>& rhs) const;
    bool operator != (const HeapAdjustableHashPriorityQueue<T,tgt,thash>& rhs) const;

    template<class T2, bool (*gt2)(const T2& a, const T2& b), int (*hash2)(const T2&)>
    friend std::ostream& operator << (std::ostream& outs, const HeapAdjustableHashPriorityQueue<T2,gt2,hash2>& pq);



    class Iterator {
      public:
        //Private constructor called in begin/end, which are friends of HeapAdjustableHashPriorityQueue<T,tgt,thash>
        ~Iterator();
        T           erase();
        std::string str  () const;
        HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator& operator ++ ();
        HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator  operator ++ (int);
        bool operator == (const HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator& rhs) const;
        bool operator != (const HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator& rhs) const;
        T& operator *  () const;
        T* operator -> () const;
        friend std::ostream& operator << (std::ostream& outs, const HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator& i) {
          outs << i.str(); //Use the same meaning as the debugging .str() method
          return outs;
        }

        friend Iterator HeapAdjustableHashPriorityQueue<T,tgt,thash>::begin () const;
        friend Iterator HeapAdjustableHashPriorityQueue<T,tgt,thash>::end   () const;

      private:
        //If can_erase is false, the value has been removed from "it" (++ does nothing)
        HeapAdjustableHashPriorityQueue<T,tgt,thash>  it;                 //copy of HPQ (from begin), to use as iterator via dequeue
        HeapAdjustableHashPriorityQueue<T,tgt,thash>* ref_pq;
        int                       expected_mod_count;
        bool                      can_erase = true;

        //Called in friends begin/end
        //These constructors have different initializers (see it(...) in first one)
        Iterator(HeapAdjustableHashPriorityQueue<T,tgt,thash>* iterate_over, bool from_begin);    // Called by begin
        Iterator(HeapAdjustableHashPriorityQueue<T,tgt,thash>* iterate_over);                     // Called by end
    };


    Iterator begin () const;
    Iterator end   () const;


    //KLUDGE: test whether i == lookup[pq[i]]) for all indexes (public, but looks at private data)
    bool kludge_test_all_index_equivalences() {
      for (int i = 0; i < used; ++i) {
        //std::cout << i << "/" << pq[i] << ":" << lookup[pq[i]] << std::endl;
        if (i != lookup[pq[i]])
          return false;
      }
      return true;
    }


  private:
    bool (*gt) (const T& a, const T& b); // The gt used by enqueue (from template or constructor)
    T*  pq;                              // Array represents a heap, so it uses heap ordering property
    HashMap<T,int,thash> lookup;         // Stores position for each value in Map (assume
    int length    = 0;                   //Physical length of array: must be >= .size()
    int used      = 0;                   //Amount of array used:  invariant: 0 <= used <= length
    int mod_count = 0;                   //For sensing concurrent modification


    //Helper methods
    void ensure_length  (int new_length);
    int  left_child     (int i) const;      //Useful abstractions for heaps as arrays
    int  right_child    (int i) const;
    int  parent         (int i) const;
    bool is_root        (int i) const;
    bool in_heap        (int i) const;
    void swap           (int i, int j);     //Update both the pq and lookup data structures
    void percolate_up   (int i);
    void percolate_down (int i);
    void heapify        ();                 // Percolate down all value is array (from indexes used-1 to 0): O(N)
  };





////////////////////////////////////////////////////////////////////////////////
//
//HeapAdjustableHashPriorityQueue class and related definitions

//Destructor/Constructors

template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
HeapAdjustableHashPriorityQueue<T,tgt,thash>::~HeapAdjustableHashPriorityQueue() {
  delete[] pq;
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
HeapAdjustableHashPriorityQueue<T,tgt,thash>::HeapAdjustableHashPriorityQueue(bool (*cgt)(const T& a, const T& b), double the_load_threshold, int (*chash)(const T& a))
: gt(tgt != (gtfunc)undefinedgt<T> ? tgt : cgt), lookup(the_load_threshold,thash != (hashfunc)undefinedhash<T> ? thash : chash) {
  if (gt == (gtfunc)undefinedgt<T>)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::default constructor: neither tgt/cgt specified");
  if (tgt != (gtfunc)undefinedgt<T> && cgt != (gtfunc)undefinedgt<T> && tgt != cgt)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::default constructor: both tgt/cgt specified and different");

  if (thash == (hashfunc)undefinedhash<T> && chash == (hashfunc)undefinedhash<T>)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::default constructor: neither thash/chash specified");
  if (thash != (hashfunc)undefinedhash<T> && chash != (hashfunc)undefinedhash<T> && thash != chash)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::default constructor: both thash/chash specified and different");

  pq = new T[length];
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
HeapAdjustableHashPriorityQueue<T,tgt,thash>::HeapAdjustableHashPriorityQueue(int initial_length, bool (*cgt)(const T& a, const T& b), double the_load_threshold, int (*chash)(const T& a))
: gt(tgt != (gtfunc)undefinedgt<T> ? tgt : cgt), length(initial_length), lookup(the_load_threshold,thash != (hashfunc)undefinedhash<T> ? thash : chash) {
  if (gt == (gtfunc)undefinedgt<T>)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::length constructor: neither tgt/cgt specified");
  if (tgt != (gtfunc)undefinedgt<T> && cgt != (gtfunc)undefinedgt<T> && tgt != cgt)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::length constructor: both tgt/cgt specified and different");

  if (thash == (hashfunc)undefinedhash<T> && chash == (hashfunc)undefinedhash<T>)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::default constructor: neither thash/chash specified");
  if (thash != (hashfunc)undefinedhash<T> && chash != (hashfunc)undefinedhash<T> && thash != chash)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::default constructor: both thash/chash specified and different");

  if (length < 0)
    length = 0;
  pq = new T[length];
}


//Copy pq but cannot get information about embedded hash; so that must be supplied, which means cgt must be supplied
template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
HeapAdjustableHashPriorityQueue<T,tgt,thash>::HeapAdjustableHashPriorityQueue(const HeapAdjustableHashPriorityQueue<T,tgt,thash>& to_copy, bool (*cgt)(const T& a, const T& b), double the_load_threshold, int (*chash)(const T& a))
//  : gt(tgt != (gtfunc)undefinedgt<T> ? tgt : cgt), length(to_copy.length), used(to_copy.used), lookup(the_load_threshold,thash != (hashfunc)undefinedhash<T> ? thash : chash != (hashfunc)undefinedhash<T> ? chash : to_copy.lookup.hash) {
  : gt(tgt != (gtfunc)undefinedgt<T> ? tgt : cgt), length(to_copy.length), used(to_copy.used), lookup(the_load_threshold,thash != (hashfunc)undefinedhash<T> ? thash : chash) {
  if (gt == (gtfunc)undefinedgt<T>)
    gt = to_copy.gt;//throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::copy constructor: neither specified");
  if (tgt != (gtfunc)undefinedgt<T> && cgt != (gtfunc)undefinedgt<T> && tgt != cgt)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::copy constructor: both tgt/cgt specified and different");

//  if (lookup.hash == (hashfunc)undefinedhash<T>)
  if (thash == (hashfunc)undefinedhash<T> && chash == (hashfunc)undefinedhash<T>)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::copy constructor: neither thash/chash specified");
  if (thash != (hashfunc)undefinedhash<T> && chash != (hashfunc)undefinedhash<T> && thash != chash)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::copy constructor: both thash/chash specified and different");

  pq = new T[length];
  for (int i=0; i<to_copy.used; ++i){
    pq[i] = to_copy.pq[i];
    lookup.put(pq[i],i);
  }

  if (gt != to_copy.gt)
    heapify();
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
HeapAdjustableHashPriorityQueue<T,tgt,thash>::HeapAdjustableHashPriorityQueue(const std::initializer_list<T>& il, bool (*cgt)(const T& a, const T& b), double the_load_threshold, int (*chash)(const T& a))
: gt(tgt != (gtfunc)undefinedgt<T> ? tgt : cgt), length(il.size()), lookup(the_load_threshold,thash != (hashfunc)undefinedhash<T> ? thash : chash) {
  if (gt == (gtfunc)undefinedgt<T>)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::initializer_list constructor: neither tgt/cgt specified");
  if (tgt != (gtfunc)undefinedgt<T> && cgt != (gtfunc)undefinedgt<T> && tgt != cgt)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::initializer_list constructor: both tgt/cgt specified and different");

  if (thash == (hashfunc)undefinedhash<T> && chash == (hashfunc)undefinedhash<T>)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::initializer_list constructor: neither thash/chash specified");
  if (thash != (hashfunc)undefinedhash<T> && chash != (hashfunc)undefinedhash<T> && thash != chash)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::initializer_list constructor: both thash/chash specified and different");

  pq = new T[length];
  int i = 0;
  for (const T& pq_elem : il) {
    if (lookup.has_key(pq_elem)) {
      std::ostringstream answer;
      answer << "HeapAdjustableHashPriorityQueue::initializer_list constructor: element(" << pq_elem << ") already in PriorityQueue";
      delete [] pq;
      throw KeyError(answer.str());
    }
    pq[i++] = pq_elem;
    lookup.put(pq_elem,i-1);
  }
  used = length;
  heapify();
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
template<class Iterable>
HeapAdjustableHashPriorityQueue<T,tgt,thash>::HeapAdjustableHashPriorityQueue(const Iterable& i, bool (*cgt)(const T& a, const T& b), double the_load_threshold, int (*chash)(const T& a))
: gt(tgt != (gtfunc)undefinedgt<T> ? tgt : cgt), length(i.size()), lookup(the_load_threshold,thash != (hashfunc)undefinedhash<T> ? thash : chash) {
  if (gt == (gtfunc)undefinedgt<T>)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::Iterable constructor: neither tgt/cgt specified");
  if (tgt != (gtfunc)undefinedgt<T> && cgt != (gtfunc)undefinedgt<T> && tgt != cgt)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::Iterable constructor: both tgt/cgt specified and different");

  if (thash == (hashfunc)undefinedhash<T> && chash == (hashfunc)undefinedhash<T>)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::Iterable constructor: neither thash/chash specified");
  if (thash != (hashfunc)undefinedhash<T> && chash != (hashfunc)undefinedhash<T> && thash != chash)
    throw TemplateFunctionError("HeapAdjustableHashPriorityQueue::Iterable constructor: both thash/chash specified and different");

  pq = new T[length];
  int j = 0;
  for (const T& pq_elem : i) {
    if (lookup.has_key(pq_elem)) {
      std::ostringstream answer;
      answer << "HeapAdjustableHashPriorityQueue::Iterable constructor: element(" << pq_elem << ") already in PriorityQueue";
      delete [] pq;
      throw KeyError(answer.str());
    }
    pq[j++] = pq_elem;
    lookup.put(pq_elem,j-1);
  }
  used = length;
  heapify();
}


////////////////////////////////////////////////////////////////////////////////
//
//Queries

template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
bool HeapAdjustableHashPriorityQueue<T,tgt,thash>::empty() const {
  return used == 0;
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
int HeapAdjustableHashPriorityQueue<T,tgt,thash>::size() const {
  return used;
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
T& HeapAdjustableHashPriorityQueue<T,tgt,thash>::peek () const {
  if (empty())
    throw EmptyError("HeapAdjustableHashPriorityQueue::peek");

  return pq[0];
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
std::string HeapAdjustableHashPriorityQueue<T,tgt,thash>::str() const {
  std::ostringstream answer;
  answer << "HeapAdjustableHashPriorityQueue[";

  if (used != 0) {
    answer << "0:" << pq[0];
    for (int i = 1; i < used; ++i)
      answer << "," << i << ":" << pq[i];
  }

  answer << "](lookup=" << lookup << ",length=" << length << ",used=" << used << ",mod_count=" << mod_count << ")";
  return answer.str();
}


////////////////////////////////////////////////////////////////////////////////
//
//Commands

template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
int HeapAdjustableHashPriorityQueue<T,tgt,thash>::enqueue(const T& element) {
  if (lookup.has_key(element))
      throw IcsError("HeapAdjustableHashPriorityQueue::enqueue");

  this->ensure_length(used+1);
  lookup.put(element, used);
  pq[used++] = element;

  this->percolate_up(used-1);
  ++mod_count;
  return 1;
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
T HeapAdjustableHashPriorityQueue<T,tgt,thash>::dequeue() {
  if (this->empty())
    throw EmptyError("HeapAdjustableHashPriorityQueue::dequeue");

  T to_return = pq[0];
  pq[0] = pq[--used];
  lookup.erase(to_return);
  if (!lookup.empty())
    lookup[pq[0]] = 0;

  percolate_down(0);

  ++mod_count;
  return to_return;
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
void HeapAdjustableHashPriorityQueue<T,tgt,thash>::update(const T& old_element, const T& new_element) {
    if (lookup.has_key(new_element) || !lookup.has_key(old_element))
        if (old_element != new_element)
            throw IcsError("HeapAdjustableHashPriorityQueue::update");

    int i = lookup[old_element];
    pq[i] = new_element;
    lookup.erase(old_element);
    lookup.put(new_element,i);
    percolate_up(i);
    percolate_down(i);
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
void HeapAdjustableHashPriorityQueue<T,tgt,thash>::clear() {
  lookup.clear();
  used = 0;
  ++mod_count;
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
template <class Iterable>
int HeapAdjustableHashPriorityQueue<T,tgt,thash>::enqueue_all (const Iterable& i) {
  int count = 0;
  for (const T& v : i)
     count += enqueue(v);

  return count;
}


////////////////////////////////////////////////////////////////////////////////
//
//Operators

template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
HeapAdjustableHashPriorityQueue<T,tgt,thash>& HeapAdjustableHashPriorityQueue<T,tgt,thash>::operator = (const HeapAdjustableHashPriorityQueue<T,tgt,thash>& rhs) {
  if (this == &rhs)
    return *this;

  gt = rhs.gt;   // if tgt != nullptr, gts are already equal (or compiler error)
  this->ensure_length(rhs.used);
  used = rhs.used;
  for (int i=0; i<rhs.used; ++i) {
      pq[i] = rhs.pq[i];
      lookup[pq[i]] = i;
  }

  ++mod_count;
  return *this;
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
bool HeapAdjustableHashPriorityQueue<T,tgt,thash>::operator == (const HeapAdjustableHashPriorityQueue<T,tgt,thash>& rhs) const {
  if (this == &rhs)
    return true;
  if (gt != rhs.gt) //For PriorityQueues to be equal, they need the same gt function, and values
    return false;
  if (used != rhs.size())
    return false;
  HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator l = this->begin(), r = rhs.begin();
  for (int i=0; i<used; ++i, ++l, ++r)
    if (*l != *r)
      return false;

  return true;
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
bool HeapAdjustableHashPriorityQueue<T,tgt,thash>::operator != (const HeapAdjustableHashPriorityQueue<T,tgt,thash>& rhs) const {
  return !(*this == rhs);
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
std::ostream& operator << (std::ostream& outs, const HeapAdjustableHashPriorityQueue<T,tgt,thash>& p) {
  outs << "priority_queue[";

  if (!p.empty()) {
    ArrayStack<T> temp(p);
    outs << temp.pop();
    for (int i = 1; i < p.used; ++i)
      outs << "," << temp.pop();
  }

  outs << "]:highest";
  return outs;
}


////////////////////////////////////////////////////////////////////////////////
//
//Iterator constructors

template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
auto HeapAdjustableHashPriorityQueue<T,tgt,thash>::begin () const -> HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator {
    return Iterator(const_cast<HeapAdjustableHashPriorityQueue<T,tgt,thash>*>(this),true);
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
auto HeapAdjustableHashPriorityQueue<T,tgt,thash>::end () const -> HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator {
  return Iterator(const_cast<HeapAdjustableHashPriorityQueue<T,tgt,thash>*>(this),false);  //Create empty pq (size == 0)
}


////////////////////////////////////////////////////////////////////////////////
//
//Private helper methods

template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
void HeapAdjustableHashPriorityQueue<T,tgt,thash>::ensure_length(int new_length) {
  if (length >= new_length)
    return;
  T*  old_pq  = pq;
  length = std::max(new_length,2*length);
  pq = new T[length];
  for (int i=0; i<used; ++i)
    pq[i] = old_pq[i];

  delete [] old_pq;
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
int HeapAdjustableHashPriorityQueue<T,tgt,thash>::left_child(int i) const
{return 2*i+1;}

template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
int HeapAdjustableHashPriorityQueue<T,tgt,thash>::right_child(int i) const
{return 2*i+2;}

template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
int HeapAdjustableHashPriorityQueue<T,tgt,thash>::parent(int i) const
{return (i-1)/2;}

template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
bool HeapAdjustableHashPriorityQueue<T,tgt,thash>::is_root(int i) const
{return i == 0;}

template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
bool HeapAdjustableHashPriorityQueue<T,tgt,thash>::in_heap(int i) const
{return i < used;}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
void HeapAdjustableHashPriorityQueue<T,tgt,thash>::swap(int i, int j) {
    lookup[pq[i]] = j;
    lookup[pq[j]] = i;
    std::swap(pq[i],pq[j]);
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
void HeapAdjustableHashPriorityQueue<T,tgt,thash>::percolate_up(int i) {
  for (/*parameter*/; !is_root(i) && gt(pq[i],pq[parent(i)]); i = parent(i))
    swap(parent(i),i);
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
void HeapAdjustableHashPriorityQueue<T,tgt,thash>::percolate_down(int i) {
  for (int l = left_child(i); in_heap(l); l = left_child(i)) {
    int r = right_child(i);
    int max_child = (!in_heap(r) || gt(pq[l],pq[r]) ? l : r);
    if ( gt(pq[i],pq[max_child]) )
       break;
    swap(i,max_child);
    i = max_child;
  }
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
void HeapAdjustableHashPriorityQueue<T,tgt,thash>::heapify() {
  for (int i = used-1; i >= 0; --i)
    percolate_down(i);
}


////////////////////////////////////////////////////////////////////////////////
//
//Iterator class definitions

//template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
//HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator::Iterator(HeapAdjustableHashPriorityQueue<T,tgt,thash>* iterate_over, bool from_begin)
//: it(*iterate_over,iterate_over->gt), ref_pq(iterate_over), expected_mod_count(iterate_over->mod_count) {
//  // Full priority queue; use copy constructor
//}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator::Iterator(HeapAdjustableHashPriorityQueue<T,tgt,thash>* iterate_over, bool from_begin)
: it(iterate_over->gt), ref_pq(iterate_over), expected_mod_count(iterate_over->mod_count) {
  if (from_begin)
    it = *iterate_over;// Empty priority queue; use default constructor (from declaration of "it")
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator::~Iterator()
{}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
T HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator::erase() {
  if (expected_mod_count != ref_pq->mod_count)
    throw ConcurrentModificationError("HeapAdjustableHashPriorityQueue::Iterator::erase");
  if (!can_erase)
    throw CannotEraseError("HeapAdjustableHashPriorityQueue::Iterator::erase Iterator cursor already erased");
  if (it.empty())
    throw CannotEraseError("HeapAdjustableHashPriorityQueue::Iterator::erase Iterator cursor beyond data structure");

  can_erase = false;
  T to_return = it.dequeue();

  int i = ref_pq->lookup[to_return];
  ref_pq->pq[i] = ref_pq->pq[--ref_pq->used];
  ref_pq->lookup.erase(to_return);
  if (!ref_pq->lookup.empty())
      ref_pq->lookup[ref_pq->pq[i]] = i;
  ref_pq->percolate_up(i);
  ref_pq->percolate_down(i);


  expected_mod_count = ref_pq->mod_count;
  return to_return;
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
std::string HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator::str() const {
  std::ostringstream answer;
  answer << it.str() << "/expected_mod_count=" << expected_mod_count << "/can_erase=" << can_erase;
  return answer.str();
}



template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
auto HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator::operator ++ () -> HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator& {
  if (expected_mod_count != ref_pq->mod_count)
    throw ConcurrentModificationError("HeapAdjustableHashPriorityQueue::Iterator::operator ++");

  if (it.empty())
    return *this;

  if (can_erase)
    it.dequeue();
  else
    can_erase = true;

  return *this;
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
auto HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator::operator ++ (int) -> HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator {
  if (expected_mod_count != ref_pq->mod_count)
    throw ConcurrentModificationError("HeapAdjustableHashPriorityQueue::Iterator::operator ++(int)");

  if (it.empty())
    return *this;

  Iterator to_return(*this);
  if (can_erase)
    it.dequeue();
  else
    can_erase = true;

  return to_return;
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
bool HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator::operator == (const HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator& rhs) const {
  const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
  if (rhsASI == 0)
    throw IteratorTypeError("HeapAdjustableHashPriorityQueue::Iterator::operator ==");
  if (expected_mod_count != ref_pq->mod_count)
    throw ConcurrentModificationError("HeapAdjustableHashPriorityQueue::Iterator::operator ==");
  if (ref_pq != rhsASI->ref_pq)
    throw ComparingDifferentIteratorsError("HeapAdjustableHashPriorityQueue::Iterator::operator ==");

  //Two iterators on the same heap are equal if their sizes are equal
  return this->it.size() == rhsASI->it.size();
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
bool HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator::operator != (const HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator& rhs) const {
  const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
  if (rhsASI == 0)
    throw IteratorTypeError("HeapAdjustableHashPriorityQueue::Iterator::operator !=");
  if (expected_mod_count != ref_pq->mod_count)
    throw ConcurrentModificationError("HeapAdjustableHashPriorityQueue::Iterator::operator !=");
  if (ref_pq != rhsASI->ref_pq)
    throw ComparingDifferentIteratorsError("HeapAdjustableHashPriorityQueue::Iterator::operator !=");

  return this->it.size() != rhsASI->it.size();
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
T& HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator::operator *() const {
  if (expected_mod_count != ref_pq->mod_count)
    throw ConcurrentModificationError("HeapAdjustableHashPriorityQueue::Iterator::operator *");
  if (!can_erase || it.empty())
    throw IteratorPositionIllegal("HeapAdjustableHashPriorityQueue::Iterator::operator * Iterator illegal: exhausted");

  return it.peek();
}


template<class T, bool (*tgt)(const T& a, const T& b), int (*thash)(const T& a)>
T* HeapAdjustableHashPriorityQueue<T,tgt,thash>::Iterator::operator ->() const {
  if (expected_mod_count != ref_pq->mod_count)
    throw ConcurrentModificationError("HeapAdjustableHashPriorityQueue::Iterator::operator *");
  if (!can_erase || it.empty())
    throw IteratorPositionIllegal("HeapAdjustableHashPriorityQueue::Iterator::operator -> Iterator illegal: exhausted");

  return &it.peek();
}

}

#endif /* HEAP_ADJUSTABLE_HASH_PRIORITY_QUEUE_HPP_ */
