#include "Adjcency_grpah.h"

Adjcency_grpah::Adjcency_grpah(){

	char Init_jannggi[HEIGHT_SIZE][WIDTH_SIZE] = {
		{'O','O','O','O','O','O','O','O','O','O'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'}};

	root = new State_node(Init_jannggi) ;
	node_list = new vector<State_node*>() ; // 탐색을 많이 해야 하므로 vector STL을 사용.
	node_list->push_back(root) ;
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
				node_list->push_back(add_state) ;
		//		add_state->Print_State() ;
				now_state->Addlist_Child(add_state) ;
				add_state->Connect_Parent(now_state) ;
				add_state->state_ordernum = now_state->next->size() ;
				now_state = add_state ;
			}
		}
	}
}

State_node* Adjcency_grpah::getRoot(){
	return root ;
}

// 현재 위치한 노드에서의 자식노드와 추가할 state와 같은게 있는지.
int Adjcency_grpah::Is_Have_childnode(State_node* sub_root, State_node* state){	
	for(int i=0; i<sub_root->num_of_next ; i++)
		if(!Diff_State(sub_root->NthCheck_Childnode(i), state))
			return i ;
	return -1 ;
}


// 현재 노드 state가 그래프로 존재하고 있는지
State_node* Adjcency_grpah::Is_In_The_List_State(State_node *state){
	for(int i=0; i<node_list->size() ; i++)
		if(!Diff_State(node_list->at(i), state))
			return node_list->at(i) ;
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