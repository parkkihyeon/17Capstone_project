/*

	capstone_project 
	20123361 �ڱ���

    output :    ������ ������ �¸� �����丮
    history :   ����ġ ����ġ ���絹 ������ �屺����
    name :      ��,�� J    �� C    �� H    �� X
                �� P      �� K    �� S
                ���� ��ܲ ��  ��ة ��ة �� ���� ���� ��  ��� ��� ��
                ���� ���� ��  ���� ���� �� ���� ���� ��     */

#include "readFile.h"
#include "parse.h"
#include "factoryPattern.h"

int main()
{
	//readFile();
	Parser *p = new tempParser() ;
	p->startParsing() ;

    return 0;
}

