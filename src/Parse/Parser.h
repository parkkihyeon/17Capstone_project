#ifndef __PARSER__H__
#define __PARSER__H__

#include "parse.h"
#define INIT_TO_ZERO 0
#define PARSE_SHORT_LEN 2
#define PARSE_LONG_LEN 4
#define NUM_OF_SANGCHALIM_POSITION 4
#define CORRECT_NUM_OF_LEFTBRAKET 11
#define NUM_OF_PARSER 3
#define NUM_OF_CHINESE2_POSITION 14
#define NUM_OF_CHINESE_POSITION 8
#define NUM_OF_KOREAN_POSITION 8
#define NUM_OF_UNIT 7

enum { KOREAN_PARSER, CHINESE_PARSER, CHINESE_2_PARSER , ERROR_PARSER , REST_TIME} ;

class Parser
{
public:
	Parser() ;

	virtual char ConvertNameToEnglish(string token) = 0 ;
	virtual char ConvertKilleeToEnglish(string token) = 0 ;

	void initVariable(int nRow, int startN, string all[_MAX_PATH]) ;
	int distinctParser(string token) ;

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

	int numOfRow ;
	int parsingStartNumber ;
	string allString[_MAX_PATH] ;
	Unit unitState ;

	int nameStartPosition, nameLen ;
	int postStartPosition, postLen ;
	int killStartPosition, killLen ;
	int addLen ;

	static char* HorseSequence[NUM_OF_SANGCHALIM_POSITION] ;
	static char* Chinese_character[NUM_OF_CHINESE2_POSITION];
	static char* Chinese_character_one[NUM_OF_CHINESE_POSITION] ;
	static char* Korean_character[NUM_OF_KOREAN_POSITION]   ;
	static char to_English[NUM_OF_UNIT];
};

#endif