#include "TetrisGame.h"

TetrisGame::TetrisGame() : score(0), amountOfShapes(0), speedGame(350)
{ // initilize the attributes
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
			matrix[i][j] = '0';
	}
}

void TetrisGame::updateTheBoard(int x, int y, EnumTetris::eShape kindOfShape, bool& flag, bool& finishUpdatedShape, short amountOfRotates, bool& finishedGame)
{//the method update the board when the shape stops
	if (y == 0 && kindOfShape != EnumTetris::eShape::BOMB)
		gameOver(finishedGame);

	else if (kindOfShape == EnumTetris::eShape::BOMB)
		checkAndExecuteExplosion(flag, x, y);
	else
	{
		if (matrix[x][y] == '0')
			matrix[x][y] = '1';

		if (finishUpdatedShape)
			deleteRowAndAddScore(y, kindOfShape, amountOfRotates);
	}
}

bool TetrisGame::checkFinishGame()
{//the method check if the game is finished
	for (int i = 0; i < ROWS; i++)
	{
		if (matrix[0][i] == '1')
			return true;
	}
	return false;
}

bool TetrisGame::checkFullLine(int y)
{//the method check if the line is full
	for (int x = 0; x < ROWS; x++)
		if (matrix[x][y] == '0')
			return false;

	return true;
}

void TetrisGame::deleteRow(int y)
{//the method delete the line and update the board
	for (int i = 0; i < ROWS; i++) // remove the required line
	{
		gotoxy(i + 35, y + 3);
		cout << ' ';
		matrix[i][y] = '0';
	}
	//update the board after the deletion
	for (int i = y - 1; i >= 1; i--)
	{
		for (int j = 0; j<ROWS; j++)
		{
			if (i + 1 < COLS)
			{
				if (matrix[j][i + 1] != matrix[j][i])
				{
					matrix[j][i + 1] = matrix[j][i];
					if (matrix[j][i] == '1')
					{
						gotoxy(j + 35, i + 3);
						cout << ' ';
						gotoxy(j + 35, i + 1 + 3);
						cout << "#";
						matrix[j][i] = '0';
					}
				}
			}
		}
	}

	//remove the first line
	for (int i = 0; i<ROWS; i++)
	{
		gotoxy(i + 35, 3);
		if (matrix[i][1] == '1')
		{
			cout << ' ';
			matrix[i][1] = '0';
		}
	}
}

Shape*  TetrisGame::createCurrentShape(EnumTetris::eShape kindOfShape)
{//the function create new shape by the random function
	Shape* currentShape = nullptr;
	switch (kindOfShape)
	{
	case EnumTetris::eShape::BOMB:
	{
		currentShape = new Bomb();
		break;
	}
	case EnumTetris::eShape::JOKER:
	{
		currentShape = new Joker();
		break;
	}
	case EnumTetris::eShape::LINE:
	{
		currentShape = new Line();
		break;
	}
	case EnumTetris::eShape::SQUARE:
	{
		currentShape = new Square();
		break;
	}
	case EnumTetris::eShape::LSHAPE:
	{
		currentShape = new Lshape();
		break;
	}
	case EnumTetris::eShape::PLUS:
	{
		currentShape = new Plus();
		break;
	}
	case EnumTetris::eShape::ZSHAPE:
	{
		currentShape = new Zshape();
		break;
	}
	default:
		break;
	}
	return currentShape;
}

