#include "Adjcency_grpah.h"
#include "Moveable.h"

movableHash *moveableHash[NUM_OF_TEAM_PIECE][NUM_OF_TEAM_PIECE];

int pow(int var, int exp) {
	int ans = 1;
	for (int i = 0; i < exp; i++) {
		ans *= var;
	}
	return ans;
}

// init hash table
void Adjcency_grpah::initMovableHash() {
	for (int i = 0; i < NUM_OF_TEAM_PIECE; i++) {
		for (int j = 0; j < NUM_OF_TEAM_PIECE; j++) {
			moveableHash[i][j] = new movableHash();
		}
	}
}

int Adjcency_grpah::convertKeyhash(int key, int key_index) {
	int indexKey = MOVABLE_KEY - 2 - key_index;
	int ten = 10;
	int regulatekey = pow(ten, indexKey);

	if ( (key / regulatekey) % ten == 0) {
		return NULL;
	}

	key -= regulatekey;
	return key;
}

string Adjcency_grpah::getMovableKey(stateNode* nowState) {
	string stringKey = "" ;
	int numofPiece[NUM_OF_PIECE] = {0} ;
	nowState->setNumOfPiece(numofPiece);

	for(int i=0; i < NUM_OF_PIECE/2; i++){
		numofPiece[i] += numofPiece[i+7] ;
	}
	
	stringKey.append(to_string(numofPiece[CHA])) ;
	stringKey.append(to_string(numofPiece[PHO])) ;
	stringKey.append(to_string(numofPiece[HORSE])) ;
	stringKey.append(to_string(numofPiece[SANG])) ;
	stringKey.append(to_string(numofPiece[SA])) ;
	stringKey.append(to_string(numofPiece[JOL])) ;
	stringKey.append(to_string(nowState->GetTurn()->Gethost())) ;
	return  stringKey;
}
// movable hash table.
void Adjcency_grpah::insertMovableHash(stateNode* nowState) {
	int cho = nowState->Getcho();
	int han = nowState->Gethan();
	moveableHash[cho][han]->insert(movableHash::value_type(getMovableKey(nowState), nowState));
}

Adjcency_grpah::Adjcency_grpah() {

	char Init_jannggi[HEIGHT_SIZE][WIDTH_SIZE];
	for (int i = 0; i < HEIGHT_SIZE; i++) {
		memset(Init_jannggi[i], 'X', sizeof(char)*WIDTH_SIZE);
	}

	root = new stateNode(Init_jannggi);
	root->Set_numUnit(0, 0);
	statenode_num = 0;
	initHashtable();
	pushToHashtable(root);
	root->SetState_number(0);
	initMovableHash();
}
//Reload Serialize¸
Adjcency_grpah::Adjcency_grpah(const Adjcency_grpah &graph) {
	root = graph.root;
	initHashtable();
	statenode_num = graph.statenode_num;
	memcpy(hashstate_list, graph.hashstate_list, sizeof(hash_4d*) * NUM_OF_TEAM_PIECE * NUM_OF_TEAM_PIECE);
}
//Save Serialize¸
Adjcency_grpah::Adjcency_grpah(Adjcency_grpah *graph) {
	root = graph->root;
	initHashtable();
	statenode_num = graph->statenode_num;
	memcpy(hashstate_list, graph->hashstate_list, sizeof(hash_4d*) * NUM_OF_TEAM_PIECE * NUM_OF_TEAM_PIECE);
}
void Adjcency_grpah::initHashtable () {
	for (int i = 0; i < NUM_OF_TEAM_PIECE; i++) {
		for (int j = 0; j < NUM_OF_TEAM_PIECE; j++) {
			hashstate_list[i][j] = new hash_4d();
		}
	}
}

// insert state node in hash table
void Adjcency_grpah::pushToHashtable(stateNode* state) {
	int cho = state->Getcho();
	int han = state->Gethan();
	int key[4] ;
	Set_4Dhashdata(key, state);
	hashstate_list[cho][han]->insert(hash_4d::value_type(pair_key(Cha_pos(key[0], key[1]), Pho_pos(key[2], key[3])), state));
}

