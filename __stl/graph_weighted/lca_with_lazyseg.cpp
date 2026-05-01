struct LCA_S {
	int depth;
	int node;
};

struct LCA_F {
	int dummy;
};

LCA_S lca_op(LCA_S a, LCA_S b) {
	if (a.depth < b.depth) return a;
	return b;
}

LCA_S lca_e() {
	return {1000000000, -1};
}

LCA_S lca_apply(LCA_F f, LCA_S x) {
	return x;
}

LCA_F lca_combine(LCA_F f, LCA_F g) {
	return {0};
}

LCA_F lca_id() {
	return {0};
}

vi lca_first, lca_depth, lca_vis;
vector<ll> lca_dist;
vector<LCA_S> lca_euler;
lazyseg<LCA_S, LCA_F>* lca_seg;

void dfs_lca(int v, int p, int depth, ll dist) {
	lca_vis[v] = 1;
	lca_depth[v] = depth;
	lca_dist[v] = dist;
	lca_first[v] = (int)lca_euler.size();
	lca_euler.pb({depth, v});
	for (auto edge : adj[v]) {
		ll w = edge.e1;
		int to = edge.e2;
		if (to == p) continue;
		if (lca_vis[to]) continue;
		dfs_lca(to, v, depth + 1, dist + w);
		lca_euler.pb({depth, v});
	}
}

void build_lca(int root = 0) {
	lca_first.assign(g_size, -1);
	lca_depth.assign(g_size, 0);
	lca_vis.assign(g_size, 0);
	lca_dist.assign(g_size, 0);
	lca_euler.clear();
	dfs_lca(root, -1, 0, 0);
	lca_seg = new lazyseg<LCA_S, LCA_F>(
		lca_euler,
		lca_op,
		lca_e,
		lca_apply,
		lca_combine,
		lca_id
	);
}

int lca(int a, int b) {
	int l = lca_first[a];
	int r = lca_first[b];
	if (l > r) swap(l, r);
	return lca_seg->rq(l, r + 1);.node;
}

ll dist_tree(int a, int b) {
	int c = lca(a, b);
	return lca_dist[a] + lca_dist[b] - 2 * lca_dist[c];
}