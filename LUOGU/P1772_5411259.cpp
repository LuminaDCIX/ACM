// luogu-judger-enable-o2
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

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

const int N = 100 + 5;
const int M = 20 + 5;
const int MAXE = M * M + 5;
const int inf = 0x3f3f3f3f;

bool exi[M][N][N];

int n;
int m;
int k;
int e;

struct Dijkstra {
  int dist[N][N][M];
  int nxt[MAXE];
  int w[MAXE];
  int ver[MAXE];
  int head[N];
  int tot;

  void addEdge(int u, int v, int _w) {
    nxt[tot] = head[u];
    ver[tot] = v;
    w[tot] = _w;
    head[u] = tot++;
  }

  struct node {
    int l;
    int r;
    int u;
    int cost;

    bool operator < (const node rhs) const {
      return cost > rhs.cost;
    }

    node (int _l, int _r, int _u, int _w) {
      l = _l;
      r = _r;
      u = _u;
      cost = _w;
    }
  };

  void solve() {
    memset(dist, inf, sizeof(dist));
    for (int i = 1; i <= n; ++i) {
      for (int j = i; j <= n; ++j) {
        dist[i][j][1] = 0;
      }
    }
    priority_queue <node> que;
    for (int i = 1; i <= n; ++i) {
      for (int j = i; j <= n; ++j) {
        que.push(node(i, j, 1, 0));
      }
    }
    while (!que.empty()) {
      int l = que.top().l;
      int r = que.top().r;
      int u = que.top().u;
      int cost = que.top().cost;
      que.pop();
      if (u == m) {
        continue;
      }
      for (int o = head[u]; ~o; o = nxt[o]) {
        int v = ver[o];
        if (!exi[v][l][r]) {
          continue;
        }
        if (dist[l][r][v] > dist[l][r][u] + w[o]) {
          dist[l][r][v] = dist[l][r][u] + w[o];
          que.push(node(l, r, v, dist[l][r][v]));
        }
      }
    }
  }

  void init() {
    memset(head, -1, sizeof(head));
  }
} s;

int g[N][N];
int dp[N];

void solve() {
  memset(dp, inf, sizeof(dp));
  dp[0] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < i; ++j) {
      dp[i] = min(dp[j] + (long long) g[j + 1][i] * (i - j) + k, (long long) dp[i]);
    }
  }
}

int main() {
  s.init();
  n = read();
  m = read();
  k = read();
  e = read();
  for (int i = 0; i < e; ++i) {
    int u = read();
    int v = read();
    int w = read();
    s.addEdge(u, v, w);
    s.addEdge(v, u, w);
  }
  int d = read();
  memset(exi, 1, sizeof(exi));
  for (int i = 0; i < d; ++i) {
    int u = read();
    int l = read();
    int r = read();
    for (int j = 1; j <= r; ++j) {
      for (int k = max(l, j); k <= n; ++k) {
        exi[u][j][k] = 0;
      }
    }
  }
  s.solve();
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) {
      g[i][j] = s.dist[i][j][m];
    }
  }
  solve();
  printf("%d\n", dp[n] - k);
  return 0;
}