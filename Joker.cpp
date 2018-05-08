#include "Joker.h"

Joker::Joker() :Shape(SIZEOFSMALLSHAPES)
{//ctor, build new joker shape
	setArrOfPoints(0, 5, 0);
}


bool Joker::moveShape(EnumTetris::eSides side, char(&matrix)[ROWS][COLS], const int& currentSpeed)
{//the method check if the shape can move to sides and do it if yes
	bool cantMove = true;//tell when the shape can't move anymore
	bool canMoveToSide = true;
	if (checkLegalityMove(matrix, side, cantMove, canMoveToSide))
		move(side, currentSpeed, matrix);
	if (cantMove == false)
		return true;
	return false;
}

bool Joker::checkLegalityMove(const char(&matrix)[ROWS][COLS], EnumTetris::eSides side, bool& cantMoveDown, bool &canMoveToSide)
{//the function check if the shape can move
	int x = getArrOfPoints()[0].getX();
	int y = getArrOfPoints()[0].getY();

	switch (side)
	{
	case EnumTetris::eSides::LEFT:
	{
		if (x - 1 >= 0)
			return true;
		else
			return false;
		break;
	}
	case EnumTetris::eSides::RIGHT:
	{
		if (x + 1 < ROWS)
			return true;
		else
			return false;
		break;
	}
	default:
	{
		if (y + 1 < COLS)
		{
			if (side != EnumTetris::eSides::STOP)
				return true;
			else if (side == EnumTetris::eSides::STOP && y == 0)
				return true;
		}
		//the shape arrived to the bottom or the user press 's' (stop)
		cantMoveDown = false;
		return false;
		break;
	}
	}
	return false;
}

void Joker::move(EnumTetris::eSides side, const int& currentSpeed, char(&matrix)[ROWS][COLS])
{ //the function move the joker shape in the game by the input user
	if (side == EnumTetris::eSides::LEFT || side == EnumTetris::eSides::RIGHT)
		moveToSide(side, matrix);
	else
	{ //the default is to go down
		if (side == EnumTetris::eSides::DOWN) // if the user enter down, the shape move faster
			Sleep(1);
		else if (side != EnumTetris::eSides::DOWN)
			Sleep(currentSpeed);

		moveToSide(side, matrix);
	}
}

void Joker::moveToSide(EnumTetris::eSides side, char(&matrix)[ROWS][COLS])
{//move joker to the side that the user input
	if (matrix[getArrOfPoints()[0].getX()][getArrOfPoints()[0].getY()] == '0')
		drawPoint(0, ' ');
	movePoint(0, side);
	if (matrix[getArrOfPoints()[0].getX()][getArrOfPoints()[0].getY()] == '0')
		drawPoint(0);
}
