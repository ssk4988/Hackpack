/**
 * Author: Tyler Marks
 * Description: Gets all factors of a number $N$ given the prime factorization of the number.
 * Time: $O(\sqrt[3]{N})$
 * Status: Tested
 */

void getFactors(auto &pF, auto &primes, auto &factors, int i = 0, int n = 1) {
	if(i == sz(pF)) {
		factors.push_back(n);
		return;
	}

	for(int j = 0, pow = 1; i <= pf[j]; j++, pow *= primes[j])
		getFactors(pF, primes, factors, i+1, n * pow);
}
