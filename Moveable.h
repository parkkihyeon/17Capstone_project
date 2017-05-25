#ifndef __MOVEABLE__  
#define __MOVEABLE__  
#include <iostream>
#include <vector>
#include <cmath>
#include <memory.h>
#include "Graph.h"
using namespace std;

typedef char (*STATE)[WIDTH_SIZE];

class Board{
	public:
		char board[11][10];

		Board(){
			for(int i = 0 ; i < 11 ; i ++){
				for(int j = 0 ; j < 10 ; j++){
					board[i][j] = '-';
				}
			}
		}
		void setBoard(char _board[][WIDTH_SIZE]){
			for(int i = 0 ; i< 11 ; i ++)
				for(int j = 0 ; j < 10 ; j++)
					board[i][j] = _board[i][j];
		}

};



class Pos {
public:
	int x, y;
	Pos();
	Pos(int _x, int _y);
	bool operator== (Pos& p);
	bool operator!= (Pos& p);

	bool isValidation();
};

void save_moveable_board(vector<Board> &boardPush , char board[][WIDTH_SIZE], int turn);
bool moveable(char board[][WIDTH_SIZE], char c_board[][WIDTH_SIZE], bool host);
bool isExistTeam(Pos cur, Pos dest, char board[][WIDTH_SIZE]);
bool moveAbleCha(Pos cur, Pos dest, char board[][WIDTH_SIZE]);
bool moveAbleGungAndSa(Pos cur, Pos dest, char board[][WIDTH_SIZE]);
bool moveAbleJol(Pos cur, Pos dest, char board[][WIDTH_SIZE]);
bool moveAbleMa(Pos cur, Pos dest, char board[][WIDTH_SIZE]);
bool moveAblePo(Pos cur, Pos dest, char board[][WIDTH_SIZE]);
bool moveAbleSang(Pos cur, Pos dest, char board[][WIDTH_SIZE]);

#endif
