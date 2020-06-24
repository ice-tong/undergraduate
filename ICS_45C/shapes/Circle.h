#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include <math.h>

class Circle
    :public Shape
{
    double radius;
public:
    Circle(double newRadius, int x, int y, string n)
	: radius(newRadius), Shape(x,y,n)
    {}

    virtual double area()
    {
	return 3.14159*radius*radius;
    }

    virtual void draw()
    {
	for (int j = radius; j >= -radius; j-=2)
	{
	    for (int i = -radius; i<= radius; ++i)
	    {
		if ((int)sqrt(i*i + j*j) == radius)
		    cout << '*';
		else
		    cout << ' ';
	    }
	    cout << endl;
	}
    }
};

#endif
