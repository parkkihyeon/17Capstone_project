#include "Chinese2Parser.h"

Chinese2Parser::Chinese2Parser()  {
	nameStartPosition = 2 ;
	nameLen = PARSE_LONG_LEN ;
	postLen = killLen = PARSE_SHORT_LEN ;
	postStartPosition = 6 ;
	killStartPosition = 8 ;
	addLen = 2 ;
}


char Chinese2Parser::ConvertNameToEnglish(string token){
	for(int i=0 ; i<NUM_OF_CHINESE2_POSITION ; i++){
		if( !strcmp(Chinese_character[i], token.c_str()) )
			return to_English[i/2] ;
	}
	return NOT_METHOD ;
}

char Chinese2Parser::ConvertKilleeToEnglish(string token){
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