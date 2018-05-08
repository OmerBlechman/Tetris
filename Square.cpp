#include "Square.h"

Square::Square() :Shape(SIZEOFBIGSHAPES)
{//ctor , build new shape and draw it to screen game
	for (int i = 0; i<2; ++i)
		setArrOfPoints(i, i + 5, 0);
	for (int i = 0; i<2; i++)
		setArrOfPoints(i + 2, i + 5, 1);
	drawPoint(2);
	drawPoint(3);
};

