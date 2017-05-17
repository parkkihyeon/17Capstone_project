#include "Statenode.h"
#include "Adjcency_grpah.h"
#include "play.h"
#include "SelectAlgorithm.h"
#include <time.h>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp> // Á÷·ÄÈ­ vector¸¦ »ç¿ëÇÏ±â À§ÇØ
#include <boost/serialization/deque.hpp> // Á÷·ÄÈ­ stackÀ» »ç¿ëÇÏ±â À§ÇØ
#include <boost/serialization/stack.hpp> // Á÷·ÄÈ­ stackÀ» »ç¿ëÇÏ±â À§ÇØ
#include <boost/serialization/map.hpp>
#include <boost/serialization/utility.hpp>

#include <boost/archive/binary_iarchive.hpp> // ¹ÙÀÌ³Ê¸® ÇüÅÂ·Î ÀÔ·ÂÇÏ±â À§ÇØ
#include <boost/archive/binary_oarchive.hpp> // ¹ÙÀÌ³Ê¸® ÇüÅÂ·Î ÀÔ·ÂÇÏ±â À§ÇØ

#include <boost/serialization/nvp.hpp>

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11
#define INITIALIZE -2
#define ORDERBIT -4

void Insert_Gibo(vector<Play*> *play);
void Play_to_Statenode(vector<Play*> *play, vector<State_node*> *state, int now_state);
void Graph_made(Adjcency_grpah* g, vector<Play*>* play, vector<vector<State_node*>*>* state);
void Second_Graph_made(Second_Graph* g2, vector<Play*>* play, vector<vector<State_node*>*> * state);
void SaveGraphData(Adjcency_grpah *i, const char *fileName);
Adjcency_grpah LoadGraphData(const char *fileName);
void SetSocket(Adjcency_grpah * graph);
void GetBoard(char* parsedData, char (&board)[HEIGHT_SIZE][WIDTH_SIZE]);
pair<int, int> CheckType(char* msg);
pair<int, int> GetStatePos(State_node *nextState, State_node *prevState);
bool isOrderBit(int _bit);
int OrderSelect(int _userOrder);