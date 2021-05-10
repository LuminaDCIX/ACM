// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

#define CO const
#define IN inline
#define RE register
#define REP(i, a, n) for (int i = (a); i <= (n); ++i)
#define PER(i, a, n) for (int i = (n); i >= (a); --i)
#define FORG(u, o) for (int o = head[u], v = ver[o]; o; o = nxt[o], v = ver[o]) 
typedef long long LL;

IN int read() {
  int f = 1, x = 0, ch = getchar();
  for (; !isdigit(ch); ch = getchar()) f = (ch == '-') ? -1 : 1;
  for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
  return f * x;
}

namespace XDYIMCMI0LY {
  CO int N = 1e5 + 5;
  CO int M = 2e5 + 5;

  int n, q, a[N], ALL;

  int head[N], nxt[M], ver[M], w[M], led[M];

  IN void _add(int u, int v, int _w) {
    static int tot = 0;
    ++tot, nxt[tot] = head[u], ver[tot] = v, w[tot] = _w, head[u] = tot;
  }


  CO int LOG = 21;

  int pre[N][LOG], dep[N], len[N];

  int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    PER (i, 0, LOG - 1) if (dep[pre[x][i]] >= dep[y]) x = pre[x][i];
    if (x == y) return x;
    PER (i, 0, LOG - 1) if (pre[x][i] != pre[y][i]) x = pre[x][i], y = pre[y][i];
    return pre[x][0];
  }

  int dist(int a, int b) { return len[a] + len[b] - len[lca(a, b)] * 2; }

  int U, R, siz[N], dp[N], vis[N];

  void findR(int u, int fa) {
    siz[u] = 1, dp[u] = 0;
    FORG (u, o) {
      if (vis[v] || v == fa) continue;
      findR(v, u), siz[u] += siz[v], dp[u] = max(dp[u], siz[v]);
    }
    dp[u] = max(dp[u], U - siz[u]);
    if (R == 0 || dp[R] > dp[u]) R = u;
  }

  void reC(int u, int fa) {
    siz[u] = 1;
    FORG (u, o) if (!vis[v] && v != fa) reC(v, u), siz[u] += siz[v];
  }

  int fa[N];

  LL ans[N], fans[N], sum[N];

  int solve(int u, int _U) {
    U = _U, R = 0, findR(u, 0);
    u = R, vis[u] = 1, reC(u, 0);
    FORG (u, o) {
      if (vis[v]) continue;
      v = solve(v, siz[v]);
      fa[v] = u, led[o] = v;
    }
    return u;
  }

  struct BIT {
    int t[N];
    void add(int u, int x) { for (int i = u; i <= n; i += i & -i) t[i] += x; }
    int sum(int x) {
      int ret = 0;
      for (; x; x -= x & -x) ret += t[x];
      return ret;
    }
  } b;

  int dfn[N], dfs_cnt, ed[N], ofa[N];

  void dfs(int u, int fa) {
    dfn[u] = ++dfs_cnt, ofa[u] = fa, pre[u][0] = fa, dep[u] = dep[fa] + 1;
    FORG (u, o) if (v != fa) len[v] = len[u] + w[o], dfs(v, u);
    ed[u] = dfs_cnt;
  }

  int findG(int u) {
    int sum = 0, bar = 0;
    FORG (u, o) {
      if (v == ofa[u]) { bar = o; continue; }
      int t = b.sum(ed[v]) - b.sum(dfn[v] - 1);
      sum += t;
      if (t > ALL / 2) return findG(led[o]); 
    }
    int t = ALL - (sum + a[u]);
    if (t > ALL / 2) return findG(led[bar]);
    return u;
  }

  IN void mod(int x, int det) {
    int o = x, nw = fa[x];
    sum[o] += det;
    while (nw) {
      ans[nw] += (LL) det * dist(nw, o), fans[x] += (LL) det * dist(nw, o);
      sum[nw] += det;
      x = nw, nw = fa[nw];
    }
  }

  IN LL calc(int x) {
    LL ret = ans[x];
    int o = x, nw = fa[x];
    //    cerr<<"--------------------"<<endl;
    while (nw) {
      //      cerr<<nw<<" sum = "<<sum[nw]<<endl;
      ret += dist(nw, o) * (sum[nw] - sum[x]);
      ret += ans[nw] - fans[x];
      x = nw, nw = fa[nw];
    }
    return ret;
  }

  int main() {
    n = read(), q = read();
    REP (i, 1, n - 1) {
      int u = read(), v = read(), w = read();
      _add(u, v, w), _add(v, u, w);
    }
    dfs(1, 0), R = solve(1, n);
    REP (j, 1, LOG - 1) REP (i, 1, n) pre[i][j] = pre[pre[i][j - 1]][j - 1];

#ifdef TEST
    a[n] = 100;
    for (int i = 1; i < n; ++i) a[i] = rand() % 10, b.add(dfn[i], a[i]), ALL += a[i];
    b.add(dfn[10], a[10]), ALL += a[10];
    REP (i, 1, n) cerr << a[i] << endl;
    cerr<<findG(R)<<endl;
#endif
    while (q--) {
      int x = read(), det = read();
      mod(x, det), a[x] += det, b.add(dfn[x], det), ALL += det;
      int k = findG(R);
      //      cerr<<k<<endl;
      printf("%lld\n", calc(k));
    }
    return 0;
  }
} 

int main() { return XDYIMCMI0LY::main(); }
