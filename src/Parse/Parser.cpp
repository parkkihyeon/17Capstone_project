#include "factoryPattern.h"

char* Parser::HorseSequence[NUM_OF_SANGCHALIM_POSITION] = { "���󸶻�", "�����", "�󸶸���", "�󸶻�" }; 
char* Parser::Chinese_character[NUM_OF_CHINESE2_POSITION] = {"����", "��ܲ", "��ة", "��ة", "����","����", "���", "���", "����","����", "����", "����", "����", "����"} ;
char* Parser::Chinese_character_one[NUM_OF_CHINESE_POSITION] = {"��", "ܲ", "ة", "��", "�", "��", "��", "��" } ;
char* Parser::Korean_character[NUM_OF_KOREAN_POSITION] ={ "��", "��", "��", "��","��", "��", "��","��"} ;
char Parser::to_English[NUM_OF_UNIT] = {'J', 'H','P', 'C', 'X', 'S', 'K'} ;

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

// ���� open�� �ؽ�Ʈ ������ open�Ѵ�. ���� ���� �ؽ�Ʈ ������ ������ ���� ����ȴ�.
int Parser::getNextTextFile(int &sp){
	// ������ ������� 0.txt ~ n-1.txt���� ���� �ִ�.
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

// ��� ����� ���Ͽ� ���� �۾�.
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

// ������ �������� ���Ͽ� ���� �Լ�.
bool Parser::writePosition(){
	int isPosition = 0 ;
	char line[MIN];

	for(int i=0 ; i < numOfRow ; i++){
		strcpy(line, allString[i].c_str()) ;

		if(strstr(line, "����")){
			for(int i=0; i < NUM_OF_SANGCHALIM_POSITION ; i++){
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

// ���� ��� �ִ� �⺸�� �ʱ�ȭ �Ѵ�.
void Parser::initAllString() {
	for(int i=0; i< numOfRow; i++){
		allString[i] = "" ;
	}
	parsingStartNumber = 0 ;
}

// �⺸�� ������ ����. �⺻������ �־�� �� ��������, �뱹 ���(�� ���º�), �׸��� �ùٸ� �������� üũ���ִ� �Լ��̴�.
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

	if(check1 && check2 && leftBraket == CORRECT_NUM_OF_LEFTBRAKET) return true  ;
	else return false ;
}

// �������� �뱹����� write�� ��, ������ ���� �����丮�� ���Ͽ� �����ϱ� ���� �Լ��̴�.
void Parser::writeHistory(){
	char line[MIN];
	for(int i=0 ; i < numOfRow ; i++){
		strcpy(line, allString[i].c_str()) ;
		if(!strcmp(line,"")) continue ;
		// � ������ �ļ��� ������ �� �������� ���� ����� ���⼭ �����Ѵ�.
		if(IsDigit(line[0])){
			parsingStartNumber = i ;

			// �� ��, �߰��� ���丮�� �����ϴ� ������, �⺸ �߰��� ��� ������ �⺸���� Ȯ���� �� �ֱ� �����̴�.
			// ����, �Ϲ����� ���丮 ���ϰ� �ٸ��� �̸� � �ļ��� ����� �� �� �� ����.
			// �߰� �ؼ� ��� �� ����� �������� � �ļ��� ������ ���丮���� �����Ѵ�.
			ParserFactory *pf = new SuperParserFactory() ;
			Parser *p = pf->createParser(line, this) ;
			if(p == NULL) return ;

			// ���� �ļ����� ���Ǿ��� �ʿ��� ������ �����ϰ�
			p->initVariable(numOfRow, parsingStartNumber, allString) ;

			// ��¥ �Ľ��� �����Ѵ�.
			p->parsingHistory() ;
			free(p) ;

			break ;
		}
	}
}

// �Ľ��� 3�ܰ�� ����� �����Ѵ�.
void Parser::startParsing(){
	int sp = 0 ;
	outputStream.open("parse.txt", ios::app);
	while(true)	{
		getNextTextFile(sp) ; 
		cout << sp << endl ;
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

// �� �ļ����� �ٸ� ����� �Ľ� ����� �ʿ��ϴ�. �θ�Ŭ������ ��� 0�� NULL�� �ʱ�ȭ �Ѵ�.
Parser::Parser() {
	nameStartPosition = nameLen = INIT_TO_ZERO ;
	postStartPosition = postLen = INIT_TO_ZERO ;
	killStartPosition = killLen = INIT_TO_ZERO ;
	addLen = 0 ;
}

// �÷��̾� �� �� ������ ������ �ʱ�ȭ �Ѵ�.
void Parser::initUnitState(){
	unitState.pre = 0 ;
	unitState.post = 0 ;
	unitState.general = false ;
	unitState.take_rest = false ;
	unitState.kill_unit = '0' ;
	unitState.name = '0' ;
}

// ���丮 ���Ͽ� ���� ���� ���� �ļ��� ������ �ʿ��� ������ ������ �����Ѵ�.
void Parser::initVariable(int nRow, int startN, string all[_MAX_PATH]){

	this->numOfRow = nRow ;
	this->parsingStartNumber = startN ;
	for(int i=0; i<nRow ; i++)
		allString[i] = all[i] ;
}

// ���� �÷��̾��� ���� ���� ������ unitState�� �����ϴ� �Լ�.
// ������ ���� ������, ���� ������ ���� ���, �屺�� ���, ���� ������ ���̸鼭 �屺�� ��쿡 ���� ��������.
// �� ��, �⺸�� �ѱ������� �߱�������, Ȥ�� �ٸ� ����� �ļ������� ���� �Ľ� ����� ������ ����
// ��ȭ�� �ʿ��� �κ��� ������ �ξ���.
// nameOfParser : ���� ������ ���� ���������� �Ľ��ϴ� �κ�. �� �κ� ���� � ���� ������� �̷�� �������� ���� �Ľ̹���� �ٲ�� ������ �Լ������͸� ����Ͽ���.
// killOfParser : ������ ���� ���� ���� ���� Ȯ���ϴ� �κ�. ���� ���� ����.
// ~~~Position, ~~~Len ���� ��� ��� �Ľ� ���� ����� ���� �ٸ��Ƿ� ������ �ξ� ����Ŭ����(KoreanParser, Chinese ...)�� ���� �ٸ��� ���� �����Ͽ���.
void Parser::readAMove(string giboToken){
	int checkGiboType = giboToken.length() ;
	unitState.name = ConvertNameToEnglish(giboToken.substr(nameStartPosition,nameLen)) ;
	unitState.post = atoi(giboToken.substr(postStartPosition,postLen).c_str()) ;

	switch(checkGiboType - addLen){
	case JUSTMOVE : return ;
	case KILLONLY :
		unitState.kill_unit = ConvertKilleeToEnglish(giboToken.substr(killStartPosition,killLen)) ; return ;
	case JANG :
		unitState.general = true ; return ;
	case KILLANDJANG :
		unitState.kill_unit = ConvertKilleeToEnglish(giboToken.substr(killStartPosition,killLen)) ;
		unitState.general = true ; return ;
	default :
		cerr << "READ MOVE ERROR" << endl ; return ;
	}
}

// �÷��̾��� ���� ���� ��¥ �Ľ��� �ϴ� �κ�.
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

				if(strcmp(token, TAKE_REST)){
					readAMove(giboToken) ;
				}
				else // �Ѽ� ���� ��� ������ �Ľ����� �ʾƵ� �ȴ�.
					unitState.take_rest = true ;				
	
				printHistory() ;
			}
		}
		free(line) ;
	}
}

int Parser::distinctParser(string token){
	static Parser * koreanParser = new KoreanParser() ;
	static Parser * chineseParser = new ChineseParser() ;
	static Parser * chinese2Parser = new Chinese2Parser() ;

	if(koreanParser->ConvertNameToEnglish(token.substr(koreanParser->nameStartPosition, koreanParser->nameLen)) != NOT_METHOD )
		return KOREAN_PARSER ;
	else if (chineseParser->ConvertNameToEnglish(token.substr(chineseParser->nameStartPosition, chineseParser->nameLen)) != NOT_METHOD) 
		return CHINESE_PARSER ;
	else if (chinese2Parser->ConvertNameToEnglish(token.substr(chinese2Parser->nameStartPosition, chinese2Parser->nameLen)) != NOT_METHOD) 
		return CHINESE_2_PARSER ;
	else if ( !token.compare(TAKE_REST))
		return REST_TIME ;
	else {
		return ERROR_PARSER ;
	}
}