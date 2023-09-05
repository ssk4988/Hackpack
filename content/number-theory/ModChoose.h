/**
 * Author: Sachin Sivakumar
 * Date: 2023-09-04
 * Description: Calculates binomial theorem coefficients under mod
 * Reduce memory by doing prefix product sweep on inv, remove invfact
 * Increase speed by constant factor by changing to arrays
 * Time: construction takes $O(N)$, query in $O(1)$
 * Status: works but not stress tested
 */
#pragma once

struct ModChoose {
	const ll MOD;
	const int LIM;
	vl inv, fact, invfact;
	ModChoose(int n, ll m) : LIM(n+1), MOD(m), inv(LIM), fact(LIM), invfact(LIM) {
		fact[0] = invfact[0] = inv[1] = fact[1] = invfact[1] = 1;
		rep(i, 2, LIM) {
			inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
			fact[i] = (i * fact[i - 1]) % MOD;
			invfact[i] = (inv[i] * invfact[i - 1]) % MOD;
		}
	}
	ll choose(int n, int k) {
		if (k > n || k < 0) return 0;
		return (fact[n] * invfact[k]) % MOD * invfact[n - k] % MOD;
	}
};
