#ifndef _PARSE_H_
#define _PARSE_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <direct.h>
#include "readFile.h"

#define JUSTMOVE 6
#define MIN_LENGTH 6
#define KILLONLY 8
#define JANG 10
#define KILLANDJANG 12
#define TOKEN ".]\" ["
#define TAKE_REST "한수쉼"
#define FORMAL_GIBO_FORM 11
#define NOT_METHOD 'O'

enum {CHO_PLAY , HAN_PLAY } ;

using namespace std;

// 현 시점 플레이어의 한 수에 대한 정보를 담아 놓은 것이다.
// pre는 전 위치, post는 후 위치,
// name은 말의 종류, kill_unit은 죽인 말
// general은 장군 여부, take_rest는 한수 쉼의 여부이다.
typedef struct _Unit {
	int pre, post ;
	char name, kill_unit ;
	bool general, take_rest ;
} Unit ;


bool IsDigit(char c); // 숫자인지 여부를 확인
void Parsing();
void Upper2lower_case(char *ch) ;
bool Is_uppercase(char ch) ;
char Korean_to_English(string str) ; // 유닛의 이름을 영어로
char Convert_Chinese_to_English(string str); //
char Convert_Chinese_to_English_one(string str);


#endif
