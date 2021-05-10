#include <bits/stdc++.h>

using namespace std;

template <typename T>
class fenwick2d {
 public:
  vector<vector<T> > fenw;
  int n, m;

  fenwick2d(int _n, int _m) : n(_n), m(_m) {
    fenw.resize(n + 1);
    for (int i = 0; i <= n; i++) {
      fenw[i].resize(m + 1);
    }
  }

  inline int lowbit(int x) { return x & -x; }
  
  inline void modify(int i, int j, T v) {
    int x = i + 1;
    while (x <= n) {
      int y = j + 1;
      while (y <= m) {
        fenw[x][y] += v;
        y += lowbit(y);
      }
      x += lowbit(x);
    }
  }

  inline T get(int i, int j) {
    T v{};
    int x = i + 1;
    while (x > 0) {
      int y = j + 1;
      while (y > 0) {
        v += fenw[x][y];
        y -= lowbit(y);
      }
      x -= lowbit(x);
    }
    return v;
  }
};

int main() {
  int n, m;
  cin >> n >> m;
  static fenwick2d<int> f(n, m);
  int op;
  while (scanf("%d", &op) != EOF) {
    if (op == 1) {
      int x, y, v;
      cin >> x >> y >> v;
      --x;
      --y;
      f.modify(x, y, v);
    } else {
      int a, b, c, d;
      cin >> a >> b >> c >> d;
      --a;
      --b;
      --c;
      --d;
      cout << f.get(c, d) + f.get(a - 1, b - 1) - f.get(c, b - 1) - f.get(a - 1, d) << endl;
    }
  }
  return 0;
}
