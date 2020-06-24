#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <iostream>

using namespace std;

class Shape
{
    int centerX;
    int centerY;
    string name;

public:
    Shape(int newX, int newY, string newName)
	: centerX(newX), centerY(newY), name(newName)
    {}

    virtual double area() = 0;
    virtual void draw() = 0;

    virtual ~Shape()
    {}
};

#endif
