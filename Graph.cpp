#include "Graph.h"
#define TEXT_NAME "Final5000.txt"

//Make Binary file with Graph Serialization
void SaveGraphData(Adjcency_grpah *i, const char *fileName) {
	Adjcency_grpah g(i);
	std::ofstream ofs(fileName, std::ios::binary);
	boost::archive::binary_oarchive oa(ofs);
	cout << "SAVE BOOST SERIALIZATION NVP START" << endl;
	oa & BOOST_SERIALIZATION_NVP(g);
	cout << "Storing Graphs Serialize Success\n" << endl;
}
//Reload Graph Serialized Binary file
Adjcency_grpah LoadGraphData(const char *fileName) {
	Adjcency_grpah g;
	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs) {
		cout << "Read Error" << endl;
		exit(1);
	}

	try {
		boost::archive::binary_iarchive ia(ifs);
		cout << "LOAD BOOST SERIALIZATION NVP START" << endl;
		ia & BOOST_SERIALIZATION_NVP(g);
		cout << "Restoring Graphs Serialize Success\n" << endl;
	}
	catch(boost::archive::archive_exception e) {
		std::cout << "BOOST ERROR " << e.what() << std::endl;
	}	
	return g;
}

void Play_to_Statenode(vector<Play*> *play, vector<State_node*> *state, int now_state)
{
	for (int j = 0; j < play->at(now_state)->game.size(); j++) {
		node * node_t = play->at(now_state)->game.at(j);
		State_node* now_state = new State_node(node_t->returnState());
		now_state->Set_numUnit(node_t->getNumOfCho(), node_t->getNumOfHan());
		now_state->SetHorse_position(node_t->getPair());
		now_state->GetTurn()->SetTurn(node_t->getActor(), node_t->getKilled(), node_t->getCheckMate(), node_t->getHost(), node_t->GetPos());
		state->push_back(now_state);
	}

}

void Graph_made(Adjcency_grpah* g, vector<Play*>* play, vector<vector<State_node*>*>* state) {
	cout << "BF GR PLAY SIZE: " << play->size() << endl;
	for (int i = 0; i < play->size(); i++) {
		vector<State_node*>*history = new vector<State_node*>();
		Play_to_Statenode(play, history, i);
		g->Insert(history);
		state->push_back(history);
		if(i % 1000 == 0)
			cout << "No." << i << endl;
	}
	cout << "Graph Generated\n" << endl;
}

void Second_Graph_made(Second_Graph* g2, vector<Play*>* play, vector<vector<State_node*>*>* state) {
	for (int i = 0; i < play->size(); i++) {
		g2->Getgraph()->Second_insert(state->at(i));
		g2->Value_process(state->at(i), play->at(i)->GetWinner());
	}
	cout << "Graph Generated_2" << endl;
}

