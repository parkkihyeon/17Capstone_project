#include "parse.h"
#include "readFile.h"

static char* HorseSequence[4] = { "¸¶»ó¸¶»ó", "¸¶»ó»ó¸¶", "»ó¸¶¸¶»ó", "»ó¸¶»ó¸¶" };
static char* Chinese_character[14] = {"õ¢ðï", "ùÓÜ²", "õ¢Ø©", "ùÓØ©", "õ¢øÐ","ùÓøÐ", "õ¢ó³", "ùÓó³", "õ¢ßÚ","ùÓßÚ", "õ¢ÞÍ", "ùÓÞÍ", "õ¢íâ", "ùÓíâ"} ;
static char* Chinese_character_one[8] = {"ðï", "Ü²", "Ø©", "øÐ", "ó³", "ßÚ", "ÞÍ", "íâ" } ;
static char* Korean_character[8] = { "Á¹", "º´", "¸¶", "Æ÷","Â÷", "»ó", "»ç","Àå"} ;
static char to_English[7] = {'J', 'H','P', 'C', 'X', 'S', 'K'} ;
int sequence_num = 0 ;

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

int Parser::getNextTextFile(int &sp){
	char numOfData[_MAX_PATH] ;

	strcpy(numOfData, "");
	itoa(sp++,numOfData, DECIMAL) ;
	strcat(numOfData, TEXT_FORM) ;
	if(sp % 100 == 0 ) cout << "¼ø¹ø : " << sp << endl ;
	stream.open(numOfData) ;
	if(stream.fail()) {
		cerr << "open filed " << endl ;
		exit(1) ;
	}
	ostream << numOfData << endl ;
	return GIBO_OPEN_SUCCESS ;
}

void Parser::writeResult(){
	char line[MIN];
	for(int i=0 ; i < numOfRow ; i++){
		strcpy(line, allString[i].c_str()) ;
		if(strstr(line, "°á°ú")){
			if(strstr(line, "ÃÊ") || strstr(line,  "ùÓ"))
				ostream << CHO_PLAY << endl ;
			else if (strstr(line, "ÇÑ") || strstr(line, "õ¢"))
				ostream << HAN_PLAY << endl ;
			else
				ostream << -1 << endl ;
		}
	}
}

bool Parser::writePosition(){
	int isPosition = 0 ;
	char line[MIN];

	for(int i=0 ; i < numOfRow ; i++){
		strcpy(line, allString[i].c_str()) ;

		if(strstr(line, "Â÷¸²")){
			for(int i=0; i < 4 ; i++){
				if (strstr(line, HorseSequence[i])) {
					ostream << i << endl;
					isPosition++ ;
					break ;
				}
			}
		}
		if(isPosition == 2 ) return true ;
	}
	return false ;
}

void Parser::initAllString() {
	for(int i=0; i< numOfRow; i++){
		allString[i] = "" ;
	}
}

bool Parser::checkGibo(){
	char temp[MIN] ;
	numOfRow = 0 ;
	int leftBraket = 0 ;

	bool check1 = false  ;
	bool check2 = false ;

	while(!stream.eof()){
		stream.getline(temp, MIN) ;
		if( !strcmp(temp, "")) continue ;

		if(strstr(temp,"Â÷¸²")) check1 = true ;
		if(strstr(temp,"°á°ú")) check2 = true ;
		allString[numOfRow++] = temp ;
		if(temp[0] == '[') leftBraket++ ;

	}
	stream.close() ;

	if(check1 && check2 && leftBraket == 11) return true  ;
	else return false ;
}

void Parser::writeHistory(){
	char line[MIN];
	char *token = new char[MIN];

	for(int i=0 ; i < numOfRow ; i++){
		strcpy(line, allString[i].c_str()) ;
		if(!strcmp(line,"")) continue ;

		if(IsDigit(line[0])){
			strtok(line, TOKEN) ;
			while(token = strtok(NULL, TOKEN)){
				if(strlen(token) >= MIN_LENGTH)
					Unit t(token) ;
			}
		}
	}
	free(token) ;
}


Parser::Parser() {
	int sp = 0 ;
	ostream.open("parse.txt", ios::app);

	while(true)
	{
		getNextTextFile(sp) ;
		if(checkGibo()){
			writePosition() ;
			writeResult() ;
			writeHistory() ;
		}

		initAllString() ;
		ostream << "\n" ;
	}
	ostream.close() ;
}

void Parser::doing() {}
void KoreanParser::doing() {

} 
void Chinese::doing() {} 
void Chinese2::doing()  {}

ParserFactory::ParserFactory(){} 
Parser* ParserFactory::createParser(int name) {
	return FactoryMethod(name) ;
}


SuperParserFactory::SuperParserFactory(){} 

Parser* SuperParserFactory::FactoryMethod(int name) {
	switch(name){
	case 1: return new KoreanParser ;
	case 2: return new Chinese ;
	case 3: return new Chinese2 ;
	default : break ;
	}
}

