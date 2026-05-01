template <class S, class F>
struct lazyseg {
	int n;
	int size;
	int log;
	vector<S> d;
	vector<F> lz;
	S (*op)(S, S);
	S (*e)();
	S (*apply)(F, S);
	F (*combine)(F, F);
	F (*id)();
	lazyseg(
		int _n,
		S (*_op)(S, S),
		S (*_e)(),
		S (*_apply)(F, S),
		F (*_combine)(F, F),
		F (*_id)()
	) {
		op = _op;
		e = _e;
		apply = _apply;
		combine = _combine;
		id = _id;
		n = _n;
		size = 1;
		log = 0;
		while (size<n) {
			size*=2;
			log++;
		}
		d.assign(size*2, e());
		lz.assign(size, id());
	}

	lazyseg(
		const vector<S>& v,
		S (*_op)(S, S),
		S (*_e)(),
		S (*_apply)(F, S),
		F (*_combine)(F, F),
		F (*_id)()
	) {
		op = _op;
		e = _e;
		apply = _apply;
		combine = _combine;
		id = _id;
		n = (int)v.size();
		size = 1;
		log = 0;
		while (size<n) {
			size*=2;
			log++;
		}
		d.assign(size*2, e());
		lz.assign(size, id());
		for (int i = 0; i < n; i++) {
			d[size+i] = v[i];
		}
		for (int i = size-1; i >= 1; i--) {
			update(i);
		}
	}

	void update(int k) {
		d[k] = op(d[2*k], d[2*k+1]);
	}

	void nodeu(int k, F f) {
		d[k] = apply(f, d[k]);
		if (k < size) lz[k] = combine(f, lz[k]);
	}

	void push(int k) {
		nodeu(2*k, lz[k]);
		nodeu(2*k+1, lz[k]);
		lz[k] = id();
	}

	void pset(int p, S x) {
		p += size;
		for (int i = log; i >= 1; i--) push(p>>i);
		d[p] = x;
		for (int i = 1; i <= log; i++) update(p>>i);
	}

	S pq(int p) {
		p += size;
		for (int i = log; i >= 1; i--) push(p>>i);
		return d[p];
	}

	S rq(int l, int r) {
		if (l == r) return e();
		l += size;
		r += size;
		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l) push(l >> i);
			if (((r >> i) << i) != r) push((r-1) >> i);
		}
		S left_result = e();
		S right_result = e();
		while (l < r) {
			if (l%2==1) {
				left_result = op(left_result, d[l]);
				l++;
			}
			if (r%2==1) {
				r--;
				right_result = op(d[r], right_result);
			}
			l/=2;
			r/=2;
		}
		return op(left_result, right_result);
	}

	S fullq() {
		return d[1];
	}

	void pu(int p, F f) {
		p += size;
		for (int i = log; i >= 1; i--) push(p >> i);
		d[p] = apply(f, d[p]);
		for (int i = 1; i <= log; i++) update(p >> i);
	}

	void ru(int l, int r, F f) {
		if (l == r) return;
		l += size;
		r += size;
		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l) push(l >> i);
			if (((r >> i) << i) != r) push((r-1) >> i);
		}
		int l_copy = l;
		int r_copy = r;
		while (l < r) {
			if (l%2==1) {
				nodeu(l, f);
				l++;
			}
			if (r%2==1) {
				r--;
				nodeu(r, f);
			}
			l/=2;
			r/=2;
		}
		l = l_copy;
		r = r_copy;
		for (int i = 1; i <= log; i++) {
			if (((l >> i) << i) != l) update(l >> i);
			if (((r >> i) << i) != r) update((r-1) >> i);
		}
	}
};

struct S {
    ll sum;
    int size;
};

struct F {
    ll add;
};

S op(S a, S b) {
    return {a.sum + b.sum, a.size + b.size};
}

S e() {
    return {0, 0};
}

S apply(F f, S x) {
    return {x.sum + f.add * x.size, x.size};
}

F combine(F f, F g) {
    return {f.add + g.add};
}

F id() {
    return {0};
}