/**
 * Author: Sachin Sivakumar
 * Date: 2023-09-04
 * Description: Generates all factors of a number
 * Time: $O(n^{1/3})$, or $O(\# factors)$ to be precise
 * Status: works but not stress-tested
 */
#pragma once

#include "ModMulLL.h"
#include "MillerRabin.h"
#include "Factor.h"

void genfactors(vi &pows, vi &es, vector<ull> &primes, ull cur, int idx, vector<ull> &res) {
	res.pb(cur);
	if(idx == sz(pows)) return;
	for(int i = idx; i < sz(pows); i++) {
		pows[i]++;
		genfactors(pows, es, primes, cur * primes[i], i + (pows[i] >= es[i]), res);
		pows[i]--;
	}
}

vector<ull> factorize(ull n) {
	vector<ull> fs = factor(n);
	map<ull, int> freq;
	for(ull j : fs) freq[j]++;
	vector<ull> primes;
	vi es;
	for(auto [prime, exp] : freq) {
		primes.pb(prime);
		es.pb(exp);
	}
	vi pows(sz(es));
	vector<ull> res;
	genfactors(pows, es, primes, 1, 0, res);
	return res;
}
