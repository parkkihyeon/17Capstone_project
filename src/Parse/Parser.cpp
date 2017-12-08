#include "factoryPattern.h"

static char* HorseSequence[4] = { "���󸶻�", "�����", "�󸶸���", "�󸶻�" };
int sequence_num = 0 ;
ofstream outputStream ;
ifstream inputStream ;

void Parser::printHistory()
{
	if(sequence_num%2==0) {
		Upper2lower_case(&unitState.name) ; // �ƽ�Ű �ڵ尪. �빮�ڸ� �ҹ��ڷ�!
	}
	else {
		if( Is_uppercase(unitState.kill_unit) )
			Upper2lower_case(&unitState.kill_unit) ;
	}

	if(unitState.take_rest) outputStream << sequence_num++%2  << " 0" << " 0" << endl ;
	else outputStream << sequence_num++%2 << " " << unitState.pre << " " << unitState.post <<" " << unitState.name
		<<" " << unitState.kill_unit << " " << unitState.general <<endl ;
	unitState.take_rest = false ;
}


int Parser::getNextTextFile(int &sp){
	char numOfData[_MAX_PATH] ;

	strcpy(numOfData, "");
	itoa(sp++,numOfData, DECIMAL) ;
	strcat(numOfData, TEXT_FORM) ;
	if(sp % 100 == 0 ) cout << "���� : " << sp << endl ;
	inputStream.open(numOfData) ;
	if(inputStream.fail()) {
		cerr << "open filed " << endl ;
		exit(1) ;
	}
	outputStream << numOfData << endl ;
	return GIBO_OPEN_SUCCESS ;
}

void Parser::writeResult(){
	char line[MIN];
	for(int i=0 ; i < numOfRow ; i++){
		strcpy(line, allString[i].c_str()) ;
		if(strstr(line, "���")){
			if(strstr(line, "��") || strstr(line,  "��"))
				outputStream << CHO_PLAY << endl ;
			else if (strstr(line, "��") || strstr(line, "��"))
				outputStream << HAN_PLAY << endl ;
			else
				outputStream << -1 << endl ;
		}
	}
}

