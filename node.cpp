#include "node.h"

node::node(State board) {
   host = -1;
   memset(arr, NULL, sizeof(char) * WIDTH_SIZE * HEIGHT_SIZE);

   for(int i = 0; i < HEIGHT_SIZE; i++) {
	   for(int j = 0; j < WIDTH_SIZE; j++) {
		   arr[i][j] = board[i][j];
	   }
   }
   num_of_cho = 0;
   num_of_han = 0;
}

// state의 상태를 출력한다.
void node::Print_State(){
   for(int i=1 ; i< HEIGHT_SIZE; i++){
      for(int j=1 ; j< WIDTH_SIZE ; j++)
         cout << arr[i][j] << " " ;
      cout << endl ;
   }
   cout << endl;
};

State node::returnState(){
	return arr ;
}

void node::getNumOfUnit() {
	for (int i = 1; i < HEIGHT_SIZE; i++) {
		for (int j = 1; j < WIDTH_SIZE; j++) {
			if (65 <= arr[i][j] && arr[i][j] <= 90)
				num_of_han++;
			else if (97 <= arr[i][j] && arr[i][j] <= 122)
				num_of_cho++;
		}
	}
}


void node::changeState(int pos[], char unit) {
  int oldPos1 = pos[0] / 10;
  int oldPos2 = pos[0] % 10;
  int newPos1 = pos[1] / 10;
  int newPos2 = pos[1] % 10;

  if (oldPos1 == 0) {
    oldPos1 = 10;
  }
  if (newPos1 == 0) {
    newPos1 = 10;
  }
  arr[oldPos1][oldPos2] = '-';
  arr[newPos1][newPos2] = unit;
  getNumOfUnit();
}

