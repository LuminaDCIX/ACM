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
  int lc[N], rc[N], fa[N];
  int fix[N], val[N], siz[N];
  int root;

  inline int rnd() {
    static int s = 20010330;
    return s += s << 2 | 1;
  }

  inline int nw(int x) {
    static int tot = 0;
    ++tot;
    lc[tot] = 0;
    rc[tot] = 0;
    fa[tot] = 0;
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
      rc[x] = merge(rc[x], y);
      fa[rc[x]] = x;
      update(x);
      return x;
    } else {
      lc[y] = merge(x, lc[y]);
      fa[lc[y]] = y;
      update(y);
      return y;
    }
  }

  pair <int, int> split(int x, int k) {
    if (!x) {
      return make_pair(0, 0);
    }
    pair <int, int> d;
    if (siz[lc[x]] >= k) {
      d = split(lc[x], k);
      lc[x] = d.second;
      fa[lc[x]] = x;
      d.second = x;
    } else {
      d = split(rc[x], k - siz[lc[x]] - 1);
      rc[x] = d.first;
      fa[rc[x]] = x;
      d.first = x;
    }
    update(x);
    return d;
  }

  int getpos(int x) {
    int ret = siz[lc[x]] + 1;
    while (x != root) {
      int p = fa[x];
      if (rc[p] == x) {
        ret += siz[lc[p]] + 1;
      }
      x = p;
    }
    return ret;
  }
  
  int getrk(int x, int k) {
    if (!x) {
      return 0;
    }
    return k <= val[x] ? getrk(lc[x], k) : getrk(rc[x], k) + 1 + siz[lc[x]];
  }

  inline int findkth(int k) {
    pair <int, int> x = split(root, k - 1);
    pair <int, int> y = split(x.second, 1);
    int ans = val[y.first];
    root = merge(x.first, merge(y.first, y.second));
    return ans;
  }

  inline int pre(int x) {
    int k = getrk(root, x);
    return findkth(k);
  }

  inline int nxt(int x) {
    int k = getrk(root, x + 1);
    return findkth(k + 1);
  }

  inline void ins(int x) {
    int k = getrk(root, x);
    pair <int, int> d = split(root, k);
    root = merge(d.first, merge(nw(x), d.second));
  }

  inline void del(int x) {
    int k = getrk(root, x);
    pair <int, int> d1 = split(root, k);
    pair <int, int> d2 = split(d1.second, 1);
    root = merge(d1.first, d2.second);
  }
} t;

 
int main() {
  m = read();
  while (m--) {
    int op = read();
    int x;
    switch (op) {
    case 1:
      x = read();
      t.ins(x);
      break;
    case 2 :
      x = read();
      t.del(x);
      break;
    case 3:
      x = read();
      printf("%d\n", t.getrk(t.root, x) + 1);
      break;
    case 4:
      x = read();
      printf("%d\n", t.findkth(x));
      break;
    case 5:
      x = read();
      printf("%d\n", t.pre(x));
      break;
    case 6:
      x = read();
      printf("%d\n", t.nxt(x));
      break;
    }
  }
  return 0;
}
