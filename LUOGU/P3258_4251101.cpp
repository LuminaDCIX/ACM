#include <vector>
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

const int N = 300000 + 5;
const int M = N << 1;
int n;

int tot;
int head[N];

struct edge {
  int to;
  int nxt;
};

edge e[M];

inline void add(int u, int v) {
  e[tot].to = v;
  e[tot].nxt = head[u];
  head[u] = tot++;
}

int a[N];

int lca[N];

vector <pair<int, int> > q[N];

int fa[N];
int col[N];

int s[N];

int get(int x) {
  return s[x] == x ? x : s[x] = get(s[x]);
}

void dfs0(int u, int pre) {
  fa[u] = pre;
  col[u] = 1;
  for (int o = head[u]; ~o; o = e[o].nxt) {
    int v = e[o].to;
    if (v == pre) {
      continue;
    }
    dfs0(v, u);
    s[v] = u;
  }
  for (int i = 0; i < q[u].size(); ++i) {
    int v = q[u][i].first;
    if (col[v] == 2) {
      lca[q[u][i].second] = get(v);
    }
  }
  col[u] = 2;
}

int tag[N];

int ans[N];

void dfs1(int u, int pre) {
  for (int o = head[u]; ~o; o = e[o].nxt) {
    int v = e[o].to;
    if (v != pre) {
      dfs1(v, u);
      tag[u] += tag[v];
    }
  }
}

int main() {
  n = read();
  for (int i = 0; i < n; ++i) {
    a[i] = read() - 1;
  }
  memset(head, -1, sizeof(head));
  for (int i = 0; i < n - 1; ++i) {
    int u = read() - 1;
    int v = read() - 1;
    add(u, v);
    add(v, u);
  }
  for (int i = 1; i < n; ++i) {
    int x = a[i];
    int y = a[i - 1];
    q[x].push_back(make_pair(y, i));
    q[y].push_back(make_pair(x, i));
  }
  for (int i = 0; i < n; ++i) {
    s[i] = i;
  }
  dfs0(0, -1);
  for (int i = 1; i < n; ++i) {
    int x = a[i - 1];
    int y = a[i];
    int c = lca[i];
    tag[x] += 1;
    tag[y] += 1;
    tag[c] -= 1;
    if (fa[c] != -1) {
      tag[fa[c]] -= 1;
    }
  }
  for (int i = 1; i < n - 1; ++i) {
    int x = a[i];
    tag[x] -= 1;
    if (fa[x] != -1) {
      tag[fa[x]] += 1;
    }
  }
  dfs1(0, -1);
  --tag[a[n - 1]];
  for (int i = 0; i < n; ++i) {
    printf("%d\n", tag[i]);
  }
  return 0;
}

