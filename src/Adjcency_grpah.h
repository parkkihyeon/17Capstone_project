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

#define RESTER_EVAL 0.001
#define MOVING_EVAL 0.0001
#define KILLER_EVAL 0.01
#define KILLEE_EVAL -0.01
#define CHECKMATER_EVAL 0.005
#define CHECKMATEE_EVAL -0.005
#define LEARNING_RATE 0.3

using namespace std;

typedef multimap<pair_key, State_node*> hash_4d; // 4���� �ؽ�
typedef multimap<string, State_node*> movableHash;

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
		ar & BOOST_SERIALIZATION_NVP(statenode_num);
		ar & BOOST_SERIALIZATION_NVP(hashstate_list);
	}
public:
	Adjcency_grpah();
	Adjcency_grpah(const Adjcency_grpah &graph);
	Adjcency_grpah(Adjcency_grpah *graph);

	void MovableHashInit();
	int ConvertKeyhash(int key, int key_index);
	string GetMovableKey(State_node* now_state);
	void insertMovableHash(State_node* now_state);

	void Init_hashtable();
	void Insert(vector<State_node*>*  state);
	void Second_insert(vector<State_node*>*  state);
	void PushList_Hashtable(State_node* state);
	void Set_4Dhashdata(int key[4], State_node* state);
	void AddMoveableChild(State_node *now_state);
	void AddMoveable() ;

	const bool operator== (Adjcency_grpah *graph) ;

	State_node* GetRoot();
	State_node* GetLeaf();

	int IsHaveChildnode(State_node* sub_root, State_node* state);

	State_node* IsHaveStateInHash(State_node *state);
	bool Diff_State(State_node *stateA, State_node *stateB);
};

class Second_Graph {
private:
	Adjcency_grpah *original_g;
public:
	Second_Graph(Adjcency_grpah *g);
	void AdjustWeight(vector<State_node*>* state) ;
	void Evaluating(vector<State_node*>* state) ;
	void LearningProcess(vector<State_node*>*  state, int winner);
	void BackPropagation(vector<State_node*>* state, int winner);
	int idxOfPiece(char piece);

	Adjcency_grpah * Getgraph();
	State_node* GetPrevState(vector<State_node*>*  state, int index);
	State_node* GetNextState(vector<State_node*>*  state, int index);
};


#endif