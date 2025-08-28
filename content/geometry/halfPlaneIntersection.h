/**
 * Author: cp-algorithms
 * Description: Half-plane intersection
*/
#pragma once

#include "Point.h"

typedef long double dbl;
typedef Point<dbl> P;
const dbl eps = 1e-9, inf = 1e9; 
struct HP {
    // 'p' is a passing point of the line
    // 'pq' is the direction vector of the line.
    P p, pq;
    dbl angle;
    HP() {}
    HP(const P& a, const P& b): p(a), pq(b - a) {
        angle = atan2l(pq.y, pq.x);
    }
    // Check if point 'r' is outside this HP.
    // Every HP allows the region to the LEFT of its line.
    bool out(const P& r) { return pq.cross(r - p) < -eps; }
    // Comparator for sorting
    bool operator<(const HP& e) const {return angle<e.angle;}
    // Intersection point of the lines of two half-planes.
    // It is assumed they're never parallel.
    friend P inter(const HP& s, const HP& t) {
        dbl alpha = (t.p-s.p).cross(t.pq)/s.pq.cross(t.pq);
        return s.p + (s.pq * alpha);
    }
};
vector<P> hp_intersect(vector<HP>& H) { 
    P box[4] = { // Bounding box in CCW order
        P(inf, inf), P(-inf, inf), P(-inf, -inf), P(inf, -inf)
    };
    rep(i, 0, 4) {
        HP aux(box[i], box[(i+1) % 4]);
        H.push_back(aux);
    }
    sort(all(H));
    deque<HP> dq;
    int len = 0;
    rep(i, 0, sz(H)) {
        while (len>1 && H[i].out(inter(dq[len-1],dq[len-2]))){
            dq.pop_back(); --len;
        }
        while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
            dq.pop_front(); --len;
        }
        if (len>0 && fabsl(H[i].pq.cross(dq[len-1].pq))<eps){
            if (H[i].pq.dot(dq[len-1].pq) < 0.0)
                return vector<P>();
            if (H[i].out(dq[len-1].p)) {
                dq.pop_back(); --len;
            } else continue;
        }
        dq.push_back(H[i]); ++len;
    }
    while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))){
        dq.pop_back(); --len;
    }
    while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
        dq.pop_front(); --len;
    }
    if (len < 3) return vector<P>();
    vector<P> ret(len);
    rep(i, 0, len - 1) ret[i] = inter(dq[i], dq[i+1]);
    ret.back() = inter(dq[len-1], dq[0]);
    return ret;
}
