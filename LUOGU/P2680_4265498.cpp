#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 300000 + 5;
const int M = N << 1;
const int MAX = 23;

inline int read() {
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x;
}

int n;

int tot;
int head[N];

struct edge {
  int to;
  int nxt;
  int val;
};

edge e[M];

inline void add(int u, int v, int w) {
  e[tot].to = v;
  e[tot].nxt = head[u];
  e[tot].val = w;
  head[u] = tot++;
}

int len[N][MAX];
int fa[N][MAX];
int dep[N];

inline void dfs(int u, int pre) {
  fa[u][0] = pre;
  for (int o = head[u]; ~o; o = e[o].nxt) {
    int v = e[o].to;
    if (v == pre) {
      continue;
    }
    dep[v] = dep[u] + 1;
    len[v][0] = e[o].val;
    dfs(v, u);
  }
}

inline int lca(int a, int b, int &dist) {
  dist = 0;
  if (dep[a] < dep[b]) {
    swap(a, b);
  }
  for (int i = MAX - 1; i >= 0; --i) {
    if (fa[a][i] != -1 && dep[fa[a][i]] >= dep[b]) {
      dist += len[a][i];
      a = fa[a][i];
    }
  }
  if (a == b) {
    return a;
  }
  for (int i = MAX - 1; i >= 0; --i) {
    if (fa[a][i] != -1 && fa[b][i] != -1 && fa[a][i] != fa[b][i]) {
      dist += len[a][i];
      dist += len[b][i];
      a = fa[a][i];
      b = fa[b][i];
    }
  }
  dist += len[a][0];
  dist += len[b][0];
  return fa[a][0];
}

long long sum = 0;
long long ans = 0;

int tag[N];
int cur;
int cnt;

bool succ;

void dfs0(int u, int pre) {
  for (int o = head[u]; ~o; o = e[o].nxt) {
    int v = e[o].to;
    if (v == pre) {
      continue;
    }
    dfs0(v, u);
    tag[u] += tag[v];
    if (e[o].val >= cur && tag[v] >= cnt) {
      succ = 1;
    }
  }
}

int d[N];
int c[N];
int s[N];
int t[N];

int main() {
  n = read();
  int q = read();
  memset(head, -1, sizeof(head));
  for (int i = 0; i < n - 1; ++i) {
    int u = read() - 1;
    int v = read() - 1;
    int t = read();
    add(u, v, t);
    add(v, u, t);
  }
  memset(fa, -1, sizeof(fa));
  dfs(0, -1);
  for (int i = 1; i < MAX; ++i) {
    for (int j = 0; j < n; ++j) {
      if (fa[j][i - 1] != -1) {
        fa[j][i] = fa[fa[j][i - 1]][i - 1];
        len[j][i] = len[j][i - 1] + len[fa[j][i - 1]][i - 1];
      }
    }
  }

  for (int i = 0; i < q; ++i) {
    int u = read() - 1;
    int v = read() - 1;
    c[i] = lca(u, v, d[i]);
    s[i] = u;
    t[i] = v;
  }
  int low = 0;
  int high = 1e9;
  int ans = -1;
  while (low <= high) {
    int mid = low + high >> 1;
    cnt = 0;
    cur = 0;
    memset(tag, 0, sizeof(tag));
    for (int i = 0; i < q; ++i) {
      if (d[i] > mid) {
        cur = max(cur, d[i] - mid);
        tag[s[i]] += 1;
        tag[t[i]] += 1;
        tag[c[i]] -= 2;
        ++cnt;
      }
    }

    // cerr << mid << " " << cnt << " " << cur << endl;
    succ = 0;
    dfs0(0, -1);
    if (succ) {
      high = mid - 1;
      ans = mid;
    } else {
      low = mid + 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}