// graph generalized
void Adjcency_grpah::Insert(vector<stateNode*>*  state) {
	stateNode *nowState = root;

	for (int index = 0; index < state->size(); index++) {
		stateNode* add_state = state->at(index);
		int childnode = IsHaveChildnode(nowState, add_state);

		if (childnode >= 0) 
			nowState = nowState->NthCheck_Childnode(childnode);
		else {
			stateNode* check_node = IsHaveStateInHash(add_state);
			if (check_node) {
				nowState->Addlist_Child(check_node);
				check_node->Connect_Parent(nowState);
				nowState = check_node;
			}
			else {
				pushToHashtable(add_state);
				insertMovableHash(add_state);
				add_state->SetState_number(++statenode_num);
				nowState->Addlist_Child(add_state);
				add_state->Connect_Parent(nowState);
				add_state->Set_Stateorder(nowState->GetNext()->size());
				nowState = add_state;
			}
		}
		state_stack.push(nowState);
		nowState->TravelCountPlus();
	}
}
// second Insert process
void Adjcency_grpah::secondInsert(vector<stateNode*>*  state) {
	stateNode *nowState = root;

	for (int index = 0; index < state->size(); index++) {
		stateNode* add_state = state->at(index);

		int childnode = IsHaveChildnode(nowState, add_state);
		nowState = nowState->NthCheck_Childnode(childnode);
		state->at(index) = nowState;
	}
}
// set up key value
void Adjcency_grpah::Set_4Dhashdata(int key[4], stateNode* state) {
	key[0] = state->GetPieceOfKey().first.first;
	key[1] = state->GetPieceOfKey().first.second;
	key[2] = state->GetPieceOfKey().second.first;
	key[3] = state->GetPieceOfKey().second.second;
}


stateNode* Adjcency_grpah::GetRoot() {
	return root;
}

stateNode* Adjcency_grpah::GetLeaf() {
	return leaf;
}

// return sequence num of child node state.
int Adjcency_grpah::IsHaveChildnode(stateNode* sub_root, stateNode* state) {
	for (int i = 0; i < sub_root->SizeofNext(); i++)
		if (!Diff_State(sub_root->NthCheck_Childnode(i), state))
			return i;
	return -1;
}

// check whether state is in hash or not.
stateNode* Adjcency_grpah::IsHaveStateInHash(stateNode *state) {

	int cho = state->Getcho();
	int han = state->Gethan();
	int key[4] ;
	Set_4Dhashdata(key, state);

	hash_4d* m = hashstate_list[cho][han];
	hash_4d::iterator itCur;
	pair<hash_4d::iterator, hash_4d::iterator> it_pair;
	it_pair = m->equal_range(pair_key(Cha_pos(key[0], key[1]), Pho_pos(key[2], key[3])));

	for (itCur = it_pair.first; itCur != it_pair.second; itCur++) {
		if (!Diff_State(itCur->second, state))
			return itCur->second;
	}

	return NULL;
}

