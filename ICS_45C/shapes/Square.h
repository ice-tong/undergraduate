#ifndef SQUARE_H
#define SQUARE_H

#include "Rectangle.h"

class Square
    :public Rectangle
{
public:
    Square(double side, int x, int y, string n)
	: Rectangle(side, side, x, y, n)
    {}
};

#endif
