//Submitter: kfarsany(Farsany,Kian)

#ifndef HASH_MAP_HPP_
#define HASH_MAP_HPP_

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
template<class KEY,class T, int (*thash)(const KEY& a) = undefinedhash<KEY>> class HashMap {
  public:
    typedef ics::pair<KEY,T>   Entry;
    typedef int (*hashfunc) (const KEY& a);

    //Destructor/Constructors
    ~HashMap ();

    HashMap          (double the_load_threshold = 1.0, int (*chash)(const KEY& a) = undefinedhash<KEY>);
    explicit HashMap (int initial_bins, double the_load_threshold = 1.0, int (*chash)(const KEY& k) = undefinedhash<KEY>);
    HashMap          (const HashMap<KEY,T,thash>& to_copy, double the_load_threshold = 1.0, int (*chash)(const KEY& a) = undefinedhash<KEY>);
    explicit HashMap (const std::initializer_list<Entry>& il, double the_load_threshold = 1.0, int (*chash)(const KEY& a) = undefinedhash<KEY>);

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    explicit HashMap (const Iterable& i, double the_load_threshold = 1.0, int (*chash)(const KEY& a) = undefinedhash<KEY>);


    //Queries
    bool empty      () const;
    int  size       () const;
    bool has_key    (const KEY& key) const;
    bool has_value  (const T& value) const;
    std::string str () const; //supplies useful debugging information; contrast to operator <<


    //Commands
    T    put   (const KEY& key, const T& value);
    T    erase (const KEY& key);
    void clear ();

    //Iterable class must support "for-each" loop: .begin()/.end() and prefix ++ on returned result
    template <class Iterable>
    int put_all(const Iterable& i);


    //Operators

    T&       operator [] (const KEY&);
    const T& operator [] (const KEY&) const;
    HashMap<KEY,T,thash>& operator = (const HashMap<KEY,T,thash>& rhs);
    bool operator == (const HashMap<KEY,T,thash>& rhs) const;
    bool operator != (const HashMap<KEY,T,thash>& rhs) const;

    template<class KEY2,class T2, int (*hash2)(const KEY2& a)>
    friend std::ostream& operator << (std::ostream& outs, const HashMap<KEY2,T2,hash2>& m);



  private:
    class LN;

  public:
    class Iterator {
      public:
         typedef pair<int,LN*> Cursor;

        //Private constructor called in begin/end, which are friends of HashMap<T>
        ~Iterator();
        Entry       erase();
        std::string str  () const;
        HashMap<KEY,T,thash>::Iterator& operator ++ ();
        HashMap<KEY,T,thash>::Iterator  operator ++ (int);
        bool operator == (const HashMap<KEY,T,thash>::Iterator& rhs) const;
        bool operator != (const HashMap<KEY,T,thash>::Iterator& rhs) const;
        Entry& operator *  () const;
        Entry* operator -> () const;
        friend std::ostream& operator << (std::ostream& outs, const HashMap<KEY,T,thash>::Iterator& i) {
          outs << i.str(); //Use the same meaning as the debugging .str() method
          return outs;
        }
        friend Iterator HashMap<KEY,T,thash>::begin () const;
        friend Iterator HashMap<KEY,T,thash>::end   () const;

      private:
        //If can_erase is false, current indexes the "next" value (must ++ to reach it)
        Cursor                current; //Pair:Bin Index/LN*; stops if LN* == nullptr
        HashMap<KEY,T,thash>* ref_map;
        int                   expected_mod_count;
        bool                  can_erase = true;

        //Helper methods
        void advance_cursors();

        //Called in friends begin/end
        Iterator(HashMap<KEY,T,thash>* iterate_over, bool from_begin);
    };


    Iterator begin () const;
    Iterator end   () const;


  private:
    class LN {
    public:
      LN ()                         : next(nullptr){}
      LN (const LN& ln)             : value(ln.value), next(ln.next){}
      LN (Entry v, LN* n = nullptr) : value(v), next(n){}

      Entry value;
      LN*   next;
  };

  int (*hash)(const KEY& k);  //Hashing function used (from template or constructor)
  LN** map      = nullptr;    //Pointer to array of pointers: each bin stores a list with a trailer node
  double load_threshold;      //used/bins <= load_threshold
  int bins      = 1;         //# bins currently in array (start it >= 1 so no divide by 0 in hash_compress)
  int used      = 0;          //Cache for number of key->value pairs in the hash table
  int mod_count = 0;          //For sensing concurrent modification


  //Helper methods
  int   hash_compress        (const KEY& key)          const;  //hash function ranged to [0,bins-1]
  LN*   find_key             (const KEY& key) const;           //Returns reference to key's node or nullptr
  LN*   copy_list            (LN*   l)                 const;  //Copy the keys/values in a bin (order irrelevant)
  LN**  copy_hash_table      (LN** ht, int bins)       const;  //Copy the bins/keys/values in ht tree (order in bins irrelevant)

  void  ensure_load_threshold(int new_used);                   //Reallocate if load_factor > load_threshold
  void  delete_hash_table    (LN**& ht, int bins);             //Deallocate all LN in ht (and the ht itself; ht == nullptr)
};





