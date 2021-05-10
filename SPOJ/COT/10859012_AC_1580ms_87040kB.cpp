#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

using namespace std;

inline int read()
{
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    f = (ch  == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

const int N = 100000 + 5;
const int MAX = N * 23;

int n;
int m;

int head[N];
int tot;

struct edge {
  int nxt;
  int to;
} e[N << 1];

inline void add(int u, int v) {
  e[tot].to = v;
  e[tot].nxt = head[u];
  head[u] = tot++;
}

int val[N];

struct node {
  node *lc;
  node *rc;
  int sum;

  void update() {
    sum = lc->sum + rc->sum;
  }
} pool[MAX];

node* null = &pool[0];

node* root[N];

inline node* newnode() {
  static node* ptr = &pool[0];
  return ++ptr;
}

int fa[N][19];

node* add(node *o, int ll, int rr, int v)
{
  node *p = newnode();
  *p = *o;
  if (ll == v && rr == v) {
    ++p->sum;
    return p;
  }
  int mid = (ll + rr) >> 1;
  if (v <= mid) {
    p->lc = add(o->lc, ll, mid, v);
  } else {
    p->rc = add(o->rc, mid + 1, rr, v);
  }
  p->update();
  return p;
}

int dep[N];

int len;

void dfs(int u)
{
  root[u] = add(root[fa[u][0]], 0, len, val[u]);
  for (int o = head[u], v; ~o; o = e[o].nxt) {
    v = e[o].to;
    if (v == fa[u][0]) {
      continue;
    }
    dep[v] = dep[u] + 1;
    fa[v][0] = u;
    dfs(v);
  }
}

inline int lca(int a, int b)
{
  if (dep[a] < dep[b]) {
    swap(a, b);
  }
  for (int i = 17; i >= 0; --i) {
    if (fa[a][i] != 0 && dep[fa[a][i]] >= dep[b]) {
      a = fa[a][i];
    }
  }
  if (a == b) {
    return a;
  }
  for (int i = 17; i >= 0; --i) {
    if (fa[a][i] != 0 && fa[b][i] != 0 && fa[a][i] != fa[b][i]) {
      a = fa[a][i];
      b = fa[b][i];
    }
  }
  return fa[a][0];
}

int query(node* tu, node* tv, node* tlca, node* tfa, int ll, int rr, int k)
{
  if (ll == rr) {
    return ll;
  }
  int lft = tu->lc->sum + tv->lc->sum - tlca->lc->sum - tfa->lc->sum;
  int mid = (ll + rr) >> 1;
  if (lft >= k) {
    return query(tu->lc, tv->lc, tlca->lc, tfa->lc, ll, mid, k);
  } else {
    return query(tu->rc, tv->rc, tlca->rc, tfa->rc, mid + 1, rr, k - lft);
  }
}

int real[N];

int b[N];

int main()
{
  n = read();
  m = read();
  for (int i = 1; i <= n; ++i) {
    val[i] = read();
    b[i] = val[i];
  }
  sort(b + 1, b + n + 1);
  len  = unique(b + 1, b + 1 + n) - b;
  for (int i = 0; i < len; ++i) {
    real[i] = b[i];
  }
  for (int i = 1; i <= n; ++i) {
    val[i] = lower_bound(b + 1, b + len, val[i]) - b;
  }
  memset(head, -1, sizeof(head));
  for (int i = 0, u, v; i < n - 1; ++i) {
    u = read();
    v = read();
    add(u, v);
    add(v, u);
  }
  int ans = 0;
  root[0] = null;
  null->lc = null;
  null->rc = null;
  dfs(1);
  {
    for (int i = 1; i <= 17; ++i) {
      for (int u = 1; u <= n; ++u) {
	fa[u][i] = fa[fa[u][i - 1]][i - 1];
      }
    }
  }
  for (int i = 0, u, v, k, c; i < m; ++i) {
    if (i) {
      puts("");
    }
    u = read();
    v = read();
    k = read();
    c = lca(u, v);
    printf("%d", real[query(root[u], root[v], root[c], root[fa[c][0]], 0, len, k)]);
  }
  return 0;
}
