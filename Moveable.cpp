#include"Moveable.h"

Pos::Pos() {
	x = -1;
	y = -1;
}
Pos::Pos(int _x, int _y) {
	x = _x;
	y = _y;
}
bool Pos::operator== (Pos& p) {
	return x == p.x && y == p.y;
};
bool Pos::operator!= (Pos& p) {
	return !operator==(p);
};
bool Pos::isValidation() {
	if (x > 10)
		return false;
	if (x < 1)
		return false;
	if (y > 9)
		return false;
	if (y < 1)
		return false;

	return true;
}

bool moveable(char board[][WIDTH_SIZE], char c_board[][WIDTH_SIZE] , bool host) {

	int cnt = 0;
	Pos prr[2];
	Pos from;
	Pos to;

	//if (host == CHO_PLAY);

	for (int i = 1; i < HEIGHT_SIZE; i++) {
		for (int j = 1; j < WIDTH_SIZE; j++) {
			if (board[i][j] == c_board[i][j])
				continue;
			else {
				if (cnt == 2) return false;
				prr[cnt].y = i, prr[cnt].x = j;
				cnt++;
			}
		}
	}
	if (c_board[prr[0].y][prr[0].x] == '-') {
		from.x = prr[0].x;
		from.y = prr[0].y;
		to.x = prr[1].x;
		to.y = prr[1].y;

	}//출발지와 도착지를 구분한다.
	else {
		from.x = prr[1].x;
		from.y = prr[1].y;
		to.x = prr[0].x;
		to.y = prr[0].y;

	}
	if (host == CHO_PLAY) {
		//대문자만
		if (board[from.y][from.x] < 'A' || board[from.y][from.x] >'Z')
			return false;
	}
	else {
		//소문자만
		if (board[from.y][from.x] < 'a' || board[from.y][from.x] >'z')
			return false;

	}
	
		switch (board[from.y][from.x])
		{
		case 'j': case 'J':
			return moveAbleJol(from, to, board);
		case 'h': case 'H':
			return moveAbleMa(from, to, board);
		case 'p': case 'P':
			return moveAblePo(from, to, board);
		case 'x': case 'X':
			return moveAbleSang(from, to, board);
		case 'c': case 'C':
			return moveAbleCha(from, to, board);
		case 's': case 'S': case 'k': case 'K':
			return moveAbleGungAndSa(from, to, board);
		default:
			std::cout << " SIBAL MOVEABLE ERROR!!!!!" << std::endl;
			break;
		}
	return false;


}



bool isExistTeam(Pos cur, Pos dest ,char board[][WIDTH_SIZE]) {
	char _a = board[cur.y][cur.x];
	char _b = board[dest.y][dest.x];
	if ((_a >= 97 && _a <= 122) && (_b >= 97 && _b <= 122))
		return false;
	if ((_a >= 65 && _a <= 90) && (_b >= 65 && _b <= 90))
		return false;

	return true;
}//도착지에 같은팀이 존재하면 갈 수 없다.

 //Moveable Piece
 //Moveable Piece
