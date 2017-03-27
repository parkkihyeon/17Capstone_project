#include "play.h"

Play::Play()
	:reportNumber(0), victory(0), cho_order(0), han_order(0)
{
	for (int i = 0; i < HEIGHT_SIZE; i++)
		for (int j = 0; j < WIDTH_SIZE; j++)
			StateInfo[i][j] = NULL;
	//마상마상 & 마상마상 기본
	char temp[HEIGHT_SIZE][WIDTH_SIZE] = {
		{ '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
		{ '-', 'C', 'X', 'H', 'S', '-', 'S', 'X', 'H', 'C' },
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
	memcpy(StateInfo, temp, sizeof(char)*HEIGHT_SIZE*WIDTH_SIZE);
}
Play::Play(int reportNum, int cho, int han, int vic)
	: reportNumber(reportNum), victory(vic), cho_order(cho), han_order(han)
{
	for (int i = 0; i < HEIGHT_SIZE; i++)
		for (int j = 0; j < WIDTH_SIZE; j++)
			StateInfo[i][j] = NULL;
	//마상마상 & 마상마상 기본
	char temp[HEIGHT_SIZE][WIDTH_SIZE] = {
		{ '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' },
		{ '-', 'C', 'X', 'H', 'S', '-', 'S', 'X', 'H', 'C' },
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
	memcpy(StateInfo, temp, sizeof(char)*HEIGHT_SIZE*WIDTH_SIZE);
}
void Play::insertStage(node *state) {
	game.push_back(state);
}
void Play::initailize() {
	node *Node = new node(StateInfo);
	Node->UnitOrder(cho_order, han_order);
	insertStage(Node);

	for (int i = 0; i < HEIGHT_SIZE; i++) {
		for (int j = 0; j < WIDTH_SIZE; j++) {
			StateInfo[i][j] = Node->arr[i][j];
		}
	}
}
void Play::createState(string line) {

	int     nCutPos;
	int     nIndex = 0;
	// 읽어드린 string을 각 변수에 맞게 split
	string* strResult = new string[TOKEN_SIZE];

	while ((nCutPos = line.find_first_of(' ')) != line.npos)
	{
		if (nCutPos > 0)
		{
			strResult[nIndex++] = line.substr(0, nCutPos);
		}
		line = line.substr(nCutPos + 1);
	}

	if (line.length() > 0)
	{
		strResult[nIndex++] = line.substr(0, nCutPos);
	}
	int pos[2] = { atoi(strResult[1].c_str()), atoi(strResult[2].c_str()) };
	char *unit = new char(2);

	// 한수쉼의 경우
	if (pos[0] == 0 && pos[1] == 0) {
		//cout << "한 수 쉼 " << atoi(strResult[0].c_str()) << endl;
		node *Node = new node(StateInfo);
		Node->host = atoi(strResult[0].c_str());
		insertStage(Node);
	//	printBoard();
		return;
	}
	// split된 값들을 이용하여 node 생성
	strcpy(unit, strResult[3].c_str());
	node *Node = new node(StateInfo);
	Node->host = atoi(strResult[0].c_str());
	Node->changeState(pos, unit[0]);
	insertStage(Node);

	//play객체의 Board 최신화
	for (int i = 0; i < HEIGHT_SIZE; i++) {
		for (int j = 0; j < WIDTH_SIZE; j++) {
			StateInfo[i][j] = Node->arr[i][j];
		}
	}
//	printBoard();
	// node의 판 print
}
void Play::printBoard() {
	for (int i = 0; i < HEIGHT_SIZE; i++) {
		for (int j = 0; j < WIDTH_SIZE; j++) {
			if (i == 0) {
				cout << j << " ";
			}
			else if (j == 0 && i == 10) {
				cout << 0 << " ";
			}
			else if (j == 0 && i != 10) {
				cout << i << " ";
			}
			else if (j == WIDTH_SIZE -1 && i == HEIGHT_SIZE / 2) {
				cout << StateInfo[i][j] << " "
					<< game.at(game.size()-1)->host;
			}
			else {
				cout << StateInfo[i][j] << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
	cout << "------------------------------------------------------" << endl;
	cout << endl;
}
Play* Play::createPlay(ifstream &file) {
	Play *returnData;
	string textLine;
	getline(file, textLine);
	if (textLine.find('.txt') != string::npos) {
		cout << textLine << endl;
		int reportNumber = INITIAL_ORDER, 
			cho = INITIAL_ORDER, han = INITIAL_ORDER, victory = INITIAL_ORDER;
		bool flag = false;
		//text라인을 한줄씩 읽기 위해서 생성
		file >> cho >> han >> victory;
		//접장기의 경우를 피하기 위해
		reportNumber = atoi(textLine.c_str());

		Play *gameReport = new Play(reportNumber, cho, han, victory);
		gameReport->initailize();
		int state_index = 1;
		while (getline(file, textLine)) {
			if (textLine.compare("") == 0 && !flag) {
				flag = true;
				continue;
			}
			else if (textLine.compare("") == 0 && flag) {
				flag = false;
				return gameReport;
			}
			else {
				//cout << state_index++ << endl;
				gameReport->createState(textLine);
			}
		}
		returnData = gameReport;
	}
	return returnData;
}