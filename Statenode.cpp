#include "Statenode.h"

static const int score_piece[PIECE_NUM]{ 13,7,5,3,3,2,100,0};

Now_turn::Now_turn(char act, char kill, bool check, int host) {
	actor = act;
	killed = kill;
	checkmate = check;
	this->host = host ;
};

Now_turn::Now_turn() {
	actor = NULL;
	killed = NULL;
	checkmate = false;
	host = NULL ;
}

char Now_turn::GetActor() {
	return actor;
}

char Now_turn::GetKilled() {
	return killed;
}

bool Now_turn::GetCheckmate() {
	return checkmate;
}

int Now_turn::Gethost() {
	return host;
}

void Now_turn::SetTurn(char act, char kill, bool check, int host) {
	actor = act;
	killed = kill;
	checkmate = check;
	this->host = host ;
}


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
	for (int i = 0; i < HEIGHT_SIZE; i++)
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
			else if (j == 0) {
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
Now_turn* State_node::GetTurn() {
	return this_turn;
}

void State_node::Set_numUnit(int cho, int han) {
	unit_of_han = han;
	unit_of_cho = cho;
}
void State_node::Set_Stateorder(int data) {
	state_ordernum = data;
}

void State_node::SetHorse_position(pair<Cha_pos, Pho_pos> s) {
	sum_of_horsepos = s;
}

void State_node::Init() {
	next = new vector<State_node*>();
	prev = new vector<State_node*>();
	this_turn = new Now_turn();
	state_ordernum = 0;
	travel_count = 0;
	state_number = 1;
	for (int i = 0; i < PIECE_NUM; i++) {
		han_weight[i] = 100000;
		cho_weight[i] = 100000;
	}
	score = 0;
	reward = 0;
}

void State_node::TravelCountPlus() {
	travel_count++;
}

void State_node::SetState_number(int setnum) {
	state_number = setnum;
}

void State_node::Print_weight(int idx) {
	ofstream stream("evaluate.txt", ios::app);
	stream << idx << "번째 : " << endl;
	stream << "초 : " << endl;
	for (int i = 0; i < 7; i++) {
		stream << cho_weight[i] << " ";
	}
	stream << endl;
	stream << "한 : " << endl;
	for (int i = 0; i < 7; i++) {
		stream << han_weight[i] << " ";
	}

	stream << endl << endl;
	stream.close();
}

void State_node::SetHan_weight(int *h_weight) {
	memcpy(han_weight, h_weight, sizeof(int)*PIECE_NUM);
}

void State_node::SetCho_weight(int *c_weight) {
	memcpy(cho_weight, c_weight, sizeof(int)*PIECE_NUM);
}

void State_node::WeightCalculate(int idx, int score, int host) {
	if (host == 0) {// cho 
		cho_weight[idx] += score;	
	}
	else { // han
		han_weight[idx] += score;
	}
}

void State_node::evaluateBoard() {
	for (int i = 1; i < HEIGHT_SIZE; i++) {
		for (int j = 1; j < WIDTH_SIZE; j++) {
			switch (arr[i][j])
			{
			case 'c':
				score -= score_piece[0] * han_weight[0];
				if (i > 5)
					score -= 10;
				break;
			case 'p':
				score -= score_piece[1] * han_weight[1];
				if (i > 5)
					score -= 10;
				break;
			case 'h':
				score -= score_piece[2] * han_weight[2];
				if (i > 5)
					score -= 10;
				break;
			case 'x':
				score -= score_piece[3] * han_weight[3];
				break;
			case 's':
				score -= score_piece[4] * han_weight[4];
				break;
			case 'j':
				score -= score_piece[5] * han_weight[5];
				break;
			case 'k':
				score -= score_piece[6] * han_weight[6];
				break;

			case 'C':
				score += score_piece[0] * cho_weight[0];
				if (i > 5)
					score += 10;
				break;
			case 'P':
				score += score_piece[1] * cho_weight[1];
				if (i > 5)
					score += 10;
				break;
			case 'H':
				score += score_piece[2] * cho_weight[2];
				if (i > 5)
					score += 10;
				break;
			case 'X':
				score += score_piece[3] * cho_weight[3];
				break;
			case 'S':
				score += score_piece[4] * cho_weight[4];
				break;
			case 'J':
				score += score_piece[5] * cho_weight[5];
				break;
			case 'K':
				score += score_piece[6] * cho_weight[6];
				break;
			case '-':
				break;
			default:
				cout << " evaluate error !" << endl;
				break;
			}
		}
	}
}

int State_node::Getnumprev() {
	return prev->size();
}
int State_node::Getnumnext() {
	return next->size();
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
	return travel_count;
}

int State_node::GetState_number() {
	return state_number;
}

int* State_node::Get_hanweight() {
	return han_weight;
}

int* State_node::Get_choweight() {
	return cho_weight;
}

int State_node::GetScore() {
	return score ;
}

int State_node::GetReward() {
	return reward;
}

vector<State_node*>* State_node::Getnext() {
	return next;
}

vector<State_node*>* State_node::Getprev() {
	return prev;
}

pair<Cha_pos, Pho_pos> State_node::GetHorse_pos() {
	return sum_of_horsepos;
}

const bool State_node::operator==(State_node *node) {
	if (memcmp(this->next, node->next, sizeof(vector<State_node*>))) {
		return false;
	}
	else if (memcmp(this->prev, node->prev, sizeof(vector<State_node*>))) {
		return false;
	}
	else if (memcmp(&this->sum_of_horsepos, &node->sum_of_horsepos, sizeof(pair<Cha_pos, Pho_pos>))) {
		return false;
	}
	else if (memcmp(&this->state_ordernum, &node->state_ordernum, sizeof(int))) {
		return false;
	}
	else if (memcmp(&this->unit_of_cho, &node->unit_of_cho, sizeof(int))) {
		return false;
	}
	else if (memcmp(&this->unit_of_han, &node->unit_of_han, sizeof(int))) {
		return false;
	}
	else if (memcmp(&this->travel_count, &node->travel_count, sizeof(int))) {
		return false;
	}
	else if (memcmp(&this->state_number, &node->state_number, sizeof(int))) {
		return false;
	}
	else if (memcmp(&this->score, &node->score, sizeof(int))) {
		return false;
	}
	else if (memcmp(&this->reward, &node->reward, sizeof(int))) {
		return false;
	}
	else if (memcmp(this->this_turn, &node->this_turn, sizeof(vector<State_node*>))) {
		return false;
	}
	else
		return true;
}