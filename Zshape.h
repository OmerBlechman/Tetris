#ifndef _ZShape
#define _ZShape
#include "Shape.h"
class Zshape : public  Shape
{
public:
	Zshape();
	Zshape(const Zshape&) = delete;
	~Zshape() {}

private:
	//Auxiliary functions
	virtual void rotateShape();
	bool checkRotate(const char(&matrix)[ROWS][COLS]);
	void rotateVerticalMode(int x, int y, int add);
	void rotateBalanceMode(int x, int y, int add);
};

#endif // !_ZShape
