#include "Zshape.h"

Zshape::Zshape() :Shape(SIZEOFBIGSHAPES)
{//ctor, build new Zshape
	setArrOfPoints(0, 4, 0);
	setArrOfPoints(1, 5, 0);

	for (int i = 2; i < SIZEOFBIGSHAPES; ++i)
	{
		setArrOfPoints(i, 3 + i, 1);
		drawPoint(i);
	}
}

bool Zshape::checkRotate(const char(&matrix)[ROWS][COLS])
{ // the function check if line shape can rotating
	int x = getArrOfPoints()[1].getX();//get x cordinate
	int y = getArrOfPoints()[1].getY();//get y cordinate

	if (getAmountOfRotates() == 0)
	{
		if (y - 1 > 0 && matrix[x - 1][y + 1] == '0' && matrix[x][y - 1] == '0')
			return true;
	}
	else
	{
		if (x + 1 < COLS && matrix[x][y + 1] == '0' && matrix[x + 1][y + 1] == '0')
			return true;
	}
	return false;
}

void Zshape::rotateShape()
{//the function rotate the shape
	int x = getArrOfPoints()[1].getX();//x axis point of rotating
	int y = getArrOfPoints()[1].getY();//y axis point of rotating
	if (getAmountOfRotates() == 0)
		rotateBalanceMode(x, y - 1, 1);
	else
		rotateVerticalMode(x - 1, y, 1);
	setAmountOfRotates(getAmountOfRotates() + 1); // after every rotate it will up in 1
	setAmountOfRotates(getAmountOfRotates() % 2);//there only 2 modes
}

void Zshape::rotateBalanceMode(int x, int y, int add)
{//the function edit the points of line shape by the rules of rotating
	for (int i = 0; i < 4; ++i)
	{
		drawPoint(i, ' ');
		setArrOfPoints(i, x, y);
		if (i == 1)
			x -= add;
		else
			y += add;
	}
	draw();//draw the shape to screen game
}

void Zshape::rotateVerticalMode(int x, int y, int add)
{//the function edit the points of line shape by the rules of rotating
	for (int i = 0; i < 4; ++i)
	{
		drawPoint(i, ' ');
		setArrOfPoints(i, x, y);
		if (i != 1)
			x += add;
		else
			y += add;
	}
	draw();//draw the shape to screen game
}