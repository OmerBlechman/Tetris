#ifndef _BOMB
#define _BOMB


#include "Shape.h"


class Bomb : public Shape
{
public:
	Bomb();
	Bomb(const Bomb&) = delete;
	~Bomb() {}

private:
	//Auxiliary functions
	virtual bool checkLegalityMoveToSide(const char(&matrix)[ROWS][COLS], EnumTetris::eSides side, bool& cantMoveDown, bool &canMoveToSide)override;
	virtual void rotateShape() {}
	bool checkRotate(const char(&matrix)[ROWS][COLS]) { return false; }
	virtual void draw() { getArrOfPoints()[0].draw('@'); }

};

#endif // !_BOMB