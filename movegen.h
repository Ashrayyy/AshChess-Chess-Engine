#include<bits/stdc++.h>
using namespace std;

bool isInvalid(int a, int b);
bool isSame(int a, int b);
bool isDifferent(int a, int b);
bool checkIfUnderAttack(pair<int,int> pos, vector<vector<int>> &board, int color);
vector<pair<int,int>> possibleRookMoves(pair<int,int> pos, vector<vector<int>> &board);
vector<vector<pair<int,int>>> allPosibleMoves(int color, vector<vector<int>> board);