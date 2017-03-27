#include "Graph.h"


//시리얼라이즈를 한 그래프를 파일로 만들어낸다.
void SaveTestData(Adjcency_grpah *i, char *fileName) {
	Adjcency_grpah g(i);
	std::ofstream ofs(fileName);
	boost::archive::binary_oarchive oa(ofs);
	oa << g;
}

//만들어진 파일을 다시 로드
Adjcency_grpah LoadTestData(char *fileName) {
	Adjcency_grpah g;
	std::ifstream ifs(fileName);
	boost::archive::binary_iarchive ia(ifs);
	ia >> g;

	return g;
}

int main()
{
	//Adjcency_grpah *g = new Adjcency_grpah(LoadTestData("G")) ;
	//vector<State_node*> state ;
	//vector<Play*> play ;
	//Insert_Gibo(play) ;

	//for(int i=0 ; i<play.size() ; i++){ 
	//	state.clear() ;
	//	Play_to_Statenode(play,state,i) ;
	//	g->Insert(state) ;
	//}
	////SaveTestData(g, "G");
	//Adjcency_grpah *test = new Adjcency_grpah(LoadTestData("G"));
	//g->getRoot()->next->at(0)->Print_State();
	//test->getRoot()->next->at(1)->Print_State();
	//Adjcency_grpah *g = new Adjcency_grpah(LoadTestData("G"));
	Adjcency_grpah *g = new Adjcency_grpah();


	vector<State_node*> state;
	vector<Play*> play;
	Insert_Gibo(play);

	for (int i = 0; i<play.size(); i++) {
		state.clear();
		Play_to_Statenode(play, state, i);
		g->Insert(state);
		std::cout << i << " 번째" << std::endl;
	}

	SaveTestData(g, "G");
	cout << "Graph Generated" << endl;
		

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
		Play *temp = each_game->createPlay(inStream);
		if (temp->getRightNode()) {
			/*play.push_back(each_game->createPlay(inStream));*/
			play.push_back(temp);
		}
		//else {
		//	inStream.seekg(-10, ios::cur);
		//}
		//play.push_back(each_game->createPlay(inStream));
	}
}
