typedef pair<ll, pair<int,int>> edge_t;

vector<edge_t> edges;

void add_edge(int a, int b, ll w) {
	edges.pb({w, {a, b}});
}

pair<ll, vector<pair<int,int>>> kruskal(int n) {
	sort(edges.begin(), edges.end());
	ufds dsu(n);
	ll total = 0;
	vector<pair<int,int>> mst_edges;
	for (auto e : edges) {
		ll w = e.first;
		int a = e.second.first;
		int b = e.second.second;
		if (dsu.rep(a) != dsu.rep(b)) {
			dsu.joinsets(a, b);
			total += w;
			mst_edges.pb({a, b});
		}
	}
	return {total, mst_edges};
}