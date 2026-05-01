int g_size;
vector<vi> adj;

void init(int n) {
	g_size = n;
	adj.assign(n, {});
	// v.assign(n, {});
}

void edge(int a, int b) {
	adj[a].pb(b);
	adj[b].pb(a);
}