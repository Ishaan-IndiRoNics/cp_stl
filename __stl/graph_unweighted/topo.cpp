vi topo() {
	vi indeg(g_size);
	for (int i = 0; i < g_size; i++) for (auto j : adj[i]) indeg[j]++;
	queue<int> q;
	for (int i = 0; i < g_size; i++) if (indeg[i] == 0) q.push(i);
	vi ans;
	while (!q.empty()) {
		int c = q.front();
		ans.pb(c);
		for (auto i : adj[c]) {
			indeg[i]--;
			if (indeg[i] == 0) q.push(i);
		}
		q.pop();
	}
	return ans;
}