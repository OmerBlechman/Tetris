#ifndef _ENUMTETRIS
#define _ENUMTETRIS

class EnumTetris
{

public:
	enum eShape { LINE, SQUARE, JOKER, BOMB, LSHAPE, PLUS, ZSHAPE };
	enum eSides { LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 'x', STOP = 's', SPACE = ' ' };
	enum eOptions { START_GAME = '1', PAUSE = '2', INCREASE_TEMPO = '3', DECREASE_TEMPO = '4', EXIT = '9' };

};

#endif // !_ENUMTETRIS
