#include "Bomb.h"

Bomb::Bomb() :Shape(SIZEOFSMALLSHAPES)
{ // ctor, build new bomb shape
	setArrOfPoints(0, 5, 0);
}

bool Bomb::checkLegalityMoveToSide(const char(&matrix)[ROWS][COLS], EnumTetris::eSides side, bool& cantMoveDown, bool &canMoveToSide)
{//the function check if the bomb can move to sides
	switch (side)
	{
	case EnumTetris::eSides::LEFT:
	{
		if (getArrOfPoints()[0].getX() - 1 < 0 || matrix[getArrOfPoints()[0].getX() - 1][getArrOfPoints()[0].getY()] == '1')
		{
			cantMoveDown = false;
			return false;
		}
		return true;
		break;
	}
	case EnumTetris::eSides::RIGHT:
	{
		if (getArrOfPoints()[0].getX() + 1 >= ROWS || matrix[getArrOfPoints()[0].getX() + 1][getArrOfPoints()[0].getY()] == '1')
		{
			cantMoveDown = false;
			return false;
		}
		return true;
		break;
	}
	default:
	{
		if (getArrOfPoints()[0].getY() + 1 >= COLS || matrix[getArrOfPoints()[0].getX()][getArrOfPoints()[0].getY() + 1] == '1')
		{
			cantMoveDown = false;
			return false;
		}
	}
	return true;
	break;
	}
}
