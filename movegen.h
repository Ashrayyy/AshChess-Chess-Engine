#include<bits/stdc++.h>
using namespace std;

bool isSame(int a, int b);
vector<pair<int,int>> possibleRookMoves(pair<int,int> pos, vector<vector<int>> &board);
vector<vector<pair<int,int>>> allPossibleMoves(int color, vector<vector<int>> board, int csw, int csb);