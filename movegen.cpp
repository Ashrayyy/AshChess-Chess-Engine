#include<bits/stdc++.h>
using namespace std;
#define pb push_back

vector<pair<int,int>> knightMoves;
vector<pair<int,int>> kingMoves;

bool isSame(int a, int b){
    if((a>0 && b>0) || (a<0 && b<0)) return true;
    return false;
}

bool isDifferent(int a, int b){
    if((a>0 && b<0) || (a<0 && b>0)) return true;
    return false;
}

bool isInvalid(int a, int b){
    return (a<0 || a>=8 || b<0 || b>=8);
}

void movegenInit(){
    kingMoves.pb({1,1});
    kingMoves.pb({1,0});
    kingMoves.pb({1,-1});
    kingMoves.pb({-1,1});
    kingMoves.pb({-1,0});
    kingMoves.pb({-1,-1});
    kingMoves.pb({0,1});
    kingMoves.pb({0,-1});
    knightMoves.pb({-2,-1});
    knightMoves.pb({-2,1});
    knightMoves.pb({2,-1});
    knightMoves.pb({2,1});
    knightMoves.pb({-1,2});
    knightMoves.pb({-1,-2});
    knightMoves.pb({1,-2});
    knightMoves.pb({1,2});
}

vector<pair<int,int>> possibleRookMoves(pair<int,int> pos, vector<vector<int>> &board){
    int val = board[pos.first][pos.second];
    vector<pair<int,int>> moves;
    for(int i=pos.first+1;i<8;i++){
        if(isSame(val,board[i][pos.second]))break;
        moves.pb({i,pos.second});
        if(isDifferent(val,board[i][pos.second])) break;
    }
    for(int i=pos.first-1;i>=0;i--){
        if(isSame(val,board[i][pos.second]))break;
        moves.pb({i,pos.second});
        if(isDifferent(val,board[i][pos.second])) break;
    }
    for(int i=pos.second-1;i>=0;i--){
        if(isSame(val,board[pos.first][i]))break;
        moves.pb({pos.first,i});
        if(isDifferent(val,board[pos.first][i])) break;
    }
    for(int i=pos.second+1;i<8;i++){
        if(isSame(val,board[pos.first][i]))break;
        moves.pb({pos.first,i});
        if(isDifferent(val,board[pos.first][i])) break;
    }
    return moves;
}

vector<pair<int,int>> possibleKnightMoves(pair<int,int> pos, vector<vector<int>> &board){
    if(knightMoves.size()==0)movegenInit();
    int val = board[pos.first][pos.second];
    vector<pair<int,int>> moves;
    for(auto xy:knightMoves){
        int nx=pos.first+xy.first;
        int ny=pos.second+xy.second;
        if(isInvalid(nx,ny))continue;;
        if(isSame(val,board[nx][ny])) continue;
        moves.pb({nx,ny});
    }
    return moves;
}

vector<pair<int,int>> possibleBishopMoves(pair<int,int> pos, vector<vector<int>> &board){
    int val = board[pos.first][pos.second];
    vector<pair<int,int>> moves;
    int j=pos.second;
    for(int i=pos.first+1;i<8;i++){
        j++;
        if(isInvalid(i,j)) break;
        if(isSame(val,board[i][j])) break;
        moves.pb({i,j});
        if(isDifferent(val,board[i][j])) break;
    }
    j=pos.second;
    for(int i=pos.first+1;i<8;i++){
        j--;
        if(isInvalid(i,j))break;
        if(isSame(val,board[i][j]))break;
        moves.pb({i,j});
        if(isDifferent(val,board[i][j])) break;
    }
    j=pos.second;
    for(int i=pos.first-1;i>=0;i--){
        j++;
        if(isInvalid(i,j))break;
        if(isSame(val,board[i][j]))break;
        moves.pb({i,j});
        if(isDifferent(val,board[i][j])) break;
    }
    j=pos.second;
    for(int i=pos.first-1;i>=0;i--){
        j--;
        if(isInvalid(i,j))break;
        if(isSame(val,board[i][j]))break;
        moves.pb({i,j});
        if(isDifferent(val,board[i][j])) break;
    }
    return moves;
}

