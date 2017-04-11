#include "Statenode.h"
#include "Adjcency_grpah.h"
#include "play.h"
#include <time.h>

void Insert_Gibo(vector<Play*> *play);
void Play_to_Statenode(vector<Play*> *play, vector<State_node*> *state, int now_state);
void Graph_made(Adjcency_grpah* g, vector<Play*>* play, vector<State_node*>* state);
void Second_Graph_made(Second_Graph* g2, vector<Play*>* play, vector<State_node*>* state);
void SaveTestData(Adjcency_grpah *i, char *fileName);
Adjcency_grpah LoadTestData(char *fileName);