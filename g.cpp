#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;

struct mint{
	long long x;
	mint(long long x = 0) :x(normalize(x)) {}

	mint &operator+=(const mint &a) {
		if((x += a.x) >= mod){
			x -= mod;
		}
		return *this;
	}

	mint &operator-=(const mint &a) {
		if((x += mod - a.x) >= mod){
			x -= mod;
		}
		return *this;
	}

	mint &operator*=(const mint &a) {
		x = (x * a.x) % mod;
		return *this;
	}

	mint &operator/=(const mint &a) {
		return *this *= a.inv();
	}

	mint operator-() const {
		return mint(-x);
	}

	mint operator+(const mint &a) const {
		return mint(*this) += a;
	}

	mint operator-(const mint &a) const {
		return mint(*this) -= a;
	}

	mint operator*(const mint &a) const {
		return mint(*this) *= a;
	}

	mint operator/(const mint &a) const {
		return mint(*this) /= a;
	}

	bool operator==(const mint &a) const {
		return x == a.x;
	}

	bool operator!=(const mint &a) const {
		return x != a.x;
	}

	mint pow(long long t) const {
		mint res(1), a(*this);
		while(t > 0) {
			if(t&1){
				res *= a;
			}
			a *= a;
			t >>= 1;
		}
		return res;
	}

	mint inv() const {
		return pow(mod-2);
	}

	static long long normalize(long long n) {
		n %= mod;
		if (n < 0){
			n += mod;
		}
		return n;
	}
};

int main(){
	int n;
	cin >> n;

	map<int, vector<mint>> mp;
	mp[1].assign(1, 2);
	mp[1][1] = 1;

	vector<mint> inv_six(7, mint(1));
	for(int i = 1; i <= 6; ++i){
		inv_six[i] /= i;
	}

	auto solve = [&](auto &&solve, int s, int idx)->mint{
		if(mp.find(s) != mp.end()){
			if(mp[s][idx] != 0){
				return mp[s][idx];
			}
		}else{
			mp[s].assign(s+1, 0);
		}
		int cnt = 0;
		for(int i = 0; i < 6; ++i){
			if(s <= 5 && i == 0) {
				continue;
			}
			if(s <= 4 && i == 5) {
				continue;
			}
			if(s <= 3 && i == 4) {
				continue;
			}
			if(s <= 2 & i == 3) {
				continue;
			}
			if(s <= 1 && i == 2) {
				continue;
			}

			++cnt;

			if(idx % 6 == i){
				continue;
			}
			if(i == 0) {
				mp[s][idx] += solve(solve, s-s/6, idx-idx/6);
			}else{
				if(i < idx % 6){
					mp[s][idx] += solve(solve, s-(s+6-i)/6, idx-idx/6-1);
				}else{
					mp[s][idx] += solve(solve, s-(s+6-i)/6, idx-idx/6);
				}
			}
		}
		mp[s][idx] *= inv_six[cnt];
		return mp[s][idx];
	};

	for(int i = 1; i <= n; ++i){
		mint ans = solve(solve, n, i);
		cout << ans.x << endl;
	}

	return 0;
}