void TetrisGame::run()
{//the method run the game
	bool finishedGame = false; // tell when the game is finished
	short counter = 0; // count how many times the user enter '2' (pause/continue)
	print();
	startOption();
	while (finishedGame == false)
	{
		bool flag = true; //tell if we still need the shape
		char keyPressed; // user input
		int random = rand() % NUMOFSHAPES; // random shape
		Shape* currentShape = createCurrentShape((EnumTetris::eShape)random);
		gotoxy(12, 1);
		cout << ++amountOfShapes << "    ";
		while (flag == true) // we are with the same shape
		{
			keyPressed = 0;
			if (_kbhit()) // checks if there is anything in the buffer
				keyPressed = _getch(); // take the head of the buffer

			if (keyPressed == EnumTetris::eOptions::PAUSE)
				pauseOption(counter);

			else if (counter != 1 && keyPressed == EnumTetris::eOptions::INCREASE_TEMPO)
			{
				if (speedGame >= 100)
					speedGame -= 50;
			}

			else if (counter != 1 && keyPressed == EnumTetris::eOptions::DECREASE_TEMPO)
				speedGame += 50;
			else if (counter != 1 && keyPressed == EnumTetris::eSides::SPACE)
			{
				bool moveDown = true;//check if the shape can move to down side
				while (moveDown == true)
				{
					if (currentShape->moveShape(EnumTetris::eSides::DOWN, matrix, 0))
						moveDown = false;
				}
				flag = false; // we finished with the shape
				updateShapeOnBoard(currentShape, (EnumTetris::eShape)random, finishedGame);
				delete currentShape;
			}
			else if (keyPressed == EnumTetris::eOptions::EXIT)
			{
				exitOption(finishedGame, flag);
				delete currentShape;
			}

			else if (counter != 1 && currentShape->moveShape((EnumTetris::eSides)keyPressed, matrix, speedGame))
			{
				flag = false; // we finished with the shape
				updateShapeOnBoard(currentShape, (EnumTetris::eShape)random, finishedGame);
				delete currentShape;
			}

			if (keyPressed == EnumTetris::eSides::DOWN)
			{//increase the score by 1
				addScore(1);
				gotoxy(7, 0);
				cout << getScore() << "   ";
			}

			Sleep(speedGame);
		}
	}
}

void TetrisGame::updateShapeOnBoard(const Shape* currentShape, EnumTetris::eShape kindOfShape, bool& finishedGame)
{//the method update the shape on board
	bool flag = false; // tell the board if there a point that you need to delete 
	bool finishUpdatedShape = false; // tell the board if the whole shape was updated on board

	if (kindOfShape == EnumTetris::eShape::BOMB)
		updateBombOnBoard(currentShape, flag, finishUpdatedShape, finishedGame);
	else
	{
		if (kindOfShape == EnumTetris::eShape::JOKER)
		{
			int x = currentShape->getArrOfPoints()[0].getX();// get X cordinate
			int y = currentShape->getArrOfPoints()[0].getY();// get Y cordinate
			finishUpdatedShape = true;
			updateTheBoard(x, y, kindOfShape, flag, finishUpdatedShape, currentShape->getAmountOfRotates(), finishedGame);
		}
		else//line or square
			updateFourPointsShapeOnBoard(currentShape, kindOfShape, flag, finishUpdatedShape, finishedGame);
	}
}

void TetrisGame::updateBombOnBoard(const Shape* bombShape, bool& flag, bool& finishUpdatedShape, bool& finishedGame)
{//the method update bomb's shape on board by the rules. delete all the points in the area of the bomb (area = 3x3)
	int x = bombShape->getArrOfPoints()[0].getX(); // get X cordinate
	int y = bombShape->getArrOfPoints()[0].getY(); // get Y cordinate
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if (x + i >= 0 && x + i < ROWS && y + j > 0 && y + j < COLS)
			{
				updateTheBoard(x + i, y + j, EnumTetris::eShape::BOMB, flag, finishUpdatedShape, bombShape->getAmountOfRotates(), finishedGame);
				if (flag == true)
				{//if exist a point in the area of bomb
					Point deletePoint(x + i, y + j);
					deletePoint.draw(' ');
					flag = false;
				}
			}
		}//for j
	}//for i
	bombShape->getArrOfPoints()[0].draw(' '); // delete the bomb from the screen
}

void TetrisGame::updateFourPointsShapeOnBoard(const Shape* currentShape, EnumTetris::eShape kindOfShape, bool& flag, bool& finishUpdatedShape, bool& finishedGame)
{//the method update the 4 points shape's in the board game
	for (int i = 3; i >= 0; i--)
	{
		if (i == 0)
			finishUpdatedShape = true;
		int x = currentShape->getArrOfPoints()[i].getX();// get X cordinate
		int y = currentShape->getArrOfPoints()[i].getY();// get Y cordinate
		updateTheBoard(x, y, kindOfShape, flag, finishUpdatedShape, currentShape->getAmountOfRotates(), finishedGame);
	}
}

