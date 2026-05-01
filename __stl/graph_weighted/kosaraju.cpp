vi kos_vis, kos_order;
vector<vi> radj;

void dfs_kos1(int v) {
	kos_vis[v] = 1;
	for (auto to : adj[v]) if (!kos_vis[to.e2]) dfs_kos1(to.e2);
	kos_order.pb(v);
}

void dfs_kos2(int v, vi& comp) {
	kos_vis[v] = 1;
	comp.pb(v);
	for (auto to : radj[v]) if (!kos_vis[to]) dfs_kos2(to, comp);
}

vector<vi> kosaraju() {
	kos_vis.assign(g_size, 0);
	kos_order.clear();
	radj.assign(g_size, {});
	for (int v = 0; v < g_size; v++) for (auto to : adj[v]) radj[to.e2].pb(v);
	for (int i = 0; i < g_size; i++) if (!kos_vis[i]) dfs_kos1(i);
	reverse(kos_order.begin(), kos_order.end());
	kos_vis.assign(g_size, 0);
	vector<vi> comps;
	for (int v : kos_order) {
		if (!kos_vis[v]) {
			vi comp;
			dfs_kos2(v, comp);
			comps.pb(comp);
		}
	}
	return comps;
}