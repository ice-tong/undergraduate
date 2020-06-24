#include <algorithm>
#include <iterator>
using namespace std;

template <typename T>
struct ListNode
{
    T info;
    ListNode<T> * next;
    ListNode<T>(T newInfo, ListNode<T> * newNext)
	: info(newInfo), next(newNext) {}

    static bool equals(ListNode<T> * L1, ListNode<T> * L2)
    {
	return L1 == nullptr || L2 == nullptr ? L1 == L2
	    : L1->info == L2->info && equals(L1->next, L2->next);
    }

    static void deleteList(ListNode<T> * L)
    {
	if (L != nullptr)
	{
	    deleteList(L->next);
	    delete L;
	}
    }
};


template <typename T>
class SetList
{
    ListNode<T> * head;

public:
    struct iterator
    {
	typedef forward_iterator_tag iterator_category;
	typedef iterator self_type;
	typedef T value_type;
	typedef T& reference;
	typedef ListNode<T>* pointer;	
    private:
	pointer ihead;
    public:
	iterator(pointer ptr) : ihead(ptr) {}
	bool operator ==(const self_type & rhs) const {return ListNode<T>::equals(ihead, rhs.ihead);}
    };

    SetList() : head(nullptr) {}
    iterator begin() {return iterator(head);}
    iterator end() {return iterator(nullptr);}
    iterator find(T & word)
    {
	for (ListNode<T> * p = head; p != nullptr; p = p->next)
	    if (p->info == word)
		return iterator(p);
	return iterator(nullptr);
    }
    void insert(T & word) {head = new ListNode<T>(word, head);}
    ~SetList() {ListNode<T>::deleteList(head);}
};