// when stateA and stateB are different, return true 
bool Adjcency_grpah::Diff_State(stateNode *stateA, stateNode *stateB) {
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
	if (memcmp(this->hashstate_list, graph->hashstate_list, sizeof(hash_4d*) * NUM_OF_TEAM_PIECE * NUM_OF_TEAM_PIECE)) {
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
// I think it is better than devide function under 20 line.
void Second_Graph::adjustWeight(vector<stateNode*>* state){

	stateNode *nowState,*prevState,*prev2State ;
	stateCondition *nowTurn = new stateCondition() ;

	char previousActor, nowActor, killed ;
	bool preHost, checkmate, host;
	int prevActorIdx;

	for (int i = 1; i < state->size(); i++) {
		nowState = state->at(i);		
		nowTurn = nowState->GetTurn() ;

		prevState = getPrevState(state, i);
		prev2State = getPrevState(state, i - 1);

		nowActor = nowTurn->GetActor();
		host = (bool)nowTurn->Gethost();

		previousActor = prevState->GetTurn()->GetActor();
		preHost = prevState->GetTurn()->Gethost();

		if (previousActor != FIRST_PIECE)
			prevActorIdx = idxOfPiece(previousActor);

		if (nowActor == REST_PIECE) {
			if (previousActor != FIRST_PIECE)
				prevState->WeightCalculate(prevActorIdx, RESTER_EVAL, preHost);
		}
		else {// killed and checkmate
			int nowActorIdx = idxOfPiece(nowActor);
			int sumOfPrevEval = MOVING_EVAL;
			int sumOfPrev2Eval = 0;
			if (nowTurn->GetKilled() != '0') {
				sumOfPrevEval += KILLER_EVAL ;
				sumOfPrev2Eval += KILLEE_EVAL ;
			}
			if (nowTurn->GetCheckmate()) {
				sumOfPrevEval += CHECKMATER_EVAL ;
				sumOfPrev2Eval += CHECKMATEE_EVAL ;
			}

			prevState->WeightCalculate(nowActorIdx, sumOfPrevEval, host);

			if(prev2State)
				prev2State->WeightCalculate(prevActorIdx, sumOfPrev2Eval, !host);

		}

	}
}

void Second_Graph::Evaluating(vector<stateNode*>* state){
	for (int i = 1; i < state->size(); i++) {
		state->at(i)->evaluateBoard();
	}	
}

void Second_Graph::backPropagation(vector<stateNode*>* state, int winner){
	int reward_start = state->size() - 3;
	stateNode *nowState, *next2State ;
	bool host ;
	double sumOfScore, addScore ;

	//backpropagation
	for (int i = reward_start; i >= 1; i--) {
		nowState = state->at(i);
		host = nowState->GetTurn()->Gethost();
		next2State = getNextState(state, i + 1);
		sumOfScore = nowState->GetScore() ;
		addScore = next2State->GetScore() * LEARNING_RATE ;

		if (host != (bool)winner) {
			sumOfScore -= addScore*3 ;			
		}
		nowState->SetScore(sumOfScore + addScore);
	}
}

void Second_Graph::learnProcess(vector<stateNode*>* state, int winner) {

	adjustWeight(state) ;
	Evaluating(state) ;
	// if the game was draw, then we don't give any scores.
	if (winner == DRAW)
		return;
	backPropagation(state, winner); 
}
// Add child nodes that are not currently registered in the state but are movable on the graph to the child list
void Adjcency_grpah::AddMoveableChild(stateNode *nowState) {
	int cho = nowState->Getcho();
	int han = nowState->Gethan();
	string stringKey = getMovableKey(nowState);
	int getNextsize = nowState->SizeofNext();
	int lengthOfKey = stringKey.length()-1 ;
	bool host = nowState->GetTurn()->Gethost();
	// when now turn is CHO, than next turn is Han. our goal is next state. So when this turn is CHO, next must be CHO
	// It is not perfect function.
	stringKey.at(lengthOfKey) = (stringKey.at(lengthOfKey) == CHO_KEY ? HAN_KEY : CHO_KEY) ;
	movableHash::iterator itCur;
	pair<movableHash::iterator, movableHash::iterator> it_pair = moveableHash[cho][han]->equal_range(stringKey);

	for (itCur = it_pair.first; itCur != it_pair.second; itCur++) {
	  stateNode *candidate_state = itCur->second;

		Moveable move(nowState->GetState(), candidate_state->GetState(), host);
		if (startMoveable(move)) {
			for (int i = 0; i < getNextsize ; i++) {
				if (!Diff_State(nowState->GetNext()->at(i), candidate_state)) break;
				else if (i == getNextsize - 1)
					nowState->Addlist_Child(candidate_state);
			}
		}
	}

}

void Adjcency_grpah::movableByBFS(int *bfs_check){
	stateNode *nowState;
	queue<stateNode*> *q = new queue<stateNode*>();
	q->push(root);
	while (!q->empty()) {
			nowState = q->front(); q->pop();
			if (nowState != root)
				AddMoveableChild(nowState);

			for (int i = 0; i < nowState->SizeofNext(); i++) {
				int bfsCheckingidx = nowState->NthCheck_Childnode(i)->GetState_number() ;
				if (bfs_check[bfsCheckingidx] != -1) {
					bfs_check[bfsCheckingidx] = -1;
					q->push(nowState->NthCheck_Childnode(i));
				}
			}
	}
	delete(q) ;
}

void Adjcency_grpah::AddMoveable() {
	int* bfs_check = new int[statenode_num + 1];
	for (int i = 0; i <= statenode_num; i++) {
		bfs_check[i] = i;
	}

	try{
		movableByBFS(bfs_check); 
	}			
	catch(exception e){
		cerr << e.what() ;
	}
	cout << "MOVEABLE COMPLETE" << endl ;
}

Adjcency_grpah * Second_Graph::Getgraph() {
	return original_g;
}

stateNode* Second_Graph::getPrevState(vector<stateNode*>*  state, int index) {
	if (index >= 1)
		return state->at(index - 1);
	return NULL;
}

stateNode* Second_Graph::getNextState(vector<stateNode*>*  state, int index) {
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
		return ERROR_CODE;
	}
}

