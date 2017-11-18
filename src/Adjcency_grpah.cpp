#include "Adjcency_grpah.h"
#include "Moveable.h"

const double rester_eval = 0.001;
const double moving_eval = 0.0001;
const double killer_eval = 0.01;
const double killee_eval = -0.01;
const double checkmater_eval = 0.005;
const double checkmatee_eval = -0.005;
const double learning_rate = 0.3;

movableHash *moveableHash[NUMUNIT][NUMUNIT];

int pow(int var, int exp) {
	int ans = 1;
	for (int i = 0; i < exp; i++) {
		ans *= var;
	}
	return ans;
}

void Adjcency_grpah::MovableHashInit() {
	for (int i = 0; i < NUMUNIT; i++) {
		for (int j = 0; j < NUMUNIT; j++) {
			moveableHash[i][j] = new movableHash();
		}
	}
}

int Adjcency_grpah::ConvertKeyhash(int key, int key_index) {
	int indexKey = MOVABLE_KEY - 2 - key_index;
	int ten = 10;
	int regulatekey = pow(ten, indexKey);

	if ( (key / regulatekey) % ten == 0) {
		return NULL;
	}

	key -= regulatekey;
	return key;
}

string Adjcency_grpah::GetMovableKey(State_node* now_state) {
	string stringKey = "" ;
	int numofCha = 0, numofPho = 0, numofHorse = 0, numofSang = 0, numofSa = 0, numofJol = 0;
	int sumKey = 0;

	for (int i = 1; i < HEIGHT_SIZE; i++) {
		for (int j = 1; j < WIDTH_SIZE; j++) {
			switch (now_state->GetState()[i][j]) {
			case 'j': case 'J':
				numofJol++;
				break;
			case 'c': case 'C':
				numofCha++;
				break;
			case 'p': case 'P':
				numofPho++;
				break;
			case 'h': case 'H':
				numofHorse++;
				break;
			case 'x': case 'X':
				numofSang++;
				break;
			case 's': case 'S':
				numofSa++;
				break;
			default:
				break;
			}
		}
	}
	stringKey.append(to_string(numofCha)) ;
	stringKey.append(to_string(numofPho)) ;
	stringKey.append(to_string(numofHorse)) ;
	stringKey.append(to_string(numofSang)) ;
	stringKey.append(to_string(numofSa)) ;
	stringKey.append(to_string(numofJol)) ;
	stringKey.append(to_string(now_state->GetTurn()->Gethost())) ;
	return  stringKey;
}

void Adjcency_grpah::insertMovableHash(State_node* now_state) {
	int cho = now_state->Getcho();
	int han = now_state->Gethan();
	moveableHash[cho][han]->insert(movableHash::value_type(GetMovableKey(now_state), now_state));
}

Adjcency_grpah::Adjcency_grpah() {

	char Init_jannggi[HEIGHT_SIZE][WIDTH_SIZE];
	for (int i = 0; i < HEIGHT_SIZE; i++) {
		memset(Init_jannggi[i], 'X', sizeof(char)*WIDTH_SIZE);
	}

	root = new State_node(Init_jannggi);
	root->Set_numUnit(0, 0);
	statenode_num = 0;
	Init_hashtable();
	PushList_Hashtable(root);
	root->SetState_number(0);
	MovableHashInit();
}
//Reload Serialize¸¦ ?§ÇÑ ±í?º º¹»ç »ý¼º?Ú
Adjcency_grpah::Adjcency_grpah(const Adjcency_grpah &graph) {
	root = graph.root;
	Init_hashtable();
	statenode_num = graph.statenode_num;
	memcpy(hashstate_list, graph.hashstate_list, sizeof(hash_4d*) * NUMUNIT * NUMUNIT);
}
//Save Serialize¸¦ ?§ÇÑ ±í?º º¹»ç »ý¼º?Ú
Adjcency_grpah::Adjcency_grpah(Adjcency_grpah *graph) {
	root = graph->root;
	Init_hashtable();
	statenode_num = graph->statenode_num;
	memcpy(hashstate_list, graph->hashstate_list, sizeof(hash_4d*) * NUMUNIT * NUMUNIT);
}
void Adjcency_grpah::Init_hashtable() {
	for (int i = 0; i < NUMUNIT; i++) {
		for (int j = 0; j < NUMUNIT; j++) {
			hashstate_list[i][j] = new hash_4d();
		}
	}
}

