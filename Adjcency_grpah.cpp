#include "Adjcency_grpah.h"

Adjcency_grpah::Adjcency_grpah(){

	char Init_jannggi[HEIGHT_SIZE][WIDTH_SIZE] ;
	for(int i=0 ; i< HEIGHT_SIZE ; i++){
		memset(Init_jannggi[i], 'X', sizeof(char)*WIDTH_SIZE);
	}

	root = new State_node(Init_jannggi) ;
	root->Set_numUnit(0,0) ;
	statenode_num = 0;
	Init_hashtable();
	PushList_Hashtable(root) ;

	leaf = NULL ;
}
//수정 필요--------------------------------------------------------------------------------
//Serialize를 위한 깊은 복사 생성자
Adjcency_grpah::Adjcency_grpah(Adjcency_grpah &graph) {
	root = graph.root;
	memcpy(hashstate_list, graph.hashstate_list, sizeof(graph.hashstate_list));
	memcpy(&state_stack, &graph.state_stack, sizeof(graph.state_stack));
	leaf = graph.leaf;
}
//Serialize를 위한 깊은 복사 생성자
Adjcency_grpah::Adjcency_grpah(Adjcency_grpah *graph) {
	root = graph->root;
	memcpy(hashstate_list, graph->hashstate_list, sizeof(graph->hashstate_list));
	memcpy(&state_stack, &graph->state_stack, sizeof(graph->state_stack));
	leaf = graph->leaf;
}
//----------------------------------------------------------------------------------------
void Adjcency_grpah::Init_hashtable() {
	for(int i=0 ; i < NUMUNIT ; i++){
		for (int j = 0; j < NUMUNIT; j++) {
		//	hashstate_list[i][j] = new hash_4d();
		}
	}
}


void Adjcency_grpah::PushList_Hashtable(State_node* state){
	int cho = state->Getcho();
	int han = state->Gethan();
	int cha_y ;	int cha_x ;	int pho_y ;	int pho_x ;
	Set_4Dhashdata(cha_y, cha_x, pho_y, pho_x, state);
	hashstate_list[cho][han].insert(hash_4d::value_type(pair_key(Cha_pos(cha_y,cha_x), Pho_pos(pho_y, pho_x)), state));
}


void Adjcency_grpah::Insert(vector<State_node*> state){
	State_node *now_state = root ;

	for(int index = 0 ; index < state.size() ; index++){
		State_node* add_state = state.at(index) ;

		int childnode = Is_Have_childnode(now_state,add_state) ;

		// 자기 자식과 같은게 있으면 그대로 이동.
		if(childnode >= 0){
			now_state = now_state->NthCheck_Childnode(childnode) ;
		}
		else {
			// 자기 자식과 같은게 없지만 어떤 노드에 존재하면 그 노드를 next로 지정한다.
			State_node* check_node = Is_In_The_List_State(add_state) ;
			if(check_node){
				now_state->Addlist_Child(check_node) ;
				check_node->Connect_Parent(now_state) ;
				now_state = check_node ;
			}
			else {
				PushList_Hashtable(add_state) ;
				add_state->SetState_number(statenode_num++);
				now_state->Addlist_Child(add_state) ;
				add_state->Connect_Parent(now_state) ;
				add_state->Set_Stateorder(now_state->Getnext()->size()) ;
				now_state = add_state ;
			}
		}
		state_stack.push(now_state) ;
		now_state->TravelCountPlus();
	}
	leaf = now_state ;
}

void Adjcency_grpah::Backtracking_stack(){
	State_node* temp = leaf ;

	temp->Print_State() ;
	cout << temp->Getcho() << " " << temp->Gethan() << endl ;
	state_stack.pop() ;

	cout << "\n< Start ! > " << endl ;
	while(!state_stack.empty()){
		cout << "borad No." << state_stack.size() << endl; //추가
		temp->Print_State() ;
		cout << temp->Getcho() << " " << temp->Gethan() << endl ;
		temp = temp->Getprev()->at(Direction_parentnode(temp));
	}

	// 스택 비우기
	while(!state_stack.empty()) state_stack.pop() ;
	cout << "< End ! >" << endl << endl << endl ;
}

