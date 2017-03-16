#include "parse.h"
#include "File_divide.h"

char* HorseSequence[4] = { "¸¶»ó¸¶»ó", "¸¶»ó»ó¸¶", "»ó¸¶¸¶»ó", "»ó¸¶»ó¸¶" };
char* Chinese_character[14] = {"õ¢ðï", "ùÓÜ²", "õ¢Ø©", "ùÓØ©", "õ¢øÐ","ùÓøÐ", "õ¢ó³", "ùÓó³", "õ¢ßÚ","ùÓßÚ", "õ¢ÞÍ", "ùÓÞÍ", "õ¢íâ", "ùÓíâ"} ;
char* Chinese_character_one[8] = {"ðï", "Ü²", "Ø©", "øÐ", "ó³", "ßÚ", "ÞÍ", "íâ" } ;
char* Korean_character[8] = { "Á¹", "º´", "¸¶", "Æ÷","Â÷", "»ó", "»ç","Àå"} ;
char to_English[7] = {'J', 'H','P', 'C', 'X', 'S', 'K'} ;
int sequence_num = 0 ;
int sp = 0 ;

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

void Unit::Printing()
{
	ofstream ostream("parse.txt", ios::app) ;
	if(sequence_num%2==0) {
		Upper2lower_case(&name) ; // ¾Æ½ºÅ° ÄÚµå°ª. ´ë¹®ÀÚ¸¦ ¼Ò¹®ÀÚ·Î!
	}
	else {
		if( Is_uppercase(kill_unit) )
			Upper2lower_case(&kill_unit) ;
	}

	if(take_rest) ostream << sequence_num++%2  << " 0" << " 0" << endl ;
	else ostream << sequence_num++%2 << " " << pre << " " << post <<" " << name
		<<" " << kill_unit << " " << general <<endl ;
	take_rest = false ;
	ostream.close() ;
}

Unit::Unit(char *str)
{
	string gibo_str(str) ;
	// 78Á¹79¸¶Àå±º 
	// pos1/pos2/pos3/pos4
	int pos_1 = 0 ;
	int pos_2 = 2 ;
	int pos_3 = 4 ;
	int pos_4 = 6 ;
	int killonly = KILLONLY ;
	int jang = JANG ;
	int killandjang = KILLANDJANG ;
	int gibo_len = gibo_str.length() ;

	pre = atoi(gibo_str.substr(0,2).c_str()) ;
	general = false ;
	take_rest = false ;
	kill_unit = '0' ;

	if(!strcmp(str, TAKE_REST))
		take_rest = true ;

	// ±âº¸°¡ ÇÑ±Û
	else if(Korean_to_English(gibo_str.substr(2,2)) != 'O'){
		name = Korean_to_English(gibo_str.substr(2,2)) ;
		post = atoi(gibo_str.substr(4,2).c_str()) ;

		// ´Ù¸¥ µ¹À» ¸Ô¾úÀ» °æ¿ì
		if( gibo_len == killonly )
			kill_unit = Korean_to_English(gibo_str.substr(pos_4,2)) ;

		// Àå±ºÀÌ µÈ °æ¿ì
		else if( gibo_len == jang )
			general = true ;

		// ´Ù¸¥ µ¹À» ¸ÔÀ¸¸é¼­ Àå±ºÀÌ µÈ °æ¿ì
		else if( gibo_len == killandjang )
		{
			kill_unit = Korean_to_English(gibo_str.substr(pos_4,2)) ;
			general = true ;
		}
	}
	else {// ±âº¸°¡ ÇÑÀÚÀÏ °æ¿ì.
		// ±âº¸°¡ µÎ±ÛÀÚ ÇÑÀÚÀÎ °æ¿ì.
		if(Convert_Chinese_to_English(gibo_str.substr(pos_2,4)) != 'O' ){
			name = Convert_Chinese_to_English(gibo_str.substr(pos_2,4)) ;
			killonly += 2 ;
			jang += 2 ;
			killandjang += 2 ;
			pos_3 += 2 ;
			pos_4 += 2 ;
		}
		else name = Convert_Chinese_to_English_one(gibo_str.substr(pos_2,2)) ;
		post = atoi(gibo_str.substr(pos_3,2).c_str()) ;

		// ´Ù¸¥ µ¹À» ¸Ô¾úÀ» °æ¿ì
		if( gibo_len == killonly )
			kill_unit = Convert_Chinese_to_English_one(gibo_str.substr(pos_4,2)) ;

		// Àå±ºÀÌ µÈ °æ¿ì
		else if( gibo_len == jang )
			general = true ;

		// ´Ù¸¥ µ¹À» ¸ÔÀ¸¸é¼­ Àå±ºÀÌ µÈ °æ¿ì
		else if( gibo_len == killandjang )
		{
			kill_unit = Convert_Chinese_to_English_one(gibo_str.substr(pos_4,2)) ;
			general = true ;
		}
	}
	Printing() ;
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
	return 'O' ;
}

bool IsDigit(char *str)
{
	for (int i = 0; i < strlen(str); i++){
		if (str[i] < '0' || str[i] >'9') return false;
	}
	return true;
}

char Convert_Chinese_to_English(string str)
{
	for(int i=0 ; i<14 ; i++){
		if( !strcmp(Chinese_character[i], str.c_str()) )
			return to_English[i/2] ;
	}
	return 'O' ;
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
	return 'O' ;
}
// Á¸³ª °³ÄÚµå .
void Parser()
{
	while(1)
	{
		sequence_num = 0 ;
		char *num_of_data = new char[100] ;
		itoa(sp++,num_of_data, DECIMAL) ;
		strcat(num_of_data, TEXT_FORM) ;

		if(sp % 100 == 0 ) cout << "¼ø¹ø : " << sp << endl ;

		int left_braket = 0 ;
		ifstream stream(num_of_data);
		if(stream.fail()) {
			cerr << "open filed " << endl ;
			break ;
		}

		ofstream ostream("parse.txt", ios::app);
		ostream << num_of_data << endl ;

		bool Start_Game = false;
		char *temp = new char[MIN];

		while (!stream.eof())
		{
			char *token = new char[MIN];
			stream.getline(temp, MIN);
			strtok(temp, TOKEN);
			if(temp[0] == '[') left_braket++ ;

			if (!strcmp(temp, "[´ë±¹°á°ú"))
			{
				if(left_braket == 11)
				{
					token = strtok(NULL, TOKEN);
					if (!strcmp(token, "ÇÑ") || !strcmp(token, "õ¢")) ostream << 1 << endl;
					else if (!strcmp(token, "ÃÊ") || !strcmp(token, "ùÓ")) ostream << 0 << endl;
					else ostream << -1 << endl ;
					Start_Game = true;
					continue ;
				}
				else break ;
			}

			while (token = strtok(NULL, TOKEN))
			{
				if (!strcmp(token, HorseSequence[0])) ostream << 0 << endl;
				else if (!strcmp(token, HorseSequence[1])) ostream << 1 << endl;
				else if (!strcmp(token, HorseSequence[2])) ostream << 2 << endl;
				else if (!strcmp(token, HorseSequence[3])) ostream << 3 << endl;

				if(Start_Game && !IsDigit(token) && strlen(token) >= MIN_LENGTH )
					Unit t(token) ;
			}
			free(token) ;
		}
		ostream << endl  ;
		stream.close() ;
		ostream.close() ;
		free(temp) ;
	}

}