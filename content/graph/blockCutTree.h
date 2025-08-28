/**
 * Author: tdas0
 * Description: Cria a block-cut tree, uma arvore com os blocos
 * e os pontos de articulacao
 * Blocos sao componentes 2-vertice-conexos maximais
 * Uma 2-coloracao da arvore eh tal que uma cor sao
 * os blocos, e a outra cor sao os pontos de art.
 * art[i] responde se i eh ponto de articulacao
 * Funciona pra grafo nao conexo, e ja limpa tudo
 * Time: $O(N+M)$
 */

const int MAX = 100100;
vi g[MAX];
stack<int> s;
int id[MAX], art[MAX], pos[MAX];
vector<vi> blocks, tree;
int dfs(int i, int &t, int p = -1) {
	int lo = id[i] = t++;
	s.push(i);
	for (int j : g[i]) if (j != p) {
		if (id[j] == -1) {
			int val = dfs(j, t, i);
			lo = min(lo, val);
			if (val >= id[i]) {
				art[i]++;
				blocks.emplace_back(1, i);
				while (blocks.back().back() != j)
					blocks.back().push_back(s.top()), s.pop();
			}
			// if (val > id[i]) aresta i-j eh ponte
		} else lo = min(lo, id[j]);
	}
	if (p == -1 and art[i]) art[i]--;
	return lo;
}
void build(int n) {
	rep(i, 0, n) id[i] = -1, art[i] = 0;
	blocks.clear(), tree.clear();
	while (s.size()) s.pop();
	int t = 0;
	rep(i, 0, n) if (id[i] == -1) dfs(i, t, -1);
	tree.resize(blocks.size()); // no maximo 2*n
	rep(i, 0, n) if (art[i])
		pos[i] = tree.size(), tree.emplace_back();
	rep(i, 0, sz(blocks)) for (int j : blocks[i]) {
        int& u = pos[j];
		if (!art[j]) u = i;
		else tree[i].push_back(u), tree[u].push_back(i);
	}
}
