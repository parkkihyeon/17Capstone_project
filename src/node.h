#ifndef __NODE__
#define __NODE__

#include <iostream>
#include <vector>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp> // ����ȭ vector�� ����ϱ� ����
#include <boost/serialization/deque.hpp> // ����ȭ stack�� ����ϱ� ����
#include <boost/serialization/stack.hpp> // ����ȭ stack�� ����ϱ� ����
#include <boost/serialization/map.hpp>
#include <boost/serialization/utility.hpp>

#include <boost/archive/binary_iarchive.hpp> // ���̳ʸ� ���·� �Է��ϱ� ����
#include <boost/archive/binary_oarchive.hpp> // ���̳ʸ� ���·� �Է��ϱ� ����

#include <boost/serialization/nvp.hpp>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11

using namespace std;

typedef char(*State)[WIDTH_SIZE];
typedef pair<int, int> Cha_pos;
typedef pair<int, int> Pho_pos;

class node
{
private:
	int host;
	int num_of_han;
	int num_of_cho;
	
	char killed;
	char actor;
	char arr[HEIGHT_SIZE][WIDTH_SIZE];

	bool checkMate;

	pair<Cha_pos, Pho_pos> sum_of_horsepos;
	pair<int, int> pos;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		ar & BOOST_SERIALIZATION_NVP(host);
		ar & BOOST_SERIALIZATION_NVP(num_of_cho);
		ar & BOOST_SERIALIZATION_NVP(num_of_han);
		ar & BOOST_SERIALIZATION_NVP(killed);
		ar & BOOST_SERIALIZATION_NVP(actor);
		ar & BOOST_SERIALIZATION_NVP(arr);
		ar & BOOST_SERIALIZATION_NVP(checkMate);
		ar & BOOST_SERIALIZATION_NVP(sum_of_horsepos);
	}

public:

	node(State board);
	node();

	// state�� ���¸� ����Ѵ�.
	void Print_State();

	// state�� ���� ��ȯ
	State returnState();

	// state�� ���¸� �ʱ�ȭ�Ѵ�.
	void UnitOrder(int cho_order, int han_order);
	// state�� ���¸� �����Ѵ�.
	void changeState(int pos[]);
	// state�� ��, ���� ���� ������ ���Ѵ�.
	void getNumOfUnit();
	void Init_Hashkeydata();
	// state initialize
	void Init();

	pair<Cha_pos, Pho_pos> getPair();

	int getNumOfHan();
	int getNumOfCho();
	int getHost();
	pair<int, int> GetPos();

	char getActor();
	char getKilled();
	bool getCheckMate();

	void setCheckMate(bool is);
	void setActor(char unit);
	void setKilled(char unit);
	void setHost(int host);
	void setPos(int prev_pos, int post_pos);

	char getArrPos(int xPos, int yPos);
};

#endif