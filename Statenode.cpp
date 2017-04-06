#include "Statenode.h"

State_node::State_node(char data[HEIGHT_SIZE][WIDTH_SIZE]) {
	for (int i = 0; i < WIDTH_SIZE; i++)
		arr[0][i] = NULL;
	for (int i = 0; i < HEIGHT_SIZE; i++)
		arr[i][0] = NULL;
	for (int i = 1; i < HEIGHT_SIZE; i++)
		for (int j = 1; j < WIDTH_SIZE; j++)
			arr[i][j] = data[i][j];
	Init();
};
State_node::State_node() {
	for (int i = 0; i< HEIGHT_SIZE; i++) 
		memset(arr[i], NULL, sizeof(char)*WIDTH_SIZE);
	
	Init();
};

// state의 상태를 출력한다.
void State_node::Print_State() {
	for (int i = 0; i < HEIGHT_SIZE; i++) {
		for (int j = 0; j < WIDTH_SIZE; j++) {
			if (i == 0) {
				cout << j << "  ";
			}
			else if(j == 0) {
				cout << i << "  ";
			}
			else {
				cout << arr[i][j] << "  ";
			}
		}
		cout << endl;
	}
	cout << endl;
};
//node의 자식을 생성.
void State_node::Addlist_Child(State_node *add_state) {
	this->next->push_back(add_state);
};
void State_node::Connect_Parent(State_node *parent_state) {
	this->prev->push_back(parent_state);
};
// n번째 자식을 return
State_node* State_node::NthCheck_Childnode(int n) {
	return next->at(n);
};
State_node* State_node::NthCheck_Parentnode(int n) {
	return prev->at(n);
};
void State_node::Set_numUnit(int cho, int han) {
	unit_of_han = han;
	unit_of_cho = cho;
}
void State_node::Set_Stateorder(int data) {
	state_ordernum = data;
}

void State_node::SetHorse_position(pair<Cha_pos, Pho_pos> s){
	sum_of_horsepos = s;
}

void State_node::Init() {
	next = new vector<State_node*>();
	prev = new vector<State_node*>();
	state_ordernum = 0;
	travel_count = 0;
	state_number = 0;
}

void State_node::TravelCountPlus() {
	travel_count++;
}

void State_node::SetState_number(int setnum) {
	state_number = setnum;
}

int State_node::Getnumprev(){
	return prev->size() ;
}
int State_node::Getnumnext() {
	return next->size() ;
}
int State_node::Getstate_ordernum() {
	return state_ordernum;
}
int State_node::Gethan() {
	return unit_of_han;
}
int State_node::Getcho() {
	return unit_of_cho;
}

int State_node::GetTravelcount() {
	return travel_count ;
}

int State_node::GetState_number() {
	return state_number;
}

vector<State_node*>* State_node::Getnext() {
	return next;
}

vector<State_node*>* State_node::Getprev() {
	return prev;
}

pair<Cha_pos, Pho_pos> State_node::GetHorse_pos(){
	return sum_of_horsepos;
}