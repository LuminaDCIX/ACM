#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

inline int read() {
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 500 + 5;
const int MAX = 500 * 500 + 5;
const int M = 500 * 500 * 4;

int n;
int m;

int a[N][N];

inline int point(int x, int y) {
  return x * m + y;
}

struct atom {
  int u;
  int v;
  int w;

  bool operator < (const atom &rhs) const {
    return w < rhs.w;
  }
};

atom e[M];

int tot;

inline void add(int u, int v, int w) {
  e[tot].u = u;
  e[tot].v = v;
  e[tot++].w = w;
}

int head[MAX];

struct edge {
  int nxt;
  int to;
};

edge ei[M];

int cnt;

inline void add_edge(int u, int v) {
  ei[cnt].to = v;
  ei[cnt].nxt = head[u];
  head[u] = cnt++;
}

int top;
int s[M];

int val[M];

long long sum = 0;

int fa[MAX];
int siz[MAX];

inline int get(int x) {
  return fa[x] == x ? x : fa[x] = get(fa[x]);
}

inline void uni(int x, int y) {
  int fx = get(x);
  int fy = get(y);
  if (fx == fy) {
    return;
  }
  if (siz[fx] < siz[fy]) {
    fa[fx] = fy;
    siz[fy] += siz[fx];
  } else {
    fa[fy] = fx;
    siz[fx] += siz[fy];
  }
}

int tar;

int o[MAX];

int vis[MAX];

int p;

void dfs(int u) {
  vis[u] = 1;
  if (o[u]) {
    ++p;
  }
  for (int o = head[u]; ~o; o = ei[o].nxt) {
    int v = ei[o].to;
    if (!vis[v]) {
      dfs(v);
    }
  }
}

int main() {
  n = read();
  m = read();
  tar = read();
  memset(head, -1, sizeof(head));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      a[i][j] = read();
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m - 1; ++j) {
      add(point(i, j), point(i, j + 1), abs(a[i][j] - a[i][j + 1]));
    }
  }
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n - 1; ++i) {
      add(point(i, j), point(i + 1, j), abs(a[i][j] - a[i + 1][j]));
    }
  }
  sort(e, e + tot);
  for (int i = 0; i < tot; ++i) {
    s[top++] = e[i].w;
  }
  int len = unique(s, s + top) - s;
  for (int i = 0; i < len; ++i) {
    val[i] = s[i];
  }
  // for (int i = 0; i < len; ++i) {
  //   cerr << val[i] << endl;
  // }
  top = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int v = read();
      if (v == 1) {
        o[point(i, j)] = 1;
      }
    }
  }
  for (int i = 0; i < n * m; ++i) {
    fa[i] = i;
    siz[i] = 1;
  }
  int ptr = 0;
  for (int i = 0; i < len; ++i) {
    int to = val[i];
    p = 0;
    while (ptr < tot && e[ptr].w <= to) {
      int u = e[ptr].u;
      int v = e[ptr].v;
      if (get(u) != get(v) && siz[get(u)] + siz[get(v)] >= tar) {
        if (siz[get(u)] < tar) {
          dfs(get(u));
        }
        if (siz[get(v)] < tar) {
          dfs(get(v));
        }
      }
      uni(u, v);
      add_edge(u, v);
      add_edge(v, u);
      ++ptr;
    }
    sum += (long long) p * to;
  }
  printf("%lld\n", sum);
  return 0;
}
