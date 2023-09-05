/**
 * Author: Sachin Sivakumar
 * Date: 2023-09-04
 * Description: Bitwise Trie with an arbitrary number of bits (use longs for $B>32$)
 * Time: $O(B)$ per query
 * Status: Works but not stress-tested
 */
#pragma once

struct Node
{
	Node *nex[2] = {};
	int bitnum;
	Node(int b) : bitnum(b) {}
	void add(int val) {
		if (bitnum == 0) return;
		int idx = 1 & (val >> (bitnum - 1));
		if (nex[idx] == NULL) nex[idx] = new Node(bitnum - 1);
		nex[idx]->add(val);
	}
	int closest(int val) {
		int res = 0;
		if (bitnum == 0) return res;
		int idx = 1 & (val >> (bitnum - 1));
		if (nex[idx] != NULL) {
			res |= idx << (bitnum - 1);
			res |= nex[idx]->closest(val);
		} else if (nex[1 - idx] != NULL) {
			res |= (1 - idx) << (bitnum - 1);
			res |= nex[1 - idx]->closest(val);
		}
		return res;
	}
};
