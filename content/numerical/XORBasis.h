/**
 * Author: Sachin Sivakumar
 * Date: 2023-09-05
 * Description: maintains a basis in $\mathbb{Z}_2^d$
 * Time: $O(B^2/32)$
 * Status: works but not stress tested
 */

#pragma once

template<int B>
struct XORBasis {
	bitset<B> basis[B];
	int npivot = 0, nfree = 0;
	bool check(bitset<B> &v) {
		rep(i, 0, B)
			if (v.test(i)) v ^= basis[i];
		return v.none();
	}
	bool add(bitset<B> &v) {
		rep(i, 0, B)
			if (v.test(i)) {
				if (basis[i].none()) return basis[i] = v, ++npivot;
				v ^= basis[i];
			}
        return !++nfree;
	}
};
