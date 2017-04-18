#include "Graph.h"
#include <time.h>

int main()
{
	clock_t start_t = clock();
	
	vector<State_node*> *state = new vector<State_node*>();
	vector<Play*> *LoadPlay = new vector<Play*>(); //--> 복구된 Vector를 복사하기 위해
	vector<Play*> *play = new vector<Play*>();
	Adjcency_grpah *g = new Adjcency_grpah();
	
	Insert_Gibo(play);
	Graph_made(g, play, state);

	SaveVectorData(play, "V_BinaryFile");
	LoadPlay = LoadVectorData("V_BinaryFile");

	SaveGraphData(g, "G_BinaryFile");
	Adjcency_grpah *AiGraph = new Adjcency_grpah(LoadGraphData("G_BinaryFile"));

	clock_t end_t = clock();
	cout << "시간 : " << (end_t - start_t) / 1000 << endl;

	return 0;
}