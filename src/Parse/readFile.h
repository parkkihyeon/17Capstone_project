// ���� ����
#ifndef _READ_FILE_H_
#define _READ_FILE_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <io.h>

#define TEXT_FORM ".txt"
#define TEXT_GIBO ".gib"
#define DECIMAL 10
#define MIN 200
#define LEFT_BRAKET '{'
#define RIGHT_BRAKET '}'
#define PATH "C:\\Users\\park\\Documents\\17Capstone_project\\Parse\\�Ƹ�����⺸\\*.gib"

using namespace std;

void getNextPageName(char *str) ; // Devide_Doc�Լ����� �����̸� �ٲܶ�.
char* Fit_Digit(int num_, int cipher) ;
char First_letter(char *str) ;
char Last_letter(char *str) ;
bool Isbraket(char *str, bool *braket) ;
bool NewLine_handling(char *str, int *num_line, char* File_name) ;
void readFile() ; // document�� ������ ���� �Լ�
void devideDoc(intptr_t hFile, _finddatai64_t c_file, char *fileName) ;
void vaildCheckGiBO(ifstream &stream, bool &braket_, char *File_name) ;

#endif
