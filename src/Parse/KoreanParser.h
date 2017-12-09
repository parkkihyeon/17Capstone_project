#ifndef __KOREAN__PARSER__
#define __KOREAN__PARSER__

#include "Parser.h"

class KoreanParser : public Parser {
public:
	KoreanParser() ;
	virtual char ConvertNameToEnglish(string token) ;
	virtual char ConvertKilleeToEnglish(string token)  ;
};

#endif