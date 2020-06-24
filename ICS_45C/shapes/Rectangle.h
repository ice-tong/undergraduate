#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle
    :public Shape
{
    double side1;
    double side2;
public:
    Rectangle(double newSide1, double newSide2, int x, int y, string n)
	:side1(newSide1), side2(newSide2), Shape(x,y,n)
    {}

    virtual double area()
    {
	return side1*side2;
    }

    virtual void draw()
    {
	for (int i = 0; i < side2; ++i)
	{
	    for (int j = 0; j < side1; ++j)
	    {
		cout << '*';
	    }
	    cout << endl;
	}
    }
};

#endif
