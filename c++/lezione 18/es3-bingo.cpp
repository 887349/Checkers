//https://www.hackerrank.com/work/tests/1341616/questions



















#include <iostream>
#include <vector>

using std::vector;
using std::endl;
using std::cout;
using std::cin;
using std::pair;

int getBingoNumber(vector<vector<int>> mat, vector<int> arr) {

	int n = mat.size();
	int m = mat[0].size();

	vector<int> rows_cnt(n,0);
	vector<int> cols_cnt(m,0);
	
	vector<pair<int,int>> loc(m*n+1);
	
	for(int r=0;r<n; ++r){
		for(int c=0;c<m;++c){
			loc[mat[r][c]] = {r,c};
		}
	}

	int found = 0;
	
	for(int i=0;i<m*n and not found;++i){
		
		pair<int,int> coord = loc[arr[i]];
		rows_cnt[coord.first]++;
		cols_cnt[coord.second]++;
	
		if(rows_cnt[coord.first] == m or cols_cnt[coord.second] == n) 
			found = arr[i];
		
	}
	
	return found;
	
}

int main() {
    
    int n,m; 
    
    std::cin >> n >> m;
    
    vector<vector<int>> mat(n,vector<int>(m,0));
    vector<int> arr(n*m,0);
    
    int i=0;
    int r=0,c=0;
    while(i<n*m){
    	cin >> mat[r][c++];
    	if(c==m){
			c = 0;
			r++;
		}
		++i;
	}
    
    i=0;
    while(i<n*m){
    	cin >> arr[i++];
	}
    
    cout << getBingoNumber(mat,arr) << endl;
    
    return 0;
}
