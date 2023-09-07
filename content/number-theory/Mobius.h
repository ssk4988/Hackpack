/**
 * Author: Luke Videckis
 * Description: Calculate mobius function from 1 to LIM
 * Time: $O(LIM\log LIM)$
 * Status: Works but not stress-tested
 */
#pragma once

const int LIM = 1e6 + 1;
int mobius[LIM];

mobius[1] = 1;
rep(i, 1, LIM) {
	for(int j = i + i; j < LIM; j += i)
		mobius[j] -= mobius[i];
}
