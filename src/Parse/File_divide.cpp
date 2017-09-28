#include "File_divide.h"

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
		NextPage_Filename(File_name) ;
		return true ;
	}

	return false ;
}

void Devide_Doc(int end_txt, char *original_name, int start_txt, int chiper)
{
	bool braket_ = false ;
	for(int num_for = start_txt ; num_for < end_txt ; num_for++){
		// text �̸� �ֱ�.
		char *name_copy = new char[MIN] ;
		char *File_name = new char[MIN] ;
		char *sentence = new char[MIN];

		// �ۼ��� ���� �̸��� ���Ŀ� �°�.
		strcpy(name_copy, original_name) ;
		strcat(name_copy, Fit_Digit(num_for, chiper)) ;
		strcat(name_copy, TEXT_GIBO) ;
		cout << "\t" << name_copy << endl ;

		// ���� ����
		ifstream stream(name_copy) ;
		if(stream.fail()) {
			cerr << "oepn failed " << endl ;
			break ;
		}
		NextPage_Filename(File_name) ;

		while (!stream.eof())
		{
			// ������ ���ϵ� 0.txt ���� �����Ѵ�.
			ofstream ostream(File_name);
			int new_line = 0 ;
			while (!stream.eof())
			{
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
