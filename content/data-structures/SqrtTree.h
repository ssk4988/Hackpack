/**
 * Author: Sachin Sivakumar
 * Date: 2024-09-15
 * Description: Alternative to RMQ which computes static range queries (inclusive-exclusive) for non-idempotent operations
 * Time: O(1) query, O(N \log \log N) construction
 * Status: Stress-tested
 */
#pragma once

template<typename T>
struct SQRT {
	vi bits, pows, t;
    vector<T> a;
	vector<vector<T>> pref, suff;
	vector<vector<vector<T>>> blocks;
	SQRT(vector<T> a) : a(a) {
		int b = __lg(sz(a)), n = sz(a);
		for(; b; b = min(b-1, (b + 1) / 2)) bits.push_back(b), pows.push_back(1 << b);
		pref.resize(sz(bits), a), suff.resize(sz(bits), a), blocks.resize(sz(bits));
		rep(i, 0, sz(bits)) {
			rep(j, 0, n)
				if(j & (pows[i]-1)) pref[i][j] = pref[i][j-1] + pref[i][j];
			for(int j = n-1; j >= 0; j--)
				if((j+1) & (pows[i]-1)) suff[i][j] = suff[i][j] + suff[i][j+1];
            
            blocks[i].assign(n / pows[i], vector<T>(pows[i]));
			for(int j = sz(blocks[i])-1; j >= 0; j--) {
				blocks[i][j][0] = suff[i][j * pows[i]];
				rep(k, 1, sz(blocks[i][j])) if(j+k < sz(blocks[i])) blocks[i][j][k] = blocks[i][j][k-1] + blocks[i][j+k][0];
			}
		}
        t.resize(30, sz(bits)-1);
        rep(i, 0, sz(t)) while(t[i] > 0 && i > bits[t[i]-1]) t[i]--;
	}
	T query(int l, int r) {
		assert(l < r);
		if(r-l == 1) return a[l];
		if(r-l == 2) return a[l] + a[l+1];
        int i = t[__lg(r - l) + (__builtin_popcount(r-l) != 1)];
		T left = suff[i][l];
		r--, l = (l | (pows[i]-1))+1;
		int s = (r-l) / pows[i];
		if(s) left = left + blocks[i][l / pows[i]][s-1];
		return left + pref[i][r];
	}
};
