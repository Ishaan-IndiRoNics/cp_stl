int gcd(int a, int b) {
	return (b==0)?a:gcd(b,a%b);
}

int mod = 1000000007;

ll mxp(int x, int p) {
	if (p==0) return 1;
	ll h = mxp(x,p/2);
	h=(h*h)%mod;
	if (p%2==1) h=(x*h)%mod;
	return h;
}

int inv(int x) {
    return (x==1)?1:mod-(ll)(mod/x)*inv(mod%x)%mod;
}