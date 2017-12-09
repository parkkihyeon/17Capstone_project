// 파일 분할
#ifndef __CHINESE__PARSER__
#define __CHINESE__PARSER__

#include "Parser.h"

class ChineseParser : public Parser {
public:
	ChineseParser() ;
	virtual char ConvertNameToEnglish(string token) ;
	virtual char ConvertKilleeToEnglish(string token)  ;
};


#endif
