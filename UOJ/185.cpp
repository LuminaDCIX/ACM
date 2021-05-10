#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 17 + 1;

int n;
int m;

int g[N][N];

long long f[N][N];

struct edge {
  int nxt;
  int to;
};

edge e[N * N];

int tot;
int head[N];

inline void add(int u, int v) {
  e[tot].to = v;
  e[tot].nxt = head[u];
  head[u] = tot++;
}

int bit[N];
int cnt;

void dfs(int u, int pre) {
  for (int i = 0; i < cnt; ++i) {
    f[u][bit[i]] = 1;
  }
  long long sum = 0;
  for (int o = head[u]; ~o; o = e[o].nxt) {
    int v = e[o].to;
    if (v == pre) {
      continue;
    }
    dfs(v, u);
    for (int i = 0; i < cnt; ++i) {
      sum = 0;
      for (int j = 0; j < cnt; ++j) {
        if (g[bit[i]][bit[j]]) {
          sum += f[v][bit[j]];
        }
      }
      f[u][bit[i]] *= sum;
    }
  }
}

long long ans;

void build(int x) {
  if (x == n) {
    memset(f, 0, sizeof(f));
    dfs(0, -1);
    long long sum = 0;
    for (int i = 0; i < cnt; ++i) {
      sum += f[0][bit[i]];
    }
    if ((n - cnt) & 1) {
      ans -= sum;
    } else {
      ans += sum;
    }
    return;
  }
  build(x + 1);
  bit[cnt++] = x;
  build(x + 1);
  --cnt;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0, u, v; i < m; ++i) {
    scanf("%d %d", &u, &v);
    --u;
    --v;
    g[u][v] = 1;
    g[v][u] = 1;
  }
  memset(head, -1, sizeof(head));
  for (int i = 0, u, v; i < n - 1; ++i) {
    scanf("%d %d", &u, &v);
    --u;
    --v;
    add(u, v);
    add(v, u);
  }
  build(0);
  printf("%lld\n", ans);
  return 0;
}