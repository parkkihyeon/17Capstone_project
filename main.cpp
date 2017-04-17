#include "Graph.h"
#include <time.h>

int main()
{
	clock_t start_t = clock();
	
	Adjcency_grpah *g = new Adjcency_grpah();
	vector<State_node*> *state = new vector<State_node*>();
	vector<Play*> *play = new vector<Play*>();
	Insert_Gibo(play);
	Graph_made(g, play, state);


	SaveVectorData(play, "V_BinaryFile");
	SaveGraphData(g, "G_BinaryFile");
	Adjcency_grpah *AiGraph = new Adjcency_grpah(LoadGraphData("G_BinaryFile"));

	clock_t end_t = clock();
	cout << "½Ã°£ : " << (end_t - start_t) / 1000 << endl;

	return 0;
}