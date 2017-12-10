// 파일 분할
#ifndef _CHINESE_2_PARSER_
#define _CHINESE_2_PARSER_

#include "Parser.h"

class Chinese2Parser : public Parser {
public:
	Chinese2Parser() ;
	virtual char ConvertNameToEnglish(string token) ;
	virtual char ConvertKilleeToEnglish(string token)  ;
};

#endif
