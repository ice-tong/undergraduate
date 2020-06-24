#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef double (*VirtualMethodPointer)(void *);
typedef VirtualMethodPointer * VTableType;

#define PI 3.14159
#define MAX_STR_LEN 100


//Begin Shape Class
typedef struct
{
    VTableType VPointer;
    char name[MAX_STR_LEN];
} Shape;

double Shape_area(Shape * _this) {
    return 0.0;
}

void Shape_draw(Shape * _this) {
    printf("You should never see this printed!\n");
}

VirtualMethodPointer Shape_VTable [] = 
{
    (VirtualMethodPointer)Shape_area,
    (VirtualMethodPointer)Shape_draw
};

Shape * Shape_Shape(Shape * _this, char newName[MAX_STR_LEN]) {
    _this->VPointer = Shape_VTable;
    strcpy(_this->name, newName);
    return _this;
}
//End Shape Class


//Begin Triangle Class
typedef struct {
    VTableType VPointer;
    char name[MAX_STR_LEN];
    int base;
    int height;
} Triangle;

double Triangle_area(Triangle * _this) {
    return 0.5 * _this->base * _this->height;
}

void Triangle_draw(Triangle * _this) {
    printf("%s: height=%d, base=%d\n", _this->name, _this->height, _this->base);

    for (int i = 0; i < 5; i++) {
	for (int j = 0; j <= i; j++) {
	    printf("*");
	}
	printf("\n");
    }
    printf("\n");
}

VirtualMethodPointer Triangle_VTable [] =
{
    (VirtualMethodPointer)Triangle_area,
    (VirtualMethodPointer)Triangle_draw
};

Triangle * Triangle_Triangle(Triangle * _this, char newName[MAX_STR_LEN], int newBase, int newHeight) {
    Shape_Shape((Shape *)_this, newName);
    _this->VPointer = Triangle_VTable;
    _this->base = newBase;
    _this->height = newHeight;
    return _this;
}
//End Triangle Class


//Begin Circle Class
typedef struct {
    VTableType VPointer;
    char name[MAX_STR_LEN];
    int radius;
} Circle;

double Circle_area(Circle * _this) {
    return PI * _this->radius * _this->radius;
}

void Circle_draw(Circle * _this) {
    printf("%s: radius=%d\n", _this->name, _this->radius);

    for (int i = 0; i <= 10; i++) {
	for (int j = 0; j <= 10; j++) {
	    int k = (int)(sqrt((i-5)*(i-5) + (j-5)*(j-5)));
	    if (k == 5)
		printf("*");
	    else
		printf(" ");
	}
        printf("\n");
    }
    printf("\n");
}

VirtualMethodPointer Circle_VTable [] =
{
    (VirtualMethodPointer)Circle_area,
    (VirtualMethodPointer)Circle_draw
};

Circle * Circle_Circle(Circle * _this, char newName[MAX_STR_LEN], int newRadius) {
    Shape_Shape((Shape *)_this, newName);
    _this->VPointer = Circle_VTable;
    _this->radius = newRadius;
    return _this;
}
//End Circle Class


//Begin Square Class
typedef struct {
    VTableType VPointer;
    char name[MAX_STR_LEN];
    int height;
} Square;

double Square_area(Square * _this) {
    return _this->height * _this->height;
}

void Square_draw(Square * _this) {
    printf("%s: side=%d\n", _this->name, _this->height);

    for (int i = 0; i < _this->height; i++) {
	for (int j = 0; j < _this->height; j++)
	    printf("*");
	printf("\n");
    }
    printf("\n");
}

VirtualMethodPointer Square_VTable [] =
{
    (VirtualMethodPointer)Square_area,
    (VirtualMethodPointer)Square_draw
};

Square * Square_Square(Square * _this, char newName[MAX_STR_LEN], int newHeight) {
    Shape_Shape((Shape *)_this, newName);
    _this->VPointer = Square_VTable;
    _this->height = newHeight;
    return _this;
}
//End Square Class


//Begin Rectangle Class
typedef struct {
    VTableType VPointer;
    char name[MAX_STR_LEN];
    int height;
    int width;
} Rectangle;

double Rectangle_area(Rectangle * _this) {
    return _this->height * _this->width;
}

void Rectangle_draw(Rectangle * _this) {
    printf("%s: height=%d, width=%d\n", _this->name, _this->height, _this->width);

    for (int i = 0; i < _this->height; i++) {
	for (int j = 0; j < _this->width; j++)
	    printf("*");
	printf("\n");
    }
    printf("\n");
}

VirtualMethodPointer Rectangle_VTable [] =
{
    (VirtualMethodPointer)Rectangle_area,
    (VirtualMethodPointer)Rectangle_draw
};

Rectangle * Rectangle_Rectangle(Rectangle * _this, char newName[MAX_STR_LEN], int newHeight, int newWidth) {
    Square_Square((Square *)_this, newName, newHeight);
    _this->VPointer = Rectangle_VTable;
    _this->width = newWidth;
    return _this; 
}
//End Rectangle Class


int main() {
    Triangle * ptr1 = malloc(sizeof(Triangle));
    Triangle * ptr2 = malloc(sizeof(Triangle));
    Circle * ptr3 = malloc(sizeof(Circle));
    Circle * ptr4 = malloc(sizeof(Circle));
    Square * ptr5 = malloc(sizeof(Square));
    Square * ptr6 = malloc(sizeof(Square));
    Rectangle * ptr7 = malloc(sizeof(Rectangle));
    Rectangle * ptr8 = malloc(sizeof(Rectangle));

    Shape * shapes [] = {
	(Shape *)Triangle_Triangle(ptr1, "FirstTriangle", 5, 5),
	(Shape *)Triangle_Triangle(ptr2, "SecondTriangle", 4, 3),
	(Shape *)Circle_Circle(ptr3, "FirstCircle", 5),
	(Shape *)Circle_Circle(ptr4, "SecondCircle", 10),
	(Shape *)Square_Square(ptr5, "FirstSquare", 5),
	(Shape *)Square_Square(ptr6, "SecondSquare", 10),
	(Shape *)Rectangle_Rectangle(ptr7, "FirstRectangle", 4, 8),
	(Shape *)Rectangle_Rectangle(ptr8, "SecondRectangle", 8, 4)
    };

    double area = 0.0;
    for (int i = 0; i < sizeof(shapes)/sizeof(*shapes); i++) {
	(shapes[i]->VPointer[1])(shapes[i]);
	area += (shapes[i]->VPointer[0])(shapes[i]);
    }

    free(ptr1);
    free(ptr2);
    free(ptr3);
    free(ptr4);
    free(ptr5);
    free(ptr6);
    free(ptr7);
    free(ptr8);

    printf("The total area of the shapes on this picture is %f square units.\n", area);
}
