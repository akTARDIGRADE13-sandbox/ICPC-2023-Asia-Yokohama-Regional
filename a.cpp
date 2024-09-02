#include<bits/stdc++.h>
using namespace std;

int main(){
	int n, m;
	cin >> n >> m;
	vector<string> x(n);
	for(int i = 0; i < n; ++i) cin >> x[i];
	vector<vector<vector<int>>> dp(8, vector<vector<int>>(n, vector<int>(m)));
	for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j){
		if(x[i][j] == 'Y') dp[0][i][j] = 1;
	}
	string S = "YOKOHAMA";
	int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
	for(int i = 1; i < 8; ++i){
		for(int j = 0; j < n; ++j) for(int k = 0; k < m; ++k){
			if(x[j][k] != S[i]) continue;
			for(int l = 0; l < 4; ++l){
				int nx = j+dx[l], ny = k+dy[l];
				if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
				dp[i][j][k] += dp[i-1][nx][ny];
			}
		}
	}
	int ans = 0;
	for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) ans += dp[7][i][j];
	cout << ans << endl;
	return 0;
}
