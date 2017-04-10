#include "Graph.h"

int main()
{
	clock_t t = clock();

	Adjcency_grpah *g = new Adjcency_grpah();
	vector<State_node*> *state = new vector<State_node*>();
	vector<Play*> *play = new vector<Play*>() ;
	Insert_Gibo(play);
	Graph_made(g, play, state) ;
	Second_Graph *g2 = new Second_Graph(g) ;
	Second_Graph_made(g2, play, state) ;


	//	SaveTestData(g, "G");
	//	g->Travelgraph_bfs();
	//	Adjcency_grpah *AiGraph = new Adjcency_grpah(LoadTestData("G"));
	//	g->Travelgraph_bfs() ;

	//	g2->Getgraph()->Travelgraph_bfs() ;
	

	clock_t end_t = clock();
	cout << "½Ã°£ : " << (end_t - t) / 1000 << endl;

	return 0;
}