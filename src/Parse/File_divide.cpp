#include "File_divide.h"

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
		NextPage_Filename(File_name) ;
		return true ;
	}

	return false ;
}

void Devide_Doc(int end_txt, char *original_name, int start_txt, int chiper)
{
	bool braket_ = false ;
	for(int num_for = start_txt ; num_for < end_txt ; num_for++){
		// text 이름 넣기.
		char *name_copy = new char[MIN] ;
		char *File_name = new char[MIN] ;
		char *sentence = new char[MIN];

		// 작성한 파일 이름을 형식에 맞게.
		strcpy(name_copy, original_name) ;
		strcat(name_copy, Fit_Digit(num_for, chiper)) ;
		strcat(name_copy, TEXT_GIBO) ;
		cout << "\t" << name_copy << endl ;

		// 읽을 파일
		ifstream stream(name_copy) ;
		if(stream.fail()) {
			cerr << "oepn failed " << endl ;
			break ;
		}
		NextPage_Filename(File_name) ;

		while (!stream.eof())
		{
			// 저장할 파일들 0.txt 부터 시작한다.
			ofstream ostream(File_name);
			int new_line = 0 ;
			while (!stream.eof())
			{
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
		delete(File_name) ;
		delete(sentence) ;
		delete(name_copy) ;
	}
}

void NextPage_Filename(char *str)
{
	// int to char
	strcpy(str, "") ;
	itoa(start_page,str, DECIMAL) ;
	strcat(str, TEXT_FORM) ;
	start_page++;
}
