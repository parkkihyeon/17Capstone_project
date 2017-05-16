#ifndef __MOVEABLE__  
#define __MOVEABLE__  

#include "Graph.h"

class Pos {
public:
	int x, y;
	Pos();
	Pos(int _x, int _y);
	bool operator== (Pos& p);
	bool operator!= (Pos& p);

	bool isValidation();
};


bool moveable(char board[][WIDTH_SIZE], char c_board[][WIDTH_SIZE], bool host);
bool isExistTeam(Pos cur, Pos dest, char board[][WIDTH_SIZE]);
bool moveAbleCha(Pos cur, Pos dest, char board[][WIDTH_SIZE]);
bool moveAbleGungAndSa(Pos cur, Pos dest, char board[][WIDTH_SIZE]);
bool moveAbleJol(Pos cur, Pos dest, char board[][WIDTH_SIZE]);
bool moveAbleMa(Pos cur, Pos dest, char board[][WIDTH_SIZE]);
bool moveAblePo(Pos cur, Pos dest, char board[][WIDTH_SIZE]);
bool moveAbleSang(Pos cur, Pos dest, char board[][WIDTH_SIZE]);

#endif