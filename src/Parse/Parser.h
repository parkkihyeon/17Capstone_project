#ifndef __PARSER__H__
#define __PARSER__H__

#include "parse.h"

class Parser
{
public:
	Parser() ;
	virtual void doing(string giboToken) = 0 ;
	void initVariable(int nRow, int startN, string all[_MAX_PATH]) ;

	int getNextTextFile(int &sp) ;
	bool writePosition() ;
	bool checkGibo() ;

	void startParsing() ;
	void writeResult() ;
	void initAllString() ;
	void writeHistory();
	void printHistory();
	void initUnitState() ;
	void parsingHistory() ;

protected:
	int numOfRow ;
	int parsingStartNumber ;
	string allString[_MAX_PATH] ;
	Unit unitState ;

};
 
class KoreanParser : public Parser {
public:
	virtual void doing(string giboToken) ;
};

class Chinese : public Parser {
public:
	virtual void doing(string giboToken) ;
};

class Chinese2 : public Parser {
public:
	virtual void doing(string giboToken);
};

class tempParser : public Parser {
public:
	virtual void doing(string giboToken) ;
};

#endif