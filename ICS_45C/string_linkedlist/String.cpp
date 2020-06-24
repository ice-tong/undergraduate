#include "String.h"


//String publics

String:: String(const char *s)
{
    head = ListNode::stringToList(s);
}

String:: String(const String & s)
{
    head = ListNode::copy(s.head);
}

String String::operator = (const String & s)
{
    ListNode::deleteList(head);
    head = ListNode::copy(s.head);
    return *this;
}

char & String::operator [] (const int index)
{
    if (! inBounds(index))
    {
	cerr << "ERROR: index not in range" << endl;
	return head->info;
    }
    ListNode *p = head;
    for (int i = 0; i < index; ++i)
	p = p->next;
    return p->info;
}

int String:: size() const
{
    return ListNode::length(head);
}

int String:: indexOf(char c) const
{
    int result = 0;
    for (ListNode *p = head; p != NULL; p = p->next)
    {
	if (p->info == c)
	    return result;
	++result;
    }
    return -1;
}

bool String::operator == (const String & s) const
{
    return ListNode::compare(head, s.head) == 0;
}

bool String::operator < (const String & s) const
{
    return ListNode::compare(head, s.head) < 0;
}

String String::operator + (const String & s) const
{
    ListNode *cat = ListNode::append(head, s.head);
    String result;
    result.head = cat;
    return result;
}

String String::operator += (const String & s)
{
    ListNode *cat = ListNode::append(head, s.head);
    ListNode::deleteList(head);
    head = cat;
    return *this;
}

String String::reverse() const
{
    String result;
    ListNode *rev = ListNode::reverse(head);
    result.head = rev;
    return result;
}


void String::print(ostream & out) const
{
    for (ListNode *p = head; p != NULL; p = p->next)
    { 
	out << p->info;
    }
}

void String::read(istream & in)
{
    char input[128];
    in.getline(input, 128);
    ListNode::deleteList(head);
    head = ListNode::stringToList(input);
}

String::~String()
{
    ListNode::deleteList(head);
}




// ListNode Statics

String::ListNode * String::ListNode::stringToList(const char *s)
{
    if (s[0] == '\0')
	return NULL;
    return new ListNode(s[0], stringToList(&s[1]));
}

String::ListNode * String::ListNode::copy(ListNode *L)
{
    if (L == NULL)
	return NULL;
    return new ListNode(L->info, copy(L->next));
}

String::ListNode * String::ListNode::reverse(ListNode *L)
{
    ListNode *result = NULL;
    for (ListNode *p = L; p != NULL; p = p->next)
	result = new ListNode(p->info, result);
    return result;
}

String::ListNode * String::ListNode::append(ListNode *L1, ListNode *L2)
{
    if (L1 == NULL)
	return copy(L2);
    return new ListNode(L1->info, append(L1->next, L2));
}

int String::ListNode::compare(ListNode *L1, ListNode *L2)
{
    if (L1 == NULL && L2 == NULL)
	return 0;
    if (L1 == NULL)
	return 1;
    if (L2 == NULL)
 	return -1;
    if (L1->info != L2->info)
	return L1->info - L2->info;
    return compare(L1->next, L2->next);
}

void String::ListNode::deleteList(ListNode *L)
{
    if (L != NULL)
    {
	deleteList(L->next);
	delete L;
    }
}

int String::ListNode::length(ListNode *L)
{
    if (L == NULL)
	return 0;
    return 1 + length(L->next);
}



// <iostream>

ostream & operator << (ostream & out, String str)
{
    str.print(out);
    return out;
}

istream & operator >> (istream & in, String & str)
{
    str.read(in);
    return in;
}
