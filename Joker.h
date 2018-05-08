#ifndef _JOKER
#define _JOKER

#include "Shape.h"

class Joker : public Shape
{
public:
	Joker();
	Joker(const Joker&) = delete;
	~Joker() {}

	bool moveShape(EnumTetris::eSides side, char(&matrix)[ROWS][COLS], const int& currentSpeed);

private:
	//Auxiliary functions
	virtual void rotateShape() {}
	virtual bool checkRotate(const char(&matrix)[ROWS][COLS]) { return false; }
	bool checkLegalityMove(const char(&matrix)[ROWS][COLS], EnumTetris::eSides side, bool& cantMoveDown, bool &canMoveToSide) override;
	void move(EnumTetris::eSides side, const int& currentSpeed, char(&matrix)[ROWS][COLS]);
	void moveToSide(EnumTetris::eSides side, char(&matrix)[ROWS][COLS]);
};

#endif // !_JOKER
