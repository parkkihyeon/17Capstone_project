#include "factoryPattern.h"

char* Parser::HorseSequence[NUM_OF_SANGCHALIM_POSITION] = { "마상마상", "마상상마", "상마마상", "상마상마" }; 
char* Parser::Chinese_character[NUM_OF_CHINESE2_POSITION] = {"楚卒", "漢兵", "楚馬", "漢馬", "楚包","漢包", "楚車", "漢車", "楚象","漢象", "楚士", "漢士", "楚將", "漢將"} ;
char* Parser::Chinese_character_one[NUM_OF_CHINESE_POSITION] = {"卒", "兵", "馬", "包", "車", "象", "士", "將" } ;
char* Parser::Korean_character[NUM_OF_KOREAN_POSITION] ={ "졸", "병", "마", "포","차", "상", "사","장"} ;
char Parser::to_English[NUM_OF_UNIT] = {'J', 'H','P', 'C', 'X', 'S', 'K'} ;

int sequence_num = 0 ;
ofstream outputStream ;
ifstream inputStream ;

void Parser::printHistory()
{
	if(sequence_num%2==0) {
		Upper2lower_case(&unitState.name) ; // 아스키 코드값. 대문자를 소문자로!
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

// 다음 open할 텍스트 파일을 open한다. 만약 다음 텍스트 파일이 없으면 강제 종료된다.
int Parser::getNextTextFile(int &sp){
	// 파일은 순서대로 0.txt ~ n-1.txt파일 까지 있다.
	char numOfData[_MAX_PATH] ;
	strcpy(numOfData, "");
	itoa(sp++,numOfData, DECIMAL) ;
	strcat(numOfData, TEXT_FORM) ;
	if(sp % 100 == 0 ) cout << "순번 : " << sp << endl ;
	inputStream.open(numOfData) ;
	if(inputStream.fail()) {
		cerr << "open filed " << endl ;
		exit(1) ;
	}
	outputStream << numOfData << endl ;
	return GIBO_OPEN_SUCCESS ;
}

// 경기 결과를 파일에 쓰는 작업.
void Parser::writeResult(){
	char line[MIN];
	for(int i=0 ; i < numOfRow ; i++){
		strcpy(line, allString[i].c_str()) ;
		if(strstr(line, "결과")){
			if(strstr(line, "초") || strstr(line,  "漢"))
				outputStream << CHO_PLAY << endl ;
			else if (strstr(line, "한") || strstr(line, "楚"))
				outputStream << HAN_PLAY << endl ;
			else
				outputStream << -1 << endl ;
		}
	}
}

// 초차림 상차림을 파일에 쓰는 함수.
bool Parser::writePosition(){
	int isPosition = 0 ;
	char line[MIN];

	for(int i=0 ; i < numOfRow ; i++){
		strcpy(line, allString[i].c_str()) ;

		if(strstr(line, "차림")){
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

// 현재 담고 있는 기보를 초기화 한다.
void Parser::initAllString() {
	for(int i=0; i< numOfRow; i++){
		allString[i] = "" ;
	}
	parsingStartNumber = 0 ;
}

// 기보의 형식을 본다. 기본적으로 있어야 할 상차림과, 대국 결과(승 무승부), 그리고 올바른 형식인지 체크해주는 함수이다.
bool Parser::checkGibo(){
	char temp[MIN] ;
	numOfRow = 0 ;
	int leftBraket = 0 ;

	bool check1 = false  ;
	bool check2 = false ;

	while(!inputStream.eof()){
		inputStream.getline(temp, MIN) ;
		if( !strcmp(temp, "")) continue ;

		if(strstr(temp,"차림")) check1 = true ;
		if(strstr(temp,"결과")) check2 = true ;
		allString[numOfRow++] = temp ;
		if(temp[0] == '[') leftBraket++ ;

	}
	inputStream.close() ;

	if(check1 && check2 && leftBraket == CORRECT_NUM_OF_LEFTBRAKET) return true  ;
	else return false ;
}

// 상차림과 대국결과를 write한 후, 나머지 게임 히스토리를 파일에 저장하기 위한 함수이다.
void Parser::writeHistory(){
	char line[MIN];
	for(int i=0 ; i < numOfRow ; i++){
		strcpy(line, allString[i].c_str()) ;
		if(!strcmp(line,"")) continue ;
		// 어떤 종류의 파서를 결정할 수 있을지에 대한 당락을 여기서 결정한다.
		if(IsDigit(line[0])){
			parsingStartNumber = i ;

			// 이 때, 중간에 팩토리가 등장하는 이유는, 기보 중간에 어떠한 종류에 기보인지 확인할 수 있기 때문이다.
			// 따라서, 일반적인 팩토리 패턴과 다르게 미리 어떤 파서를 사용할 지 알 수 없다.
			// 중간 해석 결과 그 결과를 바탕으로 어떤 파서를 만들지 팩토리에서 생성한다.
			ParserFactory *pf = new SuperParserFactory() ;
			Parser *p = pf->createParser(line, this) ;
			if(p == NULL) return ;

			// 기존 파서에서 사용되었던 필요한 변수를 전달하고
			p->initVariable(numOfRow, parsingStartNumber, allString) ;

			// 진짜 파싱을 돌입한다.
			p->parsingHistory() ;
			free(p) ;

			break ;
		}
	}
}

// 파싱을 3단계로 나뉘어서 시작한다.
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

// 각 파서마다 다른 방법의 파싱 방법이 필요하다. 부모클래스는 모두 0과 NULL로 초기화 한다.
Parser::Parser() {
	nameStartPosition = nameLen = INIT_TO_ZERO ;
	postStartPosition = postLen = INIT_TO_ZERO ;
	killStartPosition = killLen = INIT_TO_ZERO ;
	addLen = 0 ;
}

// 플레이어 한 수 에대한 정보를 초기화 한다.
void Parser::initUnitState(){
	unitState.pre = 0 ;
	unitState.post = 0 ;
	unitState.general = false ;
	unitState.take_rest = false ;
	unitState.kill_unit = '0' ;
	unitState.name = '0' ;
}

// 팩토리 패턴에 의해 새로 생긴 파서에 기존에 필요한 변수의 내용을 전달한다.
void Parser::initVariable(int nRow, int startN, string all[_MAX_PATH]){

	this->numOfRow = nRow ;
	this->parsingStartNumber = startN ;
	for(int i=0; i<nRow ; i++)
		allString[i] = all[i] ;
}

// 현재 플레이어의 수에 대한 정보를 unitState에 저장하는 함수.
// 종류는 단지 움직임, 상대방 유닛을 죽인 경우, 장군인 경우, 상대방 유닛을 죽이면서 장군인 경우에 따라 나누었다.
// 이 때, 기보가 한국어인지 중국어인지, 혹은 다른 방법의 파서인지에 따라 파싱 방법이 나누기 위해
// 변화가 필요한 부분을 변수로 두었다.
// nameOfParser : 현재 움직인 말이 무엇인지를 파싱하는 부분. 이 부분 또한 어떤 언어와 방식으로 이루어 졌는지에 따라 파싱방법이 바뀌기 때문에 함수포인터를 사용하였다.
// killOfParser : 움직인 말을 통해 죽은 말을 확인하는 부분. 위와 같은 설명.
// ~~~Position, ~~~Len 같은 경우 모두 파싱 언어와 방법에 따라 다르므로 변수로 두어 하위클래스(KoreanParser, Chinese ...)에 따라 다르게 값을 설정하였다.
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

// 플레이어의 수에 대한 진짜 파싱을 하는 부분.
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
				else // 한수 쉼인 경우 정보를 파싱하지 않아도 된다.
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