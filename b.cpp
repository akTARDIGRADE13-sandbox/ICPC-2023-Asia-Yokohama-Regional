#include<bits/stdc++.h>
using namespace std;

int main(){
	int n, c, p, q;
	cin >> n >> c >> p >> q;
	string s;
	cin >> s;
	int ans = 0, latest = -1;
	for(int i = 0; i < n; ++i){
		if(i < latest+c) continue;
		int cnt = 0;
		for(int j = i; j > max(latest, i-2*c); --j){
			if(s[j] == 'Y') ++cnt;
			if(i-j+1 >= c){
				if((long long)cnt*q >= (long long)p*(i-j+1)){
					++ans;
					latest = i;
					break;
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
