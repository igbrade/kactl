/**
* Author: Igor
* Description: li-chao tree. You can insert lines like $ax+b$ on an interval [i, j], and
* then query the maximum point in any line at position x
* Time: O(Q*log(M)), where M is the length of the range where the lines are active.
*/

ll eval(pair<int, int> f, int x) { return f.first * 1LL * x + f.second; }
struct no {
	int bg, nd, md;
	no *l, *r;
	pii best;
	no(int bgg, int ndd) : bg(bgg), nd(ndd), md((bg + nd) >> 1), best(-1e11, -1e18){
		if(bg != nd) l = new no(bg, md), r = new no(md + 1, nd);
	}
	void upd(int a, int b, pii val) {
		if(b < bg || nd < a) return;
		if(a <= bg && nd <= b)
		{
			bool lef = eval(val, bg) > eval(best, bg);
			bool mid = eval(val, md) > eval(best, md);
			if(mid) swap(val, best);
			if(bg == nd) return;
			if(lef != mid) l->upd(a, b, val);
			else r->upd(a, b, val);
			return;
		}
		l->upd(a, b, val); r->upd(a, b, val);
	}
	ll get(int pos) {
		if(bg == nd) return eval(best, pos);
		ll ret = eval(best, pos);
		return max(ret, (pos <= md ? l : r)->get(pos));
	}
};
