#ifndef _LSHAPE
#define _LSHAPE
#include "Shape.h"
class Lshape : public  Shape
{
public:
	Lshape();
	Lshape(const Lshape&) = delete;
	~Lshape() {}

private:
	//Auxiliary functions
	virtual void rotateShape();
	bool checkRotate(const char(&matrix)[ROWS][COLS]);
	void rotateVerticalMode(int x, int y, int add);
	void rotateBalanceMode(int x, int y, int add);

};

#endif // !_LSHAPE
