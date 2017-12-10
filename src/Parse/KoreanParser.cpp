// 파일 분할
#include "KoreanParser.h"

// 파서에 따라 포지션과 적용해야할 함수가 달라지므로 필요한 포지션과 파싱함수를 함수포인터로 전달받게 된다.
KoreanParser::KoreanParser() {
	// 78졸79마장군 
	nameStartPosition = 2 ;
	nameLen = postLen = killLen = PARSE_SHORT_LEN ;
	postStartPosition = 4 ;
	killStartPosition = 6 ;
} 

char KoreanParser::ConvertNameToEnglish(string token){
	for(int i=0 ; i<NUM_OF_KOREAN_POSITION ; i++){
		if( !strcmp(Korean_character[i],token.c_str()) ){
			if(i == 0)
				return to_English[0] ;
			else
				return to_English[i-1] ;
		}
	}
	return NOT_METHOD ;
}

char KoreanParser::ConvertKilleeToEnglish(string token){
	return ConvertNameToEnglish(token) ;
}