////////////////////////////////////////////////////////////////////////////////
//
//HashMap class and related definitions

//Destructor/Constructors

template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::~HashMap() {
    delete_hash_table(map, bins);
}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::HashMap(double the_load_threshold, int (*chash)(const KEY& k))
: load_threshold(the_load_threshold), hash(thash != (hashfunc)undefinedhash<KEY> ? thash : chash) {
    if (hash == (hashfunc)undefinedhash<KEY>)
        throw TemplateFunctionError("HashMap::default constructor: neither specified");
    if (thash != (hashfunc)undefinedhash<KEY> && chash != (hashfunc)undefinedhash<KEY> && thash != chash)
        throw TemplateFunctionError("HashMap::default constructor: both specified and different");

    map = new LN*[bins];
    for (int i = 0; i < bins; ++i)
        map[i] = new LN();
}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::HashMap(int initial_bins, double the_load_threshold, int (*chash)(const KEY& k))
: bins(initial_bins), load_threshold(the_load_threshold), hash(thash != (hashfunc)undefinedhash<KEY> ? thash : chash) {
    if (hash == (hashfunc)undefinedhash<KEY>)
        throw TemplateFunctionError("HashMap::bins constructor: neither specified");
    if (thash != (hashfunc)undefinedhash<KEY> && chash != (hashfunc)undefinedhash<KEY> && thash != chash)
        throw TemplateFunctionError("HashMap::bins constructor: both specified and different");

    map = new LN*[bins];
    for (int i = 0; i < bins; ++i)
        map[i] = new LN();
}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::HashMap(const HashMap<KEY,T,thash>& to_copy, double the_load_threshold, int (*chash)(const KEY& a))
: load_threshold(the_load_threshold), hash(thash != (hashfunc)undefinedhash<KEY> ? thash : chash) {
    if (hash == (hashfunc)undefinedhash<KEY>)
        hash = to_copy.hash;
    if (thash != (hashfunc)undefinedhash<KEY> && chash != (hashfunc)undefinedhash<KEY> && thash != chash)
        throw TemplateFunctionError("HashMap::copy constructor: both specified and different");

    if (hash == to_copy.hash) {
        map = copy_hash_table(to_copy.map, to_copy.bins);
        used = to_copy.used;
        bins = to_copy.bins;
    }
    else {
        map = new LN*[bins];
        for (int i = 0; i < bins; ++i)
            map[i] = new LN();
        put_all(to_copy);
    }
}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::HashMap(const std::initializer_list<Entry>& il, double the_load_threshold, int (*chash)(const KEY& k))
: load_threshold(the_load_threshold), hash(thash != (hashfunc)undefinedhash<KEY> ? thash : chash) {
    if (hash == (hashfunc)undefinedhash<KEY>)
        throw TemplateFunctionError("HashMap::initializer_list constructor: neither specified");
    if (thash != (hashfunc)undefinedhash<KEY> && chash != (hashfunc)undefinedhash<KEY> && thash != chash)
        throw TemplateFunctionError("HashMap::initializer_list constructor: both specified and different");

    map = new LN*[bins];
    for (int i = 0; i < bins; ++i)
        map[i] = new LN();

    for (const Entry& e : il)
        put(e.first, e.second);
}


