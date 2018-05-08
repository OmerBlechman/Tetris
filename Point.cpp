#include "Point.h"

Point::Point(int x, int y) : x(x), y(y) {}

void Point::draw(char c) const
{//the method draw the char to the consul
	gotoxy(x + 35, y + 3);
	cout << c << endl;
}

void Point::move(EnumTetris::eSides side)
{//the method move the point to the appropriate side
	switch (side) {
	case EnumTetris::eSides::LEFT:
	{
		dir_x = -1;
		dir_y = 0;
		x = (x + dir_x);
		y = (y + dir_y);
	}
	break;
	case EnumTetris::eSides::RIGHT:
	{
		dir_x = 1;
		dir_y = 0;
		x = (x + dir_x);
		y = (y + dir_y);
	}
	break;
	default:
	{
		dir_x = 0;
		dir_y = 1;
		x = (x + dir_x);
		y = (y + dir_y);
	}
	break;
	}

}