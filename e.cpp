#include<bits/stdc++.h>
using namespace std;

int mod = 998244353;

inline void add(int& val, int p){
	val += p;
	if(val > mod) val -= mod;
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, int>>> G(n);
	while(m--){
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b, --c;
		G[b].emplace_back(a, c);
	}

	vector<int> dp(1<<n);
	dp[0] = 1;
	for(int i = 0; i < (1<<n); ++i){
		int flag = ~i;
		for(int b = 0; b < n; ++b){
			if(flag>>b&1){
				for(auto [a, c]: G[b]){
					if(!((i>>a&1) ^ (i>>c&1))){
						flag ^= 1<<b;
						break;
					}
				}
			}
		}
		for(int j = 0; j < n; ++j){
			if(flag>>j&1){
				add(dp[i|(1<<j)], dp[i]);
			}
		}
	}
	cout << dp.back() << endl;
	return 0;
}
