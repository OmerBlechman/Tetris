#ifndef _SQUARE
#define _SQUARE

#include "Shape.h"

class Square : public Shape
{
public:
	Square();
	Square(const Square& s) = delete;
	~Square() {}

private:
	//Auxiliary functions
	virtual void rotateShape() {} 
	bool checkRotate(const char(&matrix)[ROWS][COLS]) { return false; }
};

#endif // !_SQUARE
