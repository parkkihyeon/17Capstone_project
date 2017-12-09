#ifndef __PARSER__H__
#define __PARSER__H__

#include "parse.h"
#define INIT_TO_ZERO 0
#define PARSE_SHORT_LEN 2
#define PARSE_LONG_LEN 4
#define NUM_OF_SANGCHALIM_POSITION 4
#define CORRECT_NUM_OF_LEFTBRAKET 11

class Parser
{
public:
	Parser() ;
	virtual void defineUnit(string giboToken) = 0 ;
	void initVariable(int nRow, int startN, string all[_MAX_PATH]) ;

	int getNextTextFile(int &sp) ;
	bool checkGibo() ;

	void startParsing() ;
	void initAllString() ;
	void readAMove(string giboToken) ;

	void writeHistory();
	void writeResult() ;
	bool writePosition() ;

	void printHistory();
	void initUnitState() ;
	void parsingHistory() ;

protected:
	char (*nameOfParser)(string str) ;
	char (*killOfParser)(string str) ;

	int numOfRow ;
	int parsingStartNumber ;
	string allString[_MAX_PATH] ;
	Unit unitState ;

	int nameStartPosition, nameLen ;
	int postStartPosition, postLen ;
	int killStartPosition, killLen ;
	int addLen ;

};
 
class KoreanParser : public Parser {
public:
	virtual void defineUnit(string giboToken) ;
};

class Chinese : public Parser {
public:
	virtual void defineUnit(string giboToken) ;
};

class Chinese2 : public Parser {
public:
	virtual void defineUnit(string giboToken);
};

class tempParser : public Parser {
public:
	virtual void defineUnit(string giboToken) ;
};

#endif