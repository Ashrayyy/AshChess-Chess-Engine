#include<bits/stdc++.h>
#include "utils.h"
#include "movegen.h"
using namespace std;
#define pb push_back

/*
    cd "c:\Users\ashra\OneDrive\Desktop\STUDY\stockfish\Strong Determination\" ; if ($?) { g++ Ashchess.cpp utils.cpp utils.h movegen.h movegen.cpp  -o Ashchess } ; if ($?) { .\Ashchess }
*/

void printMoves(vector<vector<int>> &board, int player){
    auto k = allPosibleMoves(player,board);
    for(auto l:k){
        for(auto j:l){
            cout<<j.first<<" "<<j.second<<" :";
        }
        cout<<endl;
    }
    cout<<evalBoard(board);
    cout<<endl;
}

vector<pair<int,int>> minimax(vector<vector<int>> &board, int depth, int player, int alpha, int beta){
    // will make this function return value in the form ( {from pos x,y}, {to pos x,y}, {eval_value, player} )
    if(abs(evalBoard(board))>500 || depth == 0){
        vector<pair<int,int>> res;
        res.pb({0,0});
        res.pb({0,0});
        res.pb({evalBoard(board),0});
        // printBoard(board);
        // cout<<"\t"<<evalBoard(board)<<endl<<endl<<endl;;
        // printMoves(board,player);
        return res;
    }
    vector<vector<pair<int,int>>> moves=allPosibleMoves(player,board);
    auto bestMove = moves[rand()%moves.size()];
    if(player>0){
        int maxEval=-10000;
        for(auto &move : moves){
            auto pPos=move[0], nPos=move[1];

            // auto nBoard = board;
            // nBoard[nPos.first][nPos.second]=nBoard[pPos.first][pPos.second];
            // nBoard[pPos.first][pPos.second]=0;
            // auto result = minimax(nBoard, depth -1, -1); // index and extract eval

            int prevPeice =  board[nPos.first][nPos.second];
            board[nPos.first][nPos.second]=board[pPos.first][pPos.second];
            board[pPos.first][pPos.second]=0;
            auto result = minimax(board, depth -1, -1, alpha, beta); // index and extract eval
            board[pPos.first][pPos.second]=board[nPos.first][nPos.second];
            board[nPos.first][nPos.second]=prevPeice;

            if(result[2].first > maxEval){
                maxEval = result[2].first;
                bestMove = move;
                bestMove.pb(result[2]);
            }
            alpha=max(alpha,result[2].first);
            if(beta<=alpha)break;
        }
        return bestMove;
    }
    else{
        int minEval=10000;
        for(auto &move : moves){
            auto pPos=move[0], nPos=move[1];

            // auto nBoard = board;
            // nBoard[nPos.first][nPos.second]=nBoard[pPos.first][pPos.second];
            // nBoard[pPos.first][pPos.second]=0;
            // auto result = minimax(nBoard, depth -1, 1); // index and extract eval

            int prevPeice =  board[nPos.first][nPos.second];
            board[nPos.first][nPos.second]=board[pPos.first][pPos.second];
            board[pPos.first][pPos.second]=0;
            auto result = minimax(board, depth -1, 1, alpha, beta); // index and extract eval
            board[pPos.first][pPos.second]=board[nPos.first][nPos.second];
            board[nPos.first][nPos.second]=prevPeice;
            if(result[2].first < minEval){
                minEval = result[2].first;
                bestMove = move;
                bestMove.pb(result[2]);
            }
            beta=min(beta,result[2].first);
            if(beta<=alpha)break;
        }
        return bestMove;
    }
}

/*
    r n b q k b . r 
	p p p p . p p p 
	. . . . . n . . 
	. . . . p . . . 
	Q . . . . . . . 
	. . P . . . . . 
	P P . P P P P P 
	R N B . K B N R 
*/

void debugBoard(){
    auto  board = customPosition();
    printBoard(board);
    auto k = allPosibleMoves(1,board);
    for(auto l:k){
        for(auto j:l){
            cout<<j.first<<" "<<j.second<<" :";
        }
        cout<<endl;
    }
    cout<<evalBoard(board);
    cout<<endl;
}

void solve(){
    auto  board = initialPosition();
    printBoard(board);
    int turn = 1;
    while(true){
        int k;
        cin>>k;
        if(k==0){
            int startTime = clock();
            auto result = minimax(board,6,turn,-10000,10000);
            // cout<<result.size()<<endl;
            // cout<<"{"<<result[0].first<<","<<result[0].second<<"}"<<" -> "<<"{"<<result[1].first<<","<<result[1].second<<"}"<<endl;
            // cout<<result[2].first<<endl;
            // cout<<"Runtime: "<<clock()-startTime<<endl;
            printInfo(result, startTime);

            board[result[1].first][result[1].second]=board[result[0].first][result[0].second];
            board[result[0].first][result[0].second]=0;
            printBoard(board);
        }
        else{
            int l1,r1,l2,r2;
            cin>>l1>>r1>>l2>>r2;
            board[l2][r2]=board[l1][r1];
            board[l1][r1]=0;
            printBoard(board);
        }
        turn *= -1;
    }
    
}

int main(){
    solve();
    return 0;
}