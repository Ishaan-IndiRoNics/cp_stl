#define A 911382323LL
#define B 1000000007LL
#define C 972663749LL
#define D 1000000009LL
#define mp make_pair

vll h1, p1, h2, p2;

void hinit(string s, int n) {
	h1.assign(n, 0);
	p1.assign(n, 0);
	h2.assign(n, 0);
	p2.assign(n, 0);
	h1[0] = s[0];
	p1[0] = 1;
	h2[0] = s[0];
	p2[0] = 1;
	for (int i = 1; i < n; i++) {
		h1[i] = (h1[i-1]*A+s[i])%B;
		p1[i] = (p1[i-1]*A)%B;
		h2[i] = (h2[i-1]*C+s[i])%D;
		p2[i] = (p2[i-1]*C)%D;
	}
}

pair<ll,ll> sbsh(int a, int b) {
	return (a==0)?mp(h1[b], h2[b]):mp((h1[b]-(h1[a-1]*p1[b-a+1])%B+B)%B,(h2[b]-(h2[a-1]*p2[b-a+1])%D+D)%D);
}
