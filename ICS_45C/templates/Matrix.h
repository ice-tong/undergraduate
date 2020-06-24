#include "Array.h"

template
    <typename Type>
class Matrix
{
private:
    int rows, cols;
    Array<Array<Type>*> m;
public:
    Matrix(int newRows, int newCols)
	:rows(newRows), cols(newCols), m(rows)
    {
	for (int i = 0; i < rows; i++)
	    m[i] = new Array<Type>(cols);
    }
    int numRows()
    {
	return rows;
    }
    int numCols()
    {
	return cols;
    }
    Array<Type> & operator [](int row)	
    {
	if (row >= rows)
	    throw IndexOutOfBoundsException();
	return * m[row];
    }
    Array<Array<Type>*> & operator = (const Array<Array<Type>*> * m)
    {}
    void print(ostream & out)
    {
	for (int i = 0; i < rows; ++i)
	    out << m[i] << endl;;
    }
    friend ostream & operator << (ostream & out, Matrix & m)
    {
	m.print(out);
	return out;
    }
    ~Matrix()
    {
	for (int i = 0; i < rows; ++i)
	    delete m[i];
    }
};
