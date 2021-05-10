#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define root (&pool[0])
using namespace std;

inline int read() 
{
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
  return x * f;
}

const int N = 5 * 1e5 + 5;
const int mod = 1000000007;

int n;
int siz[N];
int top[N];
int f[N];
int son[N];

int head[N], tot;
int ans;

struct edge {
  int nxt, to;
} e[N << 1];

inline void add(int u, int v) {
  e[tot].nxt = head[u];
  e[tot].to = v;
  head[u] = tot++;
}

void dfs1(int u, int fa)
{
  siz[u] = 1;
  f[u] = fa;
  for (int i = head[u], v; ~i; i = e[i].nxt) {
    v = e[i].to;
    if (v == fa) {
      continue;
    }
    dfs1(v, u);
    siz[u] += siz[v];
    if (son[u] == 0 || siz[son[u]] < siz[v]) {
      son[u] = v;
    }
  }
}

int id[N];
int a[N];
int cnt;

void dfs2(int u, int fa, int anc)
{
  id[u] = ++cnt;
  a[cnt] = siz[u];
  top[u] = anc;
  if (!son[u]) {
    return;
  }
  dfs2(son[u], u, anc);
  for (int i = head[u], v; ~i; i = e[i].nxt) {
    v = e[i].to;
    if (v == fa || v == son[u]) {
      continue;
    }
    dfs2(v, u, v);
  }
}

struct node {
  int l, r;
  node *lc, *rc;
  int lazy, sum;

  inline void pushdown() {
    if (l == r || lazy == 0) {
      return;
    }
    lc->sum = (lc->sum + 1ll * lazy * (lc->r - lc->l + 1)) % mod;
    rc->sum = (rc->sum + 1ll * lazy * (rc->r - rc->l + 1)) % mod;
    lc->lazy += lazy;
    rc->lazy += lazy;
    lazy = 0;
  }

  void update() {
    sum = (lc->sum + rc->sum) % mod;
  }
} pool[N << 2];

inline node* newnode() {
  static node* ptr = root;
  return ++ptr;
}

void build(node *o, int l, int r)
{
  o->l = l;
  o->r = r;
  if (l == r) {
    o->sum = a[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(o->lc = newnode(), l, mid);
  build(o->rc = newnode(), mid + 1, r);
  o->update();
}

int query(node *o, int l, int r)
{
  o->pushdown();
  if (o->l >= l && o->r <= r) {
    return o->sum;
  }
  int mid = (o->l + o->r) >> 1;
  int ret = 0;
  if (l <= mid) {
    ret += query(o->lc, l, r);
  }
  if (r > mid) {
    ret += query(o->rc, l, r);
  }
  o->update();
  return ret % mod;
}

void modify(node *o, int l, int r)
{
  o->pushdown();
  if (o->l >= l && o->r <= r) {
    o->lazy += -1;
    o->sum = (o->sum - (o->r - o->l + 1)) % mod;
    return;
  }
  int mid = (o->l + o->r) >> 1;
  int ret = 0;
  if (l <= mid) {
    modify(o->lc, l, r);
  }
  if (r > mid) {
    modify(o->rc, l, r);
  }
  o->update();
}

int t[N];
int val[N];

inline int Query(int a, int b) {
  int ret = 0;
  while (top[a] != 1) {
    ret = (ret + query(root, id[top[a]], id[a])) % mod;
    a = f[top[a]];
  }
  return (ret + query(root, 1, id[a]));
}

inline void Modify(int a, int b) {
  while (top[a] != 1) {
    modify(root, id[top[a]], id[a]);
    a = f[top[a]];
  }
  modify(root, 1, id[a]);
}

struct tree {
  int x;
  int v;

  bool operator < (const tree& rhs) const {
    return v > rhs.v;
  }

} p[N];

int main()
{
  memset(head, -1, sizeof(head));
  n = read();
  for (int i = 0, u, v; i < n - 1; ++i) {
    u = read();
    v = read();
    add(u, v);
    add(v, u);
  }
  dfs1(1, -1);
  dfs2(1, -1, 1);
  for (int i = 1; i <= n; ++i) {
    val[i] = read();
    p[i].x = i;
    p[i].v = val[i];
  }
  build(root, 1, n);
  sort(p + 1, p + n + 1);
  for (int i = 1, v; i <= n; ++i) {
    v = p[i].x;
    ans = (ans + 1ll * Query(v, 1) * val[v]) % mod;
    Modify(v, 1);
  }
  printf("%d\n", ans);
  return 0;
}
