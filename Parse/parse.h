#ifndef _PARSE_H_
#define _PARSE_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#define MIN_LENGTH 6
#define KILLONLY 8
#define JANG 10
#define KILLANDJANG 12
#define TOKEN ".]\" ["
#define TAKE_REST "한수쉼"

using namespace std;

// 유닛
class Unit
{
private:
    int pre, post ; // 전위치와 후위치
    char name, kill_unit ; // 말의 이름과 말의 움직임에 따라 죽인 유닛이 있으면 명시
    bool general, take_rest ; // 장군의 여부와 한숨쉼의 여부

public:
    void Printing() ;
    Unit(char *str); // 생성자에서 수에대해 변수를 모두 선언해줌.

};

bool IsDigit(char *str); // 숫자인지 여부를 확인
void Parser();
void Upper2lower_case(char *ch) ;
bool Is_uppercase(char ch) ;

char Korean_to_English(string str) ; // 유닛의 이름을 영어로
char Convert_Chinese_to_English(string str); //
char Convert_Chinese_to_English_one(string str);

#endif
