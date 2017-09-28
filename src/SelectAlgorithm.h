#ifndef __SELECT__STATE__  
#define __SELECT__STATE__  
#include"Adjcency_grpah.h"

#define EXIT_CODE -1
#define MIN -2100000000
enum { CHO, HAN };

State_node* SetState_fromServer(char state[HEIGHT_SIZE][WIDTH_SIZE], bool host);
State_node* SelectState(State_node *now_state);
void SelectMove(Adjcency_grpah *g);
void MinMax(State_node *game_state, State_node* now_state, bool host);
bool MoveableMinMax(State_node *game_state, State_node *now_state, Adjcency_grpah *g, bool host) ;
void Swap(char &a, char &b);
void PlaceSelect(char state[HEIGHT_SIZE][WIDTH_SIZE]);
#endif