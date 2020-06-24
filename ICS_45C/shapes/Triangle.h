#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle
    :public Shape
{
    double base;
    double height;
public:
    Triangle(double newBase, double newHeight, int x, int y, string n)
	: base(newBase), height(newHeight), Shape(x,y,n)
    {}

    virtual double area()
    {
	return 0.5*base*height;
    }

    virtual void draw()
    {
	for (int i = 0; i < height; ++i)
	{
	    for (int j = 0; j <= i; ++j)
	    {
		cout << '*';
	    }
	    cout << endl;
	}
    }
};

#endif
