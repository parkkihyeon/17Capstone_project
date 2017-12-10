#include "readFile.h"

#define FILE_PATH "gibo\\"
#define FILE_MAXLEN 256

int start_page = 0 ;

// 파싱 자릿수 맞추기
char* Fit_Digit(int num_, int cipher)
{
	int original_num_len = to_string(num_).length() ;
	char *Trans_char= new char[MIN] ;
	string Trans_str ;

	// cipher의 길이만큼 만들기 위해 나머지를 0으로 채워준 후
	for(int i=0 ; i< cipher - original_num_len ;i++)
		Trans_str.push_back('0') ;

	// num_을 뒤에 붙이면 cipher 길이 만큼 고정된다.
	Trans_str.append(to_string(num_)) ;
	strcpy(Trans_char,Trans_str.c_str()) ;

	return Trans_char; 
}

char First_letter(char *str)
{
	return str[0] ;
}

char Last_letter(char *str)
{
	return str[strlen(str)-1] ;
}

// 브라켓이 열렸는지의 여부.
bool Isbraket(char *str, bool *braket)
{
	if(First_letter(str) == LEFT_BRAKET || *braket == true){
		*braket = true ;
		// 문장의 마지막이 주석을 닫는것인지 확인.
		if(Last_letter(str) == RIGHT_BRAKET ){
			*braket = false ;
		}
		return true ;
	}
	return false ;
}

bool NewLine_handling(char *str, int *num_line, char* File_name)
{
	if (First_letter(str) == NULL) 
		(*num_line)++ ;
	if(*num_line == 2 ){
		// 파일을 저장한다.
		getNextPageName(File_name) ;
		return true ;
	}

	return false ;
}
void vaildCheckGiBO(ifstream &stream, bool &braket_, char *File_name) {
	char sentence[FILE_MAXLEN];
	while (!stream.eof()){		// 저장할 파일들 0.txt 부터 시작한다.
		ofstream ostream(File_name);
		int new_line = 0 ;
		while (!stream.eof()){
			stream.getline(sentence, MIN);
			// 브라켓이 열리면 주석이므로 주석은 저장하지 않고 넘어간다.
			if(Isbraket(sentence, &braket_))
				continue ;
			else {
				// 개행이 두번 진행되면 한 게임이 파싱이 완료된 것
				if(NewLine_handling(sentence, &new_line, File_name))
					break ;
				ostream << sentence <<endl ;
			}
		}
		ostream.close() ;
	}
	stream.close() ;
}

int devideDoc(intptr_t hFile, _finddatai64_t c_file, char *fileName) {
	bool braket_ = false ;
	char File_name[FILE_MAXLEN];

	ifstream stream(fileName) ;
	if(stream.fail()) {
		cerr << "oepn failed " << endl ;
		return GIBO_OPEN_ERROR ;
	}
	getNextPageName(File_name) ;
	vaildCheckGiBO(stream, braket_, File_name) ;
	return GIBO_OPEN_SUCCESS ;
}

void readFile()
{
	_finddatai64_t c_file;
	intptr_t hFile;
	cout << PATH << endl ;
	// 기보 파일을 모두 읽음.
	if ( (hFile = _findfirsti64(PATH, &c_file)) == -1L ) {
		switch (errno) {
		case ENOENT: printf(":: 파일이 없음 ::\n"); exit(1); 
		case EINVAL: printf("Invalid path name.\n"); exit(1); 
		case ENOMEM: printf("Not enough memory or file name too long.\n"); exit(1); 
		default: printf("Unknown error.\n"); exit(1);
		}
	} // 기보 파일을 읽은 후 분할.
	else {
		printf("-- 파일 목록 --\n");
		do {
			cout << c_file.name << endl ;
			char fileName[FILE_MAXLEN] ;
			strcpy(fileName, FILE_PATH );
			strcat(fileName, c_file.name );
			printf("%s\n", fileName);
			if(devideDoc(hFile, c_file, fileName) == GIBO_OPEN_ERROR) return ;
		} while(_findnexti64(hFile, &c_file) == 0);
	}
	_findclose(hFile); // _findfirsti64(), _findnexti64()에 사용된 메모리를 반환
}

void getNextPageName(char *str)
{
	// int to char
	strcpy(str, "") ;
	itoa(start_page,str, DECIMAL) ;
	strcat(str, TEXT_FORM) ;
	start_page++;
}
