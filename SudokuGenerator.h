#include<bits/stdc++.h>

using namespace std;


bool isValidGuess(int num, unordered_set<int> &row, unordered_set<int> &col, unordered_set<int> &sq){
    return !(row.count(num) || col.count(num) || sq.count(num));
}

vector<vector<int>> Sudokugenerator(int n){
    vector<vector<int>> mat(n,vector<int>(n));
    vector<unordered_set<int>> row(n), col(n), sq(n);
    vector<pair<int,int>> ind;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            ind.push_back({i,j});
        }
    }
    srand(time(NULL));
    vector<unordered_set<int>> hs(n*n);
    bool bck = false;
    // long long loopc = 0;
    for(int it=0; it<ind.size();){
        // loopc++;
        // if(loopc%100000==0)
        //     cout<<"loopc="<<loopc<<endl;
        int i = ind[it].first;
        int j = ind[it].second;
        int num = rand()%n + 1;
        bool gotval = false;
        while(hs[it].size()<n && !gotval){
            num = num%n + 1;
            if(hs[it].count(num)) continue;
            hs[it].insert(num);
            if(isValidGuess(num,row[i],col[j],sq[(i/3)*3+j/3])){
                gotval = true;
                break;
            }
        }
        if(gotval){
            mat[i][j] = num;
            row[i].insert(num);
            col[j].insert(num);
            sq[(i/3)*3+j/3].insert(num);
            it++;
            continue;
        }
        hs[it].clear();
        int ipr = ind[it-1].first;
        int jpr = ind[it-1].second;
        row[ipr].erase(mat[ipr][jpr]);
        col[jpr].erase(mat[ipr][jpr]);
        sq[(ipr/3)*3+jpr/3].erase(mat[ipr][jpr]);
        mat[ipr][jpr] = 0;
        it--;
    }
    // cout<<"loopc="<<loopc<<endl;
    return mat;
}

