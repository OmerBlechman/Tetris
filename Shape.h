#ifndef _SHAPE
#define _SHAPE

#include <iostream>
#include "Gotoxy.h"
#include "Point.h"
#include <vector>
#include "EnumTetris.h"
#include <Windows.h>


using namespace std;
const int ROWS = 10;
const int COLS = 16;
const int SIZEOFSMALLSHAPES = 1;
const int SIZEOFBIGSHAPES = 4;

class Shape
{
protected:
	void setArrOfPoints(int index, int x, int y)
	{//A method that update a point in array
		arrOfPoints[index].setX(x);
		arrOfPoints[index].setY(y);
	}

	void drawPoint(int index, char ch = '#') { arrOfPoints[index].draw(ch); } //A method that print a single point
	void movePoint(int index, EnumTetris::eSides side) { arrOfPoints[index].move(side); } // A method that move a single point
	virtual void draw();

public:
	//public methods
	Shape(int numberOfPoints) :amountOfRotates(0) { arrOfPoints.resize(numberOfPoints); } //ctor
	Shape(const Shape&) = delete;
	virtual~Shape() {}
	virtual bool moveShape(EnumTetris::eSides side, char(&matrix)[ROWS][COLS], const int& currentSpeed);
	virtual void rotateShape() = 0; //abstract method

	const vector<Point> getArrOfPoints() const
	{//the method return the arrOfPoints attribute
		return arrOfPoints;
	}

	short getAmountOfRotates() const
	{//the method return amountOfRotates attribute
		return amountOfRotates;
	}

	void setAmountOfRotates(short amountOfRotates)
	{//the method set amountOfRotates attribute
		this->amountOfRotates = amountOfRotates;
	}

private:
	//attributes
	vector<Point> arrOfPoints;
	short amountOfRotates;

	//Auxiliary functions
	virtual void move(EnumTetris::eSides side, const int& currentSpeed);
	virtual void moveSide(EnumTetris::eSides side);
	virtual bool checkLegalityMove(const char(&matrix)[ROWS][COLS], EnumTetris::eSides side, bool& cantmove, bool &canMoveToSide);
	virtual bool checkLegalityMoveToSide(const char(&matrix)[ROWS][COLS], EnumTetris::eSides side, bool& cantMove, bool &canMoveToSide);
	virtual bool checkRotate(const char(&matrix)[ROWS][COLS]) = 0;




};
#endif // !_SHAPE