void Adjcency_grpah::PushList_Hashtable(State_node* state) {
	int cho = state->Getcho();
	int han = state->Gethan();
	int cha_y;	int cha_x;	int pho_y;	int pho_x;
	Set_4Dhashdata(cha_y, cha_x, pho_y, pho_x, state);
	hashstate_list[cho][han]->insert(hash_4d::value_type(pair_key(Cha_pos(cha_y, cha_x), Pho_pos(pho_y, pho_x)), state));
}


void Adjcency_grpah::Insert(gameVectors state) {
	State_node *now_state = root;

	for (int index = 0; index < state->size(); index++) {
		State_node* add_state = state->at(index);

		int childnode = Is_Have_childnode(now_state, add_state);

		// ?Ú±â ?Ú½Ä°ú °°?º°Ô ?Ö?¸¸é ±×´ë·Î ?Ìµ¿.
		if (childnode >= 0) {
			now_state = now_state->NthCheck_Childnode(childnode);
		}
		else {
			// ?Ú±â ?Ú½Ä°ú °°?º°Ô ¾øÁö¸¸ ¾î¶² ³ëµå¿¡ Á¸?çÇÏ¸é ±× ³ëµå¸¦ next·Î ÁöÁ¤ÇÑ´Ù.
			State_node* check_node = Is_In_The_List_State(add_state);
			if (check_node) {
				now_state->Addlist_Child(check_node);
				check_node->Connect_Parent(now_state);
				now_state = check_node;
			}
			else {
				PushList_Hashtable(add_state);
				insertMovableHash(add_state);
				add_state->SetState_number(++statenode_num);
				now_state->Addlist_Child(add_state);
				add_state->Connect_Parent(now_state);
				add_state->Set_Stateorder(now_state->Getnext()->size());
				now_state = add_state;
			}
		}
		state_stack.push(now_state);
		now_state->TravelCountPlus();
	}
}

void Adjcency_grpah::Second_insert(gameVectors state) {
	State_node *now_state = root;

	for (int index = 0; index < state->size(); index++) {
		State_node* add_state = state->at(index);

		int childnode = Is_Have_childnode(now_state, add_state);
		now_state = now_state->NthCheck_Childnode(childnode);
		state->at(index) = now_state;
	}
}

void Adjcency_grpah::Set_4Dhashdata(int &cha_y, int &cha_x, int &pho_y, int &pho_x, State_node* state) {
	cha_y = state->GetHorse_pos().first.first;
	cha_x = state->GetHorse_pos().first.second;
	pho_y = state->GetHorse_pos().second.first;
	pho_x = state->GetHorse_pos().second.second;
}


State_node* Adjcency_grpah::GetRoot() {
	return root;
}

State_node* Adjcency_grpah::GetLeaf() {
	return leaf;
}

// Çö?ç ?§Ä¡ÇÑ ³ëµå¿¡¼­?Ç ?Ú½Ä³ëµå¿Í Ãß°¡ÇÒ state¿Í °°?º°Ô ?Ö´ÂÁö.
int Adjcency_grpah::Is_Have_childnode(State_node* sub_root, State_node* state) {
	for (int i = 0; i < sub_root->Getnumnext(); i++)
		if (!Diff_State(sub_root->NthCheck_Childnode(i), state))
			return i;
	return -1;
}

int Adjcency_grpah::Direction_parentnode(State_node* sub_node) {
	State_node* temp = state_stack.top();
	state_stack.pop();
	for (int i = 0; i < sub_node->Getnumprev(); i++) {
		if (!Diff_State(sub_node->NthCheck_Parentnode(i), temp))
			return i;
	}
	return -1;
}

