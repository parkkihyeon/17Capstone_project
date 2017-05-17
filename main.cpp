#include "Graph.h"
#pragma comment(linker, "/STACK: 524288000")

int main()
{
	clock_t start_t = clock();

	// vector<vector<State_node*>*> *state = new vector<vector<State_node*>*>();
	// vector<Play*> *LoadPlay = new vector<Play*>();
	// vector<Play*> *play = new vector<Play*>();
	// Adjcency_grpah *g = new Adjcency_grpah();

	// std::cout << "FILE PARSING START" << std::endl;
	// Insert_Gibo(play);
	// std::cout << "PLAY SIZE BF FUNCTION: " << play->size() << std::endl;
	// std::cout << "GENERATING GRAPH" << std::endl;
	// Graph_made(g, play, state);
	// Second_Graph *second_g = new Second_Graph(g);
	// Second_Graph_made(second_g, play, state);
	// second_g->Getgraph()->AddMoveable();

	// SaveGraphData(second_g->Getgraph(), "LINUX_Binary_5000");
	Adjcency_grpah *AiGraph = new Adjcency_grpah(LoadGraphData("LINUX_Binary"));
	//AiGraph->Travelgraph_bfs() ;
	// while(true) {
	// 	SelectMove(AiGraph);
	// }

	SetSocket(AiGraph);

	clock_t end_t = clock();
	cout << "Time : " << (end_t - start_t) / 1000 << endl;

	return 0;
}
