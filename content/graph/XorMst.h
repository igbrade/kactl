/**
 * Author: Igor
 * Source: codeforces blog? https://codeforces.com/blog/entry/55701 Honestly I dont remember
 * Description: Given an undirected graph with n vertex, where each vetex is assigned to a number $a_i$ and the weigth of an edge
 * between i and j is $a_i xor a_j$, compute the mininmum spanning tree of this graph. Can also be solved
 * using boruvka algorithm
 * Time: O(N)
 * Status: tested with https://codeforces.com/contest/888/problem/G
 */

int n, a[MAXN], sa[MAXN];
vector<int> adj[MAXN];
int color[MAXN];
void paint(int v) {
	for(int u : adj[v])
		if(!color[u]) {
			color[u] = color[v] ^ 3;
			paint(u);
		}
}
int trieC[MAXN * 31][2], trieCnt[MAXN * 31], trieVal[MAXN * 31], trieSz;
void insert(int key, int val) {
	int n = 0;
	for(int bit = 30; bit >= 0; --bit)
	{
		trieCnt[n]++;
		if(bit == 0)
			return void(trieVal[n] = val);
		int b = (key >> (bit - 1)) & 1;
		if(!trieC[n][b])
			trieC[n][b] = ++trieSz;
		n = trieC[n][b];
	}
}
void erase(int key) {
	int n = 0;
	for(int bit = 30; bit >= 0; --bit) {
		trieCnt[n]--;
		if(bit == 0)
			return;
		int b = (key >> (bit - 1)) & 1;
		n = trieC[n][b];
	}
}
int get(int key) {
	int n = 0;
	for(int bit = 30; bit >= 0; --bit) {
		if(bit == 0)
			return trieVal[n];
		int b = (key >> (bit - 1)) & 1;
		if(trieC[n][b] && trieCnt[trieC[n][b]])
			n = trieC[n][b];
		else
			n = trieC[n][!b];
	}
}
long long solve(int l, int r, int bit = 29) {
	if(bit == -1 || l >= r)
		return 0;
	int m = l - 1;
	while(m <= r && ((a[sa[m + 1]] >> bit) & 1) == 0)
		m++;
	long long ret = solve(l, min(r, m), bit - 1) + solve(m + 1, r, bit - 1);
	if(l <= m && m + 1 <= r)
	{
		for(int i = l; i <= m; ++i)
			insert(a[sa[i]], sa[i]);
		
		tuple<int, int, int> mn((1 << 30), 0, 0);

		for(int i = m + 1; i <= r; ++i)
		{
			int k = get(a[sa[i]]);
			mn = min(mn, make_tuple(a[k] ^ a[sa[i]], k, sa[i]));
		}

		for(int i = l; i <= m; ++i)
			erase(a[sa[i]]);

		auto[x, y, z] = mn;
		ret += x;
		adj[y].push_back(z);
		adj[z].push_back(y);
	}
	return ret;
}
