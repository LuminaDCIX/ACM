#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 5;

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

int g[N][N];

int a, b, c;

vector <pair <int, int> > p[N];

inline void input() {
  a = read();
  b = read();
  c = read();
  int x = a;
  int y = b;
  int z = c;
  bool ab = 0;
  bool ac = 0;
  if (a > b) {
    swap(a, b);
    ab = 1;
  }
  if (a > c) {
    swap(a, c);
    ac = 1;
  }
  
  for (int i = 1; i <= x; ++i) {
    for (int j = 1; j <= y; ++j) {
      for (int k = 1; k <= z; ++k) {
        int op = read();
        if (op == 1) {
          int tx = i;
          int ty = j;
          int tz = k;
          if (ab) {
            swap(tx, ty);
          }
          if (ac) {
            swap(tx, tz);
          }
          p[tx].push_back(make_pair(ty, tz));
        }
      }
    }
  }
}

int ans;

struct max_match {
  int vis[N], tot;
  int fa[N];

  bool dfs(int u) {
    for (int v = 1; v <= c; ++v) {
      if (g[u][v] && vis[v] != tot) {
        vis[v] = tot;
        if (!fa[v] || dfs(fa[v])) {
          fa[v] = u;
          return true;
        }
      }
    }
    return false;
  }
  
  int solve() {
    for (int i = 1; i <= c; ++i) {
      fa[i] = 0;
    }
    int ans = 0;
    for (int i = 1; i <= b; ++i) {
      ++tot;
      if (dfs(i)) {
        ++ans;
      }
    }
    return ans;
  }
} s;

void dfs(int nw, int cnt) {
  if (nw == a + 1) {
    ans = min(ans, s.solve() + cnt);
    return;
  }
  for (int i = 0; i < (int) p[nw].size(); ++i) {
    ++g[p[nw][i].first][p[nw][i].second];
  }
  dfs(nw + 1, cnt);
  for (int i = 0; i < (int) p[nw].size(); ++i) {
    --g[p[nw][i].first][p[nw][i].second];
  }
  dfs(nw + 1, cnt + 1);
}

int main() {
  int T = read();
  while (T--) {
    for (int i = 0; i < N; ++i) {
      p[i].clear();
    }
    ans = 1e8;
    input();
    dfs(1, 0);
    printf("%d\n", ans);
  }
  
  return 0;
}