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
bool Pos::operator!= (Pos& p){
	return !operator==(p);
};
bool Pos::isValidation(){
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

bool getTeam(char piece)
{
    return piece >= 97 ? true : false;
    //대문자일 경우
}





bool isInCastle(Pos cur , Pos dest)  // 목적지와 출발지가 같은 궁성 내부일 경우를 검사한다.
{
    int nx = cur.x;
    int ny = cur.y;
    int dx = dest.x;
    int dy = dest.y;
    if((nx >3 && nx <7) && (dx >3 && dx <7 ))
    {
        if((((dy > 0 && dy < 4))&&((ny > 0 && ny < 4)))|| ((ny > 7 && ny < 11))&&((dy > 7 && dy < 11))) return true;
    }
    return false;
    
}
void maskingEightWay(int mask[][3] , Pos cur)
{
    int nx = cur.x -4 ;
    int ny = cur.y ;
    ny = ny > 3 ? ny -8 : ny - 1;
    
    if(ny - 1 > -1 ) mask[ny-1][nx] = 1;
    if(ny + 1 < 3 ) mask[ny+1][nx] = 1;
    if(nx - 1 > -1) mask[ny][nx-1]  = 1;
    if(nx + 1 < 3 ) mask[ny][nx+1] = 1;
    
    if(ny - 1 > -1 && nx - 1 > -1) mask[ny-1][nx-1] = 1;
    if(ny - 1 > -1 && nx + 1 < 3) mask[ny-1][nx+1] = 1;
    if(ny + 1 < 3 && nx - 1 > -1) mask[ny+1][nx-1] = 1;
    if(ny + 1 < 3 && nx + 1 < 3) mask[ny+1][nx+1] = 1;
}
void maskingFourWay(int mask[][3] , Pos cur)
{
    int nx = cur.x -4 ;
    int ny = cur.y ;
    ny = ny > 3 ? ny -8 : ny - 1;
    
    if(ny - 1 > -1 ) mask[ny-1][nx] = 1;
    if(ny + 1 < 3 ) mask[ny+1][nx] = 1;
    if(nx - 1 > -1) mask[ny][nx-1]  = 1;
    if(nx + 1 < 3 ) mask[ny][nx+1] = 1;
}

void maskingTwoStep(int mask[][3] , Pos cur)
{
    int nx = cur.x -4 ;
    int ny = cur.y ;
    ny = ny > 3 ? ny -8 : ny - 1;
    if(nx -2 > -1) mask[ny][nx-2] = 1;
    if(ny -2 > -1) mask[ny-2][nx] = 1;
    if(nx +2 < 3) mask[ny][nx+2] = 1;
    if(ny +2 < 3) mask[ny+2][nx] = 1;
    if(ny +2 <3 && nx +2 <3) mask[ny+2][nx+2] = 1;
    if(ny +2 <3 && nx -2 >-1) mask[ny+2][nx-2] = 1;
    if(ny -2 > -1 && nx +2 <3) mask[ny-2][nx+2] = 1;
    if(ny-2 > -1 && nx -2 > -1) mask[ny-2][nx-2] = 1;
    
}


void determineMasking(Pos cur , Pos dest , int mask[][3] , char piece)
{
    
    int nx = cur.x % 7;
    int ny = cur.y % 7;
    for(int i = 0 ; i < 3 ; i ++) for(int j = 0 ; j < 3 ; j ++) mask[i][j] = 0;
    if(piece == 'S' || piece == 's' || piece == 'K' || piece == 'k' || piece =='J' || piece =='j')
    {
        if((ny ==2 && nx == 5) || (((ny == 1 || ny == 3) &&(nx ==4 || nx == 6)))) maskingEightWay(mask , cur);
        else maskingFourWay(mask,cur);
    }
    if(piece =='P' || piece == 'p')
    {
        maskingTwoStep(mask,cur);
    }
    if(piece == 'C' || piece == 'c')
    {
        if((ny ==1 && nx == 5) || ((ny == 1 || ny == 3) &&(nx ==4 || nx == 6))) maskingEightWay(mask , cur);
        else maskingFourWay(mask,cur);
        maskingTwoStep(mask,cur);
    }
    
}




void save_moveable_board(vector<Board> &boardPush , char board[][WIDTH_SIZE] , int turn){
	// char tmp_board[HEIGHT_SIZE][WIDTH_SIZE];
	char tmp_board[HEIGHT_SIZE][WIDTH_SIZE];
	Board tmpObj;
	if(turn == CHO_PLAY){
		for(int i = 1 ; i < HEIGHT_SIZE ; i ++){
			for(int j = 1 ; j < WIDTH_SIZE ; j++){
				if(board[i][j] > 'A' && board[i][j] < 'Z'){
					for(int y = 1 ;  y < HEIGHT_SIZE; y++){
						for(int x = 1 ; x < WIDTH_SIZE; x++){
							if(board[y][x] > 'A' && board[y][x] < 'Z'){
							}else{
								memcpy(tmp_board , board , sizeof(char) * HEIGHT_SIZE * WIDTH_SIZE);
								tmp_board[i][j] = '-';
								tmp_board[y][x] = board[i][j];
								if(moveable(board , tmp_board, false)){
									tmpObj.setBoard(tmp_board);
									boardPush.push_back(tmpObj);
								}
							}
						
						}
					}
				
				
				
				}

			}
			
		}
	}
	else{ // HAN_PLAY
        for(int i = 1 ; i < HEIGHT_SIZE ; i ++){
            for(int j = 1 ; j < WIDTH_SIZE ; j++){
                if(board[i][j] > 'a' && board[i][j] < 'z'){
                    for(int y = 1 ;  y < HEIGHT_SIZE; y++){
                        for(int x = 1 ; x < WIDTH_SIZE; x++){
                            if(board[y][x] > 'a' && board[y][x] < 'z'){
                            }else{
                                memcpy(tmp_board , board , sizeof(char) * HEIGHT_SIZE * WIDTH_SIZE);
                                tmp_board[i][j] = '-';
                                tmp_board[y][x] = board[i][j];
                                if(moveable(board , tmp_board, false)){
                                    tmpObj.setBoard(tmp_board);
                                    boardPush.push_back(tmpObj);
                                }
                            }
                            
                        }
                    }
                }
                
            }
            
        }

	
	
	
	}
	//std::cout << "SAVE COMPLETE " << std::endl;
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

	}//������� �������� �����Ѵ�.
	else {
		from.x = prr[1].x;
		from.y = prr[1].y;
		to.x = prr[0].x;
		to.y = prr[0].y;

	}
	if (host == CHO_PLAY) {
		//�빮�ڸ�
		if (board[from.y][from.x] < 'A' || board[from.y][from.x] >'Z')
			return false;
	}
	else {
		//�ҹ��ڸ�
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
}//�������� �������� �����ϸ� �� �� ����.

 //Moveable Piece
bool moveAbleCha(Pos cur, Pos dest , char board[][WIDTH_SIZE]) {
    if (!isExistTeam(cur, dest , board))
        return false;
    
    if(isInCastle(cur,dest))
    {
        int mask[3][3];
        determineMasking(cur,dest,mask,board[cur.y][cur.x]);
        int nx = dest.x -4 ;
        int ny = dest.y ;
        ny = ny > 3 ? ny -8 : ny - 1;
        for(int i = 0 ; i < 3 ; i ++ )
        {
            for(int j = 0 ; j < 3 ; j++) cout <<mask[i][j]<< " ";
            cout << endl;
        }
        
        
        if(mask[ny][nx] == 1) return true;
        else return false;
        
    }
    
    int nx = cur.x - dest.x;
    int ny = cur.y - dest.y;
    if(nx != 0 && ny != 0)
        return false;
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


bool moveAbleGungAndSa(Pos cur, Pos dest , char board[][WIDTH_SIZE])
{
    if (!isExistTeam(cur, dest , board)) return false;
    
    if(isInCastle(cur,dest))
    {
        int mask[3][3];
        determineMasking(cur,dest,mask,board[cur.y][cur.x]);
        int nx = dest.x -4 ;
        int ny = dest.y ;
        ny = ny > 3 ? ny -8 : ny - 1;
        if(mask[ny][nx] == 1) return true;
        else return false;
    }
    return false;
    
} // gung
bool moveAbleJol(Pos cur, Pos dest, char board[][WIDTH_SIZE]) {
    
    if (!isExistTeam(cur, dest, board)) return false;
    int ny = cur.y - dest.y;
    int nx = cur.x - dest.x;
    
    if (board[cur.y][cur.x] > 'a' && ny < 0)return false;
    else if(board[cur.y][cur.x] < 'a' && ny > 0) return false;
    
    if(isInCastle(cur,dest))
    {
        int mask[3][3];
        determineMasking(cur,dest,mask,board[cur.y][cur.x]);
        int x = dest.x -4 ;
        int y = dest.y ;
        y = y > 3 ? y -8 : y - 1;
        if(mask[y][x] == 1) return true;
        else return false;
        
    }
    if(ny > 1 || nx > 1 || abs(ny)+abs(nx) != 1) return false;
    if (cur.x - 1 == dest.x || cur.x + 1 == dest.x) return true;
    if (abs(ny) != 1) return false;
    return false;
    
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
    
    if (board[dest.y][dest.x] == 'p' || board[dest.y][dest.x] == 'P')
        return false;
    
    if(isInCastle(cur,dest))
    {
        int mask[3][3];
        determineMasking(cur,dest,mask,board[cur.y][cur.x]);
        int nx = dest.x -4 ;
        int ny = dest.y ;
        ny = ny > 3 ? ny -8 : ny - 1;
        
        int avgx = (cur.x + dest.x) / 2;
        int avgy = (cur.y + dest.y) / 2;
        //출발지와 목적지 사이에 빈칸또는 포가없으면 이동이 가능하다.
        if(mask[ny][nx] == 1 && (board[avgy][avgx] != '-' && board[avgy][avgx] != 'p' && board[avgy][avgx] != 'P')) return true;
        else return false;
        
    }
    
    int nx, ny;
    nx = cur.x - dest.x;
    ny = cur.y - dest.y;
    
    if(nx != 0 && ny != 0)
        return false;
    
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
                if (board[cur.y][i] != '-')
                    piece_count++;
                if (board[cur.y][i] == 'p' || board[cur.y][i] == 'P')
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
    if (piece_count == 1)
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



