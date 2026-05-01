vi v; // resize to g_size

void dfs(int c) {
	v[c] = 1;
	for (auto i : adj[c]) {
		if (v[i] == 0) {
			dfs(i);
		}
	}
}