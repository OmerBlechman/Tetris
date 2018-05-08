#ifndef _PLUS
#define _PLUS
#include "Shape.h"
class Plus : public  Shape
{
public:
	Plus();
	Plus(const Plus&) = delete;
	~Plus() {}

private:
	//Auxiliary functions
	virtual void rotateShape();
	bool checkRotate(const char(&matrix)[ROWS][COLS]);
	void rotateVerticalMode(int x, int y, int add);
	void rotateBalanceMode(int x, int y, int add);


};

#endif // !_PLUS
