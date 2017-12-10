#include "Graph.h"
#define TEXT_NAME "history-5000.txt"

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
void SetSocket(Adjcency_grpah *graph) {
int host = INITIALIZE;
	int bytesread;
	int fd_max; //maximum file descriptor number
	int _socket; //waiting socket
	int order = INITIALIZE;

	fd_set master; //master file descriptor
	fd_set temps; //temp file destriptor

	char send_message[BUFSIZ]; //buffer for client data
	char receive_message[BUFSIZ];
	char tempsBUF[BUFSIZ];
	char input_stream[BUFSIZ];
	char board[HEIGHT_SIZE][WIDTH_SIZE];

	char *token;
	char *IP = "localhost";
	char *Port = "6120";
	char *socket_id;

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

	memset((void*)send_message, 0, sizeof(send_message));
	memset((void*)receive_message, 0, sizeof(receive_message));

	while (true) {
		temps = master;
		int selector;

		if ((selector = select(fd_max + 1, &temps, NULL, NULL, NULL)) < 0) {
			std::cout << "Select Error" << std::endl;
			exit(1);
		}

		if (FD_ISSET(_socket, &temps)) {
			if ((bytesread = read(_socket, receive_message, sizeof(receive_message)))) {

				receive_message[bytesread] = '\0';
				memcpy((void*)input_stream, (void *)receive_message, strlen(receive_message));

				//CHECK RECEIVED DATA IS ORDER DATA OR BOARD DATA
				std::vector<std::string> stream;
				boost::split(stream, receive_message, boost::is_any_of(" "));

				//Node 서버로부터 받은 값이 상차림일 경우
				if(isOrder(stream)) {
					//stream format = "order socket.id order_data"
					int order = order_selection(stream);
					sprintf(send_message, "order %s %d", stream[SOCKET_IDX].c_str(), order);
					write(_socket, send_message, strlen(send_message));
				}
				//Node 서버로부터 받은 값이 판의 정보일 경우
				else {
					//stream format = "board socket.id host board_data"
					host = std::stoi(stream[HOST_IDX]);
					Get_Board(stream, board);

					pair<int, int> next_pos;
					State_node *game_state = new State_node();
					State_node *inthe_graph = new State_node();
					State_node *select_state = new State_node();
					State_node *now_state = SetState_fromServer(board, 0);

					inthe_graph = graph->Is_In_The_List_State(now_state);
					if (inthe_graph == NULL) {
						MinMax(game_state, now_state, host);
						next_pos = GetStatePos(game_state, now_state);
					}
					else {
						select_state = SelectState(inthe_graph);
						if (select_state) {
							select_state->Print_State();
							game_state->SetState(select_state->GetState());
							next_pos = GetStatePos(game_state, now_state);
						}
						else {
							MinMax(game_state, now_state, host);
							next_pos = GetStatePos(game_state, now_state);
						}
					}
					sprintf(send_message, "board %s %d %d", stream[SOCKET_IDX].c_str(), next_pos.first, next_pos.second);
					write(_socket, send_message, strlen(send_message));
				}

				stream.clear();
				memset((void*)send_message, NULL, sizeof(send_message));
				memset((void*)receive_message, NULL, sizeof(receive_message));
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
bool isOrder(std::vector<std::string> stream) {
	if (stream[IDENTIFIER] == "order") {
		return true;
	}
	else {
		return false;
	}
}
void Get_Board(std::vector<std::string> stream, char(&board)[HEIGHT_SIZE][WIDTH_SIZE]) {

	std::vector<std::string> stream_board;
	boost::split(stream_board, stream[BOARD_IDX], boost::is_any_of(","));

	int idx = 0;
	for (int row = 0; row < HEIGHT_SIZE; row++) {
		for (int col = 0; col < WIDTH_SIZE; col++) {
			board[row][col] = *stream_board[idx++].c_str();
		}
	}
}

int order_selection(std::vector<std::string> stream) {
    switch (std::stoi(stream[ORDER_IDX])) {
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
