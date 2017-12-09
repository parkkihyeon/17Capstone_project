#include "parse.h"
#include "readFile.h"

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


bool IsDigit(char c)
{
	if (c < '0' || c >'9') return false;
	return true;
}

