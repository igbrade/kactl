/**
 * Author: unknown, copied from cp-algorithms https://cp-algorithms.com/graph/bridge-searching-online.html
 * Description: Find bridges online, after each edge addition
 * Time: $O(n \log n + m \log n)$
 */
vi par, _2ecc, _cc, _cc_sz, last_visit;
int bridges, lca_it;
void init(int n) {
    par.resize(n);
    _2ecc.resize(n); _cc.resize(n); _cc_sz.resize(n);
    lca_it = bridges = 0;
    last_visit.assign(n, 0);
    rep(i, 0, n) {
        _2ecc[i] = _cc[i] = i;
        _cc_sz[i] = 1;
        par[i] = -1;
    }
}
int find_2ecc(int v) {
    if (v == -1) return -1;
    return _2ecc[v] == v ? v : _2ecc[v] = find_2ecc(_2ecc[v]);
}
int find_cc(int v) {
    v = find_2ecc(v);
    return _cc[v] == v ? v : _cc[v] = find_cc(_cc[v]);
}
void make_root(int v) {
    int root = v;
    int child = -1;
    while (v != -1) {
        int p = find_2ecc(par[v]);
        par[v] = child;
        _cc[v] = root;
        child = v;
        v = p;
    }
    _cc_sz[root] = _cc_sz[child];
}
void merge_path (int a, int b) {
    ++lca_it;
    vi path_a, path_b;
    int lca = -1;
    while (lca == -1) {
        if (a != -1) {
            a = find_2ecc(a);
            path_a.push_back(a);
            if (last_visit[a] == lca_it) { lca = a; break; }
            last_visit[a] = lca_it;
            a = par[a];
        }
        if (b != -1) {
            b = find_2ecc(b);
            path_b.push_back(b);
            if (last_visit[b] == lca_it) { lca = b; break; }
            last_visit[b] = lca_it;
            b = par[b];
        }
    }
    for (int v : path_a) {
        _2ecc[v] = lca;
        if (v == lca) break;
        --bridges;
    }
    for (int v : path_b) {
        _2ecc[v] = lca;
        if (v == lca) break;
        --bridges;
    }
}
void add_edge(int a, int b) {
    a = find_2ecc(a); b = find_2ecc(b);
    if (a == b) return;
    int ca = find_cc(a);
    int cb = find_cc(b);
    if (ca != cb) {
        ++bridges;
        if (_cc_sz[ca] > _cc_sz[cb]) swap(a, b), swap(ca, cb);
        make_root(a);
        par[a] = _cc[a] = b;
        _cc_sz[cb] += _cc_sz[a];
        return;
    }
    merge_path(a, b);
}
