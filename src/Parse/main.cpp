/*

	capstone_project 
	20123361 �ڱ���

    output :    ������ ������ �¸� �����丮
    history :   ����ġ ����ġ ���絹 ������ �屺����
    name :      ��,�� J    �� C    �� H    �� X
                �� P      �� K    �� S
                ���� ��ܲ ��  ��ة ��ة �� ���� ���� ��  ��� ��� ��
                ���� ���� ��  ���� ���� �� ���� ���� ��     */

#include "File_divide.h"
#include "parse.h"

int main()
{
	char file_name[100] ;
	int num, start_txt , chiper ;
	cout << "\n\t���� �̸��� ������ :" ;
	cin>> file_name  ;

	cout << "\t������ ������ ������ :" ;
	cin >> num ;
		
	cout << "\t������ ���� ���ڸ� ������ :" ;
	cin >> start_txt ;

	cout << "\t������ �ڸ����� ������ :" ;
	cin >> chiper ;
	
	Devide_Doc(num+start_txt, file_name, start_txt, chiper);
    Parser();
    return 0;
}

