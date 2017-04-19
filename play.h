#ifndef __PLAY__
#define __PLAY__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "node.h"

#define MIN 200
#define TOKEN_SIZE 6
#define INITIAL_ORDER -2

using namespace std;

static int fileNum = 0;

class Play {
private:
	// 기보 번호
	int reportNumber;
	// 각 진영의 포진
	int cho_order;
	int han_order;
	int victory;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		ar & BOOST_SERIALIZATION_NVP(cho_order);
		ar & BOOST_SERIALIZATION_NVP(han_order);
		ar & BOOST_SERIALIZATION_NVP(victory);
		ar & BOOST_SERIALIZATION_NVP(game);
		ar & BOOST_SERIALIZATION_NVP(reportNumber);
		ar & BOOST_SERIALIZATION_NVP(StateInfo);
	}

public:
	char StateInfo[HEIGHT_SIZE][WIDTH_SIZE];
	vector<node*> game;

	Play();
	Play(int reportNum, int cho, int han, int vic);

	// State를 멤버 변수에 삽입
	void insertStage(node *state);

	// State를 생성
	void createState(string line);

	void printBoard();

	Play* createPlay(ifstream &file);

	bool getRightNode();

	void initailize();
};
#endif