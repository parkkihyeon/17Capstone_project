#ifndef __STATE__NODE__  
#define __STATE__NODE__  

#include <iostream>
#include <vector>

#include <boost/archive/binary_iarchive.hpp> // 바이너리 형태로 입력하기 위해
#include <boost/archive/binary_oarchive.hpp> // 바이너리 형태로 출력하기 위해
#include <boost/serialization/vector.hpp> // 직렬화 vector를 사용하기 위해

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11

using namespace std ;

class State_node
{
private:
	friend class boost::serialization::access;
	template <typename AR>
	void serialize(AR &ar, const unsigned int ver) {
		ar & num_of_prev;
		ar & num_of_next;
		ar & state_ordernum;
		ar & *next;
		ar & *prev;
		ar & arr;
	}
public:
	int num_of_prev ; // 상위 노드의 갯수 
	int num_of_next ;  // 하위 노드의 갯수
	int state_ordernum ; 
	vector<State_node*> *next ; 
	vector<State_node*> *prev ; 

	char arr[HEIGHT_SIZE][WIDTH_SIZE] ;

	State_node(char data[HEIGHT_SIZE][WIDTH_SIZE]) ;
	State_node();

	// state의 상태를 출력한다.
	void Print_State();

	//node의 자식을 생성.
	void Addlist_Child(State_node *add_state);
	void Connect_Parent(State_node *parent_state) ;

	// n번째 자식을 return
	State_node* NthCheck_Childnode(int n);
	State_node* NthCheck_Parentnode(int n);
};

#endif