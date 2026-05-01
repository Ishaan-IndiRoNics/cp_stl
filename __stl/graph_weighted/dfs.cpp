vi v;

void dfs(int c) {
	v[c] = 1;
	for (auto i : adj[c]) {
		if (v[i.e2] == 0) {
			dfs(i.e2);
		}
	}
}