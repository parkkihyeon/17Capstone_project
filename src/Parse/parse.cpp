#include "parse.h"
#include "readFile.h"

static char* Chinese_character[14] = {"õ¢ğï", "ùÓÜ²", "õ¢Ø©", "ùÓØ©", "õ¢øĞ","ùÓøĞ", "õ¢ó³", "ùÓó³", "õ¢ßÚ","ùÓßÚ", "õ¢ŞÍ", "ùÓŞÍ", "õ¢íâ", "ùÓíâ"} ;
static char* Chinese_character_one[8] = {"ğï", "Ü²", "Ø©", "øĞ", "ó³", "ßÚ", "ŞÍ", "íâ" } ;
static char* Korean_character[8] = { "Á¹", "º´", "¸¶", "Æ÷","Â÷", "»ó", "»ç","Àå"} ;
static char to_English[7] = {'J', 'H','P', 'C', 'X', 'S', 'K'} ;


void Upper2lower_case(char *ch)
{
	*ch += 32 ;
}

bool Is_uppercase(char ch)
{
	if( ch >= 'A' && ch <= 'Z')
		return true ;
	else return false ;
}


char Korean_to_English(string str)
{
	for(int i=0 ; i<8 ; i++){
		if( !strcmp(Korean_character[i],str.c_str()) ){
			if(i == 0)
				return to_English[0] ;
			else
				return to_English[i-1] ;
		}
	}
	return NOT_METHOD ;
}

bool IsDigit(char c)
{
	if (c < '0' || c >'9') return false;
	return true;
}

char Convert_Chinese_to_English(string str)
{
	for(int i=0 ; i<14 ; i++){
		if( !strcmp(Chinese_character[i], str.c_str()) )
			return to_English[i/2] ;
	}
	return NOT_METHOD ;
}

char Convert_Chinese_to_English_one(string str)
{
	for(int i=0 ; i<8 ; i++){
		if( !strcmp(Chinese_character_one[i], str.c_str()) ){
			if(i == 0 )
				return to_English[0] ;
			else
				return to_English[i-1] ;
		}
	}
	return NOT_METHOD ;
}

