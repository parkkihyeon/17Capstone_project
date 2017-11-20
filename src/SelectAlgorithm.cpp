#include"SelectAlgorithm.h"
#include "Minmax.h"

//const static int THRESHOLD = 10000;
//const static int CHILD_NUM = 3;

void Swap(char &a, char &b) {
	char temp = a;
	a = b;
	b = temp;
}

void PlaceSelect(char state[HEIGHT_SIZE][WIDTH_SIZE]) {
	cout << "0 : HXHX, 1 : HXXH, 2 : XHXH, 3 : XHHX" << endl;
	int cho, han;
	cin >> cho >> han;
	switch (cho)
	{
	case 0:
		break;
	case 1:
		Swap(state[10][7], state[10][8]);
		break;
	case 2:
		Swap(state[10][7], state[10][8]);
		Swap(state[10][2], state[10][3]);
		break;
	case 3:
		Swap(state[10][2], state[10][3]);
		break;
	default:
		cout << "���Է� : " << endl;
		cin >> cho;
	}

	switch (han)
	{
	case 0:
		break;
	case 1:
		Swap(state[1][7], state[1][8]);
		break;
	case 2:
		Swap(state[1][7], state[1][8]);
		Swap(state[1][2], state[1][3]);
		break;
	case 3:
		Swap(state[1][2], state[1][3]);
		break;
	default:
		cout << "���Է� : " << endl;
		cin >> han;
	}
}

State_node* SetState_fromServer(char state[HEIGHT_SIZE][WIDTH_SIZE], bool host) {
	/*
	 �¼� : state�� host�� ���⿡ �����κ��� �ް� �ڵ� �Ѵ�.
	*/
	int cho = 0, han = 0, cha_y = 0, cha_x = 0, pho_y = 0, pho_x = 0;
	State_node* answer = new State_node(state);
	pair<Cha_pos, Pho_pos> pos;
	pair<int, int> Pos;
	Pos.first = NULL;
	Pos.second = NULL;
	answer->GetTurn()->SetTurn(0, 0, 0, host, Pos);

	for (int i = 1; i < HEIGHT_SIZE; i++) {
		for (int j = 1; j < WIDTH_SIZE; j++) {
			if ('A' <= state[i][j] && state[i][j] <= 'Z')
				han++;
			else if ('a' <= state[i][j] && state[i][j] <= 'z')
				cho++;
			if (state[i][j] == 'c' || state[i][j] == 'C') {
				cha_y += i;
				cha_x += j;
			}
			else if (state[i][j] == 'p' || state[i][j] == 'P') {
				pho_y += i;
				pho_x += j;
			}
		}
	}
	answer->Set_numUnit(cho, han);
	pos.first.first = cha_y;
	pos.first.second = cha_x;
	pos.second.first = pho_y;
	pos.second.second = pho_x;
	answer->SetHorse_position(pos);
	return answer;
}

State_node* SelectState(State_node *now_state) {

	int index = 0;
	int max ;
	int sizeOfChild = now_state->GetNext()->size();

	if (!sizeOfChild)
		return NULL;
	
	max = now_state->GetNext()->at(0)->GetScore();

	// �ƽ��� ã��
	for (int i = 1; i < sizeOfChild; i++) {
		if (now_state->GetNext()->at(i)->GetScore() > max) {
			max = now_state->GetNext()->at(i)->GetScore();
			index = i;
		}
	}

	if (max < 0) {
		cout << "max < 0\n";
		return NULL ;
	}
		

	for (int i = 0 ; i < sizeOfChild; i++) {
		cout << now_state->GetNext()->at(i)->GetScore() << " ";
	}
	cout << endl << "SELECT : " << now_state->GetNext()->at(index)->GetScore() << endl;

	return now_state->GetNext()->at(index);
}

bool MoveableMinMax(State_node *game_state, State_node *now_state, Adjcency_grpah *g){
	State_node *maxVlaueState = new State_node() ;
	int maxvalue = 0 ;

	/* movable minmax  */
}

void MinMax(State_node *game_state, State_node* now_state, bool host) {
	cout << "Min Max " << endl ;
	char t_state[HEIGHT_SIZE][WIDTH_SIZE] ;
	CJKStage test;
	test.boardChage(now_state->GetState());
	test.Infer(host);
	test.getboard(t_state) ;
	game_state->SetState(t_state);
	game_state->Print_State();
}

void SelectMove(Adjcency_grpah *g) {
	char state[HEIGHT_SIZE][WIDTH_SIZE] = {
		{ '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
		{ '-', 'C', 'H', 'X', 'S', '-', 'S', 'H', 'X', 'C' },
		{ '-', '-', '-', '-', '-', 'K', '-', '-', '-', '-' },
		{ '-', '-', 'P', '-', '-', '-', '-', '-', 'P', '-' },
		{ '-', 'J', '-', 'J', '-', 'J', '-', 'J', '-', 'J' },
		{ '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
		{ '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
		{ '-', 'j', '-', 'j', '-', 'j', '-', 'j', '-', 'j' },
		{ '-', '-', 'p', '-', '-', '-', '-', '-', 'p', '-' },
		{ '-', '-', '-', '-', '-', 'k', '-', '-', '-', '-' },
		{ '-', 'c', 'h', 'x', 's', '-', 's', 'h', 'x', 'c' }
	};

	State_node *now_state = new State_node();
	State_node *inthe_graph = new State_node();
	State_node *select_state = new State_node();

	bool host;
	bool game_ing = true;
	char temp_state[HEIGHT_SIZE][WIDTH_SIZE];
	int pre_y, pre_x, post_x, post_y;

	cout << "If User want CHO then press 1 if not press 0" << endl;
	cin >> host;
	PlaceSelect(state);

	State_node *game_state = new State_node(state);
	game_state->Print_State();

	for (int i = 0; game_ing == true; i++) {
		if (i % 2 == host) { 
			now_state = SetState_fromServer(game_state->GetState(), !host);
			inthe_graph = g->IsHaveStateInHash(now_state); 
			
			if(inthe_graph == NULL ){
				MinMax(game_state, now_state, host); 
			}
			else {
				select_state = SelectState(inthe_graph);

				if (select_state) {
					select_state->Print_State();
					game_state->SetState(select_state->GetState());
				}

				else{
					MinMax(game_state, now_state, host);
				}
			}
			/*
				�¼� : server -> unity ��ġ ��ȯ.
			*/
		}
		else {
			cin >> pre_y;
			if (pre_y == EXIT_CODE) { // -1
				return;
			}
			else {
				cin >> pre_x >> post_x >> post_y;
				memcpy(temp_state, game_state->GetState(), sizeof(char)*HEIGHT_SIZE*WIDTH_SIZE);
				Swap(temp_state[pre_y][pre_x], temp_state[post_x][post_y]);
				temp_state[pre_y][pre_x] = '-';
				game_state->SetState(temp_state);
			}
		}
		
	}

}