template<class KEY,class T, int (*thash)(const KEY& a)>
template <class Iterable>
HashMap<KEY,T,thash>::HashMap(const Iterable& i, double the_load_threshold, int (*chash)(const KEY& k))
: load_threshold(the_load_threshold), hash(thash != (hashfunc)undefinedhash<KEY> ? thash : chash) {
    if (hash == (hashfunc)undefinedhash<KEY>)
        throw TemplateFunctionError("HashMap::Iterable constructor: neither specified");
    if (thash != (hashfunc)undefinedhash<KEY> && chash != (hashfunc)undefinedhash<KEY> && thash != chash)
        throw TemplateFunctionError("HashMap::Iterable constructor: both specified and different");

    map = new LN*[bins];
    for (int i = 0; i < bins; ++i)
        map[i] = new LN();

    for (const Entry& e : i)
        put(e.first, e.second);
}


////////////////////////////////////////////////////////////////////////////////
//
//Queries

template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::empty() const {
    return used == 0;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
int HashMap<KEY,T,thash>::size() const {
    return used;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::has_key (const KEY& key) const {
    return find_key(key) != nullptr;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::has_value (const T& value) const {
    for (int i = 0; i < bins; ++i)
        for (LN* p = map[i]; p->next != nullptr; p = p->next)
            if (p->value.second == value)
                return true;

    return false;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
std::string HashMap<KEY,T,thash>::str() const {
    std::ostringstream result;
    for (int i = 0; i < bins; ++i) {
        result << "bin[" << i << "]: ";
        for (LN *p = map[i]; p != nullptr; p = p->next) {
            if (p->next == nullptr)
                result << "TRAILER" << std::endl;
            else
                result << p->value.first << "->" << p->value.second << " -> ";
        }
    }
    return result.str();
}


////////////////////////////////////////////////////////////////////////////////
//
//Commands

template<class KEY,class T, int (*thash)(const KEY& a)>
T HashMap<KEY,T,thash>::put(const KEY& key, const T& value) {
    ++mod_count;
    LN* in_map = find_key(key);
    if (in_map != nullptr) {
        T old = in_map->value.second;
        in_map->value.second = value;
        return old;
    }
    else {
        ensure_load_threshold(++used);
        int i = hash_compress(key);
        map[i] = new LN(Entry(key,value), map[i]);
        return value;
    }
}


template<class KEY,class T, int (*thash)(const KEY& a)>
T HashMap<KEY,T,thash>::erase(const KEY& key) {
    ++mod_count;
    LN* found_key = find_key(key);
    if (found_key != nullptr) {
        T result = found_key->value.second;
        LN* to_del = found_key->next;
        *found_key = *to_del;
        delete to_del;
        --used;
        return result;
    }
    else {
        std::ostringstream answer;
        answer << "HashMap::erase: key(" << key << ") not in Map";
        throw KeyError(answer.str());
    }
}


template<class KEY,class T, int (*thash)(const KEY& a)>
void HashMap<KEY,T,thash>::clear() {
    ++mod_count;
    for (int i = 0; i < bins; ++i) {
        while(map[i]->next != nullptr) {
            LN* to_del = map[i];
            map[i] = map[i]->next;
            delete to_del;
        }
    }
    used = 0;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
template<class Iterable>
int HashMap<KEY,T,thash>::put_all(const Iterable& i) {
    int result = 0;
    for (auto entry : i) {
        ++result;
        put(entry.first, entry.second);
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////
//
//Operators

template<class KEY,class T, int (*thash)(const KEY& a)>
T& HashMap<KEY,T,thash>::operator [] (const KEY& key) {
    LN* node = find_key(key);
    if (node != nullptr)
        return node->value.second;
    else {
        ensure_load_threshold(++used);
        int i = hash_compress(key);
        map[i] = new LN(Entry(key, T()), map[i]);
        ++mod_count;
        return map[i]->value.second;
    }
}


template<class KEY,class T, int (*thash)(const KEY& a)>
const T& HashMap<KEY,T,thash>::operator [] (const KEY& key) const {
    LN* result = find_key(key);
    if (result != nullptr)
        return result->value.second;

    std::ostringstream error;
    error << "HashMap::operator []: key(" << key << ") not in Map";
    throw KeyError(error.str());
}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>& HashMap<KEY,T,thash>::operator = (const HashMap<KEY,T,thash>& rhs) {
    if (this == &rhs)
        return *this;

    hash = rhs.hash;
    LN** to_del = map;
    map = copy_hash_table(rhs.map, rhs.bins);
    delete to_del;

    used = rhs.used;
    bins = rhs.bins;
    ++mod_count;
    return *this;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::operator == (const HashMap<KEY,T,thash>& rhs) const {
    if (this == &rhs)
        return true;

    if (used != rhs.size())
        return false;

    for (int i = 0; i < bins; ++i)
        for (LN* p = map[i]; p->next != nullptr; p = p->next) {
            LN* rhs_node = rhs.find_key(p->value.first);
            if (rhs_node == nullptr)
                return false;
            else if (rhs_node->value.second != p->value.second)
                return false;
        }
    return true;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::operator != (const HashMap<KEY,T,thash>& rhs) const {
    return !(*this == rhs);
}


template<class KEY,class T, int (*thash)(const KEY& a)>
std::ostream& operator << (std::ostream& outs, const HashMap<KEY,T,thash>& m) {
    outs << "map[";

    if (!m.empty()) {
        typename HashMap<KEY,T,thash>::Iterator i = m.begin();
        outs << (*i).first << "->" << (*i).second;
        ++i;
        for (; i != m.end(); ++i) {
            outs << "," << (*i).first << "->" << (*i).second;
        }
    }

    outs << "]";
    return outs;
}


////////////////////////////////////////////////////////////////////////////////
//
//Iterator constructors

template<class KEY,class T, int (*thash)(const KEY& a)>
auto HashMap<KEY,T,thash>::begin () const -> HashMap<KEY,T,thash>::Iterator {
    return Iterator(const_cast<HashMap<KEY,T,thash>*>(this),true);
}


template<class KEY,class T, int (*thash)(const KEY& a)>
auto HashMap<KEY,T,thash>::end () const -> HashMap<KEY,T,thash>::Iterator {
    return Iterator(const_cast<HashMap<KEY,T,thash>*>(this),false);
}


///////////////////////////////////////////////////////////////////////////////
//
//Private helper methods

template<class KEY,class T, int (*thash)(const KEY& a)>
int HashMap<KEY,T,thash>::hash_compress (const KEY& key) const {
    return abs(hash(key)) % bins;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
typename HashMap<KEY,T,thash>::LN* HashMap<KEY,T,thash>::find_key (const KEY& key) const {
    for (LN* p = map[hash_compress(key)]; p->next != nullptr; p = p->next)
        if (p->value.first == key)
            return p;
    return nullptr;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
typename HashMap<KEY,T,thash>::LN* HashMap<KEY,T,thash>::copy_list (LN* l) const {
    if (l == nullptr)
        return nullptr;
    else
        return new LN(l->value, copy_list(l->next));
}


template<class KEY,class T, int (*thash)(const KEY& a)>
typename HashMap<KEY,T,thash>::LN** HashMap<KEY,T,thash>::copy_hash_table (LN** ht, int bins) const {
    LN** result = new LN*[bins];
    for (int i = 0; i < bins; ++i)
        result[i] = copy_list(ht[i]);
    return result;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
void HashMap<KEY,T,thash>::ensure_load_threshold(int new_used) {
    double lf = static_cast<double>(new_used) / bins;
    if (lf <= load_threshold)
        return;
    else {
        int old_bins = bins;
        bins = bins*2;
        LN** old_map = map;
        map = new LN*[bins];
        for (int i = 0; i < bins; ++i)
            map[i] = new LN();
        for (int i = 0; i < old_bins; ++i) {
            for (LN* p = old_map[i]; p->next != nullptr; ) {
                int hashed_i = hash_compress(p->value.first);
                old_map[i] = p->next;
                p->next = map[hashed_i];
                map[hashed_i] = p;
                p = old_map[i];
            }
        }
        delete_hash_table(old_map, old_bins);
    }
}


template<class KEY,class T, int (*thash)(const KEY& a)>
void HashMap<KEY,T,thash>::delete_hash_table (LN**& ht, int bins) {
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

template<class KEY,class T, int (*thash)(const KEY& a)>
void HashMap<KEY,T,thash>::Iterator::advance_cursors(){
    current.second = current.second->next;
    if (current.second->next != nullptr)
        return;
    else {
        for (int i = current.first+1; i < ref_map->bins; ++i)
            if (ref_map->map[i]->next != nullptr) {
                current.first = i;
                current.second = ref_map->map[i];
                return;
            }
        current.first = -1;
        current.second = nullptr;
    }
}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::Iterator::Iterator(HashMap<KEY,T,thash>* iterate_over, bool from_begin)
: ref_map(iterate_over), expected_mod_count(ref_map->mod_count) {
    current.first = -1;
    current.second = nullptr;

    if (from_begin)
        for (int i = 0; i < ref_map->bins; ++i)
            if (ref_map->map[i]->next != nullptr) {
                current.first = i;
                current.second = ref_map->map[i];
                break;
            }
}


template<class KEY,class T, int (*thash)(const KEY& a)>
HashMap<KEY,T,thash>::Iterator::~Iterator()
{}


template<class KEY,class T, int (*thash)(const KEY& a)>
auto HashMap<KEY,T,thash>::Iterator::erase() -> Entry {
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::erase");
    if (!can_erase)
        throw CannotEraseError("HashMap::Iterator::erase Iterator cursor already erased");
    if (current.first == -1 && current.second == nullptr)
        throw CannotEraseError("HashMap::Iterator::erase Iterator cursor beyond data structure");

    can_erase = false;

    Entry result = current.second->value;
    LN* to_del = current.second->next;
    *current.second = *to_del;
    delete to_del;

    if (current.second->next == nullptr) {
        for (int i = current.first + 1; i < ref_map->bins; ++i) {
            if (ref_map->map[i]->next != nullptr) {
                current.first = i;
                current.second = ref_map->map[i];
                break;
            }
        }
        if (current.second->next == nullptr) {
            current.first = -1;
            current.second = nullptr;
        }
    }

    --ref_map->used;
    expected_mod_count = ref_map->mod_count;
    return result;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
std::string HashMap<KEY,T,thash>::Iterator::str() const {
    std::ostringstream result;
    result << ref_map->str() << "(current=" << current.first << "," << current.second << ",expected_mod_count=" << expected_mod_count << ",can_erase=" << can_erase << ")";
    return result.str();
}

template<class KEY,class T, int (*thash)(const KEY& a)>
auto  HashMap<KEY,T,thash>::Iterator::operator ++ () -> HashMap<KEY,T,thash>::Iterator& {
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::operator ++");

    if (current.first == -1)
        return *this;

    if (can_erase)
        advance_cursors();
    else
        can_erase = true;

    return *this;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
auto  HashMap<KEY,T,thash>::Iterator::operator ++ (int) -> HashMap<KEY,T,thash>::Iterator {
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::operator ++");

    if (current.first == -1)
        return *this;

    Iterator result(*this);
    if (can_erase)
        advance_cursors();
    else
        can_erase = true;

    return result;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::Iterator::operator == (const HashMap<KEY,T,thash>::Iterator& rhs) const {
    const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
    if (rhsASI == 0)
        throw IteratorTypeError("HashMap::Iterator::operator ==");
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::operator ==");
    if (ref_map != rhsASI->ref_map)
        throw ComparingDifferentIteratorsError("HashMap::Iterator::operator ==");

    return current == rhs.current;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
bool HashMap<KEY,T,thash>::Iterator::operator != (const HashMap<KEY,T,thash>::Iterator& rhs) const {
    const Iterator* rhsASI = dynamic_cast<const Iterator*>(&rhs);
    if (rhsASI == 0)
        throw IteratorTypeError("HashMap::Iterator::operator !=");
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::operator !=");
    if (ref_map != rhsASI->ref_map)
        throw ComparingDifferentIteratorsError("HashMap::Iterator::operator !=");

    return current != rhs.current;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
pair<KEY,T>& HashMap<KEY,T,thash>::Iterator::operator *() const {
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::operator *");
    if (!can_erase) {
        std::ostringstream where;
        where << " when size = " << ref_map->size();
        throw IteratorPositionIllegal("HashMap::Iterator::operator * Iterator illegal: " + where.str());
    }

    return current.second->value;
}


template<class KEY,class T, int (*thash)(const KEY& a)>
pair<KEY,T>* HashMap<KEY,T,thash>::Iterator::operator ->() const {
    if (expected_mod_count != ref_map->mod_count)
        throw ConcurrentModificationError("HashMap::Iterator::operator ->");
    if (!can_erase) {
        std::ostringstream where;
        where << " when size = " << ref_map->size();
        throw IteratorPositionIllegal("HashMap::Iterator::operator -> Iterator illegal: " + where.str());
    }

    return &current.second->value;
}


}

#endif /* HASH_MAP_HPP_ */
