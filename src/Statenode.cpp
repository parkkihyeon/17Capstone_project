#include "Statenode.h"

static int scorePiece[PIECE_NUM]{ CHA_VALUE, PHO_VALUE, HORSE_VALUE,
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


stateNode::stateNode(char data[HEIGHT_SIZE][WIDTH_SIZE]) {

	for (int i = colStartNum-1; i < WIDTH_SIZE; i++)
		State[0][i] = NULL;
	for (int i = rowStartNum-1; i < HEIGHT_SIZE; i++)
		State[i][0] = NULL;

	for (int i = rowStartNum; i < HEIGHT_SIZE; i++)
		for (int j = colStartNum; j < WIDTH_SIZE; j++)
			State[i][j] = data[i][j];

	Init();
};
stateNode::stateNode() {
	for (int i = 0; i < HEIGHT_SIZE; i++)
		memset(State[i], NULL, sizeof(char)*WIDTH_SIZE);

	Init();
};

void stateNode::Print_State() {
	for (int i = rowStartNum-1; i < HEIGHT_SIZE; i++) {
		for (int j = colStartNum-1 ; j < WIDTH_SIZE; j++) {
			if (i == 0) 
				cout << j << "  ";
			
			else if (j == 0) 
				cout << i << "  ";
			
			else 
				cout << State[i][j] << "  ";
			
		}
		cout << endl;
	}
	cout << endl;
};

void stateNode::Addlist_Child(stateNode *add_state) {
	this->next->push_back(add_state);
};
void stateNode::Connect_Parent(stateNode *parent_state) {
	this->prev->push_back(parent_state);
};

stateNode* stateNode::NthCheck_Childnode(int n) {
	return next->at(n);
};
stateNode* stateNode::NthCheck_Parentnode(int n) {
	return prev->at(n);
};
stateCondition* stateNode::GetTurn() {
	return this_turn;
}

void stateNode::Set_numUnit(int cho, int han) {
	numofHan = han;
	numofCho = cho;
}
void stateNode::Set_Stateorder(int data) {
	state_ordernum = data;
}

void stateNode::SetHorse_position(pair_key s) {
	sumofKeyPosition = s;
}

void stateNode::Init() {
	next = new vector<stateNode*>();
	prev = new vector<stateNode*>();
	this_turn = new stateCondition();
	travel_count = 0;
	state_number = 1;
	hanWeight = new vector<double>();
	choWeight = new vector<double>();
	for (int i = 0; i < PIECE_NUM; i++) {
		hanWeight->push_back(INIT_WEIGHT);
		choWeight->push_back(INIT_WEIGHT);
	}
	score = 0;
}

void stateNode::TravelCountPlus() {
	travel_count++;
}

void stateNode::SetState_number(int setnum) {
	state_number = setnum;
}

void stateNode::SetHan_weight(vector<double> *h_weight) {
	memcpy(hanWeight, h_weight, sizeof(int)*PIECE_NUM);
}

void stateNode::SetCho_weight(vector<double> *c_weight) {
	memcpy(choWeight, c_weight, sizeof(int)*PIECE_NUM);
}

void stateNode::SetScore(double score_) {
	score = score_;
}

void stateNode::WeightCalculate(int idx, const double score, int host) {

	try {
		if (host == CHO_PLAY) { 
			choWeight->at(idx) += score;
		}
		else { // han
			hanWeight->at(idx) += score;
		}
	}
	catch(...){
		cout << idx << " except" <<  endl;
		return ;
		//e.what() ;
	}
}
// { CHA, PHO, HORSE, SANG, SA, JOL, KING, NONE };
void stateNode::setNumOfPiece(int *piece) {
	const int teamOfNumPiece = NUM_OF_PIECE / 2 ;
	for (int i = rowStartNum; i < HEIGHT_SIZE; i++) 
		for (int j = colStartNum; j < WIDTH_SIZE; j++) {
			switch (State[i][j])
			{
			// cho
			case choPiece::CHA: piece[CHA]++ ; break;
			case choPiece::PHO: piece[PHO]++ ; break;
			case choPiece::HORSE : piece[HORSE]++ ; break;
			case choPiece::SANG : piece[SANG]++ ; break;
			case choPiece::SA : piece[SA]++ ; break;
			case choPiece::JOL : piece[JOL]++ ; break;
			case choPiece::KING : piece[KING]++ ; break;
			// han
			case hanPiece::CHA : piece[CHA+teamOfNumPiece]++ ; break;
			case hanPiece::PHO : piece[PHO+teamOfNumPiece]++ ; break;
			case hanPiece::HORSE : piece[HORSE+teamOfNumPiece]++ ; break;
			case hanPiece::SANG : piece[SANG+teamOfNumPiece]++ ; break;
			case hanPiece::SA : piece[SA+teamOfNumPiece]++ ; break;
			case hanPiece::JOL : piece[JOL+teamOfNumPiece]++ ; break;
			case hanPiece::KING : piece[KING+teamOfNumPiece]++ ; break;
			case '-': break;
			default: cout << " evaluate error !" << endl; break ;
			}
		}
}
// piece[14] : c,p,h,x ... -> han ... chp
// { CHA, PHO, HORSE, SANG, SA, JOL, KING, NONE };
void stateNode::evaluateBoard() {
	int pieceCount = numofCho + numofHan ;
	int countOfPiece[NUM_OF_PIECE] = {0} ;
	setNumOfPiece(countOfPiece) ;

	if (pieceCount >= EARLY_GAME) scorePiece[PHO] = PHO_VALUE;
	else if (pieceCount >= MIDDLE_GAME) scorePiece[PHO] = PHO_MIDDLE_VALUE;
	else scorePiece[PHO] = PHO_BOTTOM_VALUE;

	for(int i=0; i<NUM_OF_PIECE ;i++){
		int teamOfNumPiece = NUM_OF_PIECE/2 ; 
		int partition = i>teamOfNumPiece ? i-teamOfNumPiece : i ;
		int weight = i>teamOfNumPiece ? choWeight->at(i-teamOfNumPiece) : hanWeight->at(i) ; 
		score += scorePiece[partition] * weight ;
	}
}

STATE stateNode::GetState() {
	return State;
}

int stateNode::SizeofPrev() {
	return prev->size();
}
int stateNode::SizeofNext() {
	return next->size();
}
int stateNode::Getstate_ordernum() {
	return state_ordernum;
}
int stateNode::Gethan() {
	return numofHan;
}
int stateNode::Getcho() {
	return numofCho;
}

int stateNode::GetTravelcount() {
	return travel_count;
}

int stateNode::GetState_number() {
	return state_number;
}

vector<double>* stateNode::Get_hanweight() {
	return hanWeight;
}

vector<double>* stateNode::Get_choweight() {
	return choWeight;
}

double stateNode::GetScore() {
	return score;
}

vector<stateNode*>* stateNode::GetNext() {
	return next;
}

vector<stateNode*>* stateNode::GetPrev() {
	return prev;
}

pair_key stateNode::GetPieceOfKey() {
	return sumofKeyPosition;
}

const bool stateNode::operator==(stateNode *node) {
	if (!memcmp(this->next, node->next, sizeof(vector<stateNode*>)) ||
		!memcmp(this->prev, node->prev, sizeof(vector<stateNode*>)) || 
		!memcmp(&this->sumofKeyPosition, &node->sumofKeyPosition, sizeof(pair<Cha_pos, Pho_pos>)) ||
		!memcmp(&this->state_ordernum, &node->state_ordernum, sizeof(int)) ||
		!memcmp(&this->numofCho, &node->numofCho, sizeof(int)) ||
		!memcmp(&this->numofHan, &node->numofHan, sizeof(int)) ||
		!memcmp(&this->travel_count, &node->travel_count, sizeof(int)) ||
		!memcmp(&this->state_number, &node->state_number, sizeof(int)) ||
		!memcmp(&this->score, &node->score, sizeof(int)) ||
		!memcmp(this->this_turn, &node->this_turn, sizeof(vector<stateNode*>))
		)
		return true;

	return false;
}

void stateNode::SetState(char state_[HEIGHT_SIZE][WIDTH_SIZE]) {
	for(int i = 0 ; i < HEIGHT_SIZE ; i++){
		for(int j = 0 ; j < WIDTH_SIZE ; j++){
			State[i][j] = state_[i][j] ;
		}
	}
}