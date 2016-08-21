#include <bits/stdc++.h>
using namespace std;

struct PT {
	int x, y;
	PT() : x(0), y(0) {}
	PT(int x, int y) : x(x), y(y) {}
	PT(const PT& rhs) : x(rhs.x), y(rhs.y) {}
	int operator < (const PT& rhs) const {return make_pair(y, x) < make_pair(rhs.y, rhs.x);}
	int operator == (const PT& rhs) const {return make_pair(y, x) == make_pair(rhs.y, rhs.x);}
};
long long cross(PT a, PT b) {
	return (long long) a.x * b.y - (long long) a.y * b.x;
}
long long area(PT a, PT b, PT c) {
	return cross(a, b) + cross(b, c) + cross(c, a);
}
void ConvexHull(vector<PT>& pts, vector<PT>& up, vector<PT>& dn) {
	sort(pts.begin(), pts.end());
	pts.erase(unique(pts.begin(), pts.end()), pts.end());
	for (int i = 0; i < pts.size(); i++) {
		while (up.size() > 1 && area(up[up.size() - 2], up.back(), pts[i]) >= 0) up.pop_back();
		while (dn.size() > 1 && area(dn[dn.size() - 2], dn.back(), pts[i]) <= 0) dn.pop_back();
		up.push_back(pts[i]);
		dn.push_back(pts[i]);
	}
	pts = dn;
	for (int i = up.size() - 2; i >= 1; i--) pts.push_back(up[i]);
}

const int maxn = 100000 + 10;
int n;
PT p[maxn];
vector<pair<int, int> > v;

long long dist(PT a, PT b) {return (long long) (a.x - b.x) * (a.x - b.x) + (long long) (a.y - b.y) * (a.y - b.y);}
long long area(int i, int j, int k) {return abs(area(p[i], p[j], p[k]));}

int main() {
	srand(time(NULL));
	vector<PT> vp, up, dn;
	for (int i = 0; i < 100000; i++) vp.push_back(PT(rand(), rand()));
	ConvexHull(vp, up, dn);
	int u = 0, v = dn.size() - 1, w = up.size() - 1;
	long long mx = 0;
	while (u < w || v > 0) {
		mx = max(mx, dist(up[u], dn[v]));
		if (u == w) v--;
		else if (!v) u++;
		else {
			if ((long long) (up[u + 1].y - up[u].y) * (dn[v].x - dn[v - 1].x)
				> (long long) (dn[v].y - dn[v - 1].y) * (up[u + 1].x - up[u].x))
				u++;
			else
				v--;
		}
	}
	for (int i = 0; i < vp.size(); i++) {
		for (int j = i + 1; j < vp.size(); j++) {
			assert(mx >= dist(vp[i], vp[j]));
		}
	}
	cout << "Correct!\n";
	return 0;
}