// Çö?ç ³ëµå state°¡ ±×·¡ÇÁ·Î Á¸?çÇÏ°í ?Ö´ÂÁö
State_node* Adjcency_grpah::Is_In_The_List_State(State_node *state) {

	int cho = state->Getcho();
	int han = state->Gethan();
	int cha_y;	int cha_x;	int pho_y;	int pho_x;
	Set_4Dhashdata(cha_y, cha_x, pho_y, pho_x, state);

	hash_4d* m = hashstate_list[cho][han];
	hash_4d::iterator itCur;
	pair<hash_4d::iterator, hash_4d::iterator> it_pair;
	it_pair = m->equal_range(pair_key(Cha_pos(cha_y, cha_x), Pho_pos(pho_y, pho_x)));

	for (itCur = it_pair.first; itCur != it_pair.second; itCur++) {
		if (!Diff_State(itCur->second, state))
			return itCur->second;
	}

	return NULL;
}

// µÎ state°¡ °°?ºÁö ´Ù¸¥Áö È®?ÎÇÏ´Â ÇÔ¼ö.
bool Adjcency_grpah::Diff_State(State_node *stateA, State_node *stateB) {
	if (stateA->GetTurn()->Gethost() != stateB->GetTurn()->Gethost())
		return true;

	for (int i = 1; i < HEIGHT_SIZE; i++)
		for (int j = 1; j < WIDTH_SIZE; j++) {
			if (stateA->GetState()[i][j] != stateB->GetState()[i][j])
				return true;
		}
	return false;
}

const bool Adjcency_grpah::operator==(Adjcency_grpah *graph) {
	if (memcmp(this->hashstate_list, graph->hashstate_list, sizeof(hash_4d*) * NUMUNIT * NUMUNIT)) {
		return false;
	}
	else if (!(this->root->operator==(graph->GetRoot()))) {
		return false;
	}
	else
		return true;
}

Second_Graph::Second_Graph(Adjcency_grpah *g) {
	original_g = new Adjcency_grpah(g);
}

void Second_Graph::Value_process(gameVectors state, int winner) {

	if (winner == DRAW)
		return;

	State_node *now_state = new State_node();
	State_node *prev_state = new State_node();
	State_node *prev2_state = new State_node();
	State_node *next2_state = new State_node();
	stateCondition *nowTurn = new stateCondition() ;

	char actor_prev;
	bool preHost;
	int prevActor;

	for (int i = 1; i < state->size(); i++) {
		now_state = state->at(i);
		nowTurn = now_state->GetTurn() ;

		prev_state = GetPrev_state(state, i);
		prev2_state = GetPrev_state(state, i - 1);
		char actor = nowTurn->GetActor();
		char killed = nowTurn->GetKilled();
		bool checkmate = nowTurn->GetCheckmate();
		bool host = (bool)nowTurn->Gethost();

		actor_prev = prev_state->GetTurn()->GetActor();
		preHost = prev_state->GetTurn()->Gethost();

		if (actor_prev != FIRST_PIECE)
			prevActor = idxOfPiece(actor_prev);

		if (actor == REST_PIECE) {
			if (actor_prev != FIRST_PIECE)
				prev_state->WeightCalculate(prevActor, rester_eval, preHost);
		}
		else {// killed and checkmate´Â ÃÖ¼Ò 3¼ö ?Ì»ó µÇ¾î¾ß °¡´ÉÇÏ¹Ç·Î prev_state¿¡ ´ëÇØ ¿¹¿ÜÃ³¸®´Â ÇÏÁö ¾Ê´Â´Ù.
			int nowActor = idxOfPiece(actor);
			int sumOfPrevEval = moving_eval;
			int sumOfPrev2Eval = 0;

			if (killed != '0') {
				sumOfPrevEval += killer_eval ;
				sumOfPrev2Eval += killee_eval ;
			}
			if (checkmate) {
				sumOfPrevEval += checkmater_eval ;
				sumOfPrev2Eval += checkmatee_eval ;
			}

			prev_state->WeightCalculate(nowActor, sumOfPrevEval, host);
			prev2_state->WeightCalculate(prevActor, sumOfPrev2Eval, !host);

		}

	}

	// °¢ ÆÇ¿¡ ´ëÇÑ Æò°¡.
	for (int i = 1; i < state->size(); i++) {
		state->at(i)->evaluateBoard();
	}	

	bool host;
	int reward_start = state->size() - 3;

	//backpropagation
	for (int i = reward_start; i >= 1; i--) {
		now_state = state->at(i);
		host = now_state->GetTurn()->Gethost();
		next2_state = GetNext_state(state, i + 1);

		double sumOfScore = now_state->GetScore() ;
		double addScore = next2_state->GetScore() * learning_rate ;

		if (host != (bool)winner) {
			sumOfScore -= addScore*2 ;			
		}
		now_state->SetScore(sumOfScore);
	}
}

