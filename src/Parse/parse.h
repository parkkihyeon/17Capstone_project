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

enum {CHO_PLAY , HAN_PLAY } ;

using namespace std;

// ����

class Unit
{
private:
    int pre, post ; // ����ġ�� ����ġ
    char name, kill_unit ; // ���� �̸��� ���� �����ӿ� ���� ���� ������ ������ ���
    bool general, take_rest ; // �屺�� ���ο� �Ѽ����� ����

public:
    void Printing() ;
    Unit(char *str); // �����ڿ��� �������� ������ ��� ��������.

};

bool IsDigit(char *str); // �������� ���θ� Ȯ��
void Parsing();
void Upper2lower_case(char *ch) ;
bool Is_uppercase(char ch) ;

char Korean_to_English(string str) ; // ������ �̸��� �����
char Convert_Chinese_to_English(string str); //
char Convert_Chinese_to_English_one(string str);



class Parser
{
public:
	Parser() ;
	virtual void doing() = 0 ;
	int getNextTextFile(int &sp) ;
	bool writePosition() ;
	bool checkGibo() ;
	void writeResult() ;
	void initAllString() ;
	void writeHistory();

private:
	ofstream ostream ;
	ifstream stream ;
	string allString[_MAX_PATH] ;
	int numOfRow ;
};
 
class KoreanParser : public Parser {
public:
	virtual void doing() ;
};

class Chinese : public Parser {
public:
	virtual void doing() ;
};

class Chinese2 : public Parser {
public:
	virtual void doing();
};


////////////////////////////////////////////////////////////////////////////////////////////////////////

class ParserFactory {
public :
	ParserFactory() ;
	Parser* createParser(int name) ;
protected:
	virtual Parser* FactoryMethod(int name) = 0 ;
};

class SuperParserFactory : public ParserFactory{
public:
	SuperParserFactory() ;
	Parser* FactoryMethod(int name) ;

};

#endif
