#include<bits/stdc++.h>
using namespace std;

int main(){
	string s;
	cin >> s;
	int n = s.size();

	vector<vector<string>> dp(n+1, vector<string>(n+1));
	vector<vector<vector<int>>> rec(n+1, vector<vector<int>>(n+1, vector<int>(n+1)));

	for(int i = 0; i < n; ++i){
		dp[i][i+1] = s[i];
	}
	for(int start = 0; start < n; ++start){
		for(int len = 1; len <= n-start; ++len){
			string t = s.substr(start, len);
			int cnt = 1;
			while(cnt < 9 && start+len*(cnt+1) <= n && t == s.substr(start+len*cnt, len)) {
				++cnt;
				rec[start][start+len][start+len*cnt] = cnt;
			}
		}
	}

	// DP
	for(int len = 2; len <= n; ++len){
		for(int i = 0; i <= n-len; ++i){
			int idx = -1, tmp = 1<<10, j = i+len;
			if(dp[i][j] != "") tmp = dp[i][j].size();
			for(int k = i+1; k < j; ++k){
				if(tmp > (int)dp[i][k].size()+(int)dp[k][j].size()){
					tmp = (int)dp[i][k].size()+(int)dp[k][j].size();
					idx = k;
				}
			}
			if(idx >= 0) dp[i][j] = dp[i][idx] + dp[idx][j];

			int idx2 = -1, tmp2 = 1<<10;
			for(int k = i+1; k < j; ++k){
				if(rec[i][k][j]){
					if(tmp2 > (int)dp[i][k].size() + 3){
						tmp2 = (int)dp[i][k].size() + 3;
						idx2 = k;
					}
				}
			}

			if(tmp2 < tmp) dp[i][j] = to_string(rec[i][idx2][j]) + "(" + dp[i][idx2] + ")";
		}
	}
	cout << dp[0][n] << endl;

	return 0;
}
