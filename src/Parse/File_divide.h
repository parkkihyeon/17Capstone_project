// ���� ����
#ifndef _FILE_DIVIDE_H_
#define _FILE_DIVIDE_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>

#define TEXT_FORM ".txt"
#define TEXT_GIBO ".gib"
#define DECIMAL 10
#define MIN 200
#define LEFT_BRAKET '{'
#define RIGHT_BRAKET '}'

using namespace std;

void Devide_Doc(int end_txt, char *name, int start_txt, int chiper) ; // document�� ������ ���� �Լ�
void NextPage_Filename(char *str) ; // Devide_Doc�Լ����� �����̸� �ٲܶ�.
char* Fit_Digit(int num_, int cipher) ;
char First_letter(char *str) ;
char Last_letter(char *str) ;
bool Isbraket(char *str, bool *braket) ;
bool NewLine_handling(char *str, int *num_line, char* File_name) ;

#endif
