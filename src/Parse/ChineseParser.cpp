#include "ChineseParser.h"

ChineseParser::ChineseParser() {
	nameStartPosition = 2 ;
	nameLen = postLen = killLen = PARSE_SHORT_LEN ;
	postStartPosition = 4 ;
	killStartPosition = 6 ;
} 


char ChineseParser::ConvertNameToEnglish(string token){
	for(int i=0 ; i<NUM_OF_CHINESE_POSITION ; i++){
		if( !strcmp(Chinese_character_one[i], token.c_str()) ){
			if(i == 0 )
				return to_English[0] ;
			else
				return to_English[i-1] ;
		}
	}
	return NOT_METHOD ;
}

char ChineseParser::ConvertKilleeToEnglish(string token){
	return ConvertNameToEnglish(token) ;
}