void node::UnitOrder(int cho_order, int han_order) {
  switch (cho_order) { //초차림
  case 0: //마상마상
    switch (han_order) { //한차림
    case 0: //마상마상
      arr[10][2] = 'h'; arr[10][3] = 'x';
      arr[10][7] = 'h'; arr[10][8] = 'x';
      //arr[1][2] = 'X'; arr[1][3] = 'H';
      //arr[1][7] = 'X'; arr[1][8] = 'H';
	  arr[1][2] = 'H'; arr[1][3] = 'X';
	  arr[1][7] = 'H'; arr[1][8] = 'X';
      break;
    case 1: //마상상마
      arr[10][2] = 'h'; arr[10][3] = 'x';
      arr[10][7] = 'h'; arr[10][8] = 'x';
      //arr[1][2] = 'H'; arr[1][3] = 'X';
      //arr[1][7] = 'X'; arr[1][8] = 'H';
	  arr[1][2] = 'X'; arr[1][3] = 'H';
	  arr[1][7] = 'H'; arr[1][8] = 'X';
      break;
    case 2: //상마마상
      arr[10][2] = 'h'; arr[10][3] = 'x';
      arr[10][7] = 'h'; arr[10][8] = 'x';
      //arr[1][2] = 'X'; arr[1][3] = 'H';
      //arr[1][7] = 'H'; arr[1][8] = 'X';
	  arr[1][2] = 'H'; arr[1][3] = 'X';
	  arr[1][7] = 'X'; arr[1][8] = 'H';
      break;
    case 3: //상마상마
      arr[10][2] = 'h'; arr[10][3] = 'x';
      arr[10][7] = 'h'; arr[10][8] = 'x';
      //arr[1][2] = 'H'; arr[1][3] = 'X';
      //arr[1][7] = 'H'; arr[1][8] = 'X';
	  arr[1][2] = 'X'; arr[1][3] = 'H';
	  arr[1][7] = 'X'; arr[1][8] = 'H';
      break;
    }
    break;
  case 1: //마상상마
    switch (han_order) { //������
    case 0: //�������� && ���󸶻�
      arr[10][2] = 'h'; arr[10][3] = 'x';
      arr[10][7] = 'x'; arr[10][8] = 'h';
      //arr[1][2] = 'X'; arr[1][3] = 'H';
      //arr[1][7] = 'X'; arr[1][8] = 'H';
	  arr[1][2] = 'H'; arr[1][3] = 'X';
	  arr[1][7] = 'H'; arr[1][8] = 'X';
      break;
    case 1: //�������� && ��������
      arr[10][2] = 'h'; arr[10][3] = 'x';
      arr[10][7] = 'x'; arr[10][8] = 'h';
      //arr[1][2] = 'H'; arr[1][3] = 'X';
      //arr[1][7] = 'X'; arr[1][8] = 'H';
	  arr[1][2] = 'X'; arr[1][3] = 'H';
	  arr[1][7] = 'H'; arr[1][8] = 'X';
      break;
    case 2: //�������� && �󸶸���
      arr[10][2] = 'h'; arr[10][3] = 'x';
      arr[10][7] = 'x'; arr[10][8] = 'h';
      //arr[1][2] = 'X'; arr[1][3] = 'H';
      //arr[1][7] = 'H'; arr[1][8] = 'X';
	  arr[1][2] = 'H'; arr[1][3] = 'X';
	  arr[1][7] = 'X'; arr[1][8] = 'H';
      break;
    case 3: //�������� && �󸶻���
      arr[10][2] = 'h'; arr[10][3] = 'x';
      arr[10][7] = 'x'; arr[10][8] = 'h';
      //arr[1][2] = 'H'; arr[1][3] = 'X';
      //arr[1][7] = 'H'; arr[1][8] = 'X';
	  arr[1][2] = 'X'; arr[1][3] = 'H';
	  arr[1][7] = 'X'; arr[1][8] = 'H';
      break;
    }
    break;
  case 2: //상마마상
    switch (han_order) { //������
    case 0: //�󸶸��� && ���󸶻�
      arr[10][2] = 'x'; arr[10][3] = 'h';
      arr[10][7] = 'h'; arr[10][8] = 'x';
      //arr[1][2] = 'X'; arr[1][3] = 'H';
      //arr[1][7] = 'X'; arr[1][8] = 'H';
	  arr[1][2] = 'H'; arr[1][3] = 'X';
	  arr[1][7] = 'H'; arr[1][8] = 'X';
      break;
    case 1: //�󸶸��� && ��������
      arr[10][2] = 'x'; arr[10][3] = 'h';
      arr[10][7] = 'h'; arr[10][8] = 'x';
      //arr[1][2] = 'H'; arr[1][3] = 'X';
      //arr[1][7] = 'X'; arr[1][8] = 'H';
	  arr[1][2] = 'X'; arr[1][3] = 'H';
	  arr[1][7] = 'H'; arr[1][8] = 'X';
      break;
    case 2: //�󸶸��� && �󸶸���
      arr[10][2] = 'x'; arr[10][3] = 'h';
      arr[10][7] = 'h'; arr[10][8] = 'x';
      //arr[1][2] = 'X'; arr[1][3] = 'H';
      //arr[1][7] = 'H'; arr[1][8] = 'X';
	  arr[1][2] = 'H'; arr[1][3] = 'X';
	  arr[1][7] = 'X'; arr[1][8] = 'H';
      break;
    case 3: //�󸶸��� && �󸶻���
      arr[10][2] = 'x'; arr[10][3] = 'h';
      arr[10][7] = 'h'; arr[10][8] = 'x';
      //arr[1][2] = 'H'; arr[1][3] = 'X';
      //arr[1][7] = 'H'; arr[1][8] = 'X';
	  arr[1][2] = 'X'; arr[1][3] = 'H';
	  arr[1][7] = 'X'; arr[1][8] = 'H';
      break;
    }
    break;
  case 3: //상마상마
    switch (han_order) { //������
    case 0: //�󸶻��� && ���󸶻�
      arr[10][2] = 'x'; arr[10][3] = 'h';
      arr[10][7] = 'x'; arr[10][8] = 'h';
      //arr[1][2] = 'X'; arr[1][3] = 'H';
      //arr[1][7] = 'X'; arr[1][8] = 'H';
	  arr[1][2] = 'H'; arr[1][3] = 'X';
	  arr[1][7] = 'H'; arr[1][8] = 'X';
      break;
    case 1: //�󸶻��� && ��������
      arr[10][2] = 'x'; arr[10][3] = 'h';
      arr[10][7] = 'x'; arr[10][8] = 'h';
      //arr[1][2] = 'H'; arr[1][3] = 'X';
      //arr[1][7] = 'X'; arr[1][8] = 'H';
	  arr[1][2] = 'X'; arr[1][3] = 'H';
	  arr[1][7] = 'H'; arr[1][8] = 'X';
      break;
    case 2: //�󸶻��� && �󸶸���
      arr[10][2] = 'x'; arr[10][3] = 'h';
      arr[10][7] = 'x'; arr[10][8] = 'h';
      //arr[1][2] = 'X'; arr[1][3] = 'H';
      //arr[1][7] = 'H'; arr[1][8] = 'X';

	  arr[1][2] = 'H'; arr[1][3] = 'X';
	  arr[1][7] = 'X'; arr[1][8] = 'H';
      break;
    case 3: //�󸶻��� && �󸶻���
      arr[10][2] = 'x'; arr[10][3] = 'h';
      arr[10][7] = 'x'; arr[10][8] = 'h';
      //arr[1][2] = 'H'; arr[1][3] = 'X';
      //arr[1][7] = 'H'; arr[1][8] = 'X';
	  arr[1][2] = 'X'; arr[1][3] = 'H';
	  arr[1][7] = 'X'; arr[1][8] = 'H';
      break;
    }
    break;
  }
}