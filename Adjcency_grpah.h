#ifndef __ADJCENCY__GRAPH__  
#define __ADJCENCY__GRAPH__  

#include "Statenode.h"
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <fstream>
#include <cstring>
#include <string>
#include <string.h>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11
#define NUMUNIT 17
#define ERROR_CODE 8
#define REST_PIECE '0'
#define FIRST_PIECE '0'
#define DRAW -1
#define MOVABLE_KEY 7

using namespace std;

typedef pair<Cha_pos, Pho_pos> pair_key;
typedef multimap<pair_key, State_node*> hash_4d; // 4���� �ؽ�
typedef multimap<string, State_node*> movableHash;

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
//		ar & BOOST_SERIALIZATION_NVP(leaf);
		ar & BOOST_SERIALIZATION_NVP(statenode_num);
		ar & BOOST_SERIALIZATION_NVP(hashstate_list);
	}
public:
	Adjcency_grpah();
	Adjcency_grpah(const Adjcency_grpah &graph);
	Adjcency_grpah(Adjcency_grpah *graph);

	void MovableHashInit();
	int convertKeyhash(int key, int key_index);
	string getMovableKey(State_node* now_state);
	void insertMovableHash(State_node* now_state);

	void Init_hashtable();
	void Insert(vector<State_node*>* state);
	void Second_insert(vector<State_node*>* state);
	void PushList_Hashtable(State_node* state);
	void Set_4Dhashdata(int &cha_y, int &cha_x, int &pho_y, int &pho_x, State_node* state);
	void Travelgraph_bfs();
	//void AddMoveable();
	//void AddMoveableChild(State_node *now_state);

	const bool operator== (Adjcency_grpah *graph) ;

	State_node* getRoot();
	State_node* getLeaf();

	// ���� ��ġ�� ��忡���� �ڽĳ��� �߰��� state�� ������ �ִ���.
	int Is_Have_childnode(State_node* sub_root, State_node* state);
	// ���� ��ġ�� ��忡�� � �θ��忡�� �Դ��� ����.
	int Direction_parentnode(State_node* sub_node);

	// ���� ��� state�� �׷����� �����ϰ� �ִ���
	State_node* Is_In_The_List_State(State_node *state);

	// �� state�� ������ �ٸ��� Ȯ���ϴ� �Լ�.
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