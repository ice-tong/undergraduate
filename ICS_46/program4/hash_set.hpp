//Submitter: kfarsany(Farsany,Kian)

#ifndef HASH_SET_HPP_
#define HASH_SET_HPP_

#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include "ics_exceptions.hpp"
#include "pair.hpp"


namespace ics {


#ifndef undefinedhashdefined
#define undefinedhashdefined
template<class T>
int undefinedhash (const T& a) {return 0;}
#endif /* undefinedhashdefined */

//Instantiate the templated class supplying thash(a): produces a hash value for a.
//If thash is defaulted to undefinedhash in the template, then a constructor must supply chash.
//If both thash and chash are supplied, then they must be the same (by ==) function.
//If neither is supplied, or both are supplied but different, TemplateFunctionError is raised.
//The (unique) non-undefinedhash value supplied by thash/chash is stored in the instance variable hash.
template<class T, int (*thash)(const T& a) = undefinedhash<T>> class HashSet {
  public:
    typedef int (*hashfunc) (const T& a);

    //Destructor/Constructors
    ~HashSet ();

    HashSet (double the_load_threshold = 1.0, int (*chash)(const T& a) = undefinedhash<T>);
    explicit HashSet (int initial_bins, double the_load_threshold = 1.0, int (*chash)(const T& k) = undefinedhash<T>);
    HashSet (const HashSet<T,thash>& to_copy, double the_load_threshold = 1.0, int (*chash)(const T& a) = undefinedhash<T>);
    explicit HashSet (const std::initializer_list<T>& il, double the_load_threshold = 1.0, int (*chash)(const T& a) = undefinedhash<T>);

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    explicit HashSet (const Iterable& i, double the_load_threshold = 1.0, int (*chash)(const T& a) = undefinedhash<T>);


    //Queries
    bool empty      () const;
    int  size       () const;
    bool contains   (const T& element) const;
    std::string str () const; //supplies useful debugging information; contrast to operator <<

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    bool contains_all (const Iterable& i) const;


    //Commands
    int  insert (const T& element);
    int  erase  (const T& element);
    void clear  ();

    //Iterable class must support "for" loop: .begin()/.end() and prefix ++ on returned result

    template <class Iterable>
    int insert_all(const Iterable& i);

    template <class Iterable>
    int erase_all(const Iterable& i);

    template<class Iterable>
    int retain_all(const Iterable& i);


    //Operators
    HashSet<T,thash>& operator = (const HashSet<T,thash>& rhs);
    bool operator == (const HashSet<T,thash>& rhs) const;
    bool operator != (const HashSet<T,thash>& rhs) const;
    bool operator <= (const HashSet<T,thash>& rhs) const;
    bool operator <  (const HashSet<T,thash>& rhs) const;
    bool operator >= (const HashSet<T,thash>& rhs) const;
    bool operator >  (const HashSet<T,thash>& rhs) const;

    template<class T2, int (*hash2)(const T2& a)>
    friend std::ostream& operator << (std::ostream& outs, const HashSet<T2,hash2>& s);



  private:
    class LN;

  public:
    class Iterator {
      public:
        typedef pair<int,LN*> Cursor;

        //Private constructor called in begin/end, which are friends of HashSet<T,thash>
        ~Iterator();
        T           erase();
        std::string str  () const;
        HashSet<T,thash>::Iterator& operator ++ ();
        HashSet<T,thash>::Iterator  operator ++ (int);
        bool operator == (const HashSet<T,thash>::Iterator& rhs) const;
        bool operator != (const HashSet<T,thash>::Iterator& rhs) const;
        T& operator *  () const;
        T* operator -> () const;
        friend std::ostream& operator << (std::ostream& outs, const HashSet<T,thash>::Iterator& i) {
          outs << i.str(); //Use the same meaning as the debugging .str() method
          return outs;
        }
        friend Iterator HashSet<T,thash>::begin () const;
        friend Iterator HashSet<T,thash>::end   () const;

      private:
        //If can_erase is false, current indexes the "next" value (must ++ to reach it)
        Cursor              current; //Pair:Bin Index/LN*; stops if LN* == nullptr
        HashSet<T,thash>*   ref_set;
        int                 expected_mod_count;
        bool                can_erase = true;

        //Helper methods
        void advance_cursors();

        //Called in friends begin/end
        Iterator(HashSet<T,thash>* iterate_over, bool from_begin);
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
        LN* next   = nullptr;
    };

public:
  int (*hash)(const T& k);   //Hashing function used (from template or constructor)
private:
  LN** set      = nullptr;   //Pointer to array of pointers: each bin stores a list with a trailer node
  double load_threshold;     //used/bins <= load_threshold
  int bins      = 1;         //# bins currently in array (start it >= 1 so no divide by 0 in hash_compress)
  int used      = 0;         //Cache for number of elements in the hash table
  int mod_count = 0;         //For sensing concurrent modification


  //Helper methods
  int   hash_compress        (const T& element)          const;  //hash function ranged to [0,bins-1]
  LN*   find_element         (const T& element)          const;  //Returns reference to element's node or nullptr
  LN*   copy_list            (LN*   l)                   const;  //Copy the elements in a bin (order irrelevant)
  LN**  copy_hash_table      (LN** ht, int bins)         const;  //Copy the bins/keys/values in ht (order in bins irrelevant)

  void  ensure_load_threshold(int new_used);                     //Reallocate if load_threshold > load_threshold
  void  delete_hash_table    (LN**& ht, int bins);               //Deallocate all LN in ht (and the ht itself; ht == nullptr)
};





//HashSet class and related definitions

////////////////////////////////////////////////////////////////////////////////
//
//Destructor/Constructors

template<class T, int (*thash)(const T& a)>
HashSet<T,thash>::~HashSet() {
    delete_hash_table(set, bins);
}


template<class T, int (*thash)(const T& a)>
HashSet<T,thash>::HashSet(double the_load_threshold, int (*chash)(const T& element))
: load_threshold(the_load_threshold), hash(thash != (hashfunc)undefinedhash<T> ? thash : chash) {
    if (hash == (hashfunc)undefinedhash<T>)
        throw TemplateFunctionError("HashSet::default constructor: neither specified");
    if (thash != (hashfunc)undefinedhash<T> && chash != (hashfunc)undefinedhash<T> && thash != chash)
        throw TemplateFunctionError("HashSet::default constructor: both specified and different");

    set = new LN*[bins];
    for (int i = 0; i < bins; ++i)
        set[i] = new LN();
}


template<class T, int (*thash)(const T& a)>
HashSet<T,thash>::HashSet(int initial_bins, double the_load_threshold, int (*chash)(const T& element))
: bins(initial_bins), load_threshold(the_load_threshold), hash(thash != (hashfunc)undefinedhash<T> ? thash : chash) {
    if (hash == (hashfunc)undefinedhash<T>)
        throw TemplateFunctionError("HashSet::bins constructor: neither specified");
    if (thash != (hashfunc)undefinedhash<T> && chash != (hashfunc)undefinedhash<T> && thash != chash)
        throw TemplateFunctionError("HashSet::bins constructor: both specified and different");

    set = new LN*[bins];
    for (int i = 0; i < bins; ++i)
        set[i] = new LN();
}


template<class T, int (*thash)(const T& a)>
HashSet<T,thash>::HashSet(const HashSet<T,thash>& to_copy, double the_load_threshold, int (*chash)(const T& element))
: load_threshold(the_load_threshold), hash(thash != (hashfunc)undefinedhash<T> ? thash : chash) {
    if (hash == (hashfunc)undefinedhash<T>)
        hash = to_copy.hash;
    if (thash != (hashfunc)undefinedhash<T> && chash != (hashfunc)undefinedhash<T> && thash != chash)
        throw TemplateFunctionError("HashSet::copy constructor: both specified and different");

    if (hash == to_copy.hash) {
        set = copy_hash_table(to_copy.set, to_copy.bins);
        used = to_copy.used;
        bins = to_copy.bins;
    }
    else {
        set = new LN*[bins];
        for (int i = 0; i < bins; ++i)
            set[i] = new LN();
        insert_all(to_copy);
    }
}


template<class T, int (*thash)(const T& a)>
HashSet<T,thash>::HashSet(const std::initializer_list<T>& il, double the_load_threshold, int (*chash)(const T& element))
: load_threshold(the_load_threshold), hash(thash != (hashfunc)undefinedhash<T> ? thash : chash) {
    if (hash == (hashfunc)undefinedhash<T>)
        throw TemplateFunctionError("HashSet::initializer_list constructor: neither specified");
    if (thash != (hashfunc)undefinedhash<T> && chash != (hashfunc)undefinedhash<T> && thash != chash)
        throw TemplateFunctionError("HashSet::initializer_list constructor: both specified and different");

    set = new LN*[bins];
    for (int i = 0; i < bins; ++i)
        set[i] = new LN();

    for (const T& e : il)
        insert(e);
}


template<class T, int (*thash)(const T& a)>
template<class Iterable>
HashSet<T,thash>::HashSet(const Iterable& i, double the_load_threshold, int (*chash)(const T& a))
: load_threshold(the_load_threshold), hash(thash != (hashfunc)undefinedhash<T> ? thash : chash) {
    if (hash == (hashfunc)undefinedhash<T>)
        throw TemplateFunctionError("HashSet::Iterable constructor: neither specified");
    if (thash != (hashfunc)undefinedhash<T> && chash != (hashfunc)undefinedhash<T> && thash != chash)
        throw TemplateFunctionError("HashSet::Iterable constructor: both specified and different");

    set = new LN*[bins];
    for (int i = 0; i < bins; ++i)
        set[i] = new LN();

    for (const T& e : i)
        insert(e);
}


////////////////////////////////////////////////////////////////////////////////
//
//Queries

template<class T, int (*thash)(const T& a)>
bool HashSet<T,thash>::empty() const {
    return used == 0;
}


template<class T, int (*thash)(const T& a)>
int HashSet<T,thash>::size() const {
    return used;
}


template<class T, int (*thash)(const T& a)>
bool HashSet<T,thash>::contains (const T& element) const {
    return find_element(element) != nullptr;
}


template<class T, int (*thash)(const T& a)>
std::string HashSet<T,thash>::str() const {
    std::ostringstream result;
    for (int i = 0; i < bins; ++i) {
        result << "bin[" << i << "]: ";
        for (LN* p = set[i]; p != nullptr; p = p->next) {
            if (p->next == nullptr)
                result << "TRAILER" << std::endl;
            else
                result << p->value << " -> ";
        }
    }
    return result.str();
}


template<class T, int (*thash)(const T& a)>
template <class Iterable>
bool HashSet<T,thash>::contains_all(const Iterable& i) const {
    for (const T& elem : i)
        if (!contains(elem))
            return false;

    return true;
}


////////////////////////////////////////////////////////////////////////////////
//
//Commands

template<class T, int (*thash)(const T& a)>
int HashSet<T,thash>::insert(const T& element) {
    ++mod_count;
    LN* in_set = find_element(element);
    if (in_set != nullptr)
        return 0;
    else {
        ensure_load_threshold(++used);
        int i = hash_compress(element);
        set[i] = new LN(element, set[i]);
        return 1;
    }
}


template<class T, int (*thash)(const T& a)>
int HashSet<T,thash>::erase(const T& element) {
    ++mod_count;
    LN* found_elem = find_element(element);
    if (found_elem != nullptr) {
        LN* to_del = found_elem->next;
        *found_elem = *to_del;
        delete to_del;
        --used;
        return 1;
    }

    return 0;
}


template<class T, int (*thash)(const T& a)>
void HashSet<T,thash>::clear() {
    ++mod_count;
    for (int i = 0; i < bins; ++i) {
        while(set[i]->next != nullptr) {
            LN* to_del = set[i];
            set[i] = set[i]->next;
            delete to_del;
        }
    }
    used = 0;
}


template<class T, int (*thash)(const T& a)>
template<class Iterable>
int HashSet<T,thash>::insert_all(const Iterable& i) {
    int result = 0;
    for (const T& e : i)
        result += insert(e);

    return result;
}


template<class T, int (*thash)(const T& a)>
template<class Iterable>
int HashSet<T,thash>::erase_all(const Iterable& i) {
    int result = 0;
    for (const T& e : i)
        result += erase(e);

    return result;
}


template<class T, int (*thash)(const T& a)>
template<class Iterable>
int HashSet<T,thash>::retain_all(const Iterable& i) {
    HashSet s(i);
    int result = 0;
    for (int i = 0; i < bins; ++i)
        for (LN* p = set[i]; p->next != nullptr; ) {
            if (!s.contains(p->value)) {
                erase(p->value);
                ++result;
            } else
                p = p->next;
        }

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//Operators

template<class T, int (*thash)(const T& a)>
HashSet<T,thash>& HashSet<T,thash>::operator = (const HashSet<T,thash>& rhs) {
    if (this == &rhs)
        return *this;

    hash = rhs.hash;
    LN** to_del = set;
    set = copy_hash_table(rhs.set, rhs.bins);
    delete to_del;

    used = rhs.used;
    bins = rhs.bins;
    ++mod_count;
    return *this;
}


template<class T, int (*thash)(const T& a)>
bool HashSet<T,thash>::operator == (const HashSet<T,thash>& rhs) const {
    if (this == &rhs)
        return true;

    if (used != rhs.size())
        return false;

    for (int i = 0; i < bins; ++i)
        for (LN* p = set[i]; p->next != nullptr; p = p->next)
            if (!rhs.contains(p->value))
                return false;
    return true;
}


template<class T, int (*thash)(const T& a)>
bool HashSet<T,thash>::operator != (const HashSet<T,thash>& rhs) const {
    return !(*this == rhs);
}


template<class T, int (*thash)(const T& a)>
bool HashSet<T,thash>::operator <= (const HashSet<T,thash>& rhs) const {
    if (this == &rhs)
        return true;

    if (used > rhs.size())
        return false;

    for (int i = 0; i < bins; ++i)
        for (LN* p = set[i]; p->next != nullptr; p = p->next)
            if (!rhs.contains(p->value))
                return false;

    return true;
}

template<class T, int (*thash)(const T& a)>
bool HashSet<T,thash>::operator < (const HashSet<T,thash>& rhs) const {
    if (this == &rhs)
        return false;

    if (used >= rhs.size())
        return false;

    for (int i = 0; i < bins; ++i)
        for (LN* p = set[i]; p->next != nullptr; p = p->next)
            if (!rhs.contains(p->value))
                return false;

    return true;
}


template<class T, int (*thash)(const T& a)>
bool HashSet<T,thash>::operator >= (const HashSet<T,thash>& rhs) const {
    return rhs <= *this;
}


template<class T, int (*thash)(const T& a)>
bool HashSet<T,thash>::operator > (const HashSet<T,thash>& rhs) const {
    return rhs < *this;
}


template<class T, int (*thash)(const T& a)>
std::ostream& operator << (std::ostream& outs, const HashSet<T,thash>& s) {
    outs << "set[";

    if (!s.empty()) {
        typename HashSet<T,thash>::Iterator i = s.begin();
        outs << (*i);
        ++i;
        for (; i != s.end(); ++i)
            outs << "," << (*i);
    }

    outs << "]";
    return outs;
}


////////////////////////////////////////////////////////////////////////////////
//
//Iterator constructors

template<class T, int (*thash)(const T& a)>
auto HashSet<T,thash>::begin () const -> HashSet<T,thash>::Iterator {
    return Iterator(const_cast<HashSet<T,thash>*>(this),true);
}


template<class T, int (*thash)(const T& a)>
auto HashSet<T,thash>::end () const -> HashSet<T,thash>::Iterator {
    return Iterator(const_cast<HashSet<T,thash>*>(this),false);
}


///////////////////////////////////////////////////////////////////////////////
//
//Private helper methods

template<class T, int (*thash)(const T& a)>
int HashSet<T,thash>::hash_compress (const T& element) const {
    return abs(hash(element)) % bins;
}


template<class T, int (*thash)(const T& a)>
typename HashSet<T,thash>::LN* HashSet<T,thash>::find_element (const T& element) const {
    for (LN* p = set[hash_compress(element)]; p->next != nullptr; p = p->next)
        if (p->value == element)
            return p;
    return nullptr;
}

template<class T, int (*thash)(const T& a)>
typename HashSet<T,thash>::LN* HashSet<T,thash>::copy_list (LN* l) const {
    if (l == nullptr)
        return nullptr;
    else
        return new LN(l->value, copy_list(l->next));
}


template<class T, int (*thash)(const T& a)>
typename HashSet<T,thash>::LN** HashSet<T,thash>::copy_hash_table (LN** ht, int bins) const {
    LN** result = new LN*[bins];
    for (int i = 0; i < bins; ++i)
        result[i] = copy_list(ht[i]);
    return result;
}


template<class T, int (*thash)(const T& a)>
void HashSet<T,thash>::ensure_load_threshold(int new_used) {
    double lf = static_cast<double>(new_used) / bins;
    if (lf <= load_threshold)
        return;
    else {
        int old_bins = bins;
        bins = bins*2;
        LN** old_set = set;
        set = new LN*[bins];
        for (int i = 0; i < bins; ++i)
            set[i] = new LN();
        for (int i = 0; i < old_bins; ++i) {
            for (LN* p = old_set[i]; p->next != nullptr; ) {
                int hashed_i = hash_compress(p->value);
                old_set[i] = p->next;
                p->next = set[hashed_i];
                set[hashed_i] = p;
                p = old_set[i];
            }
        }
        delete_hash_table(old_set, old_bins);
    }
}


template<class T, int (*thash)(const T& a)>
void HashSet<T,thash>::delete_hash_table (LN**& ht, int bins) {
    for (int i = 0; i < bins; ++i) {
        while(ht[i] != nullptr) {
            LN* to_del = ht[i];
            ht[i] = ht[i]->next;
            delete to_del;
        }
    }
    delete[] ht;
}






////////////////////////////////////////////////////////////////////////////////
//
//Iterator class definitions

template<class T, int (*thash)(const T& a)>
void HashSet<T,thash>::Iterator::advance_cursors() {
    current.second = current.second->next;
    if (current.second->next != nullptr)
        return;
    else {
        for (int i = current.first+1; i < ref_set->bins; ++i)
            if (ref_set->set[i]->next != nullptr) {
                current.first = i;
                current.second = ref_set->set[i];
                return;
            }
        current.first = -1;
        current.second = nullptr;
    }
}


template<class T, int (*thash)(const T& a)>
HashSet<T,thash>::Iterator::Iterator(HashSet<T,thash>* iterate_over, bool begin)
: ref_set(iterate_over), expected_mod_count(ref_set->mod_count) {
    current.first = -1;
    current.second = nullptr;

    if (begin)
        for (int i = 0; i < ref_set->bins; ++i)
            if (ref_set->set[i]->next != nullptr) {
                current.first = i;
                current.second = ref_set->set[i];
                break;
            }
}


template<class T, int (*thash)(const T& a)>
HashSet<T,thash>::Iterator::~Iterator()
{}


template<class T, int (*thash)(const T& a)>
T HashSet<T,thash>::Iterator::erase() {
    if (expected_mod_count != ref_set->mod_count)
        throw ConcurrentModificationError("HashSet::Iterator::erase");
    if (!can_erase)
        throw CannotEraseError("HashSet::Iterator::erase Iterator cursor already erased");
    if (current.first == -1 && current.second == nullptr)
        throw CannotEraseError("HashSet::Iterator::erase Iterator cursor beyond data structure");

    can_erase = false;

    T result = current.second->value;
    LN* to_del = current.second->next;
    *current.second = *to_del;
    delete to_del;

    if (current.second->next == nullptr) {
        for (int i = current.first + 1; i < ref_set->bins; ++i) {
            if (ref_set->set[i]->next != nullptr) {
                current.first = i;
                current.second = ref_set->set[i];
                break;
            }
        }
        if (current.second->next == nullptr) {
            current.first = -1;
            current.second = nullptr;
        }
    }

    --ref_set->used;
    expected_mod_count = ref_set->mod_count;
    return result;
}


template<class T, int (*thash)(const T& a)>
std::string HashSet<T,thash>::Iterator::str() const {
    std::ostringstream result;
    result << ref_set->str() << "(current=" << current.first << "," << current.second << ",expected_mod_count=" << expected_mod_count << ",can_erase=" << can_erase << ")";
    return result.str();
}


template<class T, int (*thash)(const T& a)>
auto  HashSet<T,thash>::Iterator::operator ++ () -> HashSet<T,thash>::Iterator& {
    if (expected_mod_count != ref_set->mod_count)
        throw ConcurrentModificationError("HashSet::Iterator::operator ++");

    if (current.first == -1)
        return *this;

    if (can_erase)
        advance_cursors();
    else
        can_erase = true;

    return *this;
}


template<class T, int (*thash)(const T& a)>
auto  HashSet<T,thash>::Iterator::operator ++ (int) -> HashSet<T,thash>::Iterator {
    if (expected_mod_count != ref_set->mod_count)
        throw ConcurrentModificationError("HashSet::Iterator::operator ++");

    if (current.first == -1)
        return *this;

    Iterator result(*this);
    if (can_erase)
        advance_cursors();
    else
        can_erase = true;

    return result;
}


template<class T, int (*thash)(const T& a)>
bool HashSet<T,thash>::Iterator::operator == (const HashSet<T,thash>::Iterator& rhs) const {
    const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
    if (rhsASI == 0)
        throw IteratorTypeError("HashSet::Iterator::operator ==");
    if (expected_mod_count != ref_set->mod_count)
        throw ConcurrentModificationError("HashSet::Iterator::operator ==");
    if (ref_set != rhsASI->ref_set)
        throw ComparingDifferentIteratorsError("HashSet::Iterator::operator ==");

    return current == rhs.current;
}


template<class T, int (*thash)(const T& a)>
bool HashSet<T,thash>::Iterator::operator != (const HashSet<T,thash>::Iterator& rhs) const {
    const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
    if (rhsASI == 0)
        throw IteratorTypeError("HashSet::Iterator::operator !=");
    if (expected_mod_count != ref_set->mod_count)
        throw ConcurrentModificationError("HashSet::Iterator::operator !=");
    if (ref_set != rhsASI->ref_set)
        throw ComparingDifferentIteratorsError("HashSet::Iterator::operator !=");

    return current != rhs.current;
}

template<class T, int (*thash)(const T& a)>
T& HashSet<T,thash>::Iterator::operator *() const {
    if (expected_mod_count != ref_set->mod_count)
        throw ConcurrentModificationError("HashSet::Iterator::operator *");
    if (!can_erase) {
        std::ostringstream where;
        where << " when size = " << ref_set->size();
        throw IteratorPositionIllegal("HashSet::Iterator::operator * Iterator illegal: " + where.str());
    }

    return current.second->value;
}

template<class T, int (*thash)(const T& a)>
T* HashSet<T,thash>::Iterator::operator ->() const {
    if (expected_mod_count != ref_set->mod_count)
        throw ConcurrentModificationError("HashSet::Iterator::operator ->");
    if (!can_erase) {
        std::ostringstream where;
        where << " when size = " << ref_set->size();
        throw IteratorPositionIllegal("HashSet::Iterator::operator -> Iterator illegal: " + where.str());
    }

    return &current.second->value;
}

}

#endif /* HASH_SET_HPP_ */
