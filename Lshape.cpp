#include "Lshape.h"

Lshape::Lshape() :Shape(SIZEOFBIGSHAPES)
{//ctor, build new Lshape
	setArrOfPoints(0, 5, 0);
	for (int i = 1; i < SIZEOFBIGSHAPES; ++i)
	{
		setArrOfPoints(i, 4 + i, 1);
		drawPoint(i);
	}
}

bool Lshape::checkRotate(const char(&matrix)[ROWS][COLS])
{ // the function check if line shape can rotating
	int x = getArrOfPoints()[2].getX();//get x cordinate
	int y = getArrOfPoints()[2].getY();//get y cordinate

	switch (getAmountOfRotates())
	{
	case 0:
	{
		if (y + 1 < COLS)
			if (matrix[x + 1][y - 1] == '0' && matrix[x][y - 1] == '0' && matrix[x][y + 1] == '0')
				return true;
		return false;
		break;
	}
	case 1:
	{
		if (x - 1 >= 0)
			if (matrix[x - 1][y] == '0' && matrix[x + 1][y] == '0' && matrix[x + 1][y + 1] == '0')
				return true;
		return false;
		break;
	}
	case 2:
	{
		if (y - 1 >= 0)
		{
			if (matrix[x + 1][y + 1] == '0' && matrix[x + 1][y] == '0' && matrix[x - 1][y] == '0')
				return true;
		}
		return false;
		break;
	}
	case 3:
	{
		if (x + 1 < COLS)
			if (matrix[x + 1][y] == '0' && matrix[x - 1][y] == '0' && matrix[x - 1][y - 1] == '0')
				return true;
		return false;
		break;
	}
	default:
		break;
	}
	return false;
}

void Lshape::rotateShape()
{//the function rotate the shape
	int x = getArrOfPoints()[2].getX();//x axis point of rotating
	int y = getArrOfPoints()[2].getY();//y axis point of rotating
	switch (getAmountOfRotates())
	{
	case 0:
	{
		rotateBalanceMode(x + 1, y - 1, 1);
		break;
	}
	case 1:
	{
		rotateVerticalMode(x + 1, y + 1, -1);
		break;
	}
	case 2:
	{
		rotateBalanceMode(x - 1, y + 1, -1);
		break;
	}
	case 3:
	{
		rotateVerticalMode(x - 1, y - 1, 1);
		break;

	}
	}
	setAmountOfRotates(getAmountOfRotates() + 1); // after every rotate it will up in 1
	setAmountOfRotates(getAmountOfRotates() % 4);//there only 4 modes
}

void Lshape::rotateBalanceMode(int x, int y, int add)
{//the function edit the points of line shape by the rules of rotating
	for (int i = 0; i < 4; ++i)
	{
		drawPoint(i, ' ');
		setArrOfPoints(i, x, y);
		if (i == 0)
			x -= add;
		else
			y += add;
		drawPoint(i);
	}

}

void Lshape::rotateVerticalMode(int x, int y, int add)
{//the function edit the points of line shape by the rules of rotating
	for (int i = 0; i < 4; ++i)
	{
		drawPoint(i, ' ');
		setArrOfPoints(i, x, y);
		if (i == 0)
			y += add;
		else
			x += add;
		drawPoint(i);
	}
}