vector<pair<int,int>> possibleQueenMoves(pair<int,int> pos, vector<vector<int>> &board){
    int val = board[pos.first][pos.second];
    vector<pair<int,int>> moves;
    auto dMoves = possibleBishopMoves(pos,board);
    auto fMoves = possibleRookMoves(pos,board);
    for(auto &move:dMoves) moves.pb(move);
    for(auto &move:fMoves) moves.pb(move);
    return moves;
}

vector<pair<int,int>> possibleKingMoves(pair<int,int> pos, vector<vector<int>> &board){
    if(kingMoves.size()==0)movegenInit();
    int val = board[pos.first][pos.second];
    vector<pair<int,int>> moves;
    for(auto xy:kingMoves){
        int nx=pos.first+xy.first;
        int ny=pos.second+xy.second;
        if(isInvalid(nx,ny))continue;;
        if(isSame(val,board[nx][ny])) continue;
        moves.pb({nx,ny});
    }
    return moves;
}

vector<pair<int,int>> possiblePawnMoves(pair<int,int> pos, vector<vector<int>> &board){
    int val = board[pos.first][pos.second];
    vector<pair<int,int>> moves;
    if(val<0){
        if(pos.first==1 && board[3][pos.second]==0 && board[2][pos.second]==0)moves.pb({3,pos.second});
        if(!isInvalid(pos.first+1,pos.second) && board[pos.first+1][pos.second]==0) moves.pb({pos.first+1,pos.second});
        if(!isInvalid(pos.first+1,pos.second-1) && isSame(board[pos.first+1][pos.second-1],-val)) moves.pb({pos.first+1,pos.second-1});
        if(!isInvalid(pos.first+1,pos.second+1) && isSame(board[pos.first+1][pos.second+1],-val)) moves.pb({pos.first+1,pos.second+1});
    }
    else{
        if(pos.first==6 && board[4][pos.second]==0 && board[5][pos.second]==0)moves.pb({4,pos.second});
        if(!isInvalid(pos.first-1,pos.second) && board[pos.first-1][pos.second]==0) moves.pb({pos.first-1,pos.second});
        if(!isInvalid(pos.first-1,pos.second-1) && isSame(board[pos.first-1][pos.second-1],-val)) moves.pb({pos.first-1,pos.second-1});
        if(!isInvalid(pos.first-1,pos.second+1) && isSame(board[pos.first-1][pos.second+1],-val)) moves.pb({pos.first-1,pos.second+1});
    }
    return moves;
}

vector<vector<pair<int,int>>> allPosibleMoves(int color, vector<vector<int>> board){
    // i will put color as 1 or -1
    vector<vector<pair<int,int>>> moves;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            vector<pair<int,int>> peiceMoves;
            if(board[i][j] * color > 0){
                if(abs(board[i][j])==10) peiceMoves = possiblePawnMoves({i,j},board);
                if(abs(board[i][j])==30) peiceMoves = possibleKnightMoves({i,j},board);
                if(abs(board[i][j])==31) peiceMoves = possibleBishopMoves({i,j},board);
                if(abs(board[i][j])==50) peiceMoves = possibleRookMoves({i,j},board);
                if(abs(board[i][j])==90) peiceMoves = possibleQueenMoves({i,j},board);
                if(abs(board[i][j])==1000) peiceMoves = possibleKingMoves({i,j},board);
            }
            for(auto move:peiceMoves){
                vector<pair<int,int>> iMove;
                iMove.pb({i,j});
                iMove.pb({move.first,move.second});
                moves.pb(iMove);
            }
        }
    }

    // or instead, i will try {checks} then {peice takes bigger peice} then {blank moves} and at last {sacrifices}
    sort(moves.begin(),moves.end(),[&board](vector<pair<int,int>> &a, vector<pair<int,int>> &b){
        auto pPosa=a[0],nPosa=a[1];
        auto pPosb=b[0],nPosb=b[1];
        int diff1 = (abs(board[nPosa.first][nPosa.second])==0 ? 0 : (abs(board[nPosa.first][nPosa.second])-abs(board[pPosa.first][pPosa.second])));
        int diff2 = (abs(board[nPosb.first][nPosb.second])==0 ? 0 : (abs(board[nPosb.first][nPosb.second])-abs(board[pPosb.first][pPosb.second])));
        return diff1>diff2;
        return (abs(board[nPosa.first][nPosa.second])-abs(board[pPosa.first][pPosa.second]))>(abs(board[nPosb.first][nPosb.second])-abs(board[pPosb.first][pPosb.second]));
    });
    return moves;
}

