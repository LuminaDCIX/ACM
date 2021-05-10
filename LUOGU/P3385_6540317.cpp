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

const int N = 200000 + 5;

int n, m;

vector <int> ver[N];
vector <int> cost[N];

inline void add(int u, int v, int w) {
  ver[u].push_back(v);
  cost[u].push_back(w);
}

struct find_cir {
  bool instk[N];
  long long dist[N];

  bool dfs(int u) {
    instk[u] = 1;
    for (int o = 0; o < (int) ver[u].size(); ++o) {
      int v = ver[u][o];
      if (dist[v] > dist[u] + cost[u][o]) {
        dist[v] = dist[u] + cost[u][o];
        if (instk[v] || dfs(v)) {
          return true;
        }
      }
    }
    instk[u] = 0;
    return false;
  }
  
  bool judge() {
    memset(instk, 0, sizeof(instk));
    memset(dist, 0, sizeof(dist));
    for (int i = 1; i <= n; ++i) {
      if (dfs(i)) {
        return true;
      }
    }
    return false;
  }
} s;

int main() {
  int T = read();
  while (T--) {
    n = read();
    m = read();
    for (int i = 1; i <= n; ++i) {
      ver[i].clear();
      cost[i].clear();
    }
    for (int i = 1; i <= m; ++i) {
      int u = read();
      int v = read();
      int w = read();
      if (w < 0) {
        add(u, v, w);
      } else {
        add(u, v, w);
        add(v, u, w);
      }
    }
    puts(s.judge() ? "YE5" : "N0");
  }
  return 0;
}
