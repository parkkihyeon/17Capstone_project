#include "Graph.h"
#define TEXT_NAME "Final5000.txt"

//Make Binary file with Graph Serialization
void SaveGraphData(Adjcency_grpah *i, const char *fileName) {
	Adjcency_grpah g(i);
	std::ofstream ofs(fileName, std::ios::binary);
	boost::archive::binary_oarchive oa(ofs);
	cout << "SAVE BOOST SERIALIZATION NVP START" << endl;
	oa & BOOST_SERIALIZATION_NVP(g);
	cout << "Storing Graphs Serialize Success\n" << endl;
}
//Reload Graph Serialized Binary file
Adjcency_grpah LoadGraphData(const char *fileName) {
	Adjcency_grpah g;
	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs) {
		cout << "Read Error" << endl;
		exit(1);
	}

	try {
		boost::archive::binary_iarchive ia(ifs);
		cout << "LOAD BOOST SERIALIZATION NVP START" << endl;
		ia & BOOST_SERIALIZATION_NVP(g);
		cout << "Restoring Graphs Serialize Success\n" << endl;
	}
	catch(boost::archive::archive_exception e) {
		std::cout << "BOOST ERROR " << e.what() << std::endl;
	}	
	return g;
}

void Play_to_Statenode(vector<Play*> *play, vector<State_node*> *state, int now_state)
{
	for (int j = 0; j < play->at(now_state)->game.size(); j++) {
		node * node_t = play->at(now_state)->game.at(j);
		State_node* now_state = new State_node(node_t->returnState());
		now_state->Set_numUnit(node_t->getNumOfCho(), node_t->getNumOfHan());
		now_state->SetHorse_position(node_t->getPair());
		now_state->GetTurn()->SetTurn(node_t->getActor(), node_t->getKilled(), node_t->getCheckMate(), node_t->getHost(), node_t->GetPos());
		state->push_back(now_state);
	}

}

void Graph_made(Adjcency_grpah* g, vector<Play*>* play, vector<vector<State_node*>*>* state) {
	cout << "BF GR PLAY SIZE: " << play->size() << endl;
	for (int i = 0; i < play->size(); i++) {
		vector<State_node*>*history = new vector<State_node*>();
		Play_to_Statenode(play, history, i);
		g->Insert(history);
		state->push_back(history);
		if(i % 1000 == 0)
			cout << "No." << i << endl;
	}
	cout << "Graph Generated\n" << endl;
}

void Second_Graph_made(Second_Graph* g2, vector<Play*>* play, vector<vector<State_node*>*>* state) {
	for (int i = 0; i < play->size(); i++) {
		g2->Getgraph()->Second_insert(state->at(i));
		g2->Value_process(state->at(i), play->at(i)->GetWinner());
	}
	cout << "Graph Generated_2" << endl;
}

void Insert_Gibo(vector<Play*> *play)
{
	ifstream inStream(TEXT_NAME);
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
