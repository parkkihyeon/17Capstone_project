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

int main()
{
	readFile();
	/*
	ParserFactory *pf = new SuperParserFactory() ;
	Parser *p = pf->createParser(1) ;*/
	Parser *p = new KoreanParser() ;

    return 0;
}

