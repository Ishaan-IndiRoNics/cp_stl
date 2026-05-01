typedef pair<ll, int> pli;
#define mp make_pair
#define e1 first
#define e2 second

int g_size;
vector<vector<pli>> adj;

void init(int n) {
	g_size = n;
	adj.assign(n, {});
	// v.assign(n, {});
}

void edge(int a, int b, ll w) {
	adj[a].pb(mp(w,b));
	adj[b].pb(mp(w,a));
}