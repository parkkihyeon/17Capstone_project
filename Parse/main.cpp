/*

	capstone_project 
	20123361 ¹Ú±âÇö

    output :    ÃÊÂ÷¸² ÇÑÂ÷¸² ½Â¸® È÷½ºÅä¸®
    history :   ÀüÀ§Ä¡ ÈÄÀ§Ä¡ ÇöÀçµ¹ ¸ÔÀºµ¹ Àå±º¿©ºÎ
    name :      Á¹,º´ J    Â÷ C    ¸¶ H    »ó X
                Æ÷ P      Àå K    »ç S
                õ¢ğï ùÓÜ² ÂÌ  õ¢Ø© ùÓØ© ¸¶ õ¢øĞ ùÓøĞ Æ÷  õ¢ó³ ùÓó³ Â÷
                õ¢ßÚ ùÓßÚ »ó  õ¢ŞÍ ùÓŞÍ »ç õ¢íâ ùÓíâ ¿Õ     */

#include "File_divide.h"
#include "parse.h"

int main()
{
	char file_name[100] ;
	int num, start_txt , chiper ;
	cout << "\n\tÆÄÀÏ ÀÌ¸§À» ¾²¼¼¿ä :" ;
	cin>> file_name  ;

	cout << "\tÆÄÀÏÀÇ °¹¼ö¸¦ ¾²¼¼¿ä :" ;
	cin >> num ;
		
	cout << "\tÆÄÀÏÀÇ ½ÃÀÛ ¼ıÀÚ¸¦ ¾²¼¼¿ä :" ;
	cin >> start_txt ;

	cout << "\tÆÄÀÏÀÇ ÀÚ¸´¼ö¸¦ ¾²¼¼¿ä :" ;
	cin >> chiper ;
	
	Devide_Doc(num+start_txt, file_name, start_txt, chiper);
    Parser();
    return 0;
}

