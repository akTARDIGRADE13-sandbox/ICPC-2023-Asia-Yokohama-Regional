#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int main(){
	int n, m;
	cin >> n >> m;

	vector<int> dp(1<<n), dp2(1<<n);
	int u = (1<<n)-1;
	for(int i = 0; i < m; ++i){
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b, --c;
		dp[u^1<<a^1<<c] |= 1<<b;
		dp2[1<<a|1<<c] |= 1<<b;
	}
	for(int i = u; i >= 0; --i){
		for(int j = 0; j < n; ++j){
			if(!(i>>j&1)){
				dp[i] |= dp[i|1<<j];
			}
		}
		for(int j = 0; j < n; ++j){
			if(!(i>>j&1)){
				dp[i] &= ~(1<<j);
			}
		}
		int k = ~i&u;
		for(int j = 0; j < n; ++j){
			if(k>>j&1){
				dp2[k] |= dp2[k^1<<j];
			}
		}
		for(int j = 0; j < n; ++j){
			if(k>>j&1){
				dp2[k] &= ~(1<<j);
			}
		}
	}
	vector<int> ans(1<<n);
	ans[0] = 1;
	for(int i = 0; i < 1<<n; ++i){
		if(dp[i] || dp2[i]) continue;
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
