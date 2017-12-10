#ifndef __SELECT__STATE__  
#define __SELECT__STATE__  
#include"Adjcency_grpah.h"

#define EXIT_CODE -1
#define MIN -2100000000
enum { CHO, HAN };

stateNode* SetState_fromServer(char state[HEIGHT_SIZE][WIDTH_SIZE], bool host);
stateNode* SelectState(stateNode *now_state);
void SelectMove(Adjcency_grpah *g);
void MinMax(stateNode *game_state, stateNode* now_state, bool host);
bool MoveableMinMax(stateNode *game_state, stateNode *now_state, Adjcency_grpah *g, bool host) ;
void Swap(char &a, char &b);
void PlaceSelect(char state[HEIGHT_SIZE][WIDTH_SIZE]);
#endif