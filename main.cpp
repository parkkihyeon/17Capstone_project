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
	//Second_Graph *g2 = new Second_Graph(g);
	//Second_Graph_made(g2, play, state);


	//SaveTestData(g, "G_BinaryFile30");
	Adjcency_grpah *AiGraph = new Adjcency_grpah(LoadTestData("G_BinaryFile"));

	cout << "Memory Compare between generated one and restored one\n" << endl;
	
	//Compare between Generated Graph & Restored Graph
	if (g->operator==(AiGraph)) {
	cout << "Correct Same" << endl;
	}
	else {
	cout << "Not Equivalent" << endl;
	}


	clock_t end_t = clock();
	cout << "½Ã°£ : " << (end_t - start_t) / 1000 << endl;

	return 0;
}