#include "Shape.h"
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Picture.h"

int main()
{
    Picture p;

    p.enter(new Triangle(5,5, 0, 0, "FirstTriangle"));
    p.enter(new Triangle(3,4, 0, 0, "SecondTriangle"));

    p.enter(new Circle(5, 0, 0, "FirstCircle"));
    p.enter(new Circle(10, 0, 0, "SecondCircle"));

    p.enter(new Square(5, 0, 0, "FirstSquare"));
    p.enter(new Square(10, 0, 0, "SecondSquare"));

    p.enter(new Rectangle(4,8, 0, 0, "FirstRectangle"));
    p.enter(new Rectangle(8,4, 0, 0, "SecondRectangle"));

    p.drawAll();

    cout << "The total area of the shapes on this picture is " 
	<< p.totalArea() << " square units." << endl;

    return 0;
}
