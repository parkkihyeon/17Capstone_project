#include "readFile.h"

#define FILE_PATH "�Ƹ�����⺸\\"
#define FILE_MAXLEN 256

int start_page = 0 ;

// �Ľ� �ڸ��� ���߱�
char* Fit_Digit(int num_, int cipher)
{
	int original_num_len = to_string(num_).length() ;
	char *Trans_char= new char[MIN] ;
	string Trans_str ;

	// cipher�� ���̸�ŭ ����� ���� �������� 0���� ä���� ��
	for(int i=0 ; i< cipher - original_num_len ;i++)
		Trans_str.push_back('0') ;

	// num_�� �ڿ� ���̸� cipher ���� ��ŭ �����ȴ�.
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

// ������� ���ȴ����� ����.
bool Isbraket(char *str, bool *braket)
{
	if(First_letter(str) == LEFT_BRAKET || *braket == true){
		*braket = true ;
		// ������ �������� �ּ��� �ݴ°����� Ȯ��.
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
		// ������ �����Ѵ�.
		getNextPageName(File_name) ;
		return true ;
	}

	return false ;
}
void vaildCheckGiBO(ifstream &stream, bool &braket_, char *File_name) {
	char sentence[FILE_MAXLEN];
	while (!stream.eof()){		// ������ ���ϵ� 0.txt ���� �����Ѵ�.
		ofstream ostream(File_name);
		int new_line = 0 ;
		while (!stream.eof()){
			stream.getline(sentence, MIN);
			// ������� ������ �ּ��̹Ƿ� �ּ��� �������� �ʰ� �Ѿ��.
			if(Isbraket(sentence, &braket_))
				continue ;
			else {
				// ������ �ι� ����Ǹ� �� ������ �Ľ��� �Ϸ�� ��
				if(NewLine_handling(sentence, &new_line, File_name))
					break ;
				ostream << sentence <<endl ;
			}
		}
		ostream.close() ;
	}
	stream.close() ;
}

void devideDoc(intptr_t hFile, _finddatai64_t c_file, char *fileName) {
	bool braket_ = false ;
	char File_name[FILE_MAXLEN];

	ifstream stream(fileName) ;
	if(stream.fail()) {
		cerr << "oepn failed " << endl ;
		exit(1) ;
	}
	getNextPageName(File_name) ;
	vaildCheckGiBO(stream, braket_, File_name) ;
}

void readFile()
{
	_finddatai64_t c_file;
	intptr_t hFile;

	// �⺸ ������ ��� ����.
	if ( (hFile = _findfirsti64(PATH, &c_file)) == -1L ) {
		switch (errno) {
		case ENOENT: printf(":: ������ ���� ::\n"); exit(1); 
		case EINVAL: printf("Invalid path name.\n"); exit(1); 
		case ENOMEM: printf("Not enough memory or file name too long.\n"); exit(1); 
		default: printf("Unknown error.\n"); exit(1);
		}
	} // �⺸ ������ ���� �� ����.
	else {
		printf("-- ���� ��� --\n");
		do {
			char fileName[FILE_MAXLEN] ;
			strcpy(fileName, FILE_PATH );
			strcat(fileName, c_file.name );
			printf("%s\n", fileName);
			devideDoc(hFile, c_file, fileName) ;
		} while(_findnexti64(hFile, &c_file) == 0);
	}
	_findclose(hFile); // _findfirsti64(), _findnexti64()�� ���� �޸𸮸� ��ȯ
}

void getNextPageName(char *str)
{
	// int to char
	strcpy(str, "") ;
	itoa(start_page,str, DECIMAL) ;
	strcat(str, TEXT_FORM) ;
	start_page++;
}
