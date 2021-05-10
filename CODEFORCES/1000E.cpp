#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

inline void add(int &a, int b) {
  a += b;
  if (a >= mod) {
    a -= mod;
  }
}
inline void sub(int &a, int b) {
  a -= b;
  if (a < 0) {
    a += mod;
  }
}
inline int mul(int a, int b) {
  return (long long) a * b % mod;
}
inline int modexp(int a, int x) {
  int res = 1;
  while (x) {
    if (x & 1) {
      res = mul(res, a);
    }
    a = mul(a, a);
    x >>= 1;
  }
  return res;
}

// struct edge {
//   int nxt;
//   int ver;
// };
// vector<edge> e;
// void add_edge(int u, int v) {
//   e.push_back((edge){head[u], v});
//   head[u] = (int) e.size() - 1;
// }

const int N = 3e5 + 5;
const int M = 6e5 + 5;

int head[N];
int ver[M];
int nxt[M];
int val[M];

void add_edge(int u, int v) {
  static int tot = 1;
  ++tot;
  nxt[tot] = head[u];
  ver[tot] = v;
  head[u] = tot;
}

int pre[N];
int low[N];
int dfn[N];
int cnt;

void tarjan(int u, int fa) {
  pre[u] = fa;
  low[u] = dfn[u] = ++cnt;
  for (int o = head[u]; o; o = nxt[o]) {
    int v = ver[o];
    if( ! dfn[v]) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > dfn[u]) {
        val[o] = 1;
        val[o ^ 1] = 1;
      }
    }
    else if (fa != v) {
      low[u] = min(low[u], dfn[v]);
    }
  }
}


int dp[N][2];
int ans;
bool vis[N];

int n;
int m;

void dfs(int u, int fa) {
  vis[u] = 1;
  for (int o = head[u]; o; o = nxt[o]) {
    int v = ver[o];
    if (v == fa || vis[v]) {
      continue;
    }
    dfs(v, u);
    int k = dp[v][0] + val[o];
    if (k >= dp[u][0]) {
      dp[u][1] = dp[u][0];
      dp[u][0] = k;
    } else if (k > dp[u][1]) {
      dp[u][1] = k;
    }
  }
  ans = max(ans, dp[u][0] + dp[u][1]);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    add_edge(u, v);
    add_edge(v, u);
  }
  tarjan(1, 0);
  dfs(1, 0);
  cout << ans << endl;
  return 0;
}
