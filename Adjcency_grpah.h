#ifndef __ADJCENCY__GRAPH__  
#define __ADJCENCY__GRAPH__  

#include "Statenode.h"
#include <iostream>
#include <vector>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11

using namespace std ;

class Adjcency_grpah
{
private :
	State_node *root ;
	vector<State_node*> *node_list ;

public:
	Adjcency_grpah();

	void Insert(vector<State_node*> state);

	State_node* getRoot();

	// 현재 위치한 노드에서의 자식노드와 추가할 state와 같은게 있는지.
	int Is_Have_childnode(State_node* sub_root, State_node* state);

	// 현재 노드 state가 그래프로 존재하고 있는지
	State_node* Is_In_The_List_State(State_node *state);

	// 두 state가 같은지 다른지 확인하는 함수.
	bool Diff_State(State_node *stateA, State_node *stateB);
};

#endif