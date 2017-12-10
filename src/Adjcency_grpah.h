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
#define NUM_OF_TEAM_PIECE 17
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
#define CHO_KEY '0'
#define HAN_KEY '1'

using namespace std;

typedef multimap<pair_key, stateNode*> hash_4d; 
typedef multimap<string, stateNode*> movableHash;

class Adjcency_grpah
{
private:
	stateNode *root;
	stateNode *leaf;
	hash_4d* hashstate_list[NUM_OF_TEAM_PIECE][NUM_OF_TEAM_PIECE];
	stack<stateNode *> state_stack;
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

	void initMovableHash();
	int convertKeyhash(int key, int key_index);
	string getMovableKey(stateNode* now_state);
	void insertMovableHash(stateNode* now_state);

	void initHashtable();
	void Insert(vector<stateNode*>*  state);
	void secondInsert(vector<stateNode*>*  state);
	void pushToHashtable(stateNode* state);
	void Set_4Dhashdata(int key[4], stateNode* state);
	void AddMoveableChild(stateNode *now_state);
	void AddMoveable() ;
    void movableByBFS(int *bfs_check);

	const bool operator== (Adjcency_grpah *graph) ;

	stateNode* GetRoot();
	stateNode* GetLeaf();

	int IsHaveChildnode(stateNode* sub_root, stateNode* state);

	stateNode* IsHaveStateInHash(stateNode *state);
	bool Diff_State(stateNode *stateA, stateNode *stateB);
};

class Second_Graph {
private:
	Adjcency_grpah *original_g;
public:
	Second_Graph(Adjcency_grpah *g);
	void adjustWeight(vector<stateNode*>* state) ;
	void Evaluating(vector<stateNode*>* state) ;
	void learnProcess(vector<stateNode*>*  state, int winner);
	void backPropagation(vector<stateNode*>* state, int winner);
	int idxOfPiece(char piece);

	Adjcency_grpah * Getgraph();
	stateNode* getPrevState(vector<stateNode*>*  state, int index);
	stateNode* getNextState(vector<stateNode*>*  state, int index);
};


#endif