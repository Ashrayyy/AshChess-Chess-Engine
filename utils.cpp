#include<bits/stdc++.h>
using namespace std;
#define pb push_back
unordered_map<int,char> peice; // score,peice
#define fastIO ios_base::sync_with_stdio(0);cin.tie(0), cout.tie(0);

void utilsInit(){
    peice[0]='.';
    peice[-10]='p';
    peice[-30]='n';
    peice[-31]='b';
    peice[-50]='r';
    peice[-90]='q';
    peice[-1000]='k';
    peice[10]='P';
    peice[30]='N';
    peice[31]='B';
    peice[50]='R';
    peice[90]='Q';
    peice[1000]='K';
}

int evalBoard(vector<vector<int>> &board){
    int sum=0;
    for(auto row : board){
        for(auto col:row)sum+=col;
    }
    return sum;
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

vector<vector<int>> customPosition(){
    vector<vector<int>> board;
    vector<int> row;
    row ={-50,      0,      0,      0,      -1000,  0,    0,      -50};
    board.pb(row);
    row ={0,      -31,    0,    0,    -90,      0,    -10,    0};
    board.pb(row);
    row ={-10,      0  ,      -30,      0,      0,      0,    0,      -10};
    board.pb(row);
    row ={0,        -10,      0,      0,      0,    0,      30,      0};
    board.pb(row);
    row ={0,       0,      0,      0,      0,      31,      0,      90};
    board.pb(row);
    row ={0,        0,      0,     0,      -10,      0,      10,      0};
    board.pb(row);
    row ={10,       10,     10,      0,     0,     -31,     0,     10};
    board.pb(row);
    row ={0,       0,     1000,      50,   0,       50,     0,     0};
    board.pb(row);
    return board;   
}

vector<vector<int>> initialPosition(){
    vector<vector<int>> board;
    vector<int> row ={-50,-30,-31,-90,-1000,-31,-30,-50};
    board.pb(row);
    row ={-10,-10,-10,-10,-10,-10,-10,-10};
    board.pb(row);
    row ={0,0,0,0,0,0,0,0};
    board.pb(row);
    board.pb(row);
    board.pb(row);
    board.pb(row);
    row ={10,10,10,10,10,10,10,10};
    board.pb(row);
    row ={50,30,31,90,1000,31,30,50};
    board.pb(row);
    return board;   
}

void setUp(){
    fastIO;
    #ifndef ONLINE_JUDGE
        freopen("output.txt","w",stdout);
    #endif
}

void printBoard(vector<vector<int>> &board){
    static bool setupDone = false;
    if(!setupDone){
        setupDone=true;
        setUp();
    }
    if(peice.size()==0)utilsInit();
    cout<<endl;
    cout<<"\t  ";
    for(int i=0;i<8;i++)cout<<i<<" ";
    cout<<endl;
    int ct=0;
    for(auto row : board){
        cout<<"\t"<<ct++<<" ";
        for(auto col:row)cout<<peice[col]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void printInfo(vector<pair<int,int>> &result, int startTime){
    cout<<"{"<<result[0].first<<","<<result[0].second<<"}"<<" -> "<<"{"<<result[1].first<<","<<result[1].second<<"}"<<endl;
    char r1=result[0].second+'a';
    int l1=8-result[0].first;
    char r2=result[1].second+'a';
    int l2=8-result[1].first;
    cout<<r1<<l1<<r2<<l2<<endl;
    cout<<"Board Evaluated as "<<result[2].first<<endl;
    cout<<"Runtime: "<<clock()-startTime<<endl<<endl;;
}