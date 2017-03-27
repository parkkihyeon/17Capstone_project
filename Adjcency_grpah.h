#ifndef __ADJCENCY__GRAPH__  
#define __ADJCENCY__GRAPH__  

#include "Statenode.h"
#include <iostream>
#include <vector>
#include <stack>
#include <map>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11
#define NUMUNIT 17

using namespace std ;

class Adjcency_grpah
{
private :
	State_node *root ;
	State_node *leaf ;
	vector<State_node*>* hashstate_list[NUMUNIT][NUMUNIT] ;
//	vector<State_node*> node_list ;
	stack<State_node *> state_stack ;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		ar & *root;
		ar & *node_list;
		//ar & state_stack;
		ar & *leaf;
	}
public:
	Adjcency_grpah();
	Adjcency_grpah(Adjcency_grpah &graph);
	Adjcency_grpah(Adjcency_grpah *graph);

	void Init_hashtable();
	void Insert(vector<State_node*> state);
	void Backtracking_stack() ;
	void PushList_Hashtable(State_node* state) ;

	State_node* getRoot();
	State_node* getLeaf();

	// 현재 위치한 노드에서의 자식노드와 추가할 state와 같은게 있는지.
	int Is_Have_childnode(State_node* sub_root, State_node* state);
	// 현재 위치한 노드에서 어떤 부모노드에서 왔는지 비교함.
	int Direction_parentnode(State_node* sub_node);

	// 현재 노드 state가 그래프로 존재하고 있는지
	State_node* Is_In_The_List_State(State_node *state);

	// 두 state가 같은지 다른지 확인하는 함수.
	bool Diff_State(State_node *stateA, State_node *stateB);
};

#endif