/**
 * Author: Sachin Sivakumar
 * Date: 2023-09-05
 * Description: maintains a basis in $\mathbb{Z}_2^d$, use longs for $B>32$
 * Time: $O(B)$
 * Status: works but not stress tested
 */

#pragma once

template<int B = 32>
struct XORBasis {
	int basis[B] = {};
	int nbasic = 0, nfree = 0;
	bool indep(int v) {
		for(int i = B - 1; i >= 0; i--)
			if (v & (1 << i)) v ^= basis[i];
		return v;
	}
	void add(int v) {
		for(int i = B - 1; i >= 0; i--)
			if (v & (1 << i)) {
				if (basis[i]) v ^= basis[i];
				else {
					basis[i] = v;
					nbasic++;
					return;
				}
			}
		nfree++;
	}
};
