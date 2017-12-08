#ifndef _PARSE_H_
#define _PARSE_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <direct.h>
#include "readFile.h"

#define MIN_LENGTH 6
#define KILLONLY 8
#define JANG 10
#define KILLANDJANG 12
#define TOKEN ".]\" ["
#define TAKE_REST "�Ѽ���"
#define FORMAL_GIBO_FORM 11
#define NOT_METHOD 'O'

enum {CHO_PLAY , HAN_PLAY } ;

using namespace std;

// ����

typedef struct _Unit {
	int pre, post ;
	char name, kill_unit ;
	bool general, take_rest ;
} Unit ;


bool IsDigit(char c); // �������� ���θ� Ȯ��
void Parsing();
void Upper2lower_case(char *ch) ;
bool Is_uppercase(char ch) ;
char Korean_to_English(string str) ; // ������ �̸��� �����
char Convert_Chinese_to_English(string str); //
char Convert_Chinese_to_English_one(string str);


#endif
