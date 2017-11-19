#include "Statenode.h"

static int score_piece[PIECE_NUM]{ CHA_VALUE, PHO_VALUE, HORSE_VALUE,
SANG_VALUE, SA_VALUE, JOL_VALUE, KING_VALUE,NO_UNIT
};

stateCondition::stateCondition(char act, char kill, bool check, int host) {
	actor = act;
	killed = kill;
	checkmate = check;
	this->host = host;
};

stateCondition::stateCondition() {
	actor = NULL;
	killed = NULL;
	checkmate = false;
	host = NULL;
}

char stateCondition::GetActor() {
	return actor;
}

char stateCondition::GetKilled() {
	return killed;
}

bool stateCondition::GetCheckmate() {
	return checkmate;
}

int stateCondition::Gethost() {
	return host;
}

pair<int, int> stateCondition::Getpos() {
	return pos;
}

void stateCondition::SetTurn(char act, char kill, bool check, int host, pair<int, int> Pos) {
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

void State_node::Addlist_Child(State_node *add_state) {
	this->next->push_back(add_state);
};
void State_node::Connect_Parent(State_node *parent_state) {
	this->prev->push_back(parent_state);
};

State_node* State_node::NthCheck_Childnode(int n) {
	return next->at(n);
};
State_node* State_node::NthCheck_Parentnode(int n) {
	return prev->at(n);
};
stateCondition* State_node::GetTurn() {
	return this_turn;
}

void State_node::Set_numUnit(int cho, int han) {
	numofHan = han;
	numofCho = cho;
}
void State_node::Set_Stateorder(int data) {
	state_ordernum = data;
}

void State_node::SetHorse_position(pair_key s) {
	sumofKeyPosition = s;
}

void State_node::Init() {
	next = new vector<State_node*>();
	prev = new vector<State_node*>();
	this_turn = new stateCondition();
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

	try {
		if (host == 0) { 
			cho_weight->at(idx) += score;
		}
		else { // han
			han_weight->at(idx) += score;
		}
	}
	catch(...){
		cout << idx << " except" <<  endl;
		return ;
		//e.what() ;
	}
}
// piece[14] : c,p,h,x ... -> han ... chp
// { CHA, PHO, HORSE, SANG, SA, JOL, KING, NONE };
void State_node::setNumOfPiece(int *piece) {
	for (int i = 1; i < HEIGHT_SIZE; i++) 
		for (int j = 1; j < WIDTH_SIZE; j++) {
			switch (State[i][j])
			{
			// han
			case 'c': piece[CHA]++ ; break;
			case 'p': piece[PHO]++ ; break;
			case 'h': piece[HORSE]++ ; break;
			case 'x': piece[SANG]++ ; break;
			case 's': piece[SA]++ ; break;
			case 'j': piece[JOL]++ ; break;
			case 'k': piece[KING]++ ; break;
			// cho
			case 'C': piece[CHA+7]++ ; break;
			case 'P': piece[PHO+7]++ ; break;
			case 'H': piece[HORSE+7]++ ; break;
			case 'X': piece[SANG+7]++ ; break;
			case 'S': piece[SA+7]++ ; break;
			case 'J': piece[JOL+7]++ ; break;
			case 'K': piece[KING+7]++ ; break;
			case '-': break;
			default: cout << " evaluate error !" << endl;
				for (int i = 1; i < HEIGHT_SIZE; i++) {
					for (int j = 1; j < WIDTH_SIZE; j++) {
			cout << State[i][j] << " " ;
		}
					cout << endl;
				}
		

			 exit(1);
			}
		}
}
// piece[14] : c,p,h,x ... -> han ... chp
// { CHA, PHO, HORSE, SANG, SA, JOL, KING, NONE };
void State_node::evaluateBoard() {
	int piece_count = numofCho + numofHan ;
	int countOfPiece[NUM_OF_PIECE] = {0} ;
	setNumOfPiece(countOfPiece) ;

	if (piece_count >= 22) score_piece[PHO] = PHO_VALUE;
	else if (piece_count >= 13) score_piece[PHO] = PHO_MIDDLE_VALUE;
	else score_piece[PHO] = PHO_BOTTOM_VALUE;

	// han
	for(int i=0; i<7 ;i++){
		score += score_piece[i] * han_weight->at(i) ;
	}

	// cho
	for(int i=7 ; i<14; i++){
		score += score_piece[i-7] * cho_weight->at(i-7) ;
	}
}

STATE State_node::GetState() {
	return State;
}

int State_node::SizeofPrev() {
	return prev->size();
}
int State_node::SizeofNext() {
	return next->size();
}
int State_node::Getstate_ordernum() {
	return state_ordernum;
}
int State_node::Gethan() {
	return numofHan;
}
int State_node::Getcho() {
	return numofCho;
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

vector<State_node*>* State_node::GetNext() {
	return next;
}

vector<State_node*>* State_node::GetPrev() {
	return prev;
}

pair_key State_node::GetPieceOfKey() {
	return sumofKeyPosition;
}

const bool State_node::operator==(State_node *node) {
	if (memcmp(this->next, node->next, sizeof(vector<State_node*>))) {
		return false;
	}
	else if (memcmp(this->prev, node->prev, sizeof(vector<State_node*>))) {
		return false;
	}
	else if (memcmp(&this->sumofKeyPosition, &node->sumofKeyPosition, sizeof(pair<Cha_pos, Pho_pos>))) {
		return false;
	}
	else if (memcmp(&this->state_ordernum, &node->state_ordernum, sizeof(int))) {
		return false;
	}
	else if (memcmp(&this->numofCho, &node->numofCho, sizeof(int))) {
		return false;
	}
	else if (memcmp(&this->numofHan, &node->numofHan, sizeof(int))) {
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
	for(int i = 0 ; i < HEIGHT_SIZE ; i++){
		for(int j = 0 ; j < WIDTH_SIZE ; j++){
			State[i][j] = state_[i][j] ;
		}
	}
}