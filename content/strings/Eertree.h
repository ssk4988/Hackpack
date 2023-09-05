/**
 * Author: Jacob Steinebronn
 * Date: 2022-09-20
 * Description: Generates an eertree on str. $cur$ is accurate at the end of the main loop before the final assignment to $t$.
 * Time: $O(|S|)$
 * Status: Works but not stress-tested
 */

#pragma once

vector<int> slink = {0, 0}, len = {-1, 0};
vector<vector<int>> down(2, vector<int>(26, -1));
int cur = 0, t = 0;
for (int i = 0; i < str.size(); i++) {
	char c = str[i]; int ci = c - 'a';
	while (t <= 0 || str[t-1] != c) 
	t = i - len[cur = slink[cur]];
	if (down[cur][ci] == -1) {
	down[cur][ci] = slink.size();
	down.emplace_back(26, -1);
	len.push_back(len[cur] + 2);
	if (len.back() > 1) {
		do t = i - len[cur = slink[cur]];
		while(t <= 0 || str[t-1] != c);
		slink.push_back(down[cur][ci]);
	} else slink.push_back(1);
	cur = slink.size() - 1;
	} else cur = down[cur][ci];
	t = i - len[cur] + 1;
}
