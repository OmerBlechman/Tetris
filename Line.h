#ifndef _LINE
#define _LINE

#include "Shape.h"

class Line : public Shape
{
public:
	Line();
	Line(const Line&) = delete;
	~Line() {}


private:
	//Auxiliary functions
	virtual void rotateShape();
	void rotate(int x, int y, int countX, int countY);
	bool checkRotate(const char(&matrix)[ROWS][COLS]);

};

#endif // !_LINE
