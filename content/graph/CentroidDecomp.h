/**
 * Author: Andy Phan
 * Date: 2023-02-11
 * Description: Computes centroid decomposition on connected tree, and runs callback function
 * Usage: centroidDecomp(adj, [\&] (int root, vector<int>\& isIn) { ... });
	all nodes with isIn[i] = 1 connected to root are part of root's centroid
 * Time: $O(n \log n)$
 * Status: Untested
 */
#pragma once

template<class G, class F>
void centroidDecomp(G g, F f) {
	vi s(sz(g), 1), par(sz(g)), is(s);
	auto go = [&] (int u, int p, auto& go) -> void {
		if ((par[u] = p) != -1) g[u].erase(find(all(g[u]), p));
		for (int v : g[u]) go(v, u, go), s[u] += s[v];
	};
	go(0, -1, go); queue<int> q({0});
	while (sz(q)) {
		int x = q.front(), b = x, ss, c; q.pop();
		do for(int v : g[c = b]) if(s[v] > s[x]/2) b = v;
			while(c != b);
		f(c, is);
		is[c] = 0, ss = s[c];
		for (int v : g[c]) if (s[v] > 0) q.push(v);
		if (c != x) q.push(x);
		do s[c] -= ss; while ((c = par[c]) != par[x]);
	}
}
