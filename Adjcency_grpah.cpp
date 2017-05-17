#include "Adjcency_grpah.h"
#include "Moveable.h"

const double rester_eval = 0.001;
const double moving_eval = 0.0001;
const double killer_eval = 0.01;
const double killee_eval = -0.01;
const double checkmater_eval = 0.005;
const double checkmatee_eval = -0.01;
const double learning_rate = 0.5;

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

string Adjcency_grpah::getMovableKey(State_node* now_state) {
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
	moveableHash[cho][han]->insert(movableHash::value_type(getMovableKey(now_state), now_state));
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

	//	leaf = NULL;

}
//Reload Serialize¸¦ À§ÇÑ ±íÀº º¹»ç »ý¼ºÀÚ
Adjcency_grpah::Adjcency_grpah(const Adjcency_grpah &graph) {
	root = graph.root;
	//	leaf = graph.leaf;
	Init_hashtable();
	statenode_num = graph.statenode_num;
	memcpy(hashstate_list, graph.hashstate_list, sizeof(hash_4d*) * NUMUNIT * NUMUNIT);
}
//Save Serialize¸¦ À§ÇÑ ±íÀº º¹»ç »ý¼ºÀÚ
Adjcency_grpah::Adjcency_grpah(Adjcency_grpah *graph) {
	root = graph->root;
	//	leaf = graph->leaf;
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


void Adjcency_grpah::Insert(vector<State_node*>* state) {
	State_node *now_state = root;

	for (int index = 0; index < state->size(); index++) {
		State_node* add_state = state->at(index);

		int childnode = Is_Have_childnode(now_state, add_state);

		// ÀÚ±â ÀÚ½Ä°ú °°Àº°Ô ÀÖÀ¸¸é ±×´ë·Î ÀÌµ¿.
		if (childnode >= 0) {
			now_state = now_state->NthCheck_Childnode(childnode);
		}
		else {
			// ÀÚ±â ÀÚ½Ä°ú °°Àº°Ô ¾øÁö¸¸ ¾î¶² ³ëµå¿¡ Á¸ÀçÇÏ¸é ±× ³ëµå¸¦ next·Î ÁöÁ¤ÇÑ´Ù.
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
	//	leaf = now_state;
}

void Adjcency_grpah::Second_insert(vector<State_node*>* state) {
	State_node *now_state = root;

	for (int index = 0; index < state->size(); index++) {
		State_node* add_state = state->at(index);

		int childnode = Is_Have_childnode(now_state, add_state);
		// ÀÚ±â ÀÚ½Ä°ú °°Àº°Ô ÀÖÀ¸¸é ±×´ë·Î ÀÌµ¿.
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


void Adjcency_grpah::Travelgraph_bfs() {
	ofstream stream("output.txt");
	queue<State_node*> *q = new queue<State_node*>();
	State_node *temp;
	int* bfs_check = new int[statenode_num + 1];
	for (int i = 0; i <= statenode_num; i++) {
		bfs_check[i] = i;
	}
	q->push(root);

	cout << " ½ºÅ×ÀÌÆ® ¹øÈ£ , ¹æ¹® È½¼ö " << endl;

	while (!q->empty()) {
		temp = q->front();
		q->pop();
		stream << "state ¹øÈ£ : " << temp->GetState_number() << " ¹æ¹® È½¼ö : " << temp->GetTravelcount() << endl;
		stream << temp->GetTurn()->Gethost() << ", " << "score : " << temp->GetScore() << ", ÇÏÀ§ÀÚ½Ä " << temp->Getnumnext() << endl; // 0ÀÌ¸é ÃÊ, 1ÀÌ¸é ÇÑ.
		// ÃÊ¿¡ stateÀÌ¸é ´ÙÀ½ Â÷·Ê´Â ÇÑ ÀÌ¹Ç·Î ÇÑ¿¡ ´ëÇÑ weight¸¦ ±âÀç.
		for (int i = 0; i < 7; i++) {
			if (temp->GetTurn()->Gethost() == 0)
				stream << temp->Get_hanweight()->at(i) << " ";
			else
				stream << temp->Get_choweight()->at(i) << " ";
		}
		// ÇÏµåÄÚµù Áö¿ìÀÚ

		// stream << endl;
		// stream << "°ø°ÝÀÚ " << temp->GetTurn()->Gethost() << endl;
		// for (int i = 1; i < HEIGHT_SIZE; i++) {
		// 	for (int j = 1; j < WIDTH_SIZE; j++) {
		// 		stream << temp->GetState()[i][j] << " ";
		// 	}
		// 	stream << endl;
		// }

		// for (int i = 0; i < temp->Getnumnext(); i++) {
		// 	stream << "-------------------------------------" << endl;
		// 	stream << "°ø°ÝÀÚ " << temp->Getnext()->at(i)->GetTurn()->Gethost() << endl;
		// 	for (int j = 1; j < HEIGHT_SIZE; j++) {
		// 		for (int k = 1; k < WIDTH_SIZE; k++) {
		// 			stream << temp->Getnext()->at(i)->GetState()[j][k]<< " ";
		// 		}
		// 		stream << endl;
		// 	}
		// }

		stream << endl << endl;
		for (int i = 0; i < temp->Getnumnext(); i++) {
			if (bfs_check[temp->NthCheck_Childnode(i)->GetState_number()] != -1) {
				bfs_check[temp->NthCheck_Childnode(i)->GetState_number()] = -1;
				q->push(temp->NthCheck_Childnode(i));
			}
		}
	}
	stream.close();
}

State_node* Adjcency_grpah::getRoot() {
	return root;
}

State_node* Adjcency_grpah::getLeaf() {
	return leaf;
}

// ÇöÀç À§Ä¡ÇÑ ³ëµå¿¡¼­ÀÇ ÀÚ½Ä³ëµå¿Í Ãß°¡ÇÒ state¿Í °°Àº°Ô ÀÖ´ÂÁö.
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

// ÇöÀç ³ëµå state°¡ ±×·¡ÇÁ·Î Á¸ÀçÇÏ°í ÀÖ´ÂÁö
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

// µÎ state°¡ °°ÀºÁö ´Ù¸¥Áö È®ÀÎÇÏ´Â ÇÔ¼ö.
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
	else if (!(this->root->operator==(graph->getRoot()))) {
		return false;
	}
	//else if (!(this->leaf->operator==(graph->getLeaf()))) {
	//	return false;
	//}
	else
		return true;
}

Second_Graph::Second_Graph(Adjcency_grpah *g) {
	original_g = new Adjcency_grpah(g);
}

void Second_Graph::Value_process(vector<State_node*>* state, int winner) {

	State_node *now_state = new State_node();
	State_node *prev_state = new State_node();
	State_node *prev2_state = new State_node();
	State_node *next2_state = new State_node();
	char actor_prev;
	bool host_prev;
	int prev_actor_piece;
	for (int i = 1; i < state->size(); i++) {
		now_state = state->at(i);
		prev_state = GetPrev_state(state, i);
		prev2_state = GetPrev_state(state, i - 1);
		char actor = now_state->GetTurn()->GetActor();
		char killed = now_state->GetTurn()->GetKilled();
		bool checkmate = now_state->GetTurn()->GetCheckmate();
		bool host = (bool)now_state->GetTurn()->Gethost();

		/*Áö¿ìÀÚ*/
		/*cout << i << endl;
		now_state->Print_State();
		cout << now_state->Getcho() << " " << now_state->Gethan() << endl; */

		actor_prev = prev_state->GetTurn()->GetActor();
		host_prev = prev_state->GetTurn()->Gethost();

		// Ã¹ ¼ö°¡ ¾Æ´Ò¶§.
		if (actor_prev != FIRST_PIECE)
			prev_actor_piece = idxOfPiece(actor_prev);

		/*Top Down Æò°¡*/
		if (actor == REST_PIECE) {
			//	cout << "ÇÑ¼ö½°" << endl;
				// ¿¬¼Ó ÇÑ¼ö½°ÀÌ ¾Æ´Ñ °æ¿ì¸¸ !!
			if (actor_prev != FIRST_PIECE)
				prev_state->WeightCalculate(prev_actor_piece, rester_eval, host_prev);
		}
		else {// killed and checkmate´Â ÃÖ¼Ò 3¼ö ÀÌ»ó µÇ¾î¾ß °¡´ÉÇÏ¹Ç·Î prev_state¿¡ ´ëÇØ ¿¹¿ÜÃ³¸®´Â ÇÏÁö ¾Ê´Â´Ù.
			// ¿òÁ÷ÀÓ ÀÚÃ¼¿¡ ´ëÇØ Á¡¼ö¸¦ ÁØ´Ù.
			int now_actor_piece = idxOfPiece(actor);
			prev_state->WeightCalculate(now_actor_piece, moving_eval, host);
			if (killed != '0') {
				// ÀÌÀü ½ºÅ×ÀÌÆ®¿¡¼­ ÇöÀç actor ´ëÇÑ °¡Ä¡¸¦ ³ôÀÎ´Ù
				prev_state->WeightCalculate(now_actor_piece, killer_eval, host);
				prev2_state->WeightCalculate(prev_actor_piece, killee_eval, !host);
			}
			if (checkmate) {
				// ÀÌÀü ½ºÅ×ÀÌÆ®¿¡¼­ ÇöÀç actor ´ëÇÑ °¡Ä¡¸¦ ³ôÀÎ´Ù
				prev_state->WeightCalculate(now_actor_piece, checkmater_eval, host);
				prev2_state->WeightCalculate(prev_actor_piece, checkmatee_eval, !host);
			}
		}
	}

	// °¢ ÆÇ¿¡ ´ëÇÑ Æò°¡.
	for (int i = 1; i < state->size(); i++) {
		state->at(i)->evaluateBoard();
	}

	/*Bottom Up º¸»ó*/
	if (winner == DRAW)
		return;

	bool host;
	int reward_start = state->size() - 3;

	for (int i = reward_start; i >= 1; i--) {
		now_state = state->at(i);
		host = now_state->GetTurn()->Gethost();
		next2_state = GetNext_state(state, i + 1);
		if (host == (bool)winner) {
			now_state->SetScore(now_state->GetScore() + next2_state->GetScore() * learning_rate);
		}
		else {
			now_state->SetScore(now_state->GetScore() - next2_state->GetScore() * learning_rate);
		}
	}
}

void Adjcency_grpah::AddMoveableChild(State_node *now_state) {
	int cho = now_state->Getcho();
	int han = now_state->Gethan();
	int getNextsize = now_state->Getnumnext();

	string stringKey = getMovableKey(now_state);
	if (stringKey.at(stringKey.length()-1) == '0') {
		stringKey.at(stringKey.length()-1) = '1' ;
	}
	else
		stringKey.at(stringKey.length()-1) = '0' ;	
	//int changeKey = NULL;
	bool host = now_state->GetTurn()->Gethost();
	movableHash *m = moveableHash[cho][han];
	movableHash::iterator itCur;
	State_node *candidate_state;
	pair<movableHash::iterator, movableHash::iterator> it_pair;
	it_pair = m->equal_range(stringKey);

	// ÀâÈ÷Áö ¾ÊÀº °æ¿ì.
	// °°Àº Å°¸¦ °°Àº ÇØ½¬ ºÎºÐÀ» Ã£À½.

	for (itCur = it_pair.first; itCur != it_pair.second; itCur++) {
		candidate_state = itCur->second;
		// ¹«ºê¾îºíÀÌ °¡´ÉÇÏ´Ù¸é, ÀÚ½Ä³ëµå¿Í °°Àº°Ô ¾ø´ÂÁö È®ÀÎÈÄ¿¡ ÀÚ½ÄÀ¸·Î.
		if (moveable(now_state->GetState(), candidate_state->GetState(), host)) {
			for (int i = 0; i < getNextsize ; i++) {
				if (!Diff_State(now_state->Getnext()->at(i), candidate_state))
					break;
				else if (i == getNextsize - 1)
					now_state->Addlist_Child(candidate_state);
			}
		}
	}

	// host°¡ CHO_PLAY¸é HANÀÇ °ø°ÝÂ÷·Ê.
	// if (host == CHO_PLAY) {
	// 	cho--;
	// }
	// else
	// 	han--;

	// m = moveableHash[cho][han];
	// for (int i = 0; i < MOVABLE_KEY -1 ; i++) {
	// 	changeKey = convertKeyhash(stringKey, i);
	// 	if (changeKey == NULL)
	// 		continue;

	// 	it_pair = m->equal_range(changeKey);

	// 	for (itCur = it_pair.first; itCur != it_pair.second; itCur++) {
	// 		candidate_state = itCur->second;
	// 		// ¹«ºê¾îºíÀÌ °¡´ÉÇÏ´Ù¸é, ÀÚ½Ä³ëµå¿Í °°Àº°Ô ¾ø´ÂÁö È®ÀÎÈÄ¿¡ ÀÚ½ÄÀ¸·Î.
	// 		if (moveable(now_state->GetState(), candidate_state->GetState(), host)) {
	// 			for (int i = 0; i < getNextsize ; i++) {
	// 				if (!Diff_State(now_state->Getnext()->at(i), candidate_state))
	// 					break;
	// 				else if (i == getNextsize - 1)
	// 					now_state->Addlist_Child(candidate_state);
	// 			}
	// 		}
	// 	}
	// }

}

void Adjcency_grpah::AddMoveable() {
	queue<State_node*> *q = new queue<State_node*>();
	State_node *now_state;
	int* bfs_check = new int[statenode_num + 1];
	for (int i = 0; i <= statenode_num; i++) {
		bfs_check[i] = i;
	}
	q->push(root);
	int n = 0;
	try{
		while (!q->empty()) {
			now_state = q->front();
			q->pop();
			n++;
			if (n % 1000 == 0)
				cout << "No." << n << " moveable" << endl;
			if (now_state != root)
				AddMoveableChild(now_state);

			for (int i = 0; i < now_state->Getnumnext(); i++) {
				if (bfs_check[now_state->NthCheck_Childnode(i)->GetState_number()] != -1) {
					bfs_check[now_state->NthCheck_Childnode(i)->GetState_number()] = -1;
					q->push(now_state->NthCheck_Childnode(i));
				}
			}
		}
	}			
	catch(exception e){
		cout << now_state->Getstate_ordernum() << " " << now_state->GetState_number() << endl ;
		now_state->Print_State() ;
		cerr << e.what() ;
	}
	cout << "MOVEABLE COMPLETE" << endl ;
}

Adjcency_grpah * Second_Graph::Getgraph() {
	return original_g;
}

State_node* Second_Graph::GetPrev_state(vector<State_node*>* state, int index) {
	if (index >= 1)
		return state->at(index - 1);
	return NULL;
}

State_node* Second_Graph::GetNext_state(vector<State_node*>* state, int index) {
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

