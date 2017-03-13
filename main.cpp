#include<iostream>
#include<vector>

#define POINTER_SIZE 300
#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11
#define MAX 100000

using namespace std ;

char Init_jannggi[HEIGHT_SIZE][WIDTH_SIZE] = {('3','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X')};

char Init_jannggi2[HEIGHT_SIZE][WIDTH_SIZE] = {('1','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X'),
	('X','X','X','X','X','X','X','X','X','X')};

class State_node
{
public:
	int num_of_prev ;
	int num_of_next ;
	bool leaf_node ;
	State_node *prev[POINTER_SIZE] ;
	State_node *next[POINTER_SIZE] ;
	char arr[HEIGHT_SIZE][WIDTH_SIZE] ;

	State_node(char data[HEIGHT_SIZE][WIDTH_SIZE]) {
		for(int i=1 ; i< HEIGHT_SIZE; i++)
			for(int j=1 ; j< WIDTH_SIZE ; j++)
				arr[i][j] = data[i][j] ;
		num_of_prev = 0 ;
		num_of_next = 0 ;
		leaf_node = false ;
	} 

	// state의 상태를 출력한다.
	void Print_State(){
		for(int i=1 ; i<= 10; i++){
			for(int j=1 ; j<=9 ; j++)
				cout << arr[i][j] << " " ;
			cout << endl ;
		}
	}

	//node의 자식을 생성.
	void Create_Child(State_node *add_state){
		this->next[num_of_next++] = add_state ;
	}

	// n번째 자식을 return
	State_node* NthCheck_Childnode(int n){
		return this->next[n] ;
	}

	void Plus_Siblingnode(){
		num_of_next++ ;
	}

	void Plus_Parentnode(){
		num_of_prev++ ;
	}

};

class Adjcency_grpah
{
private :
	State_node *root ;
	vector<State_node*> *node_list ;

public:
	Adjcency_grpah(){
		root = new State_node(Init_jannggi) ;
		node_list = new vector<State_node*>() ;
		node_list->push_back(root) ;
	}

	void Insert(State_node* state[], int len_history){
		int index = 0 ;
		State_node *now_state = root ;

		while(state[index]){
			State_node* add_state = state[index] ;
			int childnode = Is_Have_childnode(now_state,add_state) ;

			// 자기 자식과 같은게 있으면 그대로 이동.
			if(childnode)
				now_state = now_state->NthCheck_Childnode(childnode) ;
			// 자기 자식과 같은게 없지만 어떤 노드에 존재하면 그 노드를 next로 지정한다.
			else {
				now_state->Create_Child(add_state) ;
				now_state = add_state ;
				if(!Is_In_The_List_State(add_state)){
					node_list->push_back(add_state) ;
				}
			}
			index++ ;
		}
	}

	State_node* getRoot(){
		return root ;
	}

	// 현재 위치한 노드에서의 자식노드와 추가할 state와 같은게 있는지.
	int Is_Have_childnode(State_node* sub_root, State_node* state){	
		for(int i=0; i<sub_root->num_of_next ; i++)
			if(!Diff_State(sub_root->NthCheck_Childnode(i), state))
				return i ;
		return NULL ;
	}


	// 현재 노드 state가 그래프로 존재하고 있는지
	State_node* Is_In_The_List_State(State_node *state){
		for(int i=0; i<node_list->size() ; i++)
			if(!Diff_State(node_list->at(i), state))
				return node_list->at(i) ;
		return NULL ; 
	}

	// 두 state가 같은지 다른지 확인하는 함수.
	bool Diff_State(State_node *stateA, State_node *stateB){
		for(int i=1 ; i< HEIGHT_SIZE; i++)
			for(int j=1 ; j< WIDTH_SIZE ; j++){
				if ( stateA->arr[i][j] != stateB->arr[i][j] )
					return true ;
			}
			return false ;
	}
};

Adjcency_grpah *g = new Adjcency_grpah() ;

int main()
{
	char data[HEIGHT_SIZE][WIDTH_SIZE] ;
	for(int i=1 ; i <=10 ; i++)
	{
		for(int j=1 ; j<=9 ; j++){
			data[i][j] = 'A' + i - 1 ;
		}
	}

	State_node *t = new State_node(data) ;
	State_node *t2 = new State_node(Init_jannggi2) ;
	g->getRoot()->Print_State() ;

	return 0 ;
}
