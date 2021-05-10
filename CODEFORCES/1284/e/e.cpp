#include <bits/stdc++.h>

using namespace std;

#define y1 temp_y1
#define all(x) x.begin(), x.end()

const double pi = acos(-1);
const double eps = 1e-8;

int sgn(double x) { return x < -eps ? -1 : x > eps; }

inline bool eq(double x, double y) { return sgn(x - y) == 0; }
inline bool lt(double x, double y) { return sgn(x - y) < 0; }
inline bool gt(double x, double y) { return sgn(x - y) > 0; }
inline bool leq(double x, double y) { return sgn(x - y) <= 0; }
inline bool geq(double x, double y) { return sgn(x - y) >= 0; }

struct point {
  double x, y;
  point(double x = 0, double y = 0) : x(x), y(y) {}
  point(const point& a, const point& b) : x(b.x - a.x), y(b.y - a.y) {}
  point operator + (const point& b) const { return point(x + b.x, y + b.y); }
  point operator - (const point& b) const { return point(x - b.x, y - b.y); }
  point operator * (double k) const { return point(x * k, y * k); }
  point operator / (double k) const { return point(x / k, y / k); }
  double len() const { return hypot(x, y); }
  double len2() const { return x * x + y * y; }
};

ostream& operator << (ostream& os, const point& p) { return os << "(" << p.x << ", " << p.y << ")"; }
istream& operator >> (istream& is, point& p) { return is >> p.x >> p.y; }

double dist(const point& a, const point& b) { return (b - a).len(); }
double dot(const point& a, const point& b) { return a.x * b.x + a.y * b.y; }
double det(const point& a, const point& b) { return a.x * b.y - a.y * b.x; }
double cross(const point& s, const point& t, const point& o) { return det(point(o, s), point(o, t)); }

int quad(const point& a) {
  if(gt(a.x, 0)&& geq(a.y, 0)) {
    return 0;
  }
  if(leq(a.x, 0)&& gt(a.y, 0)) {
    return 1;
  }
  if(lt(a.x, 0)&& leq(a.y, 0)) {
    return 2;
  }
  if(geq(a.x, 0)&& lt(a.y, 0)) {
    return 3;
  }
  return -1;
}

vector<int> polar_sort(const vector<point>& a, const point &o) {
  vector<int> res(a.size());
  iota(res.begin(), res.end(), 0);
  sort(res.begin(), res.end(), [&](int i, int j) -> bool {
    const point x = a[i] - o;
    const point y = a[j] - o;
    if (quad(x) == quad(y)) {
      double t = det(x, y);
      return eq(t, 0) ? lt(x.len2(), y.len2()) : gt(t, 0);
    } else {
      return quad(x) < quad(y);
    }
  });
  return res;
}

long long binom(int n, int m) {
  if (n < m) {
    return 0;
  }
  long long ret = 1;
  for (int i = n; i >= n - m + 1; --i) {
    ret *= i;
  }
  for (int i = 1; i <= m; ++i) {
    ret /= i;
  }
  return ret;
}


int main() {
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  vector<point> p;
  for (int i = 0, x, y; i < n; ++i) {
    cin >> x >> y;
    p.emplace_back(x, y);
  }
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    vector<int> order = polar_sort(p, p[i]);
    for (int k = 1; k < n; ++k) {
      order.push_back(order[k]);
    }
    int b = 1;
    for (int j = 1; j < n; ++j) {
      b = max(b, j);
      while (!eq((p[order[b + 1]] - p[order[j]]).len2(), 0) && lt(cross(p[i], p[order[b + 1]], p[order[j]]), 0)) {
	++b;
      }

      int m = b - j;
      //cerr << i << " " << order[j] << " " << order[b] << " " << m << endl;
      ans += binom(m, 3);
    }
  }
  ans = 5 * binom(n, 5) - ans;
  cout << ans << endl;
  return 0;
}