void Insert_Gibo(vector<Play*> *play)
{
	ifstream inStream(TEXT_NAME);
	if (inStream.fail()) {
		cout << "Stream File Failed" << endl;
		exit(1);
	}
	while (!inStream.eof()) {
		Play *each_game = NULL;
		Play *temp = each_game->createPlay(inStream);
		if (temp->getRightNode()) {
			play->push_back(temp);
		}
	}
}
void SetSocket(Adjcency_grpah * graph) {
	int host = INITIALIZE;
	int bytesread;
	int fd_max; //maximum file descriptor number
	int _socket; //waiting socket
	int order = INITIALIZE;

	fd_set master; //master file descriptor
	fd_set temps; //temp file destriptor

	char sendMSG[BUFSIZ]; //buffer for client data
	char receiveMSG[BUFSIZ];
	char tempsBUF[BUFSIZ];
	char certifiData[BUFSIZ];
	char board[HEIGHT_SIZE][WIDTH_SIZE];

	char *token;
	char *IP = "203.246.112.146";
	char *Port = "6120";

	struct hostent *_host;
	struct sockaddr_in  _server; //server's address

								 // NEED TO CREATE A SOCKET FOR TCP SERVER
	if ((_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		std::cout << "Generate Socket Error" << std::endl;
		exit(1);
	}

	//return DNS to IP
	if ((_host = gethostbyname(IP)) == 0) {
		std::cout << Port << ": Unknown Host" << std::endl;
		exit(1);
	}

	//Initialize Server Setting
	memset((void *)&_server, 0, sizeof(_server));
	_server.sin_family = AF_INET;
	_server.sin_port = htons((u_short)atoi(Port));
	memcpy((void*)&_server.sin_addr, _host->h_addr, _host->h_length);

	//Server Connection
	if (connect(_socket, (struct sockaddr *)&_server, sizeof(_server)) < 0) {
		(void)close(_socket);
		std::cout << "Connection Error" << std::endl;
		exit(1);
	}

	// BIT INITIALIZE
	FD_ZERO(&master);
	FD_ZERO(&temps);

	//ADD THE LISTENR TO THE READS SET
	FD_SET(_socket, &master); // =set 1 index 3

							  //KEEP TRACK OF THE BIGGEST FILE DESCRIPTOR
	fd_max = _socket;

	memset((void*)sendMSG, 0, sizeof(sendMSG));
	memset((void*)receiveMSG, 0, sizeof(receiveMSG));

	int count = 1;

	std::cout << "Graph Module Generated" << std::endl;
	char state[HEIGHT_SIZE][WIDTH_SIZE] = {
		{ '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
		{ '-', 'C', 'H', 'X', 'S', '-', 'S', 'H', 'X', 'C' },
		{ '-', '-', '-', '-', '-', 'K', '-', '-', '-', '-' },
		{ '-', '-', 'P', '-', '-', '-', '-', '-', 'P', '-' },
		{ '-', 'J', '-', 'J', '-', 'J', '-', 'J', '-', 'J' },
		{ '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
		{ '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
		{ '-', 'j', '-', 'j', '-', 'j', '-', 'j', '-', 'j' },
		{ '-', '-', 'p', '-', '-', '-', '-', '-', 'p', '-' },
		{ '-', '-', '-', '-', '-', 'k', '-', '-', '-', '-' },
		{ '-', 'c', 'h', 'x', 's', '-', 's', 'h', 'x', 'c' }
	};


	while (true) {
		temps = master;
		int selector;

		if ((selector = select(fd_max + 1, &temps, NULL, NULL, NULL)) < 0) {
			std::cout << "Select Error" << std::endl;
			exit(1);
		}

		if (FD_ISSET(_socket, &temps)) {
			if ((bytesread = read(_socket, receiveMSG, sizeof(receiveMSG)))) {
				std::cout << "Data Received Number: " << count++ << std::endl;

				receiveMSG[bytesread] = '\0';
				memcpy((void*)certifiData, (void *)receiveMSG, strlen(receiveMSG));
				//std::cout << receiveMSG << std::endl;
				std::cout << "=================================================================================" << std::endl;

				//CHECK RECEIVED DATA IS ORDER DATA OR BOARD DATA
				pair<int, int> checkBit = CheckType(certifiData);

				//IF CHECKBIT == -4 -> ORDER BIT
				if (isOrderBit(checkBit.first)) {
					int order = OrderSelect(checkBit.second);
					sprintf(sendMSG, "ORDER|%d", order);
					write(_socket, sendMSG, strlen(sendMSG));
					cout << "POS-1: " << checkBit.first << " " << "POS-2: " << checkBit.second << endl;
					//PlaceSelect(state, order, order);
				}
				// IF CHECKBIT != -4 -> BOARD DATA
				else {
					host = checkBit.first;
					GetBoard(receiveMSG, board);

					// FIND IN GRAPH WITH DATA(host, board)
					pair<int, int> pos;
					State_node *game_state = new State_node();
					State_node *inthe_graph = new State_node();
					State_node *select_state = new State_node();
					State_node *now_state = SetState_fromServer(board, host);

					inthe_graph = graph->Is_In_The_List_State(now_state);
					if (inthe_graph == NULL) {
						MinMax(game_state, now_state, host);
						pos = GetStatePos(game_state, now_state);
					}
					else {
						select_state = SelectState(inthe_graph);
						if (select_state) {
							select_state->Print_State();
							game_state->SetState(select_state->GetState());
							pos = game_state->GetTurn()->Getpos();
							cout << "POS-1: " << pos.first << " " << "POS-2: " << pos.second << endl;
						}
						else {
							MinMax(game_state, now_state, host);
							pos = GetStatePos(game_state, now_state);
						}
					}

					sprintf(sendMSG, "BORAD|%d %d", pos.first, pos.second);
					write(_socket, sendMSG, strlen(sendMSG));
				}

				memset((void*)sendMSG, NULL, sizeof(sendMSG));
				memset((void*)receiveMSG, NULL, sizeof(receiveMSG));
				memset((void*)board, NULL, sizeof(char) * HEIGHT_SIZE * WIDTH_SIZE);
			}
			if (bytesread == -1) {
				std::cout << "Server Disconnected" << std::endl;
				close(_socket);
				exit(1);
			}
		}
	}
}
pair<int, int> CheckType(char* _received) {
	char *token;
	pair<int, int> order;
	token = strtok(_received, "|");
	if (strcmp(token, "order") == 0) {
		token = strtok(NULL, "|");
		order.first = ORDERBIT;
		order.second = atoi(token);
		return order;
	}
	else {
		order.first = atoi(token);
		order.second = -100;
		return order;
	}
}
bool isOrderBit(int _bit) {
	if (_bit == ORDERBIT) {
		return true;
	}
	else {
		return false;
	}
}
void GetBoard(char* parsedData, char(&board)[HEIGHT_SIZE][WIDTH_SIZE]) {
	char *token;
	token = strtok(parsedData, "|");

	for (int i = 0; i < HEIGHT_SIZE; i++) {
		for (int j = 0; j < WIDTH_SIZE; j++) {
			token = strtok(NULL, ",");
			board[i][j] = token[0];
		}
	}
}

pair<int, int> GetStatePos(State_node *nextState, State_node *prevState) {
	pair<int, int> pos;
	
	int HeightIndex = 0, WidthIndex = 0;
	for(int i = 1; i < HEIGHT_SIZE; i++) {
		for(int j = 1; j < WIDTH_SIZE; j++) {
			HeightIndex = i, WidthIndex = j;
			if(nextState->GetState()[i][j] != prevState->GetState()[i][j]) {
				if(i == 10) {
					HeightIndex = 0;
				}
				if(nextState->GetState()[i][j] == '-') {
					pos.first = HeightIndex * 10 + WidthIndex;
				}
				else if(nextState->GetState()[i][j] != '-') {
					pos.second = HeightIndex * 10 + WidthIndex;
				}
			}
		}
	}
	cout << "POS-1: " << pos.first << " " << "POS-2: " << pos.second << endl;
	return pos;
}
int OrderSelect(int _userOrder) {
    switch (_userOrder) {
        case 0:
            return 0;
        case 1:
            return 3;
        case 2:
            return 1;
        case 3:
            return 3;
    }
}