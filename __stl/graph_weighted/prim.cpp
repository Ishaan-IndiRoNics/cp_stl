pair<ll, vector<pair<int,int>>> prim() {
	vi used(g_size, 0);
	vector<pair<int,int>> mst_edges;
	ll total = 0;
	priority_queue<
		pair<ll, pair<int,int>>,
		vector<pair<ll, pair<int,int>>>,
		greater<pair<ll, pair<int,int>>>
	> pq;
	for (int start = 0; start < g_size; start++) {
		if (used[start]) continue;
		pq.push(mp(0, mp(start, -1)));
		while (!pq.empty()) {
			auto cur = pq.top();
			pq.pop();
			ll w = cur.e1;
			int v = cur.e2.e1;
			int parent = cur.e2.e2;
			if (used[v]) continue;
			used[v] = 1;
			total += w;
			if (parent != -1) mst_edges.pb(mp(parent, v));
			for (auto edge : adj[v]) {
				ll nw = edge.e1;
				int to = edge.e2;
				if (!used[to]) pq.push(mp(nw, mp(to, v)));
			}
		}
	}
	return {total, mst_edges};
}