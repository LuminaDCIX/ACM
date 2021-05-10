#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

inline int read() {
  int x = -1;
  scanf("%d", &x);
  return x;
}

const int N = 100 + 5;
const int M = 100 * 100 / 2 + 5;
const int MAX = 100 * 100 + 5;

int n;
int m;

int tot;
int head[N];

struct edge {
  int to;
  int nxt;
  int val[2];
};

edge e[M];

inline void add(int u, int v, int w0, int w1) {
  e[tot].to = v;
  e[tot].nxt = head[u];
  e[tot].val[0] = w0;
  e[tot].val[1] = w1;
  head[u] = tot++;
}

int ind[N];

int h;
int t;
int que[N];


int f[MAX];
int g[MAX];

bitset <MAX> x[N];

inline void solve(int f[], int l) {
  for (int i = 0; i < n; ++i) {
    x[i].reset();
  }
  x[n - 1].set(0);
  for (int i = n - 1; i >= 0; --i) {
    int u = i;
    for (int o = head[u]; ~o; o = e[o].nxt) {
      int v = e[o].to;
      x[u] |= x[v] << e[o].val[l];
    }
  }
  for (int i = 0; i < MAX; ++i) {
    f[i] = x[0].test(i);
  }
}

int main() {
  n = read();
  m = read();
  memset(head, -1, sizeof(head));
  for (int i = 0; i < m; ++i) {
    int u = read() - 1;
    int v = read() - 1;
    int w0 = read();
    int w1 = read();
    add(u, v, w0, w1);
  }
  solve(f, 0);
  solve(g, 1);
  for (int i = 0; i < MAX; ++i) {
    if (f[i] && g[i]) {
      printf("%d\n", i);
      return 0;
    }
  }
  puts("IMPOSSIBLE");
  return 0;
}
