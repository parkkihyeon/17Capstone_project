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
#define TAKE_REST "�Ѽ���"

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
void Parser();
void Upper2lower_case(char *ch) ;
bool Is_uppercase(char ch) ;

char Korean_to_English(string str) ; // ������ �̸��� �����
char Convert_Chinese_to_English(string str); //
char Convert_Chinese_to_English_one(string str);

#endif
