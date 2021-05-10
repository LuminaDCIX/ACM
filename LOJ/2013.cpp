#include <bits/stdc++.h>

#define fff __inline__ __attribute__((always_inline))

using namespace std;

const int N = 20000 + 5;
const int M = 60;
const int MAX = N * 4 + 5;

inline long long read() {
  int f = 1;
  long long x = 0;
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

int n;

struct lb {
  long long s[M + 5];

  lb() {
    memset(s, 0, sizeof(s));
  }
  
  fff void ins(long long x) {
    for (int i = M; i >= 0; --i) {
      if (x & (1ll << i)) {
        if (s[i]) {
          x ^= s[i];
        } else {
          s[i] = x;
          return;
        }
      }
    }
  }

  fff long long mx() {
    long long ret = 0;
    for (int i = M; i >= 0; --i) {
      if ((ret ^ s[i]) > ret) {
        ret ^= s[i];
      }
    }
    return ret;
  }
};

fff void merge(lb &a, lb &b) {
  for (int i = M; i >= 0; --i) {
    if (b.s[i]) {
      a.ins(b.s[i]);
    }
  }
}

lb t[MAX];

int dfn[N], pre[N], dfs_cnt;
int siz[N], son[N], top[N], dep[N], fa[N];

long long a[N];

vector <int> ver[N];

void dfs1(int u) {
  siz[u] = 1;
  for (int o = 0; o < (int) ver[u].size(); ++o) {
    int v = ver[u][o];
    if (v == fa[u]) {
      continue;
    }
    fa[v] = u;
    dep[v] = dep[u] + 1;
    dfs1(v);
    siz[u] += siz[v];
    if (siz[v] >= siz[son[u]]) {
      son[u] = v;
    }
  }
}

void dfs2(int u, int anc) {
  top[u] = anc;
  dfn[u] = ++dfs_cnt;
  pre[dfs_cnt] = u;
  
  if (son[u]) {
    dfs2(son[u], anc);
  } else {
    return;
  }
  for (int o = 0; o < (int) ver[u].size(); ++o) {
    int v = ver[u][o];
    if (v == fa[u] || v == son[u]) {
      continue;
    }
    dfs2(v, v);
  }
}

void build(int o, int ll, int rr) {
  if (ll == rr) {
    t[o].ins(a[pre[ll]]);
    return;
  }
  int mid = (ll + rr) >> 1;
  build(o << 1, ll, mid);
  build(o << 1 | 1, mid + 1, rr);
  t[o] = t[o << 1];
  merge(t[o], t[o << 1 | 1]);
}

lb rr;

void qry(int o, int x, int y, int l, int r) {
  if (x >= l && y <= r) {
    merge(rr, t[o]);
    return;
  }
  int m = (x + y) >> 1;
  if (l <= m) {
    qry(o << 1, x, m, l, r);
  }
  if (r > m) {
    qry(o << 1 | 1, m + 1, y, l, r);
  }
}

fff void solve(int x, int y) {
  rr = lb();
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) {
      swap(x, y);
    }
    qry(1, 1, n, dfn[top[x]], dfn[x]);
    x = fa[top[x]];
  }
  if (dfn[x] > dfn[y]) {
    swap(x, y);
  }
 qry(1, 1, n, dfn[x], dfn[y]);
  printf("%lld\n", rr.mx());
}

int main() {
  n = read();
  int m = read();
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
  }
  for (int i = 2; i <= n; ++i) {
    int u = read();
    int v = read();
    ver[u].push_back(v);
    ver[v].push_back(u);
  }
  dep[1] = 1;
  
  dfs1(1);
  dfs2(1, 1);

  build(1, 1, n);

  while (m--) {
    solve(read(), read());
  }
  return 0;
}