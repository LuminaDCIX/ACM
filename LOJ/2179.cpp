#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;
const int MAX = 5000817;

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

int n, ans = -2e9;

int L, R;

struct Sgt {
  int lc[MAX], rc[MAX];
  int mx[MAX];

  int stk[MAX], top;
  
  void init() {
    mx[0] = -2e9;
    for (int i = 1; i < MAX; ++i) {
      stk[++top] = i;
    }
  }
  
  inline int nw() {
    int p = stk[top--];
    lc[p] = rc[p] = 0;
    mx[p] = -2e9;
    return p;
  }

  inline void del(int x) {
    stk[++top] = x;
  }

  int gc(int &x) {
    return x == 0 ? x = nw() : x;
  }
  
  void mod(int o, int ll, int rr, int p, int v) {
    if (ll == rr) {
      mx[o] = max(mx[o], v);
      return;
    }
    int mid = (ll + rr) >> 1;
    if (p <= mid) {
      mod(gc(lc[o]), ll, mid, p, v);
    } else {
      mod(gc(rc[o]), mid + 1, rr, p, v);
    }
    mx[o] = max(mx[lc[o]], mx[rc[o]]);
  }

  int qry(int o, int ll, int rr, int l, int r) {
    if (ll >= l && rr <= r) {
      return mx[o];
    }
    int ret = -2e9;
    int mid = (ll + rr) >> 1;
    if (l <= mid) {
      ret = max(ret, qry(lc[o], ll, mid, l, r));
    }
    if (r > mid) {
      ret = max(ret, qry(rc[o], mid + 1, rr, l, r));
    }
    return ret;
  }

  void clr(int o) {
    if (!o) {
      return;
    }
    clr(lc[o]);
    clr(rc[o]);
    del(o);
  }

  void update(int o, int ll, int rr, int t) {
    if (!o) {
      return;
    }
    if (ll == rr) {
      int l = max(1, L - ll);
      int r = min(n, R - ll);
      if (r >= 1 && r >= l) {
        ans = max(ans, mx[o] + qry(t, 1, n, l, r));
      }
      return;
    }
    int mid = (ll + rr) >> 1;
    update(lc[o], ll, mid, t);
    update(rc[o], mid + 1, rr, t);
  }
  
  void merge(int o, int ll, int rr, int t) {
    if (!o) {
      return;
    }
    if (ll == rr) {
      mod(t, 1, n, ll, mx[o]);
      return;
    }
    int mid = (ll + rr) >> 1;
    merge(lc[o], ll, mid, t);
    merge(rc[o], mid + 1, rr, t);
  }
} sgt;


int m, a[N];

int siz[N], dp[N];


typedef vector <int> vi;

vi ver[N], val[N];

void add(int u, int v, int c) {
  ver[u].push_back(v);
  val[u].push_back(c);
}

int fa[N], vis[N];

map <int, int> rt;

int lst[N], len[N], dep[N];

int det;

void dfs1(int u, int t) {
  siz[u] = 1;
  int l = max(1, L - dep[u]);
  int r = min(n, R - dep[u]);
  if (r >= 1 && l <= r) {
    int k = sgt.qry(t, 1, n, l, r);
    ans = max(ans, k + len[u] - det);
  }
  if (dep[u] >= L && dep[u] <= r) {
    ans = max(ans, len[u]);
  }
  
  // cerr << u << " " << fa[u] << " " << dep[u] << " " << len[u] << " " << ans << endl;
  for (int o = 0; o < (int) ver[u].size(); ++o) {
    int v = ver[u][o];
    if (v != fa[u] && !vis[v]) {
      fa[v] = u;
      dep[v] = dep[u] + 1;
      lst[v] = val[u][o];
      len[v] = len[u] + (lst[v] == lst[u] ? 0 : a[lst[v]]);
      dfs1(v, t);
      siz[u] += siz[v];
    }
  }
}

void dfs2(int u, int t) {
  sgt.mod(t, 1, n, dep[u], len[u]);
  for (int o = 0; o < (int) ver[u].size(); ++o) {
    int v = ver[u][o];
    if (v == fa[u] || vis[v]) {
      continue;
    }
    dfs2(v, t);
  }
}

int root, all;

void dfs3(int u) {
  dp[u] = 0;
  for (int o = 0; o < (int) ver[u].size(); ++o) {
    int v = ver[u][o];
    if (v == fa[u] || vis[v]) {
      continue;
    }
    dfs3(v);
    dp[u] = max(dp[u], siz[v]);
  }
  dp[u] = max(dp[u], all - siz[u]);
  if (root == 0 || dp[u] < dp[root]) {
    root = u;
  }
}

void solve(int u) {

  vis[u] = 1;
  rt.clear();
  for (int o = 0; o < (int) ver[u].size(); ++o) {
    int v = ver[u][o];
    if (vis[v]) {
      continue;
    }
    if (rt.find(val[u][o]) == rt.end()) {
      rt[val[u][o]] = sgt.nw();
    }
    dep[v] = 1;
    lst[v] = val[u][o];
    len[v] = a[val[u][o]];
    det = a[val[u][o]];
    fa[v] = u;
    dfs1(v, rt[val[u][o]]);
    dfs2(v, rt[val[u][o]]);
  }
  if (rt.size() == 0) {
    return;
  }
  map <int, int>::iterator it = rt.begin();
  int t = it->second;
  for (++it; it != rt.end(); ++it) {
    sgt.update(it->second, 1, n, t);
    sgt.merge(it->second, 1, n, t);
    sgt.clr(it->second);
  }
  sgt.clr(t);

  for (int o = 0; o < (int) ver[u].size(); ++o) {
    int v = ver[u][o];
    if (vis[v]) {
      continue;
    }
    root = 0;
    all = siz[v];
    dfs3(v);
    solve(root);
  }
}

int main() {
  // cerr << sizeof(sgt.lc) * 4 / 1000 / 1000 << endl;
  sgt.init();
  n = read();
  m = read();
  L = read();
  R = read();
  for (int i = 1; i <= m; ++i) {
    a[i] = read();
  }
  for (int i = 1; i < n; ++i) {
    int u = read();
    int v = read();
    int c = read();
    add(u, v, c);
    add(v, u, c);
  }
  solve(1);
  printf("%d\n", ans);
  return 0;
}