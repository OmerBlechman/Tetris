#include "Line.h"

Line::Line() :Shape(SIZEOFBIGSHAPES)
{//ctor, build new Line shape
	for (int i = 0; i < SIZEOFBIGSHAPES; i++)
		setArrOfPoints(i, 5 + i, 0);
}

bool Line::checkRotate(const char(&matrix)[ROWS][COLS])
{ // the function check if line shape can rotating
	int x;//get x cordinate
	int y;//get y cordinate
	if (getAmountOfRotates() == 0)
	{ //in balanced mode
		x = getArrOfPoints()[2].getX();
		y = getArrOfPoints()[2].getY();
		if (y - 2 >= 1 && y + 1 < COLS && matrix[x][y - 2] == '0' && matrix[x][y - 1] == '0' && matrix[x][y + 1] == '0')
			return true;
	}
	else if (getAmountOfRotates() == 1)
	{//in vertical mode
		x = getArrOfPoints()[2].getX();
		y = getArrOfPoints()[2].getY();
		if (x - 2 >= 0 && x + 1 < ROWS && matrix[x - 2][y] == '0' && matrix[x - 1][y] == '0' && matrix[x + 1][y] == '0')
			return true;
	}
	else if (getAmountOfRotates() == 2)
	{//in balanced mode
		x = getArrOfPoints()[1].getX();
		y = getArrOfPoints()[1].getY();
		if (y - 1 >= 1 && y + 2 < COLS && matrix[x][y - 1] == '0' && matrix[x][y + 1] == '0' && matrix[x][y + 2] == '0')
			return true;
	}
	else if (getAmountOfRotates() == 3)
	{//in vertical mode
		x = getArrOfPoints()[1].getX();
		y = getArrOfPoints()[1].getY();
		if (x - 1 >= 0 && x + 2 < ROWS && matrix[x - 1][y] == '0' && matrix[x + 1][y] == '0' && matrix[x + 2][y] == '0')
			return true;
	}
	return false;
}

void Line::rotateShape()
{//the function rotate the shape
	int x;//x axis point of rotating
	int y;//y axis point of rotating
	if (getAmountOfRotates() == 0)
	{//the first time of rotating - in balance mode
		x = getArrOfPoints()[2].getX();
		y = getArrOfPoints()[2].getY();
		rotate(x, y, 0, 2);
	}
	else if (getAmountOfRotates() == 1)
	{// if rotate before once time - in vertical mode
		x = getArrOfPoints()[2].getX();
		y = getArrOfPoints()[2].getY();
		rotate(x, y, 2, 0);
	}
	else if (getAmountOfRotates() == 2)
	{//if rotated before twice - in balance mode
		x = getArrOfPoints()[1].getX();
		y = getArrOfPoints()[1].getY();
		rotate(x, y, 0, 1);
	}
	else if (getAmountOfRotates() == 3)
	{//if rotated before three times - in vertical mode
		x = getArrOfPoints()[1].getX();
		y = getArrOfPoints()[1].getY();
		rotate(x, y, 1, 0);
	}

	setAmountOfRotates(getAmountOfRotates() + 1); // after every rotate it will up in 1
	setAmountOfRotates(getAmountOfRotates() % 4);//there only 4 modes
}

void Line::rotate(int x, int y, int countX, int countY)
{//the function edit the points of line shape by the rules of rotating
	for (int i = 0; i <= 3; i++)
	{
		drawPoint(i, ' ');
		setArrOfPoints(i, x - countX, y - countY);
		drawPoint(i);
		if (getAmountOfRotates() == 0 || getAmountOfRotates() == 2)
		{
			countY--;
			if (countY == 0)
			{
				i++;
				countY--;
			}
		}
		else
		{
			countX--;
			if (countX == 0)
			{
				i++;
				countX--;
			}
		}
	}
}