void TetrisGame::print()
{//the method print the locals to the consul
	cout << "Score: " << score;
	cout << "\nParts Down: " << amountOfShapes;
	cout << " \nGame Status: Running\n" << endl << endl;
	cout << "Menu:\n\n";
	cout << " 1) Start Game" << endl << " 2) Pause/Continue Game" << endl << " 3) Increase tempo of game" << endl << " 4) Decrease tempo of game" << endl << " 9) Exit";

	for (int i = 1; i < COLS; i++)
	{
		gotoxy(34, 3 + i);
		cout << (char)186;
		gotoxy(34 + 11, 3 + i);
		cout << (char)186;
	}
	gotoxy(34, 19);
	cout << (char)200;
	for (int i = 1; i < 11; i++)
		cout << (char)205;
	cout << (char)188;
}

void TetrisGame::checkAndExecuteExplosion(bool&flag, int x, int y)
{//the function check if there a shape in the relevant side and execute explostion if the answer is 'yes' 
	if (matrix[x][y] == '1')
	{
		matrix[x][y] = '0';
		score -= FIFTY_POINTS;
		gotoxy(7, 0); // go to the line of the score and update the score
		cout << score << "   ";
		flag = true; // tell if there a point to delete 
	}
}

void TetrisGame::deleteLineRowAndAddScore(int y, short amountOfRotates)
{//the function check if the line is full and update the matrix and the score
	if (amountOfRotates == 0 || amountOfRotates == 2) //balance mode
	{
		if (checkFullLine(y))
		{
			deleteRow(y);
			score += HUNDRED_POINTS;
			gotoxy(7, 0);// go to the line of the score and update the score
			cout << score << "   ";
		}
	}
	else
	{
		int counter = 3; // help to go to the bottom of the shape
		int numberOfRowsThatDeleted = 0; // help to increase the score
		for (int i = 3; i >= 0; i--)
		{
			if (checkFullLine(y + counter))
			{
				deleteRow(y + counter);
				numberOfRowsThatDeleted++;
			}
			else
				counter--;
		}
		if (numberOfRowsThatDeleted == 4)
		{
			score += EIGHT_HUNDRED_POINTS;
			gotoxy(7, 0);
			cout << score << "   ";
		}
		else
		{
			score += (HUNDRED_POINTS * numberOfRowsThatDeleted);
			gotoxy(7, 0);
			cout << score << "   ";
		}
	}
}

void TetrisGame::deleteSquareRowAndAddScore(int y)
{//the function check if the line is full and update the matrix and the score
	int counter = 1; // help to go to the bottom of the shape
	int numberOfRowsThatDeleted = 0; // help to increase the score

	for (int i = 1; i >= 0; i--)
	{
		if (checkFullLine(y + counter))
		{
			deleteRow(y + counter);
			numberOfRowsThatDeleted++;
		}
		else
			counter--;
	}

	score += (HUNDRED_POINTS * numberOfRowsThatDeleted);
	gotoxy(7, 0);// go to the line of the score and update the score
	cout << score << "   ";
}

void TetrisGame::deleteJokerRowAndAddScore(int y)
{//the function check if the line is full and update the matrix and the score
	if (checkFullLine(y))
	{
		deleteRow(y);
		score += FIFTY_POINTS;
		gotoxy(7, 0);// go to the line of the score and update the score
		cout << score << "   ";
	}
}

void TetrisGame::deleteLShapeRowAndAddScore(int y, short amountOfRotates)
{//the function check if the line is full and update the matrix and the score 
	switch (amountOfRotates)
	{
	case 0:
	{
		checkAndDeleteRowShapeAndUpdateScore(y + 1);
		break;
	}
	case 1:
	{
		int counter = 2;
		for (int i = 2; i >= 0; --i)
		{
			if (checkAndDeleteRowShapeAndUpdateScore(y + counter) == false)
				counter--;
		}
		break;
	}
	case 2:
	{
		int counter = 0;
		for (int i = 2; i >= 1; --i)
		{
			if (checkAndDeleteRowShapeAndUpdateScore(y + counter) == false)
				counter--;
		}

		break;
	}
	case 3:
	{
		checkAndDeleteRowShapeAndUpdateScore(y);
		break;
	}
	default:
		break;
	}

}