bool Parser::writePosition(){
	int isPosition = 0 ;
	char line[MIN];

	for(int i=0 ; i < numOfRow ; i++){
		strcpy(line, allString[i].c_str()) ;

		if(strstr(line, "����")){
			for(int i=0; i < 4 ; i++){
				if (strstr(line, HorseSequence[i])) {
					outputStream << i << endl;
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
	parsingStartNumber = 0 ;
}

bool Parser::checkGibo(){
	char temp[MIN] ;
	numOfRow = 0 ;
	int leftBraket = 0 ;

	bool check1 = false  ;
	bool check2 = false ;

	while(!inputStream.eof()){
		inputStream.getline(temp, MIN) ;
		if( !strcmp(temp, "")) continue ;

		if(strstr(temp,"����")) check1 = true ;
		if(strstr(temp,"���")) check2 = true ;
		allString[numOfRow++] = temp ;
		if(temp[0] == '[') leftBraket++ ;

	}
	inputStream.close() ;

	if(check1 && check2 && leftBraket == 11) return true  ;
	else return false ;
}

void Parser::writeHistory(){
	char line[MIN];
	for(int i=0 ; i < numOfRow ; i++){
		strcpy(line, allString[i].c_str()) ;
		if(!strcmp(line,"")) continue ;

		if(IsDigit(line[0])){
			parsingStartNumber = i ;
			ParserFactory *pf = new SuperParserFactory() ;
			Parser *p = pf->createParser(line) ;
			p->initVariable(numOfRow, parsingStartNumber, allString) ;
			p->parsingHistory() ;
			free(p) ;

			break ;
		}
	}
}

void Parser::startParsing(){
	int sp = 0 ;
	outputStream.open("parse.txt", ios::app);

	while(true)	{
		getNextTextFile(sp) ;
		if(checkGibo()){
			writePosition() ;
			writeResult() ;
			writeHistory() ;
		}

		initAllString() ;
		outputStream << "\n" ;
	}
	outputStream.close() ;
}

Parser::Parser() {
}

void Parser::doing(string giboToken) {}

void Parser::initUnitState(){
	unitState.pre = 0 ;
	unitState.post = 0 ;
	unitState.general = false ;
	unitState.take_rest = false ;
	unitState.kill_unit = '0' ;
	unitState.name = '0' ;
}

void Parser::initVariable(int nRow, int startN, string all[_MAX_PATH]){
	this->numOfRow = nRow ;
	this->parsingStartNumber = startN ;
	for(int i=0; i<nRow ; i++)
		allString[i] = all[i] ;
}

void Parser::parsingHistory() {
	for(int i=parsingStartNumber ; i < numOfRow ; i++){
		char *token = new char[MIN];
		char *line = new char[allString[i].length() + 1 ] ;
		strcpy(line, allString[i].c_str()) ;
		strtok(line , TOKEN) ;

		while(token = strtok(NULL, TOKEN)){
			if(strlen(token) >= MIN_LENGTH){
				initUnitState() ;
				string giboToken = token ;
				int checkGiboType = giboToken.length() ;

				if(!strcmp(token, TAKE_REST)){
					unitState.take_rest = true ;
					continue ;
				}
				doing(giboToken) ;
			}
		}
		free(line) ;
	}
}

void KoreanParser::doing(string giboToken) {
	// 78��79���屺 

	int checkGiboType = giboToken.length() ;
	unitState.name = Korean_to_English(giboToken.substr(2,2)) ;
	unitState.post = atoi(giboToken.substr(4,2).c_str()) ;

	if( checkGiboType == KILLONLY )	// �ٸ� ���� �Ծ��� ���
		unitState.kill_unit = Korean_to_English(giboToken.substr(6,2)) ;

	else if( checkGiboType == JANG ) // �屺�� �� ���
		unitState.general = true ;

	else if( checkGiboType == KILLANDJANG ){ // �ٸ� ���� �����鼭 �屺�� �� ���	
		unitState.kill_unit = Korean_to_English(giboToken.substr(6,2)) ;
		unitState.general = true ;
	}
	printHistory() ;


} 

void Chinese::doing(string giboToken) {
	int checkGiboType = giboToken.length() ;

	unitState.name = Convert_Chinese_to_English_one(giboToken.substr(2,2)) ;
	unitState.post = atoi(giboToken.substr(4,2).c_str()) ;

	if( checkGiboType == KILLONLY )	// �ٸ� ���� �Ծ��� ���
		unitState.kill_unit = Convert_Chinese_to_English_one(giboToken.substr(6,2)) ;

	else if( checkGiboType == JANG ) // �屺�� �� ���
		unitState.general = true ;

	else if( checkGiboType == KILLANDJANG ){ // �ٸ� ���� �����鼭 �屺�� �� ���	
		unitState.kill_unit = Convert_Chinese_to_English_one(giboToken.substr(6,2)) ;
		unitState.general = true ;
	}
	printHistory() ;


} 

void Chinese2::doing(string giboToken)  {
	int checkGiboType = giboToken.length() ;

	unitState.name = Convert_Chinese_to_English(giboToken.substr(2,4)) ;
	unitState.post = atoi(giboToken.substr(6,2).c_str()) ;

	if( checkGiboType == KILLONLY+2 )	// �ٸ� ���� �Ծ��� ���
		unitState.kill_unit = Convert_Chinese_to_English_one(giboToken.substr(8,2)) ;

	else if( checkGiboType == JANG+2 ) // �屺�� �� ���
		unitState.general = true ;

	else if( checkGiboType == KILLANDJANG+2 ){ // �ٸ� ���� �����鼭 �屺�� �� ���	
		unitState.kill_unit = Convert_Chinese_to_English_one(giboToken.substr(8,2)) ;
		unitState.general = true ;
	}
	printHistory() ;

}
void tempParser::doing(string giboToken)  {}
