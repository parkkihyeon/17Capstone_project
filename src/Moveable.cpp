#include "Moveable.h"

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
void Pos::operator=(Pos& p)
{
    x = p.x ;
    y = p.y ;
}
void Moveable::operator=(Moveable& opr)
{
    for(int i = 0 ; i < 11 ; i++) for(int j = 0 ; j < 10 ; j++) board[i][j] = opr.board[i][j];
    cur = opr.cur;
    dest = opr.dest;
    host = opr.host;
    
}

bool Moveable::isExistTeam(char piece)
{
    return piece >= 97 ? true : false;
    //대문자일 경우
}

bool Moveable::getTeam(char piece)
{
    return piece >= 97 ? true : false;
    //대문자일 경우
}

Moveable::Moveable(char board[][WIDTH_SIZE], char c_board[][WIDTH_SIZE] , bool host)
{
    int cnt = 0;
    Pos prr[2];
    ispossible = true;
    
    for (int i = 1; i < HEIGHT_SIZE; i++)
    {
        for (int j = 1; j < WIDTH_SIZE; j++)
        {
            if (board[i][j] == c_board[i][j])
                continue;
            else
            {
                if (cnt == 2) ispossible = false;;
                prr[cnt].y = i, prr[cnt].x = j;
                cnt++;
            }
        }
    }
    if (c_board[prr[0].y][prr[0].x] == '-')
    {
        cur.x = prr[0].x;
        cur.y = prr[0].y;
        dest.x = prr[1].x;
        dest.y = prr[1].y;
        
    }
    else
    {
        cur.x = prr[1].x;
        cur.y = prr[1].y;
        dest.x = prr[0].x;
        dest.y = prr[0].y;
        
    }
    for(int i = 0 ; i < 11 ; i ++) for(int j = 0 ; j < 10 ; j++) this->board[i][j] = board[i][j];
    
    this->host = host;
    
    
    if (host == CHO_PLAY)
    {
        if (board[cur.y][cur.x] < 'A' || board[cur.y][cur.x] >'Z') ispossible = false;
            
    }
    else
    {
        if (board[cur.y][cur.x] < 'a' || board[cur.y][cur.x] >'z') ispossible =false;
        
    }
    
}
Moveable::Moveable(char board[][WIDTH_SIZE])
{
     for(int i = 0 ; i < 11 ; i ++) for(int j = 0 ; j < 10 ; j++) this->board[i][j] = board[i][j];
}

char Moveable::getPiece()
{
    return board[cur.y][cur.x];
}


bool startMoveable(Moveable obj)
{
    Moveable *JKPiece;
    if(!obj.getIsPossible()) return false;
    
    switch (obj.getPiece())
    {
        case 'j': case 'J':
            JKPiece = new MoveableJol(obj.board , obj.cur , obj.dest, obj.host);
            break;
        case 'h': case 'H':
            JKPiece = new MoveableMa(obj.board , obj.cur , obj.dest, obj.host);
            break;
        case 'p': case 'P':
            JKPiece = new MoveablePo(obj.board , obj.cur , obj.dest, obj.host);
            break;
        case 'x': case 'X':
           JKPiece = new MoveableSang(obj.board , obj.cur , obj.dest, obj.host);
            break;
        case 'c': case 'C':
            JKPiece = new MoveableCha(obj.board , obj.cur , obj.dest, obj.host);
            break;
        case 's': case 'S': case 'k': case 'K':
           JKPiece = new MoveableGungAndSa(obj.board , obj.cur , obj.dest, obj.host);
            break;
        default:
            break;
    }
    
    return JKPiece->isMoveable();
}


/*****************isMoveable구현 ********************/


bool Moveable::isMoveable()
{
    return false;
}

bool MoveableJol::isMoveable()
{
    cout << " JOL isMoveable" <<endl;
    
    if (!isExistTeam(board[cur.y][cur.x])) return false;
    int ny = cur.y - dest.y;
    int nx = cur.x - dest.x;
    
    if (board[cur.y][cur.x] > 'a' && ny < 0)return false;
    else if(board[cur.y][cur.x] < 'a' && ny > 0) return false;
    
    if(MaskingInCastle::isInCastle())
    {
        
        MaskingInCastle::determineMasking();
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
    
    
    
    return false;
}
bool MoveableGungAndSa::isMoveable()
{
    
    cout << "GungAndSa isMoveable"<<endl;
    
    if (!isExistTeam(Moveable::getPiece())) return false;
    
    if(isInCastle())
    {
        int mask[3][3];
        determineMasking();
        int nx = dest.x -4 ;
        int ny = dest.y ;
        ny = ny > 3 ? ny -8 : ny - 1;
        if(mask[ny][nx] == 1) return true;
        else return false;
    }
    
    return false;
}
bool MoveableCha::isMoveable()
{
    cout << "Cha isMovable"<<endl;
    
    if (!isExistTeam(Moveable::getPiece()))
        return false;
    
    if(isInCastle())
    {
        int mask[3][3];
        determineMasking();
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

}
bool MoveablePo::isMoveable()
{
    if (!isExistTeam(Moveable::getPiece()))
        return false;
    
    if (board[dest.y][dest.x] == 'p' || board[dest.y][dest.x] == 'P')
        return false;
    
    if(isInCastle())
    {
        int mask[3][3];
        determineMasking();
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
    
}


bool MoveableSang::isMoveable()
{
    if (!isExistTeam(Moveable::getPiece()))
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

}
bool MoveableMa::isMoveable()
{
    
    if (!isExistTeam(Moveable::getPiece()))
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
}

/********************MaskingInCastle **************************/

bool MaskingInCastle::isInCastle()
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

void MaskingInCastle::determineMasking()
{
    
    char piece = Moveable::getPiece();
    int nx = cur.x % 7;
    int ny = cur.y % 7;
    for(int i = 0 ; i < 3 ; i ++) for(int j = 0 ; j < 3 ; j ++) mask[i][j] = 0;
    if(piece == 'S' || piece == 's' || piece == 'K' || piece == 'k' || piece =='J' || piece =='j')
    {
        if((ny ==2 && nx == 5) || (((ny == 1 || ny == 3) &&(nx ==4 || nx == 6)))) maskingEightWay();
        else maskingFourWay();
    }
    if(piece =='P' || piece == 'p')
    {
        maskingTwoStep();
    }
    if(piece == 'C' || piece == 'c')
    {
        if((ny ==1 && nx == 5) || ((ny == 1 || ny == 3) &&(nx ==4 || nx == 6))) maskingEightWay();
        else maskingFourWay();
        maskingTwoStep();
    }
}

void MaskingInCastle::maskingTwoStep()
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

void MaskingInCastle::maskingFourWay()
{
    int nx = cur.x -4 ;
    int ny = cur.y ;
    ny = ny > 3 ? ny -8 : ny - 1;
    
    if(ny - 1 > -1 ) mask[ny-1][nx] = 1;
    if(ny + 1 < 3 ) mask[ny+1][nx] = 1;
    if(nx - 1 > -1) mask[ny][nx-1]  = 1;
    if(nx + 1 < 3 ) mask[ny][nx+1] = 1;
}


void MaskingInCastle::maskingEightWay()
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



