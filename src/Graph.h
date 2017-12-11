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
#include <boost/algorithm/string.hpp>


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

#define IDENTIFIER 0
#define SOCKET_IDX 1
#define ORDER_IDX 2
#define HOST_IDX 2
#define BOARD_IDX 3

void Insert_Gibo(vector<Play*> *play);
void Node2StateNode(vector<Play*> *play, vector<stateNode*> *state, int now_state);
void Graph_made(Adjcency_grpah* g, vector<Play*>* play, vector<vector<stateNode*>*>* state);
void Second_Graph_made(Second_Graph* g2, vector<Play*>* play, vector<vector<stateNode*>*> * state);
void SaveGraphData(Adjcency_grpah *i, const char *fileName);
Adjcency_grpah LoadGraphData(const char *fileName);
void SetSocket(Adjcency_grpah *graph);
pair<int, int> GetStatePos(State_node *nextState, State_node *prevState);
bool isOrder(std::vector<std::string> stream);
int order_selection(std::vector<std::string> stream);
void Get_Board(std::vector<std::string> stream, char(&board)[HEIGHT_SIZE][WIDTH_SIZE]);