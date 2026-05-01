class ufds {
public:
	vi p, r, size;
	int nsets;
	ufds(int n) {
		p.assign(n, 0);
		r.assign(n, 0);
		size.assign(n, 1);
		nsets = n;
		for (int i = 0; i < n; i++) p[i] = i;
	}
	int rep(int i) {
		if (p[i]==i) return i;
		p[i] = rep(p[i]);
		return p[i];
	}
	void joinsets(int i, int j) {
		int x = rep(i), y = rep(j);
		if (x == y) return;
		if (r[x] > r[y]) swap(x, y);
		p[x] = y;
		if (r[x] == r[y]) r[y]++;
		size[y] += size[x];
		nsets--;
	}
};