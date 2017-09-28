#ifndef __PLAY__
#define __PLAY__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "node.h"

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp> // ����ȭ vector�� ����ϱ� ����
#include <boost/serialization/deque.hpp> // ����ȭ stack�� ����ϱ� ����
#include <boost/serialization/stack.hpp> // ����ȭ stack�� ����ϱ� ����
#include <boost/serialization/map.hpp>
#include <boost/serialization/utility.hpp>

#include <boost/archive/binary_iarchive.hpp> // ���̳ʸ� ���·� �Է��ϱ� ����
#include <boost/archive/binary_oarchive.hpp> // ���̳ʸ� ���·� �Է��ϱ� ����

#include <boost/serialization/nvp.hpp>

#define TOKEN_SIZE 6
#define INITIAL_ORDER -2

using namespace std;

static int fileNum = 0;

class Play {
private:
	// �⺸ ��ȣ
	int reportNumber;
	// �� ������ ����
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

	// State�� ��� ������ ����
	void insertStage(node *state);

	// State�� ����
	void createState(string line);

	void printBoard();

	Play* createPlay(ifstream &file);
	int GetWinner();

	bool getRightNode();

	void initailize();
};
#endif