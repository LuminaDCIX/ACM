#include <bits/stdc++.h>

using namespace std;

template <typename T>
class fenwick {
 public:
  vector<T> fenw;
  int n;

  fenwick(int _n) : n(_n) { fenw.resize(n + 1); }

  inline int lowbit(int x) { return x & -x; }

  void modify(int x, T v) {
    ++x;
    while (x <= n) {
      fenw[x] += v;
      x += lowbit(x);
    }
  }

  T get(int x) {
    T v{};
    ++x;
    while (x > 0) {
      v += fenw[x];
      x -= lowbit(x);
    }
    return v;
  }
};

int main() {
  ios::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  fenwick<int> f(n);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    f.modify(i, x);
  }
  for (int i = 0; i < m; ++i) {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 1) {
      --x;
      f.modify(x, y);
    } else {
      --x;
      --y;
      cout << f.get(y) - f.get(x - 1) << endl;
    }
  }
  return 0;
}
