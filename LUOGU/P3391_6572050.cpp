// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

inline int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

const int N = 100000 + 5;

int m;

struct treap {
  int lc[N], rc[N];
  int fix[N], val[N], siz[N];
  int root;

  bool tag[N];

  inline int rnd() {
    static int s = 20010330;
    return s += s << 2 | 1;
  }

  void settag(int x) {
    swap(lc[x], rc[x]);
    tag[x] ^= 1;
  }
  
  void push(int x) {
    if (tag[x]) {
      settag(lc[x]);
      settag(rc[x]);
      tag[x] = 0;
    }
  }

  inline int nw(int x) {
    static int tot = 0;
    ++tot;
    lc[tot] = 0;
    rc[tot] = 0;
    siz[tot] = 1;
    val[tot] = x;
    fix[tot] = rnd();
    return tot;
  }

  inline void update(int x) {
    siz[x] = siz[lc[x]] + siz[rc[x]] + 1;
  }

  int merge(int x, int y) {
    if (!x) {
      return y;
    }
    if (!y) {
      return x;
    }
    if (fix[x] < fix[y]) {
      push(x);
      rc[x] = merge(rc[x], y);
      update(x);
      return x;
    } else {
      push(y);
      lc[y] = merge(x, lc[y]);
      update(y);
      return y;
    }
  }

  pair <int, int> split(int x, int k) {
    if (!x) {
      return make_pair(0, 0);
    }
    if (tag[x]) {
      push(x);
    }
    pair <int, int> d;
    if (siz[lc[x]] >= k) {
      d = split(lc[x], k);
      lc[x] = d.second;
      d.second = x;
    } else {
      d = split(rc[x], k - siz[lc[x]] - 1);
      rc[x] = d.first;
      d.first = x;
    }
    update(x);
    return d;
  }
  
  inline void ins(int x) {
    root = merge(root, nw(x));
  }

  void mod(int l, int r) {
    pair <int, int> x = split(root, l - 1);
    pair <int, int> y = split(x.second, r - l + 1);
    settag(y.first);
    root = merge(x.first, merge(y.first, y.second));
  }


  void dfs(int x) {
    if (!x) {
      return;
    }
    if (tag[x]) {
      push(x);
    }
    dfs(lc[x]);
    printf("%d ", val[x]);
    dfs(rc[x]);
  }
} t;

 
int main() {
  int n = read();
  for (int i = 1; i <= n; ++i) {
    t.ins(i);
  }
  m = read();
  while (m--) {
    int l = read();
    int r = read();
    t.mod(l, r);
  }
  t.dfs(t.root);
  puts("");
  return 0;
}
