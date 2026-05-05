#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<vector<pair<int,int>>> spt;
vector<int> par,hvy,fst,grp,pew;
vector<pair<int,int>> et;

int hld(int c, int d) {
	int s = 1, m = 0;
	fst[c] = et.size();
	et.push_back({d,c});
	for (auto i : adj[c]) {
		if (i==par[c]) continue;
		par[i]=c;
		int cs = hld(i,d+1);
		et.push_back({d,c});
		s+=cs;
		if (cs>m) {
			m=cs;
			hvy[c]=i;
		}
	}
	return s;
}

void sptb(int n) {
	int mp = 1, mpi = 0;
	while (mp<=(n<<1)-2) {
		mp<<=1;
		mpi++;
	}
	spt.resize(mpi);
	for (int i = 0; i < (n<<1) - 1; i++) spt[0].push_back(et[i]);
	for (int i = 1; i < mpi; i++) for (int j = 0; j <= (n<<1) - 1 - (1<<i); j++) spt[i].push_back(min(spt[i-1][j],spt[i-1][j+(1<<(i-1))]));
}

int lca(int a, int b) {
	a = fst[a];
	b = fst[b];
	if (a>b) swap(a,b);
	int s = 31-__builtin_clz(b-a+1);
	return min(spt[s][a],spt[s][b+1-(1<<s)]).second;
}

void pa(int d, int a) {
	while (et[fst[d]].first>et[fst[a]].first) {
		if (d==grp[d]) {
			pew[d]++;
			d = par[d];
		}
		else {
			int n = max(et[fst[grp[d]]],et[fst[a]]).second;
			pew[hvy[n]]++;
			if (hvy[d]>0) pew[hvy[d]]--;
			d = n;
		}
	}
}

void decomp(int c, int g) {
	grp[c] = g;
	for (auto i : adj[c]) {
		if (i==par[c]) continue;
		if (i==hvy[c]) decomp(i,g);
		else decomp(i,i);
	}
}

int main() {
	int n,m,k,i,e1,e2;
	cin >> n >> m >> k;
	adj.resize(n);
	par.resize(n);
	hvy.resize(n);
	fst.resize(n);
	grp.resize(n);
	pew.resize(n);
	int el[n-1][2];
	for (i = 0; i < n-1; i++) {
		cin >> e1 >> e2;
		adj[--e1].push_back(--e2);
		adj[e2].push_back(e1);
		el[i][0] = e1;
		el[i][1] = e2;
	}
	hld(0,0);
	decomp(0,0);
	sptb(n);
	int pei[n];
	for (i = 0; i < n-1; i++) pei[max(et[fst[el[i][0]]],et[fst[el[i][1]]]).second] = i+1;
	for (int j = 0; j < m; j++) {
		cin >> e1;
		vector<pair<int,int>> qs(e1);
		for (i = 0; i < e1; i++) {
			cin >> e2;
			qs[i] = {fst[e2-1],e2-1};
		}
		sort(qs.begin(), qs.end());
		int prev = qs[0].second, oca = prev, og = prev;
		for (i = 1; i < e1; i++) {
			oca = lca(oca,qs[i].second);
			pa(qs[i].second,lca(qs[i].second,prev));
			prev = qs[i].second;
		}
		pa(og,oca);
	}
	vector<int> id;
	for (i = 1; i < n; i++) {
		if (fst[i]==-1) continue;
		else if (i==hvy[par[i]]) {
			int c = grp[i], s = 0;
			while (hvy[c]>0) {
				c = hvy[c];
				s += pew[c];
				if (s>=k) id.push_back(pei[c]);
				fst[c] = -1;
			}
		}
		else if (pew[i]>=k) id.push_back(pei[i]);
	}
	cout << id.size() << endl;
	sort(id.begin(), id.end());
	for (auto i : id) cout << i << " ";
}