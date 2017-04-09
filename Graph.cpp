#include "Graph.h"

void SaveTestData(Adjcency_grpah *i, char *fileName) {
	Adjcency_grpah g(i);
	std::ofstream ofs(fileName);
	boost::archive::text_oarchive oa(ofs);
	oa & BOOST_SERIALIZATION_NVP(g);
}

//만들어진 파일을 다시 로드
Adjcency_grpah LoadTestData(char *fileName) {
	Adjcency_grpah g;
	std::ifstream ifs(fileName);
	boost::archive::text_iarchive ia(ifs);
	ia & BOOST_SERIALIZATION_NVP(g);

	return g;
}

void Play_to_Statenode(vector<Play*> *play, vector<State_node*> *state, int now_state)
{
	for (int j = 0; j < play->at(now_state)->game.size(); j++) {
		node * node_t = play->at(now_state)->game.at(j);
		State_node* now_state = new State_node(node_t->returnState());
		now_state->Set_numUnit(node_t->num_of_cho, node_t->num_of_han);
		now_state->SetHorse_position(node_t->sum_of_horsepos);
		now_state->GetTurn()->SetTurn(node_t->actor, node_t->killed , node_t->checkMate) ;
		state->push_back(now_state);
	}

}

void Graph_made(Adjcency_grpah* g, vector<Play*>* play, vector<State_node*>* state){
	try {
		for (int i = 0; i < play->size(); i++) {
			state->clear();
			Play_to_Statenode(play, state, i);
			g->Insert(state);
			cout << i << "번째\n" << endl;
		}
	}
	catch (exception &e) {
		std::cerr << e.what();
	}
	cout << "Graph Generated" << endl;
}


void Insert_Gibo(vector<Play*> *play)
{
	ifstream inStream("testFile.txt");
	if (inStream.fail()) {
		cout << "Stream File Failed" << endl;
		exit(1);
	}
	while (!inStream.eof()) {
		Play *each_game = NULL;
		Play *temp = each_game->createPlay(inStream);
		if (temp->getRightNode()) {
			play->push_back(temp);
		}
	}
}