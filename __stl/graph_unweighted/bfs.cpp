vi bfs(int s) {
	vi dist(g_size, 1000000000);
	queue<int> q;
	dist[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int c = q.front();
		for (auto i : adj[c]) {
			if (dist[i] < 1000000000) continue;
			dist[i] = dist[c]+1;
			q.push(i);
		}
		q.pop();
	}
	return dist;
}