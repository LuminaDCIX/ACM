// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

inline int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) {
    f = (ch == '-') ? -1 : 1;
  }
  for (; ch >= '0' && ch <= '9'; ch = getchar()) {
    x = x * 10 + ch - '0';
  }
  return f * x;
}
             

int n, m;

typedef vector <int> vi;

const int N = 1000 + 5;

vi ver[N];

struct max_match {
  int lnk[N];
  int vis[N];
  int tot;

  bool dfs(int u) {
    for (int o = 0; o < (int) ver[u].size(); ++o) {
      int v = ver[u][o];
      if (vis[v] != tot) {
        vis[v] = tot;
        if (!lnk[v] || dfs(lnk[v])) {
          lnk[v] = u;
          return true;
        }
      }
    }
    return false;
  }

  inline int solve() {
    int ret = 0;
    memset(lnk, 0, sizeof(lnk));
    memset(vis, 0, sizeof(vis));
    tot = 0;
    for (int i = 1; i <= n; ++i) {
      ++tot;
      if (dfs(i)) {
        ++ret;
      }
    }
    return ret;
  }
};

max_match mm;

int main() {
  n = read();
  m = read();
  int cnt = read();
  for (int i = 1; i <= cnt; ++i) {
    int u = read();
    int v = read();
    if (v > m) {
      continue;
    }
    ver[u].push_back(v);
  }
  printf("%d\n", mm.solve());
  return 0;
}
  
