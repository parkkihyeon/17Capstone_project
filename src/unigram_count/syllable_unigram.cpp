#include"syllable_unigram.h"

int freq[ASCII_NUM] = { 0 };  // �ƽ�Ű ���� ������
int hfreq[HANGUL_HEIGHT][HANGUL_WIDTH]; // �ѱ� ������

void Ascii_frequency(int ch, int freq[])
{
	if(ch < 128 )
		freq[ch]++ ;
}

void Hangul_frequency(int c1, int c2, int hfreq[HANGUL_HEIGHT][HANGUL_WIDTH])
{
	if (c1 >= 0xB0 && c1 <= 0xC8 && c2 >= 0xA1 && c2 <= 0xFE) // �ѱ� ������
		hfreq[c1-0xB0][c2-0xA1]++;
}

boolean Ishangul(char c1){
	if(c1 & 0x80) 
		return true ;
	else return false ;
}

void Frequency_research(){
	int c1, c2;
	FILE * fp_input = fopen("input.txt", "r");

	while (!feof(fp_input)) {
		c1 = fgetc(fp_input) ;
		if (Ishangul(c1)) {
			c2 = fgetc(fp_input) ;
			Hangul_frequency(c1,c2,hfreq) ;
		}
		Ascii_frequency(c1, freq) ;
		

	}
	fclose(fp_input) ;
}

void Syllable_onesearch()
{	
	int c1, c2 ;
	fflush(stdin) ;
	printf("\t���ϴ� �ѱ��ڸ� �Է� : ") ;
	c1 = getchar() ;
	if (c1 & 0x80) 
		c2 = getchar() ;
	fflush(stdin) ;
	if (c1 >= 0xB0 && c1 <= 0xC8 && c2 >= 0xA1 && c2 <= 0xFE)
		printf("\tf[%c%c] = %d\n", c1, c2, hfreq[c1-0xB0][c2-0xA1]);
	else if ( c1 <= 127 )
		printf("\tf[%c] = %d\n", c1, freq[c1]) ;
	printf("*********** Search�� ��ó�� �Ǿ�� �մϴ�. ************\n") ;
	
}


void Syllable_unigram() {
	int i, j ;
	printf("\t���� �Ѱ�\n") ;

	for(int i = 0 ; i < 128 ; i++ ){
		if(freq[i]){
			if( i == char('\n')){
				printf("\tf[\\n] = %d\n", i, freq[i]) ;
			}
			else
				printf("\tf[%c] = %d\n", i, freq[i]) ;
		}
	}

	for (i=0xB0; i <= 0xC8; i++) { // �ѱ� ������
		for (j=0xA1; j <= 0xFE; j++) {
			if (hfreq[i-0xB0][j-0xA1]){
				printf("\tf[%c%c] = %d\n", i, j, hfreq[i-0xB0][j-0xA1]);
			}
		}
	}
}
