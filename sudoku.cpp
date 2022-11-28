#include<bits/stdc++.h>

using namespace std;


bool isValid(int num, unordered_set<int> &row, unordered_set<int> &col, unordered_set<int> &sq){
    return !(row.count(num) || col.count(num) || sq.count(num));
}

void psu(vector<vector<int>> &mat){
    int n = mat.size();
    int sn = sqrt(n+1);
    for(int i=0; i<mat.size(); i++){
        for(int j=0; j<mat[i].size(); j++){
            if(mat[i][j]==0) cout<<" ";
            else
                cout<<mat[i][j];
            if((j+1)%sn == 0){
                cout<<"|";
            }
            else cout<<",";
        }
        cout<<endl;
        if((i+1)%sn==0){
            for(int j=0; j<n; j++){
                cout<<"-";
            }
            cout<<endl;
        }
    }
}


void pvv(vector<vector<int>> &v){
    for(int i=0; i<v.size(); i++){
        for(int j=0; j<v[i].size(); j++){
            cout<<v[i][j]<<",";
        }
        cout<<endl;
    }
}

void pv(vector<int> v){
    for(int i=0; i<v.size(); i++){
        cout<<v[i]<<",";
    }
    cout<<endl;
}

////////*********//////////

vector<vector<int>> Sudokugenerator(int n, int emp);

vector<vector<int>> PutECell(vector<vector<int>> mat);

bool isValid(vector<vector<int>> &board, int row, int col, int c) {
  for (int i = 0; i < 9; i++) {
    if (board[i][col] == c)
      return false;

    if (board[row][i] == c)
      return false;

    if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
      return false;
  }
  return true;
}

bool solveSudoku(vector < vector < char >> & board) {
  for (int i = 0; i < board.size(); i++){
    for (int j = 0; j < board[0].size(); j++){
      if (board[i][j] == '.') {
        for (char c = '1'; c <= '9'; c++){
          if (isValid(board, i, j, c)){
            board[i][j] = c;
            if (solveSudoku(board))
              return true;
            else
              board[i][j] = '.';
          }
        }
        return false;
      }
    }
  }
  return true;
}

int main(){
    int n=9;
    cin>>n;
    vector<vector<int>> validsudoku = Sudokugenerator(n);
    psu(validsudoku);
    vector<vector<int>> trysudoku = PutECell(validsudoku,50);
    psu(trysudoku);
    solveSudoku(trysudoku);
    psu(trysudoku);
    return 0;
}


vector<vector<int>> Sudokugenerator(int n, int emp){
    vector<vector<int>> mat(n,vector<int>(n));
    vector<unordered_set<int>> row(n), col(n), sq(n);
    vector<pair<int,int>> ind;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            ind.push_back({i,j});
            // cout<<(i/3)*3+j/3<<",";
        }
        // cout<<endl;
    }
    srand(time(NULL));
    vector<unordered_set<int>> hs(n*n);
    // vector<set<int>> hs(n*n);
    bool bck = false;
    long long loopc = 0;
    for(int it=0; it<ind.size();){
        loopc++;
        if(loopc%100000==0)
            cout<<"loopc="<<loopc<<endl;
        int i = ind[it].first;
        int j = ind[it].second;
        // cout<<"("<<i<<","<<j<<")"<<"it="<<it<<endl;
        // psu(mat);
        // cout<<endl;
        int num = rand()%n + 1;
        bool gotval = false;
        // int dbi=4, dbj = 7;
        // if((i==dbi && j==dbj) || bck==true){
        //     cout<<"hs[it].size()="<<hs[it].size()<<endl;
        //     cout<<"hs["<<it<<"]=";
        //     for(auto x: hs[it]){
        //         cout<<x<<",";
        //     }
        //     cout<<endl;
        //     cout<<"row["<<i<<"]=";
        //     for(auto x: row[i]){
        //         cout<<x<<",";
        //     }
        //     cout<<endl;
        //     cout<<"col["<<j<<"]=";
        //     for(auto x: col[j]){
        //         cout<<x<<",";
        //     }
        //     cout<<endl;
        //     cout<<"sq["<<(i/3)*3+j/3<<"]=";
        //     for(auto x: sq[(i/3)*3+j/3]){
        //         cout<<x<<",";
        //     }
        //     cout<<endl;
        // }
        while(hs[it].size()<n && !gotval){
            num = num%n + 1;
            if(hs[it].count(num)) continue;
            hs[it].insert(num);
            if(isValid(num,row[i],col[j],sq[(i/3)*3+j/3])){
                gotval = true;
                break;
            }
            // if((i==dbi && j==dbj) || bck==true){
            //     cout<<"hs[it].size()="<<hs[it].size()<<endl;
            //     // return mat;
            // }
        }
        if(gotval){
            mat[i][j] = num;
            row[i].insert(num);
            col[j].insert(num);
            sq[(i/3)*3+j/3].insert(num);
            it++;
            // bck=false;
            continue;
        }
        // if(bck==true && (it<=27)){
        //     return mat;
        // }
        hs[it].clear();
        int ipr = ind[it-1].first;
        int jpr = ind[it-1].second;
        // i = ind[it-1].first;
        // j = ind[it-1].second;
        // cout<<"ipr="<<ipr<<endl;
        // cout<<"jpr="<<jpr<<endl;
        row[ipr].erase(mat[ipr][jpr]);
        col[jpr].erase(mat[ipr][jpr]);
        sq[(ipr/3)*3+jpr/3].erase(mat[ipr][jpr]);
        mat[ipr][jpr] = 0;
        it--;
        // bck=true;
        // if((i==dbi && j==dbj) || bck==true){
        //     cout<<"hs[it].size()="<<hs[it].size()<<endl;
        //     cout<<"hs["<<it<<"]=";
        //     for(auto x: hs[it]){
        //         cout<<x<<",";
        //     }
        //     cout<<endl;
        //     cout<<"row["<<i<<"]=";
        //     for(auto x: row[i]){
        //         cout<<x<<",";
        //     }
        //     cout<<endl;
        //     cout<<"col["<<j<<"]=";
        //     for(auto x: col[j]){
        //         cout<<x<<",";
        //     }
        //     cout<<endl;
        //     cout<<"sq["<<(i/3)*3+j/3<<"]=";
        //     for(auto x: sq[(i/3)*3+j/3]){
        //         cout<<x<<",";
        //     }
        //     cout<<endl;
        // }
        // cout<<endl<<"---------------------------------"<<endl;
    }
    cout<<"loopc="<<loopc<<endl;
    return mat;
}


vector<vector<int>> PutECell(vector<vector<int>> mat, int emp){
    int n = mat.size();
    long long count = n*1ll*n*emp/100;
    while(count>0){
        int i1 = rand()%n;
        int j1 = rand()%n;
        bool got=false;
        for(int i=0; i<n; i++){
            int i2 = (i1+i)%n;
            for(int j=0; j<n; j++){
                int j2 = (j1+j)%n;
                if(mat[i2][j2]==0) continue;
                mat[i2][j2]=0;
                got=true;
                count--;
                break;
            }
            if(got) break;
        }
    }
}

