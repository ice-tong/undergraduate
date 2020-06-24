import java.lang.Math;


//Various Shape Implementations
class Shape
{
    String name;

    Shape(String newName)
    {
	name = newName;
    }
    double area()
    {
	return 0.0;
    }
    void draw()
    {
	System.out.println("Shape.draw() You should never see this.");
    }
}

class Triangle extends Shape
{
    int height, base;

    Triangle(String name, int h, int b)
    {
	super(name);
	height = h;
	base = b;
    }
    double area()
    {
	return 0.5*base*height;
    }
    void draw()
    {
	System.out.println(name + ": height=" + height + ", base=" + base);
	for (int i = 0; i < 5; i++)
	{
	    for (int j = 0; j <= i; j++)
		System.out.print("*");
	    System.out.println();
	}
    }
}

class Circle extends Shape
{
    int radius;

    Circle(String name, int r)
    {
	super(name);
	radius = r;
    }
    double area()
    {
	return Math.PI*radius*radius;
    }
    void draw()
    {
	System.out.println(name + ": radius=" + radius);
	for (int i = 0; i <= 10; i++) {
	    for (int j = 0; j <= 10; j++) {
		int k = (int)Math.sqrt((i-5)*(i-5) + (j-5)*(j-5));
		if (k == 5)
		    System.out.print("*");
		else
		    System.out.print(" ");
	    }
	System.out.println();
	}
    }
}

class Square extends Shape
{
    int height;

    Square(String name, int h)
    {
	super(name);
	height = h;
    }
    double area()
    {
	return height*height;
    }
    void draw()
    {
	System.out.println(name + ": side=" + height);
	for (int i = 0; i < height; i++)
	{
	    for (int j = 0; j < height; j++)
		System.out.print("*");
	    System.out.println();
	}
    }
}

class Rectangle extends Square
{
    int width;

    Rectangle(String name, int h, int w)
    {
	super(name, h);
	width = w;
    }
    double area()
    {
	return width*height;
    }
    void draw()
    {
	System.out.println(name + ": height=" + height + ", width=" + width);
	for (int i = 0; i < height; i++)
	{
	    for (int j = 0; j < width; j++)
		System.out.print("*");
	    System.out.println();
	}
    }
}

//Linked List Implementation
class ListNode {
    Shape info;
    ListNode next;

    ListNode(Shape newInfo, ListNode newNext) {
	info = newInfo;
	next = newNext;
    }
}

class LinkedList {
    ListNode head;

    public LinkedList() {
	head = null;
    }

    public void add(Shape x) {
	head = new ListNode(x, head);
    }

    public int length() {
	int len = 0;
	for (ListNode p = head; p != null; p = p.next)
	    len++;
	return len;
    }

    public boolean isEmpty() {
	return head == null;
    }
}


//Picture Implementation using LinkedList of Shapes
class Picture
{
    LinkedList shapes = new LinkedList();

    void add(Shape sh)
    {
	shapes.add(sh);
    }
    void drawAll()
    {
	for (ListNode p = shapes.head; p != null; p = p.next)
	{
	    p.info.draw();
	    System.out.println();
	}
    }
    double totalArea()
    {
	double sum = 0.0;
	for (ListNode p = shapes.head; p != null; p = p.next)
	    sum += p.info.area();
	return sum;
    }
}


public class mainClass
{
    static void printArea(double d)
    {
	System.out.println("The total area of the shapes on this picture is " + d
				+ " square units.");
    }

    public static void main(String[] args)
    {
	Picture p = new Picture();
	p.add(new Triangle("FirstTriangle", 5, 5));
	p.add(new Triangle("SecondTriangle", 4, 3));
	p.add(new Circle("FirstCircle", 5));
	p.add(new Circle("SecondCircle", 10));
	p.add(new Square("FirstSquare", 5));
	p.add(new Square("SecondSquare", 10));
	p.add(new Rectangle("FirstRectangle", 4, 8));
	p.add(new Rectangle("SecondRectangle", 8, 4));

	p.drawAll();
	System.out.println();
	printArea(p.totalArea());
    }
}
