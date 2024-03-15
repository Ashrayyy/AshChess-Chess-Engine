#include<bits/stdc++.h>
#include "utils.h"
#include "movegen.h"
#include <thread>
#include <future>
#include <chrono>
using namespace std;
#define pb push_back

bool time_over;

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

vector<pair<int,int>> minimax(vector<vector<int>> &board, int depth, int player, int alpha, int beta, int csw, int csb){
    // printBoard(board);
    // cout<<csw<<" "<<csb<<endl<<endl;
    if(time_over){
        vector<pair<int,int>> res;
        res.pb({0,0});
        res.pb({0,0});
        res.pb({0,0});
        return res;
    }
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
    auto bestMove = moves[clock()%moves.size()];
    if(player>0){
        int maxEval=-10000;
        if(csw>=2){
            if(board[7][1]==0 && board[7][2]==0 && board[7][3]==0  && !checkIfUnderAttack({7,3},board,1) && !checkIfUnderAttack({7,2},board,1) && !checkIfUnderAttack({7,4},board,1)){
                //O-O-O
                swap(board[7][0],board[7][3]);
                swap(board[7][2],board[7][4]);
                
                auto result = minimax(board, depth -1, -1, alpha, beta, 0, csb); // index and extract eval
                
                swap(board[7][0],board[7][3]);
                swap(board[7][2],board[7][4]);

                auto move = vector<pair<int,int>> (0);
                move.pb({7,4});
                move.pb({7,2});
                if(result[2].first > maxEval){
                    maxEval = result[2].first;
                    bestMove = move;
                    bestMove.pb(result[2]);
                    bestMove.pb({7,0});
                    bestMove.pb({7,3});
                }
                alpha=max(alpha,result[2].first);
            }
        }
        if(csw%2){
            if(board[7][5]==0 && board[7][6]==0 && !checkIfUnderAttack({7,5},board,1) && !checkIfUnderAttack({7,6},board,1) && !checkIfUnderAttack({7,4},board,1)){
                //O-O
                swap(board[7][7],board[7][5]);
                swap(board[7][6],board[7][4]);

                auto result = minimax(board, depth -1, -1, alpha, beta, 0, csb); 
                
                swap(board[7][7],board[7][5]);
                swap(board[7][6],board[7][4]);

                auto move = vector<pair<int,int>> (0);
                move.pb({7,4});
                move.pb({7,6});
                if(result[2].first > maxEval){
                    maxEval = result[2].first;
                    bestMove = move;
                    bestMove.pb(result[2]);
                    bestMove.pb({7,7});
                    bestMove.pb({7,5});
                }
                alpha=max(alpha,result[2].first);
            }
        }
        for(auto &move : moves){
            auto pPos=move[0], nPos=move[1];

            int prevPeice =  board[nPos.first][nPos.second];
            board[nPos.first][nPos.second]=board[pPos.first][pPos.second];
            board[pPos.first][pPos.second]=0;
            auto result = minimax(board, depth -1, -1, alpha, beta,csw,csb); // index and extract eval
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
        if(csb>=2){
            if(board[0][1]==0 && board[0][2]==0 && board[0][3]==0  && !checkIfUnderAttack({0,3},board,-1) && !checkIfUnderAttack({0,2},board,-1) && !checkIfUnderAttack({0,4},board,-1)){
                //O-O-O
                swap(board[0][0],board[0][3]);
                swap(board[0][2],board[0][4]);
                
                auto result = minimax(board, depth -1, 1, alpha, beta, csw, 0); // index and extract eval
                
                swap(board[0][0],board[0][3]);
                swap(board[0][2],board[0][4]);

                auto move = vector<pair<int,int>> (0);
                move.pb({0,4});
                move.pb({0,2});
                if(result[2].first < minEval){
                    minEval = result[2].first;
                    bestMove = move;
                    bestMove.pb(result[2]);
                    bestMove.pb({0,0});
                    bestMove.pb({0,3});
                }
                beta=min(beta,result[2].first);
            }
        }
        if(csb%2){
            if(board[0][5]==0 && board[0][6]==0 && !checkIfUnderAttack({0,5},board,-1) && !checkIfUnderAttack({0,6},board,-1) && !checkIfUnderAttack({0,4},board,-1)){
                //O-O
                swap(board[0][7],board[0][5]);
                swap(board[0][6],board[0][4]);
                auto result = minimax(board, depth -1, 1, alpha, beta, csw, 0); 
                
                swap(board[0][7],board[0][5]);
                swap(board[0][6],board[0][4]);

                auto move = vector<pair<int,int>> (0);
                move.pb({0,4});
                move.pb({0,6});
                if(result[2].first < minEval){
                    minEval = result[2].first;
                    bestMove = move;
                    bestMove.pb(result[2]);
                    bestMove.pb({0,7});
                    bestMove.pb({0,5});
                }
                beta=min(beta,result[2].first);
            }
        }
        for(auto &move : moves){
            auto pPos=move[0], nPos=move[1];

            int prevPeice =  board[nPos.first][nPos.second];
            board[nPos.first][nPos.second]=board[pPos.first][pPos.second];
            board[pPos.first][pPos.second]=0;
            auto result = minimax(board, depth -1, 1, alpha, beta,csw,csb); // index and extract eval
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

void findValue(promise<vector<pair<int,int>>> &pr, vector<vector<int>> &board, int depth, int player,int csw,int csb){
    vector<pair<int,int>> result = minimax(board, depth, player, -10000, 10000,csw,csb);
    pr.set_value(result);
}

void debugBoard(){
    int cswDebug = 3, csbDebug = 3;
    time_over = false;
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

    promise<vector<pair<int,int>>> pr2,pr3,pr4,pr5,pr6,pr7,pr8,pr9;
    future <vector<pair<int,int>>> ftr2 = pr2.get_future();
    future <vector<pair<int,int>>> ftr3 = pr3.get_future();
    future <vector<pair<int,int>>> ftr4 = pr4.get_future();
    future <vector<pair<int,int>>> ftr5 = pr5.get_future();
    future <vector<pair<int,int>>> ftr6 = pr6.get_future();
    future <vector<pair<int,int>>> ftr7 = pr7.get_future();
    future <vector<pair<int,int>>> ftr8 = pr8.get_future();
    future <vector<pair<int,int>>> ftr9 = pr9.get_future();

    auto nBoard2 = board;
    thread t2(&findValue, ref(pr2), ref(nBoard2), 2, turn, cswDebug, csbDebug);
    auto nBoard3 = board;
    thread t3(&findValue, ref(pr3), ref(nBoard3), 3, turn, cswDebug, csbDebug);
    auto nBoard4 = board;
    thread t4(&findValue, ref(pr4), ref(nBoard4), 4, turn, cswDebug, csbDebug);
    auto nBoard5 = board;
    thread t5(&findValue, ref(pr5), ref(nBoard5), 5, turn, cswDebug, csbDebug);
    auto nBoard6 = board;
    thread t6(&findValue, ref(pr6), ref(nBoard6), 6, turn, cswDebug, csbDebug);
    auto nBoard7 = board;
    thread t7(&findValue, ref(pr7), ref(nBoard7), 7, turn, cswDebug, csbDebug);
    auto nBoard8 = board;
    thread t8(&findValue, ref(pr8), ref(nBoard8), 8, turn, cswDebug, csbDebug);
    auto nBoard9 = board;
    thread t9(&findValue, ref(pr9), ref(nBoard9), 9, turn, cswDebug, csbDebug);
    
    auto nBoard = board;
    result = minimax(nBoard,1,turn,-10000,10000, cswDebug, csbDebug);
    
    this_thread :: sleep_for(chrono :: seconds(40));
    
    int finalDepth = 1;

    if(ftr2.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr2.get(),finalDepth = 2;
    if(ftr3.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr3.get(),finalDepth = 3;
    if(ftr4.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr4.get(),finalDepth = 4;
    if(ftr5.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr5.get(),finalDepth = 5;
    if(ftr6.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr6.get(),finalDepth = 6;
    if(ftr7.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr7.get(),finalDepth = 7;
    if(ftr8.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr8.get(),finalDepth = 8;
    if(ftr9.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr9.get(),finalDepth = 9;

    time_over = true; 
    this_thread :: sleep_for(chrono :: seconds(1));

    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();

    cout<<endl<<"Result calculated up till "<<finalDepth<<" depth, and is\n";
    printInfo(result, startTime);

    if(result.size()==5){
        swap(board[result[0].first][result[0].second],board[result[1].first][result[1].second]);
        swap(board[result[3].first][result[3].second],board[result[4].first][result[4].second]);
    }
    else{
        board[result[1].first][result[1].second]=board[result[0].first][result[0].second];
        board[result[0].first][result[0].second]=0;
    }

    if(board[7][4] != 1000) cswDebug&=0;
    if(board[0][4] != -1000) csbDebug&=0;
    if(board[7][7] != 50)cswDebug&=2;
    if(board[7][0] != 50)cswDebug&=1;
    if(board[0][7] != -50)csbDebug&=2;
    if(board[0][0] != -50)csbDebug&=1;
    printBoard(board);
}

void assignNums(string move, int &l1, int &r1, int &l2, int &r2){
    r1=move[0]-'a';
    l1='8'-move[1];
    r2=move[2]-'a';
    l2='8'-move[3];
}

void makeMove(vector<vector<int>> &board, int player, int time, int &csw, int &csb){
    time_over = false;
    int turn = player;
    auto k = allPosibleMoves(turn,board);
    
    int startTime = clock();
    vector<pair<int,int>> result;

    promise<vector<pair<int,int>>> pr2,pr3,pr4,pr5,pr6,pr7,pr8,pr9;
    future <vector<pair<int,int>>> ftr2 = pr2.get_future();
    future <vector<pair<int,int>>> ftr3 = pr3.get_future();
    future <vector<pair<int,int>>> ftr4 = pr4.get_future();
    future <vector<pair<int,int>>> ftr5 = pr5.get_future();
    future <vector<pair<int,int>>> ftr6 = pr6.get_future();
    future <vector<pair<int,int>>> ftr7 = pr7.get_future();
    future <vector<pair<int,int>>> ftr8 = pr8.get_future();
    future <vector<pair<int,int>>> ftr9 = pr9.get_future();

    auto nBoard2 = board;
    thread t2(&findValue, ref(pr2), ref(nBoard2), 2, turn, csw, csb);
    auto nBoard3 = board;
    thread t3(&findValue, ref(pr3), ref(nBoard3), 3, turn, csw, csb);
    auto nBoard4 = board;
    thread t4(&findValue, ref(pr4), ref(nBoard4), 4, turn, csw, csb);
    auto nBoard5 = board;
    thread t5(&findValue, ref(pr5), ref(nBoard5), 5, turn, csw, csb);
    auto nBoard6 = board;
    thread t6(&findValue, ref(pr6), ref(nBoard6), 6, turn, csw, csb);
    auto nBoard7 = board;
    thread t7(&findValue, ref(pr7), ref(nBoard7), 7, turn, csw, csb);
    auto nBoard8 = board;
    thread t8(&findValue, ref(pr8), ref(nBoard8), 8, turn, csw, csb);
    auto nBoard9 = board;
    thread t9(&findValue, ref(pr9), ref(nBoard9), 9, turn, csw, csb);
    
    auto nBoard = board;
    result = minimax(nBoard,1,turn,-10000,10000, csw, csb);
    
    this_thread :: sleep_for(chrono :: seconds(time));
    
    int finalDepth = 1;

    if(ftr2.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr2.get(),finalDepth = 2;
    if(ftr3.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr3.get(),finalDepth = 3;
    if(ftr4.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr4.get(),finalDepth = 4;
    if(ftr5.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr5.get(),finalDepth = 5;
    if(ftr6.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr6.get(),finalDepth = 6;
    if(ftr7.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr7.get(),finalDepth = 7;
    if(ftr8.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr8.get(),finalDepth = 8;
    if(ftr9.wait_for(chrono::seconds(0)) == future_status::ready) result = ftr9.get(),finalDepth = 9;

    time_over = true; 
    this_thread :: sleep_for(chrono :: seconds(1));

    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();

    cout<<endl<<"Result calculated up till "<<finalDepth<<" depth, and is\n";
    printInfo(result, startTime);

    if(result.size()==5){
        swap(board[result[0].first][result[0].second],board[result[1].first][result[1].second]);
        swap(board[result[3].first][result[3].second],board[result[4].first][result[4].second]);
    }
    else{
        board[result[1].first][result[1].second]=board[result[0].first][result[0].second];
        board[result[0].first][result[0].second]=0;
    }

    if(board[7][4] != 1000) csw&=0;
    if(board[0][4] != -1000) csb&=0;
    if(board[7][7] != 50)csw&=2;
    if(board[7][0] != 50)csw&=1;
    if(board[0][7] != -50)csb&=2;
    if(board[0][0] != -50)csb&=1;
}

void solve(){
    auto  board = initialPosition();
    printBoard(board);
    int depth = 6;
    int turn = 1;
    int csw =3,csb=3;
    while(true){
        int k;
        cin>>k;
        if(k==0){
            int startTime = clock();

            // Multithreading Enabled Function
            makeMove(board, turn, 10, csw, csb);

            // Disabled Multithreading, simple defined depth search code
            // auto result = minimax(board,depth,turn,-10000,10000,csw,csb);
            // printInfo(result, startTime);
            // board[result[1].first][result[1].second]=board[result[0].first][result[0].second];
            // board[result[0].first][result[0].second]=0;

            printBoard(board);
        }
        else if(k==2){
            // skip turn 
        }
        else{
            int l1,r1,l2,r2;
            string moveMade;
            cin>>moveMade;
            assignNums(moveMade,l1,r1,l2,r2);

            cout<<endl<<"User Moved: "<<moveMade<<endl;
            board[l2][r2]=board[l1][r1];
            board[l1][r1]=0;
            printBoard(board);
        }
        turn *= -1;
    }
    
}

int main(){
    srand(time(NULL));
    solve();
    // debugBoard();
    // auto board = customPosition();
    // auto result = minimax(board,1,-1,-10000,10000,3,3);
    return 0;
}