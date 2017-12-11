#ifndef __MOVEABLE__
#define __MOVEABLE__
#include <iostream>
#include <vector>
#include <cmath>
#include <memory.h>
//#include "Graph.h"
using namespace std;
#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11
enum {CHO_PLAY, HAN_PLAY};

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
    void operator=(Pos& p);
    bool isValidation();
};


class Moveable
{
    public :
    char board[11][10];
    Pos cur;
    Pos dest;
    bool host;
    bool ispossible;
    
    protected :
    bool isExistTeam(char piece);
    bool getTeam(char piece);
    void operator=(Moveable& opr);
    
    
    public:
    Moveable(char board[][WIDTH_SIZE], char c_board[][WIDTH_SIZE] , bool host);
    Moveable(char board[][WIDTH_SIZE]);
    Moveable(){}
    char getPiece();
    bool getIsPossible()
    {
        return ispossible;
    }
    virtual bool isMoveable();
    
    
    
    
    
};
class MaskingInCastle : public Moveable
{
    public:
    int mask[3][3];
    bool isInCastle() ;
    void determineMasking();
    void maskingTwoStep();
    void maskingFourWay();
    void maskingEightWay();
    
    public:
    MaskingInCastle():Moveable()
    {
        for(int i =0 ; i < 3 ; i++) for(int j = 0 ; j < 3 ; j ++) mask[i][j] = 0;
    }
};

class MoveableGungAndSa : public MaskingInCastle
{
    public:
    virtual bool isMoveable();
    
    
    
    public:
    MoveableGungAndSa(char board[][WIDTH_SIZE], Pos cur , Pos dest , bool host) :MaskingInCastle()
    {
        for(int i = 0 ; i < 11 ; i++) for(int j = 0 ; j < 10 ; j++) this->board[i][j] = board[i][j];
        this->cur = cur;
        this->dest = dest;
        this->host = host;
    }

};
class MoveableCha : public MaskingInCastle
{
    public:
    virtual bool isMoveable();
    
    public:
    MoveableCha(char board[][WIDTH_SIZE], Pos cur , Pos dest , bool host) :MaskingInCastle()
    {
        for(int i = 0 ; i < 11 ; i++) for(int j = 0 ; j < 10 ; j++) this->board[i][j] = board[i][j];
        this->cur = cur;
        this->dest = dest;
        this->host = host;
    }
    

    
};
class MoveablePo : public MaskingInCastle
{
    public:
    virtual bool isMoveable();
    
    
    public:
    MoveablePo(char board[][WIDTH_SIZE], Pos cur , Pos dest , bool host) :MaskingInCastle()
    {
        for(int i = 0 ; i < 11 ; i++) for(int j = 0 ; j < 10 ; j++) this->board[i][j] = board[i][j];
        this->cur = cur;
        this->dest = dest;
        this->host = host;
    }

    
    
};
class MoveableJol : public MaskingInCastle
{
    public:
    virtual bool isMoveable();
    
    public:
    MoveableJol(char board[][WIDTH_SIZE], Pos cur , Pos dest , bool host) :MaskingInCastle()
    {
        for(int i = 0 ; i < 11 ; i++) for(int j = 0 ; j < 10 ; j++) this->board[i][j] = board[i][j];
        this->cur = cur;
        this->dest = dest;
        this->host = host;
    }

    
};



class MoveableSang : public Moveable
{
    public:
    virtual bool isMoveable();
    
    
    public:
    MoveableSang(char board[][WIDTH_SIZE], Pos cur , Pos dest , bool host) :Moveable()
    {
        for(int i = 0 ; i < 11 ; i++) for(int j = 0 ; j < 10 ; j++) this->board[i][j] = board[i][j];
        this->cur = cur;
        this->dest = dest;
        this->host = host;
    }
    
    
    

};

class MoveableMa : public Moveable
{
    public:
    virtual bool isMoveable();
    
    MoveableMa(char board[][WIDTH_SIZE], Pos cur , Pos dest , bool host) :Moveable()
    {
        for(int i = 0 ; i < 11 ; i++) for(int j = 0 ; j < 10 ; j++) this->board[i][j] = board[i][j];
        this->cur = cur;
        this->dest = dest;
        this->host = host;
    }
    

};


bool startMoveable(Moveable obj);



#endif





