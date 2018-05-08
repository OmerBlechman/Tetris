#include "Shape.h"

bool Shape::moveShape(EnumTetris::eSides side, char(&matrix)[ROWS][COLS], const int& currentSpeed)
{//The method check if the a shape can move to all sides and if yes it will move the shape
	bool cantMoveDown = true;//tell when the shape can't move anymore
	bool canMoveToSide = true;
	if (checkLegalityMove(matrix, side, cantMoveDown, canMoveToSide))
	{
		if (canMoveToSide == false)
			move(EnumTetris::eSides::DOWN, currentSpeed);
		else
			move(side, currentSpeed);
	}
	if (cantMoveDown == false)
		return true;
	return false;
}

void Shape::move(EnumTetris::eSides side, const int& currentSpeed)
{//the function move the shape by the input to the side
	switch (side)
	{
	case EnumTetris::eSides::LEFT:
	{
		moveSide(side);
		break;
	}
	case EnumTetris::eSides::RIGHT:
	{
		moveSide(side);
		break;
	}
	case EnumTetris::eSides::UP:
	{ //rotate option
		rotateShape();
		break;
	}
	default:
	{//the default is to get down
		if (side == EnumTetris::eSides::DOWN) // if the user enter down, the shape move faster
			Sleep(1);

		else if (side != EnumTetris::eSides::DOWN)
			Sleep(currentSpeed);

		moveSide(side);
		break;
	}
	}
}

void Shape::moveSide(EnumTetris::eSides side)
{//the function move the shape to side and draw it to screen
	for (size_t i = 0; i < arrOfPoints.size(); ++i)
	{
		arrOfPoints[i].draw(' ');
		arrOfPoints[i].move(side);
	}
	draw();
}

bool Shape::checkLegalityMove(const char(&matrix)[ROWS][COLS], EnumTetris::eSides side, bool& cantMoveDown, bool &canMoveToSide)
{ //the function check if the shape can rotate or move
	if (side == EnumTetris::eSides::UP)
	{
		if (checkRotate(matrix)) // if can rotate
			return true;
	}
	else
		return(checkLegalityMoveToSide(matrix, side, cantMoveDown, canMoveToSide));
	return false;
}

bool Shape::checkLegalityMoveToSide(const char(&matrix)[ROWS][COLS], EnumTetris::eSides side, bool& cantMoveDown, bool &canMoveToSide)
{//the function check if the shape can move to sides

	if(side == EnumTetris::eSides::LEFT)
	{
		for (size_t i = 0; i < arrOfPoints.size(); ++i)
		{
			if (arrOfPoints[i].getX() - 1 < 0 || matrix[arrOfPoints[i].getX() - 1][arrOfPoints[i].getY()] == '1')
				canMoveToSide = false;
		}
	}
	else if(side == EnumTetris::eSides::RIGHT)
	{
		for (size_t i = 0; i < arrOfPoints.size(); ++i)
		{
			if (arrOfPoints[i].getX() + 1 >= ROWS || matrix[arrOfPoints[i].getX() + 1][arrOfPoints[i].getY()] == '1')
				canMoveToSide = false;
		}
	}

	if((side != EnumTetris::eSides::LEFT && side != EnumTetris::eSides::RIGHT) || canMoveToSide == false)
	{
		for (size_t i = 0; i < arrOfPoints.size(); ++i)
		{
			if (arrOfPoints[i].getY() + 1 >= COLS || matrix[arrOfPoints[i].getX()][arrOfPoints[i].getY() + 1] == '1')
			{
				cantMoveDown = false;
				return false;
			}
		}
	}

	return true;
}

void Shape::draw()
{//the function draw the shape to game screen
	for (size_t i = 0; i < arrOfPoints.size(); ++i)
		arrOfPoints[i].draw();
}