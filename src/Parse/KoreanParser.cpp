// ���� ����
#include "KoreanParser.h"

// �ļ��� ���� �����ǰ� �����ؾ��� �Լ��� �޶����Ƿ� �ʿ��� �����ǰ� �Ľ��Լ��� �Լ������ͷ� ���޹ް� �ȴ�.
KoreanParser::KoreanParser() {
	// 78��79���屺 
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