void TetrisGame::deleteZShapeRowAndAddScore(int y, short amountOfRotates)
{//the function check if the line is full and update the matrix and the score
	if (amountOfRotates == 0)
		checkAndDeleteRowShapeAndUpdateScore(y + 1);
	else
	{
		int counter = 2;
		for (int i = 1; i >= 0; --i)
		{
			if (checkAndDeleteRowShapeAndUpdateScore(y + counter) == false)
				counter--;
		}
	}
}

void TetrisGame::deletePlusRowAndAddScore(int y, short amountOfRotates)
{//the function check if the line is full and update the matrix and the score
	switch (amountOfRotates)
	{
	case 0:
	{
		checkAndDeleteRowShapeAndUpdateScore(y + 1);
		break;
	}
	case 2:
	{
		int counter = 0;
		for (int i = 1; i >= 0; --i)
		{
			if (checkAndDeleteRowShapeAndUpdateScore(y + counter) == false)
				counter--;
		}

		break;
	}
	default:
	{
		int counter = 0;
		for (int i = 1; i >= 0; --i)
		{
			if (checkAndDeleteRowShapeAndUpdateScore(y + 1 + counter) == false)
				counter--;
		}
		break;
	}
	}

}

bool TetrisGame::checkAndDeleteRowShapeAndUpdateScore(int y)
{//the function check if the line is full and update the matrix and the score
	if (checkFullLine(y))
	{
		deleteRow(y);
		score += HUNDRED_POINTS;
		gotoxy(7, 0);// go to the line of the score and update the score
		cout << score << "   ";
		return true;
	}
	return false;
}

void TetrisGame::deleteRowAndAddScore(int y, EnumTetris::eShape kindOfShape, short amountOfRotates)
{//the function check which shape we have and check if the line is full and update the matrix and the score 
	switch (kindOfShape)
	{
	case EnumTetris::LINE:
	{
		deleteLineRowAndAddScore(y, amountOfRotates);
		break;
	}

	case EnumTetris::SQUARE:
	{
		deleteSquareRowAndAddScore(y);
		break;
	}

	case EnumTetris::JOKER:
	{
		deleteJokerRowAndAddScore(y);
		break;
	}
	case EnumTetris::LSHAPE:
	{
		deleteLShapeRowAndAddScore(y, amountOfRotates);
		break;
	}
	case EnumTetris::eShape::PLUS:
	{
		deletePlusRowAndAddScore(y, amountOfRotates);
		break;
	}
	case EnumTetris::eShape::ZSHAPE:
	{
		deleteZShapeRowAndAddScore(y, amountOfRotates);
		break;
	}
	default:
		break;
	}
}

void TetrisGame::exitOption(bool& finishedGame, bool&flag)
{// the function exit from the game
	gotoxy(13, 2);
	cout << "Finished     ";
	gotoxy(20, 20);
	cout << "You finished to play\n";
	Sleep(3000);
	flag = false;
	finishedGame = true;
}

void TetrisGame::startOption()
{// the function start the game
	char startGame = 0;
	gotoxy(0, 13);

	while (startGame != EnumTetris::eOptions::START_GAME)
		startGame = _getch(); // take the head of the buffer
}

void TetrisGame::pauseOption(short& counter)
{//the function pause the game
	gotoxy(13, 2);
	counter++;
	if (counter == 1)
		cout << "Paused     ";
	else if (counter == 2) // if you want to continue
	{
		counter = 0;
		cout << "Running     ";
	}
}

void TetrisGame::gameOver(bool& finishedGame)
{//the function print that the game is over the exit from the game
	gotoxy(13, 2);
	cout << "Game Over!   ";
	Sleep(3000);
	finishedGame = true;
}