#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int main(){
	int n, m;
	cin >> n >> m;
	vector<int> dp(1<<n);
	for(int i = 0; i < m; ++i){
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b, --c;
		dp[1<<a|1<<c]++;
		dp[1<<b]++;
		dp[1<<a|1<<b]--;
		dp[1<<b|1<<c]--;
	}
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < 1<<n; ++j){
			if(j>>i&1){
				dp[j] += dp[j^1<<i];
			}
		}
	}

	vector<int> ans(1<<n);
	ans[0] = 1;
	for(int i = 0; i < 1<<n; ++i){
		if(dp[i]) continue;
		for(int j = 0; j < n; ++j){
			if(!(i>>j&1)){
				ans[i|1<<j] += ans[i];
				if(ans[i|1<<j] > mod){
					ans[i|1<<j] -= mod;
				}
			}
		}
	}
	cout << ans.back() << endl;
	return 0;
}
