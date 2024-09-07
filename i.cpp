#include<bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n), b(n), c(m), d(m);
	for(int i = 0; i < n; ++i) cin >> a[i];
	for(int i = 0; i < n; ++i) cin >> b[i];
	for(int i = 0; i < m; ++i) cin >> c[i];
	for(int i = 0; i < m; ++i) cin >> d[i];
	map<pair<int, int>, int> mp, mp2;
	for(int i = 0; i < n; ++i){
		int g = gcd(a[i], b[i]);
		mp[make_pair(a[i]/g, b[i]/g)] += g;
	}
	for(int i = 0; i < m; ++i){
		int g = gcd(c[i], d[i]);
		mp2[make_pair(c[i]/g, d[i]/g)] += g;
	}

	vector<tuple<int, int, int>> f, g;
	for(auto [i, j]: mp){
		f.emplace_back(i.first, i.second, j);
	}
	for(auto [i, j]: mp2){
		g.emplace_back(i.first, i.second, j);
	}
	sort(f.begin(), f.end(), [](auto l, auto r)->bool{
			return (long long)get<1>(l) * get<0>(r) < (long long) get<1>(r) * get<0>(l);});
	sort(g.begin(), g.end(), [](auto l, auto r)->bool{
			return (long long)get<1>(l) * get<0>(r) < (long long) get<1>(r) * get<0>(l);});
	
	vector<pair<long long, long long>> F(f.size()+1), G(g.size()+1);
	for(int i = 0; i < f.size(); ++i){
		F[i+1].first += F[i].first + get<0>(f[i])*get<2>(f[i]);
		F[i+1].second += F[i].second + get<1>(f[i])*get<2>(f[i]);
	}
	for(int i = 0; i < g.size(); ++i){
		G[i+1].first += G[i].first + get<0>(g[i])*get<2>(g[i]);
		G[i+1].second += G[i].second + get<1>(g[i])*get<2>(g[i]);
	}
	
	n = F.size();
	m = G.size();

	bool flag = true;
	for(int i = 0; i < n-1; ++i) {
		pair<long long, long long> PQ = make_pair(F[i+1].first-F[i].first, F[i+1].second-F[i].second);
		for(int j = 0; j < m-1; ++j){
			pair<long long, long long> PR = make_pair(G[j+1].first-F[i].first, G[j+1].second-F[i].second);
			flag &= (PR.second * PQ.first - PR.first * PQ.second >= 0);
		}
	}

	if(flag){
		cout << "Yes" << endl;
	}else{
		cout << "No" << endl;
	}
	
	return 0;
}
