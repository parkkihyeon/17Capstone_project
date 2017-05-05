#ifndef __ADJCENCY__GRAPH__  
#define __ADJCENCY__GRAPH__  

#include "Statenode.h"
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <fstream>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11
#define NUMUNIT 17
#define ERROR_CODE 8
#define REST_PIECE '0'
#define FIRST_PIECE '0'
#define DRAW -1

using namespace std;

typedef pair<Cha_pos, Pho_pos> pair_key;
typedef multimap<pair_key, State_node*> hash_4d; // 4차원 해쉬

enum {CHO_PLAY, HAN_PLAY};

class Adjcency_grpah
{
private:
	State_node *root;
	State_node *leaf;
	hash_4d* hashstate_list[NUMUNIT][NUMUNIT];
	stack<State_node *> state_stack;
	int statenode_num;
	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		ar & BOOST_SERIALIZATION_NVP(root);
		ar & BOOST_SERIALIZATION_NVP(leaf);
		ar & BOOST_SERIALIZATION_NVP(statenode_num);
		ar & BOOST_SERIALIZATION_NVP(hashstate_list);
	}
public:
	Adjcency_grpah();
	Adjcency_grpah(Adjcency_grpah &graph);
	Adjcency_grpah(Adjcency_grpah *graph);

	void Init_hashtable();
	void Insert(vector<State_node*>* state);
	void Second_insert(vector<State_node*>* state);
	void PushList_Hashtable(State_node* state);
	void Set_4Dhashdata(int &cha_y, int &cha_x, int &pho_y, int &pho_x, State_node* state);
	void Travelgraph_bfs();
	void AddMoveable();
	void AddMoveableChild(State_node *now_state);

	const bool operator== (Adjcency_grpah *graph) ;

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

class Second_Graph {
private:
	Adjcency_grpah *original_g;
public:
	Second_Graph(Adjcency_grpah *g);
	void Value_process(vector<State_node*>* state, int winner);
	int idxOfPiece(char piece);

	Adjcency_grpah * Getgraph();
	State_node* GetPrev_state(vector<State_node*>* state, int index);
	State_node* GetNext_state(vector<State_node*>* state, int index);
};


#endif