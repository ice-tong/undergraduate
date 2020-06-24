#ifndef PICTURE_H
#define PICTURE_H

#include "Shape.h"

typedef class ShapeLinkedListPair * ShapeLinkedList;
class ShapeLinkedListPair
{
public:
    Shape * info;
    ShapeLinkedList next;
    ShapeLinkedListPair(Shape * newInfo, ShapeLinkedList newNext)
	: info(newInfo), next(newNext)
    {}
};

class Picture
{
    ShapeLinkedList head;
public:
    Picture()
	: head(0)
    {}

    void enter(Shape * s)
    {
	head = new ShapeLinkedListPair(s, head);
    }

    double totalArea()
    {
	double total = 0.0;
	for (ShapeLinkedList p = head; p != 0; p = p->next)
	    total += p->info->area();
	return total;
    }

    void drawAll()
    {
	for (ShapeLinkedList p = head; p != 0; p = p->next)
	{
	    p->info->draw();
	    cout << endl;
	}
    }

    ~Picture()
    {
	ShapeLinkedList temp;
	for (ShapeLinkedListPair *p = head; p != 0; )
	{
	    temp = p;
	    p = p->next;
	    delete temp->info;
	    delete temp;
	}
    }
};

#endif
