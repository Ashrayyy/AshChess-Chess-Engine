#include <bits/stdc++.h>
using namespace std;

class Trie{
    public:
    vector<pair<string,Trie>> nextTrie;
};

int main() {
    fstream new_file;
    new_file.open("openingsUCInotation.txt", ios::in); 

    Trie trie = Trie();
    Trie *temp_trie;

    if (new_file.is_open()) { 
        cout<<"Opening file found, loading Openings"<<endl;
        string sa;
        while (getline(new_file, sa)){
            string move="";
            temp_trie = &trie;
            for(auto k:sa){
                if(k!=' '){
                    move+=k;
                }
                if(move.size()==4){
                    //process move
                    // cout<<move<<" ";
                    bool found =false;
                    for(auto &k : temp_trie->nextTrie){
                        if(k.first==move){
                            found = true;
                            temp_trie = &k.second;
                            break;
                        }
                    }
                    if(!found){
                        Trie new_trie = Trie();
                        temp_trie->nextTrie.push_back({move,new_trie});
                        temp_trie = &new_trie;
                    }
                    move.clear();
                }
                else if(move.size()>0 && k==' '){
                    cout<<"error"<<endl;
                }
                else{
                    // eat 5 star, do nothing
                }
            }
        }
        new_file.close(); 
        cout<<"Openings Loaded!"<<endl;
    }
    else{
        cout<<"Openings not found!"<<endl;
    }
    temp_trie = &trie;
    temp_trie = &(temp_trie->nextTrie[19].second);
    for(auto move:temp_trie->nextTrie){
        cout<<move.first<<" ";
    }
    cout<<endl;
}