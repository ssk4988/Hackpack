/**
 * Description: Returns the intersection of halfplanes as a polygon
 * Time: O(n \log n)
 * Author: Tyler Marks
 * Source: CP-Algorithms 
 */

const double eps = 1e-8;
typedef Point<double> P;
struct HalfPlane {
	P s, e, d;
	HalfPlane(P s = P(), P e = P()): s(s), e(e), d(e - s) {}
	bool contains(P p) { return d.cross(p - s) > -eps; }
	bool operator<(HalfPlane hp) {
		if(abs(d.x) < eps && abs(hp.d.x) < eps) 
			return d.y > 0 && hp.d.y < 0;
		bool side = d.x < eps || (abs(d.x) <= eps && d.y > 0);
		bool sideHp = hp.d.x < eps || (abs(hp.d.x) <= eps && hp.d.y > 0);
		if(side != sideHp) return side;
		return d.cross(hp.d) > 0;
	}
	P inter(HalfPlane hp) {
		auto p = hp.s.cross(e, hp.e), q = hp.s.cross(hp.e, s);
		return (s * p + e * q) / d.cross(hp.d);
	}
};

vector<P> hpIntersection(vector<HalfPlane> hps) {
	sort(all(hps));
	int n = sz(hps), l = 1, r = 0;
	vector<HalfPlane> dq(n+1);
	rep(i, 0, n) {
		while(l < r && !hps[i].contains(dq[r].inter(dq[r-1]))) r--;
		while(l < r && !hps[i].contains(dq[l].inter(dq[l+1]))) l++;
		dq[++r] = hps[i];
		if(l < r && abs(dq[r].d.cross(dq[r-1].d)) < eps) {
			if(dq[r].d.dot(dq[r-1].d) < 0) return {};
			r--;
			if(dq[r].contains(hps[i].s)) dq[r] = hps[i];
		}
	}
	while(l < r - 1 && !dq[l].contains(dq[r].inter(dq[r-1]))) r--;
	while(l < r - 1 && !dq[r].contains(dq[l].inter(dq[l+1]))) l++;
	if(l > r - 2) return {};
	vector<P> poly;
	rep(i, l, r)
		poly.push_back(dq[i].inter(dq[i+1]));
	poly.push_back(dq[r].inter(dq[l]));
	return poly;
}
