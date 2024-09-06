#include<bits/stdc++.h>

namespace atcoder {

namespace internal {

int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}

}

namespace atcoder {

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
  public:
    lazy_segtree() : lazy_segtree(0) {}
    lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push(r >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

}

using namespace std;

using S = int;
using F = int; 

const S INF = 1e9;

S op(S a, S b){ return std::min(a, b); }
S e(){ return INF; }
S mapping(F f, S x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

using ll = long long;

vector<int> sz, in, out, nxt;
vector<vector<int>> g;
int t;

void dfs_sz(int v = 0){
	sz[v] = 1;
	for(auto &u: g[v]){
		dfs_sz(u);
		sz[v] += sz[u];
		if(sz[u] > sz[g[v][0]]){
			swap(g[v][0], u);
		}
	}
}

void dfs_hld(int v = 0){
	in[v] = t++;
	for(auto u: g[v]){
		nxt[u] = (u == g[v][0] ? nxt[v] : u);
		dfs_hld(u);
	}
	out[v] = t;
}

int main(){

	int n;
	cin >> n;

	sz.assign(n, 0);
	in.assign(n, 0);
	out.assign(n, 0);
	nxt.assign(n, 0);
	g.assign(n, vector<int>());
	t = 0;

	vector<int> par(n, 0);

	for(int i = 0; i < n-1; ++i){
		int b;
		cin >> b;
		--b;
		g[b].push_back(i+1);
		par[i+1] = b;
	}

	vector<ll> f(n);
	for(int i = 0; i < n; ++i) cin >> f[i];

	dfs_sz();
	dfs_hld();

	vector<int> vec(n);
	for(int i = 0; i < n; ++i){
		vec[in[i]] = sz[i];
	}

	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(vec);

	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
	vector<ll> cnt(n);

	for(int i = 0; i < n; ++i){
		pq.emplace(f[i], i);
	}

	auto add_path = [&](int u, int v, int p)->void{
		while(nxt[u] != nxt[v]){
			if(sz[nxt[u]] > sz[nxt[v]]) swap(u, v);
			seg.apply(in[nxt[u]], in[u]+1, p);
			u = par[nxt[u]];
		}
		if(sz[u] < sz[v]) swap(u, v);
		seg.apply(in[u], in[v]+1, p);
	};

	auto get_min = [&](int u, int v)->int{
		int ret = INT_MAX;
		while(nxt[u] != nxt[v]){
			if(sz[nxt[u]] > sz[nxt[v]]) swap(u, v);
			ret = min(ret, seg.prod(in[nxt[u]], in[u]+1));
			u = par[nxt[u]];
		}
		if(sz[u] < sz[v]) swap(u, v);
		ret = min(ret, seg.prod(in[u], in[v]+1));
		return ret;
	};

	ll ans = 0;
	int iter = 0;
	while(iter < n){	
		auto [c, tmp] = pq.top();
		pq.pop();
		if(get_min(0, tmp) <= 0){
			continue;
		}
		++iter;
		ans += c;
		add_path(0, tmp, -1);
		cnt[tmp]++;
		if(cnt[tmp] > sz[tmp]) continue;
		pq.emplace(f[tmp]*(cnt[tmp]*2+1), tmp);
	}
	cout << ans << endl;
		
	return 0;
}
