#include <bits/stdc++.h>

using namespace std;

class dsu {
 public:
  vector<int> p;
  int n;

  dsu(int _n) : n(_n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x]))); }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      return true;
    }
    return false;
  }
};


const int N = 2000 + 5;

class point {
 public:
  int x, y;
  point(int _x, int _y) : x(_x), y(_y) {};
};

int a[N];
vector<point> p;

int main() {
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x, y, id;
    cin >> x >> y >> id;
    --id;
    a[i] = id;
    p.emplace_back(x, y);
  }
  int piv = -1;
  dsu d(n);
  vector<int> order;
  for (int i = 0; i < n; ++i) {
    if (a[i] == i) {
      continue;
    }
    if (piv == -1 || p[i].x < p[piv].x || (p[i].x == p[piv].x && p[i].y < p[piv].y)) {
      piv = i;
    }
    order.push_back(i);
    int u = i;
    do {
      d.unite(u, a[u]);
      u = a[u];
    } while (u != i);
  }
  if (piv == -1) {
    cout << 0 << endl;
    return 0;
  }
  sort(order.begin(), order.end(), [&](int i, int j) -> bool {
    if (i == piv) {
      return true;
    }
    if (j == piv) {
      return false;
    }
    long long xi = p[i].x - p[piv].x;
    long long yi = p[i].y - p[piv].y;
    long long xj = p[j].x - p[piv].x;
    long long yj = p[j].y - p[piv].y;
    return xi * yj - xj * yi > 0;
  });


  assert(order[0] == piv);
  vector<array<int, 2> > ops;
  
  for (int i = 1; i + 1 < (int) order.size() ; ++i) {
    if (d.get(order[i]) != d.get(order[i + 1])) {
      ops.push_back({order[i], order[i + 1]});
      d.unite(order[i], order[i + 1]);
      swap(a[order[i]], a[order[i + 1]]);
    }
  }
  while (piv != a[piv]) {
    int u = a[piv];
    swap(a[piv], a[u]);
    ops.push_back({piv, u});
  }

  cout << ops.size() << endl;
  for (auto &[i, j] : ops) {
    cout << i + 1 << " " << j + 1 << endl;
  }
  
  return 0;
}