void Adjcency_grpah::AddMoveableChild(State_node *now_state) {
	int cho = now_state->Getcho();
	int han = now_state->Gethan();
	string stringKey = GetMovableKey(now_state);

	int getNextsize = now_state->Getnumnext();
	int lengthOfKey = stringKey.length()-1 ;


	if (stringKey.at(lengthOfKey) == '0') {
		stringKey.at(lengthOfKey) = '1' ;
	}
	else
		stringKey.at(lengthOfKey) = '0' ;	

	bool host = now_state->GetTurn()->Gethost();
	movableHash *m = moveableHash[cho][han];
	movableHash::iterator itCur;
	State_node *candidate_state;
	pair<movableHash::iterator, movableHash::iterator> it_pair;
	it_pair = m->equal_range(stringKey);

	for (itCur = it_pair.first; itCur != it_pair.second; itCur++) {
		candidate_state = itCur->second;

		if (moveable(now_state->GetState(), candidate_state->GetState(), host)) {
			for (int i = 0; i < getNextsize ; i++) {
				if (!Diff_State(now_state->Getnext()->at(i), candidate_state))
					break;
				else if (i == getNextsize - 1)
					now_state->Addlist_Child(candidate_state);
			}
		}
	}

}

void Adjcency_grpah::AddMoveable() {
	queue<State_node*> *q = new queue<State_node*>();
	State_node *now_state;
	int* bfs_check = new int[statenode_num + 1];

	for (int i = 0; i <= statenode_num; i++) {
		bfs_check[i] = i;
	}
	q->push(root);

	try{
		while (!q->empty()) {
			now_state = q->front();
			q->pop();

			if (now_state != root)
				AddMoveableChild(now_state);

			for (int i = 0; i < now_state->Getnumnext(); i++) {
				int bfsCheckingidx = now_state->NthCheck_Childnode(i)->GetState_number() ;
				if (bfs_check[bfsCheckingidx] != -1) {
					bfs_check[bfsCheckingidx] = -1;
					q->push(now_state->NthCheck_Childnode(i));
				}
			}
		}
	}			
	catch(exception e){
		now_state->Print_State() ;
		cerr << e.what() ;
	}
	cout << "MOVEABLE COMPLETE" << endl ;
}

Adjcency_grpah * Second_Graph::Getgraph() {
	return original_g;
}

State_node* Second_Graph::GetPrev_state(gameVectors state, int index) {
	if (index >= 1)
		return state->at(index - 1);
	return NULL;
}

State_node* Second_Graph::GetNext_state(gameVectors state, int index) {
	if (index <= state->size() - 2)
		return state->at(index + 1);
	return NULL;
}

int Second_Graph::idxOfPiece(char piece) {
	switch (piece)
	{
	case 'c': case 'C':
		return CHA;
	case 'p': case 'P':
		return PHO;
	case 'h': case 'H':
		return HORSE;
	case 'x': case 'X':
		return SANG;
	case 's': case 'S':
		return SA;
	case 'j': case 'J':
		return JOL;
	case 'k': case 'K':
		return KING;
	case '-':
		return NONE;
	default:
		cerr << "idxOfPiece error" << endl;
		cerr << piece << "<- ¹®Á¦" << endl;
		return ERROR_CODE;
	}
}

