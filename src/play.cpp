#include "play.h"

Play::Play()
	:reportNumber(0), victory(0), cho_order(0), han_order(0)
{
	for (int i = 0; i < HEIGHT_SIZE; i++)
		for (int j = 0; j < WIDTH_SIZE; j++)
			StateInfo[i][j] = NULL;
	//���󸶻� & ���󸶻� �⺻
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
	//���󸶻� & ���󸶻� �⺻
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
	Node->getNumOfUnit();
	insertStage(Node);

	for (int i = 0; i < HEIGHT_SIZE; i++) {
		for (int j = 0; j < WIDTH_SIZE; j++) {
			StateInfo[i][j] = Node->getArrPos(i, j);
		}
	}
}
void Play::createState(string line) {

	int     nCutPos;
	int     nIndex = 0;
	// �о��帰 string�� �� ������ �°� split
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

	// �Ѽ����� ����
	if (pos[0] == 0 && pos[1] == 0) {
		node *Node = new node(StateInfo);
		Node->setHost(atoi(strResult[0].c_str()));
		Node->getNumOfUnit();
		insertStage(Node);
		return;
	}
	// split�� ������ �̿��Ͽ� node ����
	strcpy(unit, strResult[3].c_str());
	node *Node = new node(StateInfo);
	Node->setHost(atoi(strResult[0].c_str()));
	Node->setActor(*unit);
	Node->setPos(pos[0], pos[1]);
	Node->setKilled(*strResult[4].c_str());
	if (atoi(strResult[5].c_str()) == 1) {
		Node->setCheckMate(true);
	}
	else {
		Node->setCheckMate(false);
	}
	Node->changeState(pos);
	insertStage(Node);

	//play��ü�� Board �ֽ�ȭ
	for (int i = 0; i < HEIGHT_SIZE; i++) {
		for (int j = 0; j < WIDTH_SIZE; j++) {
			StateInfo[i][j] = Node->getArrPos(i, j);
		}
	}
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
			else if (j == WIDTH_SIZE - 1 && i == HEIGHT_SIZE / 2) {
				cout << StateInfo[i][j] << " "
					<< game.at(game.size() - 1)->getHost();
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
		if (fileNum % 100 == 0) {
			cout << textLine << endl;
			cout << endl;
		}
		//cout << textLine<< endl;
		fileNum++;
		int reportNumber = INITIAL_ORDER,
			cho = INITIAL_ORDER, han = INITIAL_ORDER, victory = INITIAL_ORDER;
		bool flag = false;
		reportNumber = atoi(textLine.c_str());

		getline(file, textLine);
		if (textLine.compare("") != 0) {
			cho = atoi(textLine.c_str());
			getline(file, textLine);

			if (textLine.compare("") != 0) {
				han = atoi(textLine.c_str());
				getline(file, textLine);

				if (textLine.compare("") != 0) {
					victory = atoi(textLine.c_str());
				}
				else {
					Play *gameReport = new Play(reportNumber, cho, han, victory);
					return gameReport;
				}
			}
			else {
				Play *gameReport = new Play(reportNumber, cho, han, victory);
				return gameReport;
			}
		}
		else {
			Play *gameReport = new Play(reportNumber, cho, han, victory);
			return gameReport;
		}

		Play *gameReport = new Play(reportNumber, cho, han, victory);
		gameReport->initailize();
		int state_index = 1;
		while (getline(file, textLine)) {
			if (textLine.compare("\r\n") == 0 ||
				textLine.compare("\r") == 0 ||
				textLine.compare("\n") == 0) {
				return gameReport;
			}
			else {
				gameReport->createState(textLine);
			}
		}
		returnData = gameReport;
	}
	return returnData;
}
bool Play::getRightNode() {
	if (cho_order == INITIAL_ORDER ||
		han_order == INITIAL_ORDER ||
		victory == INITIAL_ORDER) {
		return false;
	}
	else {
		return true;
	}
}

int Play::GetWinner() {
	return victory;
}
