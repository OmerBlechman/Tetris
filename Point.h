#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "Gotoxy.h"
#include "EnumTetris.h"

using namespace std;

class Point
{

public:
	Point(int x = 5, int y = 0);
	void draw(char c = '#') const;
	int getX() const
	{//the method return the X value
		return x;
	}
	int getY() const
	{//the method return the Y value
		return y;
	}
	void setX(int x)
	{//the method set the X value
		this->x = x;
	}
	void setY(int y)
	{//the method set the Y value
		this->y = y;
	}
	void move(EnumTetris::eSides side);

private:
	int x;
	int y;
	int dir_x = 1;
	int dir_y = 0;
};


#endif