bool moveAbleCha(Pos cur, Pos dest , char board[][WIDTH_SIZE]) {
	if (!isExistTeam(cur, dest , board))
		return false;

	if (cur.y == 2 && cur.x == 5) {
		if (dest.y == 1 && dest.x == 4 || cur.y == 1 && cur.x == 6 || cur.y == 3 && cur.x == 4 || cur.y == 3 && cur.x == 6)
			return true;
	} // 중앙
	if (cur.y == 1 && cur.x == 4) {
		if (dest.y == 2 && dest.x == 5) return true;
		if (dest.y == 3 && dest.x == 6) {
			if (board[2][5] == '-') return true;
			else return false;
		}
	}
	if (cur.y == 1 && cur.x == 6) {
		if (dest.y == 2 && dest.x == 5) return true;
		if (dest.y == 3 && dest.x == 4) {
			if (board[2][5] == '-') return true;
			else return false;
		}
	}
	if (cur.y == 3 && cur.x == 4) {
		if (dest.y == 2 && dest.x == 5) return true;
		if (dest.y == 1 && dest.x == 6) {
			if (board[2][5] == '-') return true;
			else return false;
		}
	}
	if (cur.y == 3 && cur.x == 6) {
		if (dest.y == 2 && dest.x == 5) return true;
		if (dest.y == 1 && dest.x == 4) {
			if (board[2][5] == '-') return true;
			else return false;
		}
	}


	if (cur.y == 9 && cur.x == 5) {
		if (dest.y == 8 && dest.x == 4 || cur.y == 8 && cur.x == 6 || cur.y == 10 && cur.x == 4 || cur.y == 10 && cur.x == 6)
			return true;
	} // 중앙
	if (cur.y == 8 && cur.x == 4) {
		if (dest.y == 9 && dest.x == 5) return true;
		if (dest.y == 10 && dest.x == 6) {
			if (board[9][5] == '-') return true;
			else return false;
		}
	}
	if (cur.y == 8 && cur.x == 6) {
		if (dest.y == 9 && dest.x == 5) return true;
		if (dest.y == 10 && dest.x == 4) {
			if (board[9][5] == '-') return true;
			else return false;
		}
	}
	if (cur.y == 10 && cur.x == 4) {
		if (dest.y == 9 && dest.x == 5) return true;
		if (dest.y == 8 && dest.x == 6) {
			if (board[9][5] == '-') return true;
			else return false;
		}
	}
	if (cur.y == 10 && cur.x == 6) {
		if (dest.y == 9 && dest.x == 5) return true;
		if (dest.y == 8 && dest.x == 4) {
			if (board[9][5] == '-') return true;
			else return false;
		}
	}


	int nx, ny;
	nx = cur.x - dest.x;
	ny = cur.y - dest.y;
	if (nx == 0) { // move forward y
		if (ny > 0) { // move up
			for (int i = dest.y + 1; i < cur.y; i++)
				if (board[i][cur.x] != '-')
					return false;
		}
		else { // move down
			for (int i = cur.y + 1; i < dest.y; i++)
				if (board[i][cur.x] != '-')
					return false;
		}
	}
	else { // move forward x
		if (nx > 0) { //move left
			for (int i = dest.x + 1; i < cur.x; i++)
				if (board[cur.y][i] != '-')
					return false;
		}
		else { //move right
			for (int i = cur.x + 1; i < dest.x; i++)
				if (board[cur.y][i] != '-')
					return false;

		}
	}
	return true;

} // cha
bool moveAbleGungAndSa(Pos cur, Pos dest , char board[][WIDTH_SIZE]) {// 한과 초를 구분해줘야 한다.
	if (!isExistTeam(cur, dest , board))
		return false;

	int px = cur.x - dest.x;
	int py = cur.y - dest.y;


	if (board[cur.y][cur.x] >= 97) { // 초 순서이다.
		if ((dest.y == 10 && (dest.x >= 4 && dest.x <= 6)) ||
			(dest.y == 9 && (dest.x >= 4 && dest.x <= 6)) ||
			(dest.y == 8 && (dest.x >= 4 && dest.x <= 6))) {
			if (cur.y == 10 && cur.x == 4) {
				if (dest.y == 9 && dest.x == 4)
					return true;
				if (dest.y == 9 && dest.x == 5)
					return true;
				if (dest.y == 10 && dest.x == 5)
					return true;
			}
			if (cur.y == 10 && cur.x == 5) {
				if (dest.y == 10 && dest.x == 4)
					return true;
				if (dest.y == 9 && dest.x == 5)
					return true;
				if (dest.y == 10 && dest.x == 6)
					return true;

			}
			if (cur.y == 10 && cur.x == 6) {
				if (dest.y == 10 && dest.x == 5)
					return true;
				if (dest.y == 9 && dest.x == 5)
					return true;
				if (dest.y == 9 && dest.x == 6)
					return true;

			}
			if (cur.y == 9 && cur.x == 4) {
				if (dest.y == 8 && dest.x == 4)
					return true;
				if (dest.y == 9 && dest.x == 5)
					return true;
				if (dest.y == 10 && dest.x == 4)
					return true;

			}
			if (cur.y == 9 && cur.x == 5) {
				if (dest.y == 10 && dest.x == 4)
					return true;
				if (dest.y == 10 && dest.x == 5)
					return true;
				if (dest.y == 10 && dest.x == 6)
					return true;
				if (dest.y == 9 && dest.x == 4)
					return true;
				if (dest.y == 9 && dest.x == 6)
					return true;
				if (dest.y == 8 && dest.x == 4)
					return true;
				if (dest.y == 8 && dest.x == 5)
					return true;
				if (dest.y == 8 && dest.x == 6)
					return true;

			}
			if (cur.y == 9 && cur.x == 6) {
				if (dest.y == 8 && dest.x == 6)
					return true;
				if (dest.y == 9 && dest.x == 5)
					return true;
				if (dest.y == 10 && dest.x == 6)
					return true;
			}
			if (cur.y == 8 && cur.x == 4) {
				if (dest.y == 8 && dest.x == 5)
					return true;
				if (dest.y == 9 && dest.x == 5)
					return true;
				if (dest.y == 9 && dest.x == 4)
					return true;

			}
			if (cur.y == 8 && cur.x == 5) {
				if (dest.y == 8 && dest.x == 4)
					return true;
				if (dest.y == 9 && dest.x == 5)
					return true;
				if (dest.y == 8 && dest.x == 6)
					return true;
			}
			if (cur.y == 8 && cur.x == 6) {
				if (dest.y == 8 && dest.x == 5)
					return true;
				if (dest.y == 9 && dest.x == 5)
					return true;
				if (dest.y == 9 && dest.x == 6)
					return true;

			}
		}


	}
	else { //한 순서이다.
		if ((dest.y == 1 && (dest.x >= 4 && dest.x <= 6)) ||
			(dest.y == 2 && (dest.x >= 4 && dest.x <= 6)) ||
			(dest.y == 3 && (dest.x >= 4 && dest.x <= 6))) {
			if (cur.y == 1 && cur.x == 4) {
				if (dest.y == 2 && dest.x == 4)
					return true;
				if (dest.y == 2 && dest.x == 5)
					return true;
				if (dest.y == 1 && dest.x == 5)
					return true;
			}
			if (cur.y == 1 && cur.x == 5) {
				if (dest.y == 1 && dest.x == 4)
					return true;
				if (dest.y == 2 && dest.x == 5)
					return true;
				if (dest.y == 1 && dest.x == 6)
					return true;

			}
			if (cur.y == 1 && cur.x == 6) {
				if (dest.y == 1 && dest.x == 5)
					return true;
				if (dest.y == 2 && dest.x == 5)
					return true;
				if (dest.y == 2 && dest.x == 6)
					return true;

			}
			if (cur.y == 2 && cur.x == 4) {
				if (dest.y == 3 && dest.x == 4)
					return true;
				if (dest.y == 2 && dest.x == 5)
					return true;
				if (dest.y == 1 && dest.x == 4)
					return true;

			}
			if (cur.y == 2 && cur.x == 5) {
				if (dest.y == 1 && dest.x == 4)
					return true;
				if (dest.y == 1 && dest.x == 5)
					return true;
				if (dest.y == 1 && dest.x == 6)
					return true;
				if (dest.y == 2 && dest.x == 4)
					return true;
				if (dest.y == 2 && dest.x == 6)
					return true;
				if (dest.y == 3 && dest.x == 4)
					return true;
				if (dest.y == 3 && dest.x == 5)
					return true;
				if (dest.y == 3 && dest.x == 6)
					return true;

			}
			if (cur.y == 2 && cur.x == 6) {
				if (dest.y == 3 && dest.x == 6)
					return true;
				if (dest.y == 2 && dest.x == 5)
					return true;
				if (dest.y == 1 && dest.x == 6)
					return true;
			}
			if (cur.y == 3 && cur.x == 4) {
				if (dest.y == 3 && dest.x == 5)
					return true;
				if (dest.y == 2 && dest.x == 5)
					return true;
				if (dest.y == 2 && dest.x == 4)
					return true;

			}
			if (cur.y == 3 && cur.x == 5) {
				if (dest.y == 3 && dest.x == 4)
					return true;
				if (dest.y == 2 && dest.x == 5)
					return true;
				if (dest.y == 3 && dest.x == 6)
					return true;
			}
			if (cur.y == 3 && cur.x == 6) {
				if (dest.y == 3 && dest.x == 5)
					return true;
				if (dest.y == 2 && dest.x == 5)
					return true;
				if (dest.y == 2 && dest.x == 6)
					return true;

			}
		}
	}


	/*int px = cur.x - dest.x;
	int py = cur.y - dest.y;

	if ((cur.y == 1 && (cur.x ==  || cur.x == 8)) ||
	(cur.y == 2 && (cur.x == 0 || cur.x == 2 || cur.x == 7 || cur.x == 9)) ||
	(cur.y == 3 && (cur.x == 1 || cur.x == 8))) {
	if (px*px + py*py > 2)
	return false;

	}*/
	return true;

} // gun
bool moveAbleJol(Pos cur, Pos dest, char board[][WIDTH_SIZE]) {

	if (!isExistTeam(cur, dest, board))
		return false;

	if (cur.y == 2 && cur.x == 5) {
		if (dest.y == 1 && dest.x == 4 || cur.y == 1 && cur.x == 6)
			return true;
	} // 중앙
	if (cur.y == 3 && cur.x == 4) {
		if (dest.y == 2 && dest.x == 5) return true;
	}
	if (cur.y == 3 && cur.x == 6) {
		if (dest.y == 2 && dest.x == 5) return true;
	}


	if (cur.y == 9 && cur.x == 5) {
		if (cur.y == 10 && cur.x == 4 || cur.y == 10 && cur.x == 6)
			return true;
	} // 중앙
	if (cur.y == 8 && cur.x == 4) {
		if (dest.y == 9 && dest.x == 5) return true;
	}
	if (cur.y == 8 && cur.x == 6) {
		if (dest.y == 9 && dest.x == 5) return true;
	}//대각선 처리 ! 
	 //////////////////////////////////////////////////////////////////////////////////////

	int ny = cur.y - dest.y;
	int nx = cur.x - dest.x;
	if (cur.x - 1 == dest.x || cur.x + 1 == dest.x)
		if (ny == 0)
			return true;
	if (board[cur.y][cur.x] >= 97) {//초 차례이다.
		if (ny < 0)
			return false;
	}
	else { // 한차례이다.
		if (ny > 0)
			return false;
	}
	if (abs(ny) != 1)
		return false;
	return true;

} // jol
bool moveAbleMa(Pos cur, Pos dest, char board[][WIDTH_SIZE]) {

	if (!isExistTeam(cur, dest , board))
		return false;

	int nx = cur.x - dest.x;
	int ny = cur.y - dest.y;

	if (nx == 2 && abs(ny) == 1 && board[cur.y][cur.x - 1] == '-') {
		return true;
	}
	else if (nx == -2 && abs(ny) == 1 && board[cur.y][cur.x + 1] == '-') {
		return true;
	}
	else if (ny == 2 && abs(nx) == 1 && board[cur.y - 1][cur.x] == '-') {
		return true;
	}
	else if (ny == -2 && abs(nx) == 1 && board[cur.y + 1][cur.x] == '-') {
		return true;
	}
	return false;


} // ma
bool moveAblePo(Pos cur, Pos dest , char board[][WIDTH_SIZE]) {

	if (!isExistTeam(cur, dest , board))
		return false;

	if (board[dest.y][dest.x] == 'p' || board[dest.y][dest.x] == 'P') //목적지에 포가 있으면 갈 수 없다.
		return false;

	if (cur.y == 1 && cur.x == 4) {
		if (dest.y == 3 && dest.x == 6) {
			if (board[2][5] != '-' && board[2][5] != 'p' && board[2][5] != 'P') return true;
			else return false;
		}
	}
	if (cur.y == 1 && cur.x == 6) {
		if (dest.y == 3 && dest.x == 4) {
			if (board[2][5] != '-' && board[2][5] != 'p' && board[2][5] != 'P') return true;
			else return false;
		}
	}
	if (cur.y == 3 && cur.x == 4) {
		if (dest.y == 1 && dest.x == 6) {
			if (board[2][5] != '-' && board[2][5] != 'p' && board[2][5] != 'P') return true;
			else return false;
		}
	}
	if (cur.y == 3 && cur.x == 6) {
		if (dest.y == 1 && dest.x == 4) {
			if (board[2][5] != '-' && board[2][5] != 'p' && board[2][5] != 'P') return true;
			else return false;
		}
	}

	if (cur.y == 8 && cur.x == 4) {

		if (dest.y == 10 && dest.x == 6) {
			if (board[9][5] == '-' &&  board[9][5] != 'p' && board[9][5] != 'P') return true;
			else return false;
		}
	}
	if (cur.y == 8 && cur.x == 6) {

		if (dest.y == 10 && dest.x == 4) {
			if (board[9][5] == '-' &&  board[9][5] != 'p' && board[9][5] != 'P') return true;
			else return false;
		}
	}
	if (cur.y == 10 && cur.x == 4) {

		if (dest.y == 8 && dest.x == 6) {
			if (board[9][5] == '-' &&  board[9][5] != 'p' && board[9][5] != 'P') return true;
			else return false;
		}
	}
	if (cur.y == 10 && cur.x == 6) {

		if (dest.y == 8 && dest.x == 4) {
			if (board[9][5] == '-' &&  board[9][5] != 'p' && board[9][5] != 'P') return true;
			else return false;
		}
	}



	int nx, ny;
	nx = cur.x - dest.x;
	ny = cur.y - dest.y;

	int piece_count = 0;

	if (nx == 0) {
		if (ny > 0) {
			for (int i = cur.y - 1; i > dest.y; i--) {
				if (board[i][cur.x] != '-')
					piece_count++;
				if (board[i][cur.x] == 'p' || board[i][cur.x] == 'P')
					return false;

			}
		}
		else {
			for (int i = cur.y + 1; i < dest.y; i++) {
				if (board[i][cur.x] != '-')
					piece_count++;
				if (board[i][cur.x] == 'p' || board[i][cur.x] == 'P')
					return false;
			}
		}
	}
	else {
		if (nx > 0) {
			for (int i = cur.x - 1; i > dest.x; i--) {
				if (board[cur.y][i] != '-') //가는 길목에 말이 1개인지를 파악한다.
					piece_count++;
				if (board[cur.y][i] == 'p' || board[cur.y][i] == 'P') //가는 길목에 포가 있으면 넘지 못한다.
					return false;
			}
		}
		else { //move forward up
			for (int i = cur.x + 1; i < dest.x; i++) {
				if (board[cur.y][i] != '-')
					piece_count++;
				if (board[cur.y][i] == 'p' || board[cur.y][i] == 'P')
					return false;
			}

		}
	}
	if (piece_count == 1) //목적지까지 말이 하나만 존재해야 갈 수 있다.
		return true;
	else
		return false;
} // po
bool moveAbleSang(Pos cur, Pos dest , char board[][WIDTH_SIZE]) {

	if (!isExistTeam(cur, dest , board))
		return false;
	int nx = cur.x - dest.x;
	int ny = cur.y - dest.y;

	if (nx == 3 && ny == 2 && board[cur.y][cur.x - 1] == '-' && board[cur.y - 1][cur.x - 2] == '-') {
		return true;
	}
	else if (nx == 3 && ny == -2 && board[cur.y][cur.x - 1] == '-' && board[cur.y + 1][cur.x - 2] == '-') {
		return true;
	}
	else if (nx == -3 && ny == 2 && board[cur.y][cur.x + 1] == '-' && board[cur.y - 1][cur.x + 2] == '-') {
		return true;
	}
	else if (nx == -3 && ny == -2 && board[cur.y][cur.x + 1] == '-' && board[cur.y + 1][cur.x + 2] == '-') {
		return true;
	}
	else if (ny == 3 && nx == -2 && board[cur.y - 1][cur.x] == '-' && board[cur.y - 2][cur.x + 1] == '-') {
		return true;
	}
	else if (ny == 3 && nx == 2 && board[cur.y - 1][cur.x] == '-' && board[cur.y - 2][cur.x - 1] == '-') {
		return true;
	}
	else if (ny == -3 && nx == 2 && board[cur.y + 1][cur.x] == '-' && board[cur.y + 2][cur.x - 1] == '-') {
		return true;
	}
	else if (ny == -3 && nx == -2 && board[cur.y + 1][cur.x] == '-' && board[cur.y + 2][cur.x + 1] == '-') {
		return true;
	}
	return false;

} //sang



