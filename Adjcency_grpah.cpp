#include "Adjcency_grpah.h"
#include "Moveable.h"

const double rester_eval = 0.001;
const double moving_eval = 0.0001;
const double killer_eval = 0.01;
const double killee_eval = -0.01;
const double checkmater_eval = 0.005;
const double checkmatee_eval = -0.01;
const double learning_rate = 0.5;

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
//	leaf = NULL;

}
//Reload Serialize를 위한 깊은 복사 생성자
Adjcency_grpah::Adjcency_grpah(Adjcency_grpah &graph) {
	root = graph.root;
//	leaf = graph.leaf;
	Init_hashtable();
	statenode_num = graph.statenode_num;
	memcpy(hashstate_list, graph.hashstate_list, sizeof(hash_4d*) * NUMUNIT * NUMUNIT);
}
//Save Serialize를 위한 깊은 복사 생성자
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

		// 자기 자식과 같은게 있으면 그대로 이동.
		if (childnode >= 0) {
			now_state = now_state->NthCheck_Childnode(childnode);
		}
		else {
			// 자기 자식과 같은게 없지만 어떤 노드에 존재하면 그 노드를 next로 지정한다.
			State_node* check_node = Is_In_The_List_State(add_state);
			if (check_node) {
				now_state->Addlist_Child(check_node);
				check_node->Connect_Parent(now_state);
				now_state = check_node;
			}
			else {
				PushList_Hashtable(add_state);
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
		// 자기 자식과 같은게 있으면 그대로 이동.
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

	cout << " 스테이트 번호 , 방문 횟수 " << endl;
	while (!q->empty()) {
		temp = q->front();
		q->pop();
		stream << "state 번호 : " << temp->GetState_number() << " 방문 횟수 : " << temp->GetTravelcount() << endl;
		stream << temp->GetTurn()->Gethost() << ", " << "score : " << temp->GetScore() << ", 하위자식 " << temp->Getnumnext() << endl; // 0이면 초, 1이면 한.
		// 초에 state이면 다음 차례는 한 이므로 한에 대한 weight를 기재.
		for (int i = 0; i < 7; i++) {
			if(temp->GetTurn()->Gethost() == 0)
				stream << temp->Get_hanweight()->at(i) << " ";
			else
				stream << temp->Get_choweight()->at(i) << " ";
		}
		// 하드코딩 지우자

		//stream << endl;
		//stream << "공격자 " << temp->GetTurn()->Gethost() << endl;
		//for (int i = 1; i < HEIGHT_SIZE; i++) {
		//	for (int j = 1; j < WIDTH_SIZE; j++) {
		//		stream << temp->GetState()[i][j] << " ";
		//	}
		//	stream << endl;
		//}

		//for (int i = 0; i < temp->Getnumnext(); i++) {
		//	stream << "-------------------------------------" << endl;
		//	stream << "공격자 " << temp->Getnext()->at(i)->GetTurn()->Gethost() << endl;
		//	for (int j = 1; j < HEIGHT_SIZE; j++) {
		//		for (int k = 1; k < WIDTH_SIZE; k++) {
		//			stream << temp->Getnext()->at(i)->GetState()[j][k]<< " ";
		//		}
		//		stream << endl;
		//	}
		//}

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

// 현재 위치한 노드에서의 자식노드와 추가할 state와 같은게 있는지.
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

// 현재 노드 state가 그래프로 존재하고 있는지
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
		if (!Diff_State(itCur->second, state) )
			return itCur->second;
	}

	return NULL;
}

// 두 state가 같은지 다른지 확인하는 함수.
bool Adjcency_grpah::Diff_State(State_node *stateA, State_node *stateB) {
	if ( stateA->GetTurn()->Gethost() != stateB->GetTurn()->Gethost())
		return true ;
	for (int i = 1; i < HEIGHT_SIZE; i++)
		for (int j = 1; j < WIDTH_SIZE; j++) {
			if (stateA->GetState()[i][j] != stateB->GetState()[i][j] )
				return true;
		}
	return false  ;
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
		prev2_state = GetPrev_state(state, i-1);
		char actor = now_state->GetTurn()->GetActor();
		char killed = now_state->GetTurn()->GetKilled();
		bool checkmate = now_state->GetTurn()->GetCheckmate();
		bool host = (bool)now_state->GetTurn()->Gethost() ;

		/*지우자*/
		/*cout << i << endl;
		now_state->Print_State();
		cout << now_state->Getcho() << " " << now_state->Gethan() << endl; */

		actor_prev = prev_state->GetTurn()->GetActor();
		host_prev = prev_state->GetTurn()->Gethost();	

		// 첫 수가 아닐때.
		if(actor_prev != FIRST_PIECE)
			prev_actor_piece = idxOfPiece(actor_prev);

		/*Top Down 평가*/
 		if (actor == REST_PIECE) {
		//	cout << "한수쉼" << endl;
			// 연속 한수쉼이 아닌 경우만 !!
			if(actor_prev != FIRST_PIECE)
				prev_state->WeightCalculate(prev_actor_piece, rester_eval, host_prev);
		}
		else {// killed and checkmate는 최소 3수 이상 되어야 가능하므로 prev_state에 대해 예외처리는 하지 않는다.
			// 움직임 자체에 대해 점수를 준다.
			int now_actor_piece = idxOfPiece(actor);
			prev_state->WeightCalculate(now_actor_piece, moving_eval, host);
			if (killed != '0') {
				// 이전 스테이트에서 현재 actor 대한 가치를 높인다
				prev_state->WeightCalculate(now_actor_piece, killer_eval, host);
				prev2_state->WeightCalculate(prev_actor_piece, killee_eval, !host);
			}
			if (checkmate) {
				// 이전 스테이트에서 현재 actor 대한 가치를 높인다
				prev_state->WeightCalculate(now_actor_piece, checkmater_eval, host);
				prev2_state->WeightCalculate(prev_actor_piece, checkmatee_eval, !host);
			}
		}
	}

	// 각 판에 대한 평가.
	for (int i = 1; i < state->size(); i++) {
		state->at(i)->evaluateBoard();
	}

	/*Bottom Up 보상*/
	if (winner == DRAW)
		return;

	bool host;
	int reward_start = state->size() - 3;

	for (int i = reward_start ; i >= 1; i--) {
		now_state = state->at(i);
		host = now_state->GetTurn()->Gethost();
		next2_state = GetNext_state(state, i+1);
	    if (host == (bool)winner) {
			now_state->SetScore(now_state->GetScore() + next2_state->GetScore() * learning_rate);
		}
		else {
			now_state->SetScore(now_state->GetScore() - next2_state->GetScore() * learning_rate);
		}
	}
}
//
//void Adjcency_grpah::AddMoveableChild(State_node *now_state) {
//	int cho = now_state->Getcho();
//	int han = now_state->Gethan();
//	int cha_y, cha_x, pho_y, pho_x;
//	bool host = now_state->GetTurn()->Gethost();
//	Set_4Dhashdata(cha_y, cha_x, pho_y, pho_x, now_state);
//
//	hash_4d* m = hashstate_list[cho][han];
//	hash_4d::iterator itCur;
//	State_node *candidate_state;
//	// 잡히지 않은 경우.
//	for (itCur = m->begin(); itCur != m->end(); itCur++) {
//		candidate_state = itCur->second;
//		if (host != candidate_state->GetTurn()->Gethost())
//			if (moveable(now_state->GetState(), candidate_state->GetState(), host)) {
//				for (int i = 0; i < now_state->Getnumnext(); i++) {
//					if (!Diff_State(now_state->Getnext()->at(i), candidate_state))
//						break; 
//					else if (i == now_state->Getnumnext() - 1 )
//						now_state->Addlist_Child(candidate_state);
//				}
//			}
//	}
//
//	if (host == CHO_PLAY) {
//		cho--;
//		m = hashstate_list[cho][han]; 
//		for (itCur = m->begin(); itCur != m->end(); itCur++) {
//			candidate_state = itCur->second;
//			if (CHO_PLAY != candidate_state->GetTurn()->Gethost())
//				if (moveable(now_state->GetState(), candidate_state->GetState(), host)) {
//					for (int i = 0; i < now_state->Getnumnext(); i++) {
//						if (!Diff_State(now_state->Getnext()->at(i), candidate_state))
//							break;
//						else if (i == now_state->Getnumnext() - 1)
//							now_state->Addlist_Child(candidate_state);
//					}
//				}
//		}
//	}
//	// host == HAN_PLAY
//	else {
//		han--;
//		m = hashstate_list[cho][han]; 
//		for (itCur = m->begin(); itCur != m->end(); itCur++) {
//			if (HAN_PLAY != candidate_state->GetTurn()->Gethost())
//				if (moveable(now_state->GetState(), candidate_state->GetState(),host)) {
//					for (int i = 0; i < now_state->Getnumnext(); i++) {
//						if (!Diff_State(now_state->Getnext()->at(i), candidate_state))
//							break;
//						else if (i == now_state->Getnumnext() - 1)
//							now_state->Addlist_Child(candidate_state);
//					}
//				}
//		}
//	}
//	
//}
//
//void Adjcency_grpah::AddMoveable() {
//	
//	queue<State_node*> *q = new queue<State_node*>();
//	State_node *now_state;
//	int* bfs_check = new int[statenode_num + 1];
//	for (int i = 0; i <= statenode_num; i++) {
//		bfs_check[i] = i;
//	}
//	q->push(root);
//	int n = 0;
//	while (!q->empty()) {
//		now_state = q->front();
//		q->pop();
//		n++;
//		if (n % 10 == 0)
//			cout << n <<"번째 moveable" << endl;
//		if(now_state != root)
//			AddMoveableChild(now_state);
//		
//		for (int i = 0; i < now_state->Getnumnext(); i++) {
//			if (bfs_check[now_state->NthCheck_Childnode(i)->GetState_number()] != -1) {
//				bfs_check[now_state->NthCheck_Childnode(i)->GetState_number()] = -1;
//				q->push(now_state->NthCheck_Childnode(i));
//			}
//		}
//	}
//}

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
		return 0;
	case 'p': case 'P':
		return 1;
	case 'h': case 'H':
		return 2;
	case 'x': case 'X':
		return 3;
	case 's': case 'S':
		return 4;
	case 'j': case 'J':
		return 5;
	case 'k': case 'K':
		return 6;
	case '-':
		return 7;
	default :
		cerr << "idxOfPiece error" << endl;
		cerr << piece << "<- 문제" << endl;
		return ERROR_CODE ;
	}
}