void Adjcency_grpah::Set_4Dhashdata(int &cha_y, int &cha_x, int &pho_y, int &pho_x, State_node* state) {
	cha_y = state->GetHorse_pos().first.first;
	cha_x = state->GetHorse_pos().first.second;
	pho_y = state->GetHorse_pos().second.first;
	pho_x = state->GetHorse_pos().second.second;
}


//void Adjcency_grpah::Travelgraph_bfs() {
//	queue<State_node*> *q = new queue<State_node*>();
//	State_node *temp;
//	int* bfs_check = new int[statenode_num+1];
//	for (int i = 0; i < statenode_num; i++) {
//		bfs_check[i] = i;
//	}
//	q->push(root->NthCheck_Childnode(0));
//
//	cout << " 스테이트 번호 , 방문 횟수 " << endl;
//	while (!q->empty()) {
//		temp = q->front();
//		q->pop();
//		cout << "state 번호 : "  << temp->GetState_number() << " 방문 횟수 : " << temp->GetTravelcount() << endl;
//		for (int i = 0; i < temp->Getnumnext(); i++) {
//			for (int j = 0; j < statenode_num; j++) {
//				if (bfs_check[j] == temp->GetState_number()) {
//					bfs_check[j] = -1;
//					q->push(temp->NthCheck_Childnode(i));
//					break;
//				}
//				if (j == statenode_num - 1 && q->empty())
//					return;
//			}
//		}
//	}
//
//}

State_node* Adjcency_grpah::getRoot(){
	return root ;
}

State_node* Adjcency_grpah::getLeaf(){
	return leaf ;
}

// 현재 위치한 노드에서의 자식노드와 추가할 state와 같은게 있는지.
int Adjcency_grpah::Is_Have_childnode(State_node* sub_root, State_node* state) {
	for (int i = 0; i<sub_root->Getnumnext(); i++)
		if (!Diff_State(sub_root->NthCheck_Childnode(i), state))
			return i;
	return -1;
}

int Adjcency_grpah::Direction_parentnode(State_node* sub_node) {
	State_node* temp = state_stack.top();
	state_stack.pop();
	for (int i = 0; i<sub_node->Getnumprev(); i++) {
		if (!Diff_State(sub_node->NthCheck_Parentnode(i), temp))
			return i;
	}
	return -1;
}

// 현재 노드 state가 그래프로 존재하고 있는지
State_node* Adjcency_grpah::Is_In_The_List_State(State_node *state){

	int cho = state->Getcho();
	int han = state->Gethan();
	int cha_y;	int cha_x;	int pho_y;	int pho_x;
	Set_4Dhashdata(cha_y, cha_x, pho_y, pho_x, state);

	hash_4d m = hashstate_list[cho][han];
	hash_4d::iterator itCur;
	pair<hash_4d::iterator, hash_4d::iterator> it_pair;
	it_pair = m.equal_range(pair_key(Cha_pos(cha_y, cha_x), Pho_pos(pho_y, pho_x)));
	//cout << horse_x << " " << horse_y << endl;
	for (itCur = it_pair.first ; itCur != it_pair.second ; itCur++) {
		if (!Diff_State(itCur->second, state))
			return itCur->second;
	}

	return NULL ; 
}

// 두 state가 같은지 다른지 확인하는 함수.
bool Adjcency_grpah::Diff_State(State_node *stateA, State_node *stateB){
	for(int i=1 ; i< HEIGHT_SIZE; i++)
		for(int j=1 ; j< WIDTH_SIZE ; j++){
			if ( stateA->arr[i][j] != stateB->arr[i][j] )
				return true ;
		}
		return false ;
}
