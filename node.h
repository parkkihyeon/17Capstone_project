#ifndef __NODE__
#define __NODE__

#include <iostream>
#include <vector>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11

using namespace std ;

typedef char (*State)[WIDTH_SIZE] ;

class node
{
public:
   int host;
   char arr[HEIGHT_SIZE][WIDTH_SIZE] ;
   node(State board);

   // state의 상태를 출력한다.
   void Print_State();

   // state의 판을 반환
   State returnState();

   // state의 상태를 초기화한다.
   void UnitOrder(int cho_order, int han_order);

   // state의 상태를 변경한다.
   void changeState(int pos[], char unit);
};

#endif
