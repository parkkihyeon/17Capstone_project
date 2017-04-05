#ifndef __STATE__NODE__  
#define __STATE__NODE__  

#include <iostream>
#include <vector>

#include <boost/serialization/serialization.hpp>
//#include <boost/archive/binary_iarchive.hpp> // 바이너리 형태로 입력하기 위해
//#include <boost/archive/binary_oarchive.hpp> // 바이너리 형태로 출력하기 위해
#include <boost/serialization/vector.hpp> // 직렬화 vector를 사용하기 위해
#include <boost/serialization/deque.hpp> // 직렬화 stack을 사용하기 위해
#include <boost/serialization/stack.hpp> // 직렬화 stack을 사용하기 위해
#include <boost/serialization/map.hpp>
#include <boost/serialization/utility.hpp>

#include <boost/archive/text_iarchive.hpp> // 텍스트 형태로 입력하기 위해
#include <boost/archive/text_oarchive.hpp> // 텍스트 형태로 출력하기 위해

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/exception/all.hpp>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11

using namespace std ;

class State_node
{
private:
	int num_of_prev;
	int num_of_next;
	int state_ordernum;
	int unit_of_han;
	int unit_of_cho;
	int sequence_node ;
	vector<State_node*>* next;
	vector<State_node*>* prev;
	pair<int, int> sum_of_horsepos;
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		/*ar & BOOST_SERIALIZATION_NVP(num_of_prev);
		ar & BOOST_SERIALIZATION_NVP(num_of_next);
		ar & BOOST_SERIALIZATION_NVP(state_ordernum);
		ar & BOOST_SERIALIZATION_NVP(unit_of_cho);
		ar & BOOST_SERIALIZATION_NVP(unit_of_han);
		ar & BOOST_SERIALIZATION_NVP(arr);
		ar & BOOST_SERIALIZATION_NVP(sum_of_horsepos);
		ar & BOOST_SERIALIZATION_NVP(next);
		ar & BOOST_SERIALIZATION_NVP(prev);*/
	}
public:
	char arr[HEIGHT_SIZE][WIDTH_SIZE] ;

	State_node(char data[HEIGHT_SIZE][WIDTH_SIZE]) ;
	State_node();

	// state의 상태를 출력한다.
	void Print_State();

	//node의 자식을 생성.
	void Addlist_Child(State_node *add_state);
	void Connect_Parent(State_node *parent_state) ;
	void Set_numUnit(int cho, int han) ;
	void Set_Stateorder(int data);
	void SetHorse_position(pair<int, int> s);
	void Set_sequence_node(int data);

	// n번째 자식을 return
	State_node* NthCheck_Childnode(int n);
	State_node* NthCheck_Parentnode(int n);
	
	int Getnumprev();
	int Getnumnext();
	int Getstate_ordernum();
	int Gethan();
	int Getcho();
	int Getsequence_node();
	vector<State_node*> *Getnext();
	vector<State_node*> *Getprev();
	pair<int, int> GetHorse_pos();
};

#endif