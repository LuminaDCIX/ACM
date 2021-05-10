#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100000 + 5;

inline int read() {
  int x;
  scanf("%d", &x);
  return x;
}

int n;
int m;



int f;
int siz[N];

int hd;
int tl;
int que[N];
int ind[N];
int scc_cnt;

struct graph {
  int tot;
  int head[N];
  
  struct edge {
    int to;
    int nxt;
  };

  edge e[N];

  inline void add(int u, int v) {
    e[tot].to = v;
    e[tot].nxt = head[u];
    head[u] = tot++;
  }

  inline void topo(int dist[], int sz) {
    memset(ind, 0, sizeof(ind));
    for (int u = 1; u <= scc_cnt; ++u) {
      for (int o = head[u]; ~o; o = e[o].nxt) {
        ++ind[e[o].to];
      }
    }
    tl = 0;
    hd = 0;
    for (int u = 1; u <= scc_cnt; ++u) {
      if (ind[u] == 0) {
        que[tl++] = u;
      }
    }
    while (hd < tl) {
      int u = que[hd++];
      for (int o = head[u]; ~o; o = e[o].nxt) {
        int v = e[o].to;
        --ind[v];
        if (ind[v] == 0) {
          que[tl++] = v;
        }
      }
    }
    // for (int i = 0; i < tl; ++i) {
    //   cerr << que[i] << " ";
    // }
    // cerr << endl;
    memset(dist, 0xcfcf, sz);
    dist[f] = 0;
    for (int i = tl - 1; i >= 0; --i) {
      int u = que[i];
      if (u == f) {
        continue;
      }
      for (int o = head[u]; ~o; o = e[o].nxt) {
        int v = e[o].to;
        dist[u] = max(dist[u], siz[u] + dist[v]);
      }
    }
  }
};

graph g0;

int top;
int stk[N];
int dfn[N];
int low[N];
int bel[N];
int dfs_cnt;
bool instk[N];

void dfs(int u) {
  stk[top++] = u;
  dfn[u] = ++dfs_cnt;
  low[u] = dfs_cnt;
  instk[u] = 1;
  for (int o = g0.head[u]; ~o; o = g0.e[o].nxt) {
    int v = g0.e[o].to;
    if (!dfn[v]) {
      dfs(v);
      low[u] = min(low[u], low[v]);
    } else if (instk[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    int y;
    ++scc_cnt;
    do {
      y = stk[--top];
      instk[y] = 0;
      bel[y] = scc_cnt;
      ++siz[scc_cnt];
    } while (y != u);
  }
}

graph g1;
graph g2;

int s[N];
int t[N];

int main() {
  n = read();
  m = read();
  memset(g0.head, -1, sizeof(g0.head));
  for (int i = 0; i < m; ++i) {
    int u = read();
    int v = read();
    g0.add(u, v);
  }
  for (int i = 1; i <= n; ++i) {
    if (!dfn[i]) {
      dfs(i);
    }
  }
  f = bel[1];
  memset(g1.head, -1, sizeof(g1.head));
  memset(g2.head, -1, sizeof(g2.head));
  for (int u = 1; u <= n; ++u) {
    for (int o = g0.head[u]; ~o; o = g0.e[o].nxt) {
      int v = g0.e[o].to;
      if (bel[v] == bel[u]) {
        continue;
      }

      g1.add(bel[u], bel[v]);
      g2.add(bel[v], bel[u]);
    }
  }
  g1.topo(t, sizeof(t));
  g2.topo(s, sizeof(s));
  int ans = 0;
  // for (int i = 1; i <= scc_cnt; ++i) {
  //   cerr << t[i] << endl;
  // }
  for (int u = 1; u <= scc_cnt; ++u) {
    for (int o = g1.head[u]; ~o; o = g1.e[o].nxt) {
      int v = g1.e[o].to;
      if (t[u] >= 0 && s[v] >= 0) {
        ans = max(ans, t[u] + s[v]);
      }
    }
  }
  printf("%d\n", ans + siz[f]);
  return 0;
}
