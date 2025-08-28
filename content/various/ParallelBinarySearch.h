/**
* Author: himanshujaju(codeforces)
* Source: https://codeforces.com/blog/entry/45578
* Description: (Meteors) There are $N$ member states and $M$ sectors. Each sector is owned by a member state. There are $Q$ queries, each of which denote the amount of meteor shower in a
* [L, R] range of sectors on that day. The ith member state wants to collect readq[i] meteors over all its sectors. For every member state, what is the minimum number of days  it would have to
* wait to collect atleast the required amount of meteors.
* Time: $O(Q \times log(Q) \times log(M))$
*/
ll bit[MAXN];
void add(int pos, int val); // BIT ADD(+=)
ll get(int pos); //BIT GET (-=)
void apply(int i, int x) {
	if(l[i] <= r[i]) {
		add(l[i], a[i] * x); add(r[i] + 1, -a[i] * x);
	}
	else {
		add(1, a[i] * x);add(r[i] + 1, -a[i] * x); add(l[i], a[i] * x);
	}
}
void solve(vector<int> cands, int bg, int nd, int &last) {
	if(bg == nd) {
		for(int x : cands)
			ans[x] = bg;
		return;
	}
	int md = (bg + nd) >> 1;
	vector<int> cl, cr;
	while(last != md) {
		if(last > md) {
			apply(last, -1); last--;
		} else {
			last++; apply(last, 1);
		}
	}
	for(int x : cands) {
		ll cur = 0;
		for(int y : c[x]) {
			cur += get(y);
			if(cur >= p[x])
				break;
		}
		(cur >= p[x] ? cl : cr).push_back(x);
	}
	solve(cl, bg, md, last); solve(cr, md + 1, nd, last);
}

// for all logQ steps:
//     clear range tree and linked list check
//     for all member states i:
//         if L[i] != R[i]:
//             mid = (L[i] + R[i]) / 2
//             insert i in check[mid]
//     for all queries q:
//         apply(q)
//         for all member states m in check[q]:
//             if m has requirements fulfilled:
//                 R[m] = q
//             else:
//                 L[m] = q + 1
