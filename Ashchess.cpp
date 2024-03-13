#include<bits/stdc++.h>
#include "utils.h"
#include "movegen.h"
#include <thread>
#include <future>
#include <chrono>
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

void findValue(promise<vector<pair<int,int>>> &pr, vector<vector<int>> &board, int depth, int player){
    vector<pair<int,int>> result = minimax(board, depth, player, -10000, 10000);
    pr.set_value(result);
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
    
    int turn =1;
    int startTime = clock();
    vector<pair<int,int>> result;

    promise<vector<pair<int,int>>> pr1,pr2,pr3,pr4,pr5,pr6,pr7,pr8,pr9,pr10;
    future <vector<pair<int,int>>> ftr1 = pr1.get_future();
    future <vector<pair<int,int>>> ftr2 = pr2.get_future();
    future <vector<pair<int,int>>> ftr3 = pr3.get_future();
    future <vector<pair<int,int>>> ftr4 = pr4.get_future();
    future <vector<pair<int,int>>> ftr5 = pr5.get_future();
    future <vector<pair<int,int>>> ftr6 = pr6.get_future();
    future <vector<pair<int,int>>> ftr7 = pr7.get_future();
    future <vector<pair<int,int>>> ftr8 = pr8.get_future();
    future <vector<pair<int,int>>> ftr9 = pr9.get_future();
    future <vector<pair<int,int>>> ftr10 = pr10.get_future();
    
    thread t1(&findValue, ref(pr1), ref(board), 6, turn);
    // thread t2(&findValue, ref(pr2), ref(board), 2, turn);
    // thread t3(&findValue, ref(pr3), ref(board), 3, turn);
    // thread t4(&findValue, ref(pr4), ref(board), 4, turn);
    // thread t5(&findValue, ref(pr5), ref(board), 5, turn);
    // thread t6(&findValue, ref(pr6), ref(board), 6, turn);
    // thread t7(&findValue, ref(pr7), ref(board), 7, turn);
    // thread t8(&findValue, ref(pr8), ref(board), 8, turn);
    // thread t9(&findValue, ref(pr9), ref(board), 9, turn);
    // thread t10(&findValue, ref(pr10), ref(board), 10, turn);
    
    t1.join();
    result = ftr1.get();
    // if(ftr2.wait_for(chrono::seconds(0))==future_status::ready) result = ftr2.get();
    // t2.detach();
    // if(ftr3.wait_for(chrono::seconds(10))==future_status::ready) result = ftr3.get();
    // t3.detach();
    // if(ftr4.wait_for(chrono::seconds(12))==future_status::ready) result = ftr4.get();
    // t4.detach();
    // if(ftr5.wait_for(chrono::seconds(10))==future_status::ready) result = ftr5.get();
    // t5.detach();
    // if(ftr6.wait_for(chrono::seconds(10))==future_status::ready) result = ftr6.get();
    // t6.detach();
    // if(ftr7.wait_for(chrono::seconds(10))==future_status::ready) result = ftr7.get();
    // t7.detach();
    // if(ftr8.wait_for(chrono::seconds(10))==future_status::ready) result = ftr8.get();
    // t8.detach();
    // if(ftr9.wait_for(chrono::seconds(10))==future_status::ready) result = ftr9.get();
    // t9.detach();
    // if(ftr10.wait_for(chrono::seconds(10))==future_status::ready) result = ftr10.get();
    // t10.detach();

    cout<<endl<<"Result at the end is "<<"\n";
    printInfo(result, startTime);

    board[result[1].first][result[1].second]=board[result[0].first][result[0].second];
    board[result[0].first][result[0].second]=0;
    printBoard(board);
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

            promise<vector<pair<int,int>>> pr1;
            future <vector<pair<int,int>>> ftr1 = pr1.get_future();
            auto nBoard=board;
            thread t1(&findValue, ref(pr1), ref(nBoard), 6, turn);
            
            auto result = minimax(board,5,turn,-10000,10000);

            this_thread :: sleep_for(chrono::seconds(10));
            if(ftr1.wait_for(chrono :: seconds (0))==future_status::ready){
                result =ftr1.get();
                cout<<"Depth 6 Calculated"<<endl;
            } 
            if(t1.joinable())t1.detach();

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
    // debugBoard();
    return 0;
}