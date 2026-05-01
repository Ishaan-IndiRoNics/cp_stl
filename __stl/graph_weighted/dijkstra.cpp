vll dij(int s) {
	vll dist(g_size, 2000000000000000000);
	priority_queue<pli, vector<pli>, greater<pli>> pq;
	dist[s] = 0;
	pq.push(mp(0, s));
	while (!pq.empty()) {
		pli c = pq.top();
		pq.pop();
		if (c.e1 > dist[c.e2]) continue;
		for (auto i : adj[c.e2]) {
			if (dist[c.e2] + i.e1 < dist[i.e2]) {
				dist[i.e2] = dist[c.e2] + i.e1;
				pq.push(mp(dist[i.e2], i.e2));
			}
		}
	}
	return dist;
}