bool checkIfUnderAttack(pair<int,int> pos, vector<vector<int>> &board, int color){
    int val = color;

    // Bishop and Queen Checks
    int j=pos.second;
    for(int i=pos.first+1;i<8;i++){
        j++;
        if(isInvalid(i,j)) break;
        if(isSame(val,board[i][j])) break;
        if(isDifferent(val,board[i][j])){
            if(abs(board[i][j]) == 90 || abs(board[i][j]) == 31) return true;
        }
    }
    j=pos.second;
    for(int i=pos.first+1;i<8;i++){
        j--;
        if(isInvalid(i,j))break;
        if(isSame(val,board[i][j]))break;
        if(isDifferent(val,board[i][j])){
            if(abs(board[i][j]) == 90 || abs(board[i][j]) == 31) return true;
        }
    }
    j=pos.second;
    for(int i=pos.first-1;i>=0;i--){
        j++;
        if(isInvalid(i,j))break;
        if(isSame(val,board[i][j]))break;
        if(isDifferent(val,board[i][j])){
            if(abs(board[i][j]) == 90 || abs(board[i][j]) == 31) return true;
        }
    }
    j=pos.second;
    for(int i=pos.first-1;i>=0;i--){
        j--;
        if(isInvalid(i,j))break;
        if(isSame(val,board[i][j]))break;
        if(isDifferent(val,board[i][j])){
            if(abs(board[i][j]) == 90 || abs(board[i][j]) == 31) return true;
        }
    }
    
    // Rook and Queen checks 
    for(int i=pos.first+1;i<8;i++){
        if(isSame(val,board[i][pos.second]))break;
        if(isDifferent(val,board[i][pos.second])){
            if(abs(board[i][pos.second]) == 90 || abs(board[i][pos.second]) == 50) return true;
        }
    }
    for(int i=pos.first-1;i>=0;i--){
        if(isSame(val,board[i][pos.second]))break;
        if(isDifferent(val,board[i][pos.second])){
            if(abs(board[i][pos.second]) == 90 || abs(board[i][pos.second]) == 50) return true;
        }
    }
    for(int i=pos.second-1;i>=0;i--){
        if(isSame(val,board[pos.first][i]))break;
        if(isDifferent(val,board[pos.first][i])){
            if(abs(board[pos.first][i]) == 90 || abs(board[pos.first][i]) == 50) return true;
        }
    }
    for(int i=pos.second+1;i<8;i++){
        if(isSame(val,board[pos.first][i]))break;
        if(isDifferent(val,board[pos.first][i])){
            if(abs(board[pos.first][i]) == 90 || abs(board[pos.first][i]) == 50) return true;
        }
    }

    // knight checks
    for(auto xy:knightMoves){
        int nx=pos.first+xy.first;
        int ny=pos.second+xy.second;
        if(isInvalid(nx,ny))continue;;
        if(isDifferent(val,board[nx][ny]) && abs(board[nx][ny])==30) return true;
    }

    // king checks
    for(auto xy:kingMoves){
        int nx=pos.first+xy.first;
        int ny=pos.second+xy.second;
        if(isInvalid(nx,ny))continue;;
        if(isDifferent(val,board[nx][ny]) && abs(board[nx][ny])==1000) return true;
    }

    // pawns checks
    if(color > 0){
        bool left = (!isInvalid(pos.first-1,pos.second-1) && (board[pos.first-1][pos.second-1]==-10));
        bool right = (!isInvalid(pos.first-1,pos.second+1) && (board[pos.first-1][pos.second+1]==-10));
        if(left || right){
            return true;
        }
    }
    else{
        bool left = (!isInvalid(pos.first+1,pos.second-1) && (board[pos.first+1][pos.second-1]==10));
        bool right = (!isInvalid(pos.first+1,pos.second+1) && (board[pos.first+1][pos.second+1]==10));
        if(left || right){
            return true;
        }
    }
    return false;
}