#ifndef _TetrisGame
#define _TetrisGame

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Bomb.h"
#include "Square.h"
#include "Line.h"
#include "Joker.h"
#include "Lshape.h"
#include "Plus.h"
#include "Zshape.h"

using namespace std;

const int NUMOFSHAPES = 7;
const int FIFTY_POINTS = 50;
const int HUNDRED_POINTS = 100;
const int EIGHT_HUNDRED_POINTS = 800;
class TetrisGame
{
public:
	//public methods
	void run();
	TetrisGame();
	TetrisGame(const TetrisGame&) = delete;
	void updateTheBoard(int x, int y, EnumTetris::eShape kindOfShape, bool& flag, bool& finishUpdatedShape, short amountOfRotates, bool& finishedGame);
	void updateShapeOnBoard(const Shape* currentShape, EnumTetris::eShape kindOfShape, bool& finishedGame);
	bool checkFullLine(int y);
	void deleteRow(int y);
	bool checkFinishGame();
	void print();

	void addScore(int score)
	{//the method add score to our current score
		this->score += score;
	}

	void setSpeed(int speed)
	{//the method set the speed of the game
		speedGame = speed;
	}

	bool getFullCurrentPosition(int x, int y) const
	{//the method tells if the joker shape will arrive to a point that there another shape
		if (matrix[x][y] == '0')
			return true;
		else
			return false;
	}

	int getScore() const
	{//the method return the score
		return score;
	}

private:
	//attributes
	char matrix[ROWS][COLS];
	int score;
	int speedGame;
	int amountOfShapes;

	//private methods
	void gameOver(bool& finishedGame);
	void pauseOption(short& counter);
	void startOption();
	void exitOption(bool& finishedGame, bool&flag);
	void checkAndExecuteExplosion(bool&flag, int x, int y);
	void deleteRowAndAddScore(int y, EnumTetris::eShape kindOfShape, short amountOfRotates);
	void deleteLineRowAndAddScore(int y, short amountOfRotates);
	void deleteSquareRowAndAddScore(int y);
	void deleteJokerRowAndAddScore(int y);
	void deleteLShapeRowAndAddScore(int y, short amountOfRotates);
	void deletePlusRowAndAddScore(int y, short amountOfRotates);
	void deleteZShapeRowAndAddScore(int y, short amountOfRotates);

	void updateBombOnBoard(const Shape* bombShape, bool& flag, bool& finishUpdatedShape, bool& finishedGame);
	void updateFourPointsShapeOnBoard(const Shape* currentShape, EnumTetris::eShape kindOfShape, bool& flag, bool& finishUpdatedShape, bool& finishedGame);
	Shape* createCurrentShape(EnumTetris::eShape kindOfShape);
	bool checkAndDeleteRowShapeAndUpdateScore(int y);
};
#endif // !_TetrisGame
