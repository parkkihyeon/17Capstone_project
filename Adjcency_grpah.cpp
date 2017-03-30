#include "Adjcency_grpah.h"

Adjcency_grpah::Adjcency_grpah(){

	char Init_jannggi[HEIGHT_SIZE][WIDTH_SIZE] ;
	for(int i=0 ; i< HEIGHT_SIZE ; i++){
		memset(Init_jannggi[i], 'X', sizeof(char)*WIDTH_SIZE);
	}

	root = new State_node(Init_jannggi) ;
	root->Set_numUnit(0,0) ;

	//node_list.push_back(root) ;
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
			hashstate_list[i][j] = new vector<State_node*>();
		}
	}
}


void Adjcency_grpah::PushList_Hashtable(State_node* state){
	pair<int,int> point ;
	int cho = state->Getcho();
	int han = state->Gethan();
	//cout << "cho : " << cho << ", han : " << han << endl;
	hashstate_list[cho][han]->push_back(state) ;

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
				now_state->Addlist_Child(add_state) ;
				add_state->Connect_Parent(now_state) ;
				add_state->Set_Stateorder(now_state->Getnext()->size()) ;
				now_state = add_state ;
			}
		}
		state_stack.push(now_state) ;
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
		temp->Print_State() ;
		cout << temp->Getcho() << " " << temp->Gethan() << endl ;
		temp = temp->Getprev()->at(Direction_parentnode(temp));
	}

	// 스택 비우기
	while(!state_stack.empty()) state_stack.pop() ;
	cout << "< End ! >" << endl << endl << endl ;
}


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

	vector<State_node*>* now_state = hashstate_list[cho][han] ;
	for(int i = 0 ; i < now_state->size() ; i++)
		if(!Diff_State(now_state->at(i), state))
			return now_state->at(i) ;
	

	/*for(int i=0; i<node_list.size() ; i++)
		if(!Diff_State(node_list.at(i), state))
			return node_list.at(i) ;
	*/return NULL ; 
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