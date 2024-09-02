#include<bits/stdc++.h>
using namespace std;

int main(){
	int n, q;
	cin >> n >> q;
	vector<int> a(n), b(n);
	for(int i = 0; i < n; ++i){
		if(i%2){
			a[i] = 1;
			b[i] = 1;
		}
	}
	long long x = n-1, y = n-1;
	while(q--){
		string s;
		int p;
		cin >> s >> p;
		--p;
		if(s == "ROW"){
			if(p > 0){
				if(a[p] != a[p-1]){
					--x;
				}else{
					++x;
				}
			}
			if(p < n-1){
				if(a[p] != a[p+1]){
					--x;
				}else{
					++x;
				}
			}
			a[p] ^= 1;
		}else{
			if(p > 0){
				if(b[p] != b[p-1]){
					--y;
				}else{
					++y;
				}
			}
			if(p < n-1){
				if(b[p] != b[p+1]){
					--y;
				}else{
					++y;
				}
			}
			b[p] ^= 1;
		}
		cout << (x+1)*(y+1) << endl;
	}
	return 0;
}
