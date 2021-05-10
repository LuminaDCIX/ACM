// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

const int N = 10000 + 5;
const int MAX = 10000000 + 5;

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

int n, m;

bool ok[MAX];

vector <int> ver[N];
vector <int> cost[N];

void add(int u, int v, int c) {
  ver[u].push_back(v);
  cost[u].push_back(c);
}

set <int> all;

struct divide {
  

  int len;
  bool flg;
  int dep[N];

  void dfs(int u) {
    if (dep[u] > len) {
      return;
    }
    if (dep[u] == len || all.find(len - dep[u]) != all.end()) {
      flg = 1;
    }
    for (int o = 0; o < (int) ver[u].size(); ++o) {
      int v = ver[u][o];
      if (vis[v] || v == fa[u]) {
        continue;
      }
      dep[v] = dep[u] + cost[u][o];
      dfs(v);
    }
  }

   void dfs2(int u) {
    if (dep[u] > len) {
      return;
    }
    all.insert(dep[u]);
    for (int o = 0; o < (int) ver[u].size(); ++o) {
      int v = ver[u][o];
      if (vis[v] || v == fa[u]) {
        continue;
      }
      dfs2(v);
    }
  }

  int siz[N], dp[N], fa[N];
  
  bool vis[N];

  void init() {
    memset(vis, 0, sizeof(vis));
  }

  inline bool ok(int u, int v) {
    return !vis[v] && (v != fa[u]);
  }

  void find(int u, int cnt, int &root) {
    siz[u] = 1;
    for (int o = 0; o < (int) ver[u].size(); ++o) {
      int v = ver[u][o];
      if (ok(u, v)) {
        fa[v] = u;
        find(v, cnt, root);
        dp[u] = max(dp[u], siz[v]);
        siz[u] += siz[v];
      }
    }
    dp[u] = max(dp[u], cnt - siz[u]);
    if (root == 0 || dp[u] < dp[root]) {
      root = u;
    }
  }

  void init(int u) {
    siz[u] = 1;
    for (int o = 0; o < (int) ver[u].size(); ++o) {
      int v = ver[u][o];
      if (ok(u, v)) {
        fa[v] = u;
        init(v);
        siz[u] += siz[v];
      }
    }
  }
  
  
  void calc(int u) {
    vis[u] = 1;
    all.clear();
    for (int o = 0; o < (int) ver[u].size(); ++o) {
      int v = ver[u][o];
      if (vis[v] || v == fa[u]) {
        continue;
      }
      dep[v] = cost[u][o];
      dfs(v);
      dfs2(v);
    }
  }
  
  void solve(int u, int cnt) {
    int root = 0;
    fa[u] = 0;
    find(u, cnt, root);
    fa[root] = 0;
    for (int o = 0; o < (int) ver[root].size(); ++o) {
      int v = ver[root][o];
      if (ok(root, v)) {
        fa[v] = root;
        init(v);
      }
    }
    calc(root);
    for (int o = 0; o < (int) ver[root].size(); ++o) {
      int v = ver[root][o];
      if (ok(root, v)) {
        solve(v, siz[v]);
      }
    }
  }
} d;



int main() {
  n = read();
  m = read();
  for (int i = 0; i < n - 1; ++i) {
    int u = read();
    int v = read();
    int w = read();
    add(u, v, w);
    add(v, u, w);
  }
  for (int i = 0; i < m; ++i) {
    int len = read();
    d.flg = 0;
    d.len = len;
    d.init();
    d.solve(1, n);
    puts(d.flg ? "AYE" : "NAY");
  }
  return 0;
}
