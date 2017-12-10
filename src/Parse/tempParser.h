// 파일 분할
#ifndef __TEMP__PARSER__
#define __TEMP__PARSER__

#include "Parser.h"

class tempParser : public Parser {
public:
	tempParser() ;
	virtual char ConvertNameToEnglish(string token) ;
	virtual char ConvertKilleeToEnglish(string token)  ;
};

#endif
