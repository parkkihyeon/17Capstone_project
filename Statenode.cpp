#include "Statenode.h"

static int score_piece[PIECE_NUM]{ CHA_VALUE, PHO_VALUE, HORSE_VALUE,
SANG_VALUE, SA_VALUE, JOL_VALUE, KING_VALUE,NO_UNIT
};

Now_turn::Now_turn(char act, char kill, bool check, int host) {
	actor = act;
	killed = kill;
	checkmate = check;
	this->host = host;
};

Now_turn::Now_turn() {
	actor = NULL;
	killed = NULL;
	checkmate = false;
	host = NULL;
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

pair<int, int> Now_turn::Getpos() {
	return pos;
}

void Now_turn::SetTurn(char act, char kill, bool check, int host, pair<int, int> Pos) {
	actor = act;
	killed = kill;
	checkmate = check;
	this->host = host;
	pos = Pos;
}


State_node::State_node(char data[HEIGHT_SIZE][WIDTH_SIZE]) {
	for (int i = 0; i < WIDTH_SIZE; i++)
		State[0][i] = NULL;
	for (int i = 0; i < HEIGHT_SIZE; i++)
		State[i][0] = NULL;
	for (int i = 1; i < HEIGHT_SIZE; i++)
		for (int j = 1; j < WIDTH_SIZE; j++)
			State[i][j] = data[i][j];
	Init();
};
State_node::State_node() {
	for (int i = 0; i < HEIGHT_SIZE; i++)
		memset(State[i], NULL, sizeof(char)*WIDTH_SIZE);

	Init();
};

// state�� ���¸� ����Ѵ�.
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
				cout << State[i][j] << "  ";
			}
		}
		cout << endl;
	}
	cout << endl;
};
//node�� �ڽ��� ����.
void State_node::Addlist_Child(State_node *add_state) {
	this->next->push_back(add_state);
};
void State_node::Connect_Parent(State_node *parent_state) {
	this->prev->push_back(parent_state);
};
// n��° �ڽ��� return
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
	han_weight = new vector<double>();
	cho_weight = new vector<double>();
	for (int i = 0; i < PIECE_NUM; i++) {
		han_weight->push_back(INIT_WEIGHT);
		cho_weight->push_back(INIT_WEIGHT);
	}
	score = 0;
}

void State_node::TravelCountPlus() {
	travel_count++;
}

void State_node::SetState_number(int setnum) {
	state_number = setnum;
}

void State_node::Print_weight(int idx) {
	ofstream stream("evaluate.txt", ios::app);
	stream << idx << "��° : " << endl;
	stream << "�� : " << endl;
	for (int i = 0; i < 7; i++) {
		stream << cho_weight->at(i) << " ";
	}
	stream << endl;
	stream << "�� : " << endl;
	for (int i = 0; i < 7; i++) {
		stream << han_weight->at(i) << " ";
	}

	stream << endl << endl;
	stream.close();
}

void State_node::SetHan_weight(vector<double> *h_weight) {
	memcpy(han_weight, h_weight, sizeof(int)*PIECE_NUM);
}

void State_node::SetCho_weight(vector<double> *c_weight) {
	memcpy(cho_weight, c_weight, sizeof(int)*PIECE_NUM);
}

void State_node::SetScore(double score_) {
	score = score_;
}

void State_node::WeightCalculate(int idx, const double score, int host) {
	if (host == 0) {// cho 
		cho_weight->at(idx) += score;
	}
	else { // han
		han_weight->at(idx) += score;
	}
}

void State_node::evaluateBoard() {
	int piece_count = 0;
	for (int i = 1; i < HEIGHT_SIZE; i++) {
		for (int j = 1; j < WIDTH_SIZE; j++) {
			if ((State[i][j] >= 'a' && State[i][j] <= 'z') || (State[i][j] >= 'A' && State[i][j] <= 'Z'))
				piece_count++;
		}
	}

	// test��.
	if (piece_count >= 22) score_piece[PHO] = PHO_VALUE;
	else if (piece_count >= 13) score_piece[PHO] = PHO_MIDDLE_VALUE;
	else score_piece[PHO] = PHO_BOTTOM_VALUE;

	for (int i = 1; i < HEIGHT_SIZE; i++) {
		for (int j = 1; j < WIDTH_SIZE; j++) {
			switch (State[i][j])
			{
			case 'c':
				score += score_piece[CHA] * han_weight->at(CHA);
				if (i > 5)
					score -= 10;
				break;
			case 'p':
				score += score_piece[PHO] * han_weight->at(PHO);
				if (i > 5)
					score -= 10;
				break;
			case 'h':
				score += score_piece[HORSE] * han_weight->at(HORSE);
				if (i > 5)
					score += 10;
				break;
			case 'x':
				score += score_piece[SANG] * han_weight->at(SANG);
				break;
			case 's':
				score += score_piece[SA] * han_weight->at(SA);
				break;
			case 'j':
				score += score_piece[JOL] * han_weight->at(JOL);
				break;
			case 'k':
				score += score_piece[KING] * han_weight->at(KING);
				break;

			case 'C':
				score += score_piece[CHA] * cho_weight->at(CHA);
				if (i > 5)
					score += 10;
				break;
			case 'P':
				score += score_piece[PHO] * cho_weight->at(PHO);
				if (i > 5)
					score += 10;
				break;
			case 'H':
				score += score_piece[HORSE] * cho_weight->at(HORSE);
				if (i > 5)
					score += 10;
				break;
			case 'X':
				score += score_piece[SANG] * cho_weight->at(SANG);
				break;
			case 'S':
				score += score_piece[SA] * cho_weight->at(SA);
				break;
			case 'J':
				score += score_piece[JOL] * cho_weight->at(JOL);
				break;
			case 'K':
				score += score_piece[KING] * cho_weight->at(KING);
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

STATE State_node::GetState() {
	return State;
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

vector<double>* State_node::Get_hanweight() {
	return han_weight;
}

vector<double>* State_node::Get_choweight() {
	return cho_weight;
}

double State_node::GetScore() {
	return score;
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
	else if (memcmp(this->this_turn, &node->this_turn, sizeof(vector<State_node*>))) {
		return false;
	}
	else
		return true;
}

void State_node::SetState(char state_[HEIGHT_SIZE][WIDTH_SIZE]) {
	memcpy(State, state_, sizeof(char) * HEIGHT_SIZE * WIDTH_SIZE);
}