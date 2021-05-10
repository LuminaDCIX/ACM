#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 40000 + 5;
const int Q = 100000 + 5;
const int M = N * 2 + 5;
const int LOG = 17;
 
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
 
int n;
int q;
int lim;
int val[N];
 
int head[N];
int nxt[M];
int ver[M];
 
void add(int u, int v) {
  static int tot = 0;
  nxt[tot] = head[u];
  ver[tot] = v;
  head[u] = tot++;
}
 
int dfs_cnt;
int dep[N];
int dfn[N];
int pre[N][LOG];
 
int top;
int cnt;
int stk[N];
int bel[N];
 
void dfs(int u, int fa) {
  pre[u][0] = fa;
  dep[u] = dep[fa] + 1;
  dfn[u] = dfs_cnt++;
  int cur = top;
  for (int o = head[u]; ~o; o = nxt[o]) {
    int v = ver[o];
    if (v == fa) {
      continue;
    }
    dfs(v, u);
    if (top - cur >= lim) {
      ++cnt;
      while (top != cur) {
        int k = stk[--top];
        bel[k] = cnt;
      }
    }
  }
  stk[top++] = u;
}
 
struct query {
  int a, b;
  int id;
  query() {};
  query(int _a, int _b, int _id): a(_a), b(_b), id(_id) {};
 
  bool operator < (const query &rhs) const {
    return bel[a] == bel[rhs.a] ? dfn[b] < dfn[rhs.b] : bel[a] < bel[rhs.a];
  }
};
 
query f[Q];
 
int tot[N];
int sum;
 
int ans[Q];
int in[N];
 
int lca(int a, int b) {
  if (dep[a] < dep[b]) {
    swap(a, b);
  }
  for (int i = LOG - 1; i >= 0; --i) {
    if (dep[pre[a][i]] >= dep[b]) {
      a = pre[a][i];
    }
  }
  if (a == b) {
    return a;
  }
  for (int i = LOG - 1; i >= 0; --i) {
    if (pre[a][i] != pre[b][i]) {
      a = pre[a][i];
      b = pre[b][i];
    }
  }
  return pre[a][0];
}
 
void getxor(int u, int c) {
  while (u != c) {
    if (in[u]) {
      in[u] = 0;
      --tot[val[u]];
      sum -= tot[val[u]] == 0;
    } else {
      in[u] = 1;
      ++tot[val[u]];
      sum += tot[val[u]] == 1;
    }
    u = pre[u][0];
  }
}
 
int main() {
  n = read();
  q = read();
  lim = sqrt(n);
  for (int i = 1; i <= n; ++i) {
    val[i] = read();
  }
  {
    vector <int> v;
    for (int i = 1; i <= n; ++i) {
      v.push_back(val[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for (int i = 1; i <= n; ++i) {
      val[i] = lower_bound(v.begin(), v.end(), val[i]) - v.begin();
    }
  }
  memset(head, -1, sizeof(head));
  for (int i = 0; i < n - 1; ++i) {
    int u = read();
    int v = read();
    add(u, v);
    add(v, u);
  }
  dfs(1, 0);
  while (top) {
    int k = stk[--top];
    bel[k] = cnt;
  } 
  for (int i = 1; i < LOG; ++i) {
    for (int j = 1; j <= n; ++j) {
      pre[j][i] = pre[pre[j][i - 1]][i - 1];
    }
  }
  for (int i = 0; i < q; ++i) {
    int u = read();
    int v = read();
    f[i] = query(u, v, i);
  }
  sort(f, f + q);
  int x = 1;
  int y = 1;
  for (int i = 0; i < q; ++i) {
    int u = f[i].a;
    int v = f[i].b;
    //T(u, y) x -> u
    int c = lca(x, u);
    getxor(x, c);
    getxor(u, c);
    //T(u, v) y -> v;
    c = lca(y, v);
    getxor(y, c);
    getxor(v, c);
    x = u;
    y = v;
    c = lca(u, v);
    ans[f[i].id] = sum + (!tot[val[c]]);
  }
  for (int i = 0; i < q; ++i) {
    printf("%d\n", ans[i]);
  }
  return 0;
} 