#define lso(S) ((S) & -(S))

class ft0 {
public:
	vll ft;
	ft0(int m) {
		ft.assign(m+1, 0);
	}
	void build(const vll &f) {
		int m = (int)f.size()-1;
		ft.assign(m+1, 0);
		for (int i = 1; i <= m; i++) {
			ft[i] += f[i];
			if (i+lso(i) <= m) ft[i+lso(i)] += ft[i];
		}
	}
	ft0(const vll &f) {
		build(f);
	}
	ft0(int m, const vi &s) {
		vll f(m+1, 0);
		for (int i = 0; i < (int)s.size(); i++) f[s[i]]++;
		build(f);
	}
	ll rq(int j) {
		ll s = 0;
		for (; j; j -= lso(j)) s += ft[j];
		return s;
	}
	ll rq(int i, int j) {
		return rq(j) - rq(i-1);
	}
	void upd(int i, ll v) {
		for (; i < (int)ft.size(); i += lso(i)) ft[i] += v;
	}
	int sel(ll k) {
		int p = 1;
		while (p*2 < (int)ft.size()) p *= 2;
		int i = 0;
		while (p) {
			if (k > ft[i+p]) {
				k -= ft[i+p];
				i += p;
			}
			p /= 2;
		}
		return i+1;
	}
};

class ft1 {
public:
	ft0 ft;
	ft1(int m) : ft(ft0(m)) {}
	void ru(int ui, int uj, ll v) {
		ft.upd(ui, v);
		ft.upd(uj+1, -v);
	}
	ll pq(int i) {
		return ft.rq(i);
	}
};

class ft2 {
public:
	ft1 rupq;
	ft0 purq;
	ft2(int m) : rupq(ft1(m)), purq(ft0(m)) {}
	void ru(int ui, int uj, ll v) {
		rupq.ru(ui, uj, v);
		purq.upd(ui, v*(ui-1));
		purq.upd(uj+1, -v*uj);
	}
	ll rq(int j) {
		return rupq.pq(j)*j - purq.rq(j);
	}
	ll rq(int i, int j) {
		return rq(j) - rq(i-1);
	}
};