#ifndef __STATE__NODE__  
#define __STATE__NODE__  

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/stack.hpp> 
#include <boost/serialization/map.hpp>
#include <boost/serialization/utility.hpp>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp> 

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/exception/all.hpp>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11
#define PIECE_NUM 8 
#define INIT_WEIGHT 1
#define NUM_OF_PIECE 14
#define PHO_MIDDLE_VALUE 5
#define PHO_BOTTOM_VALUE 2
#define EARLY_GAME 22 
#define MIDDLE_GAME 13
#define rowStartNum 1
#define colStartNum 1

using namespace std;

typedef pair<int, int> Cha_pos;
typedef pair<int, int> Pho_pos;
typedef pair<Cha_pos, Pho_pos> pair_key;
typedef char (*STATE)[WIDTH_SIZE] ;

enum {CHO_PLAY, HAN_PLAY};
enum { CHA, PHO, HORSE, SANG, SA, JOL, KING, NONE };
enum {
	NO_UNIT = 0, 
	JOL_VALUE = 2, 
	SA_VALUE = 3, 
	SANG_VALUE = 3,
	HORSE_VALUE = 5, 
	PHO_VALUE = 7, 
	CHA_VALUE = 13, 
	KING_VALUE = 100
};

namespace choPiece{
	static const char CHA = 'c' ;
	static const char PHO = 'p' ;
	static const char HORSE = 'h' ;
	static const char SANG = 'x' ;
	static const char SA = 's' ;
	static const char JOL = 'j' ;
	static const char KING = 'k' ;
}

namespace hanPiece {
	static const char CHA = 'C' ;
	static const char PHO = 'P' ;
	static const char HORSE = 'H' ;
	static const char SANG = 'X' ;
	static const char SA = 'S' ;
	static const char JOL = 'J' ;
	static const char KING = 'K' ;
}

class stateCondition
{
private:
	char actor;
	char killed;
	bool checkmate;
	int host;
	pair<int, int> pos;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		ar & BOOST_SERIALIZATION_NVP(actor);
		ar & BOOST_SERIALIZATION_NVP(killed);
		ar & BOOST_SERIALIZATION_NVP(checkmate);
		ar & BOOST_SERIALIZATION_NVP(host);
		ar & BOOST_SERIALIZATION_NVP(pos);
	}

public:
	stateCondition(char act, char kill, bool check, int host);
	stateCondition();
	char GetActor();
	char GetKilled();
	bool GetCheckmate();
	int Gethost() ;
	pair<int, int> Getpos();
	void SetTurn(char act, char kill, bool check, int host, pair<int, int> Pos);
};


class stateNode
{
private:
	int state_ordernum; 
	int numofHan;
	int numofCho;
	int travel_count;
	int state_number; 

	vector<double> *hanWeight ;
	vector<double> *choWeight ;
	double score;
	char State[HEIGHT_SIZE][WIDTH_SIZE];

	stateCondition *this_turn;
	vector<stateNode*>* next;
	vector<stateNode*>* prev;
	pair_key sumofKeyPosition;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		ar & BOOST_SERIALIZATION_NVP(state_ordernum);
		ar & BOOST_SERIALIZATION_NVP(state_number);
		ar & BOOST_SERIALIZATION_NVP(numofCho);
		ar & BOOST_SERIALIZATION_NVP(numofHan);
		ar & BOOST_SERIALIZATION_NVP(travel_count);
		ar & BOOST_SERIALIZATION_NVP(hanWeight);
		ar & BOOST_SERIALIZATION_NVP(choWeight);
		ar & BOOST_SERIALIZATION_NVP(score);
		ar & BOOST_SERIALIZATION_NVP(State);
		ar & BOOST_SERIALIZATION_NVP(sumofKeyPosition);
		ar & BOOST_SERIALIZATION_NVP(next);
		ar & BOOST_SERIALIZATION_NVP(prev);
		ar & BOOST_SERIALIZATION_NVP(this_turn);
	}
public:

	stateNode(char data[HEIGHT_SIZE][WIDTH_SIZE]);
	stateNode();

	void Print_State();

	void Addlist_Child(stateNode *add_state);
	void Connect_Parent(stateNode *parent_state);
	void Set_numUnit(int cho, int han);
	void Set_Stateorder(int data);
	void SetHorse_position(pair_key s);
	void Init();
	void TravelCountPlus();
	void SetState_number(int setnum);
	void SetHan_weight(vector<double> *h_weight);
	void SetCho_weight(vector<double> *c_weight);
	void SetScore(double score_);
	void WeightCalculate(int idx, const double score, int host);
	void setNumOfPiece(int *piece) ;
	void evaluateBoard();

	const bool operator==(stateNode *node);

	stateNode* NthCheck_Childnode(int n);
	stateNode* NthCheck_Parentnode(int n);
	stateCondition* GetTurn();
	STATE GetState();

	int SizeofPrev();
	int SizeofNext();
	int Getstate_ordernum();
	int Gethan();
	int Getcho();
	int GetTravelcount();
	int GetState_number();
	vector<double>* Get_hanweight();
	vector<double>* Get_choweight();
	double GetScore();

	vector<stateNode*> *GetNext();
	vector<stateNode*> *GetPrev();
	pair_key GetPieceOfKey();

	void SetState(char state_[HEIGHT_SIZE][WIDTH_SIZE]);
};

#endif
