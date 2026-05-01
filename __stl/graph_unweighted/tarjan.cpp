vi tin, low, vis, is_art;
vector<pair<int,int>> bridges;
int timer_tarjan;

void dfs_tarjan(int v, int p) {
	vis[v] = 1;
	low[v] = timer_tarjan++;
	tin[v] = low[v];
	int children = 0;
	for (auto to : adj[v]) {
		if (to == p) continue;
		if (vis[to]) low[v] = min(low[v], tin[to]);
		else {
			dfs_tarjan(to, v);
			low[v] = min(low[v], low[to]);
			if (low[to] > tin[v]) bridges.pb({v, to});
			if (p != -1 && low[to] >= tin[v]) is_art[v] = 1;
			children++;
		}
	}
	if (p == -1 && children > 1) is_art[v] = 1;
}

pair<vi, vector<pair<int,int>>> tarjan() {
	tin.assign(g_size, 0);
	low.assign(g_size, 0);
	vis.assign(g_size, 0);
	is_art.assign(g_size, 0);
	bridges.clear();
	timer_tarjan = 0;
	for (int i = 0; i < g_size; i++) if (!vis[i]) dfs_tarjan(i, -1);
	vi arts;
	for (int i = 0; i < g_size; i++) if (is_art[i]) arts.pb(i);
	return {arts, bridges};
}