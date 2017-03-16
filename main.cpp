#include "Graph.h"

int main()
{
	Adjcency_grpah *g = new Adjcency_grpah() ;
	vector<State_node*> state ;
	vector<Play*> play ;
	Insert_Gibo(play) ;

	for(int i=0 ; i<play.size() ; i++){ 
		state.clear() ;
		Play_to_Statenode(play,state,i) ;
		g->Insert(state) ;
	}

	return 0 ;
}

void Play_to_Statenode(vector<Play*> play,  vector<State_node*> &state, int now_state)
{
	for (int j=0 ; j<play.at(now_state)->game.size() ; j++){
		State_node* t = new State_node(play.at(now_state)->game.at(j)->returnState()) ;
		state.push_back(t) ;
	}

}

void Insert_Gibo(vector<Play*> &play) 
{
	ifstream inStream("testFile.txt");
	if (inStream.fail()) {
		cout << "Stream File Failed" << endl;
		exit(1);
	}
	while (!inStream.eof()) {
		Play *each_game = NULL;
		play.push_back(each_game->createPlay(inStream));
	}
}
