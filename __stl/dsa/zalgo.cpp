vi z_algo(string s) {
	int n = (int)s.size();
	vi z(n, 0);
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r) z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
		}
	}
	z[0] = n;
	return z;
}

vi z_match(string text, string pat) {
	string s = pat + "#" + text;
	vi z = z_algo(s);
	vi ans;
	int m = (int)pat.size();
	for (int i = m + 1; i < (int)s.size(); i++) if (z[i] >= m) ans.pb(i - m - 1);
	return ans;
}