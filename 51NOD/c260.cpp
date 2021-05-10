#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int E = (5 * 100000) * 2 + N;

int n;
int m;

struct edge {
  edge *nxt;
  int to;
};

edge e[E];
edge *head[N];

inline void addEdge(int u, int v) {
  static edge* ptr = e;
  ptr->to = v;
  ptr->nxt = head[u];
  head[u] = ptr++;
}

struct IdomTree {

  int head[N];
  int pre[N];
  int dom[N];
  int to[E];
  int nxt[E];
  int top;

  void addEdge(int *h, int fr,int tt) {
    ++top;
    nxt[top] = h[fr];
    to[top] = tt;
    h[fr] = top;
  }

  int bcj[N];
  int semi[N];
  int idom[N];
  int best[N];
  int dfn[N];
  int id[N];
  int fa[N];
  int dfs_clock;
  
  int push(int v) {
    if(v == bcj[v]) {
      return v;
    }
    int y = push(bcj[v]);
    if (dfn[semi[best[bcj[v]]]] < dfn[semi[best[v]]]) {
      best[v] = best[bcj[v]];
    }
    return bcj[v] = y;
  }
  
  void dfs(int rt) {
    dfn[rt] = ++dfs_clock;
    id[dfs_clock] = rt;
    for (int i = head[rt]; i; i = nxt[i]) {
      if (!dfn[to[i]]) {
	dfs(to[i]);
	fa[to[i]] = rt;
      }
    }
  }
  
  void tarjan() {
    for(int i = dfs_clock, u; i >= 2; --i) {
      u = id[i];
      for(int j = pre[u]; j; j = nxt[j]) {
	if (!dfn[to[j]]) {
	  continue;
	}
	push(to[j]);
	if (dfn[semi[best[to[j]]]] < dfn[semi[u]]) {
	  semi[u] = semi[best[to[j]]];
	}
      }
      addEdge(dom, semi[u], u);
      bcj[u] = fa[u];
      u = id[i - 1];
      for (int j = dom[u]; j; j = nxt[j]) {
	push(to[j]);
	if(semi[best[to[j]]] == u) idom[to[j]] = u;
	else idom[to[j]] = best[to[j]];
      }
    }
    for(int i = 2, u; i <= dfs_clock; ++i) {
      u = id[i];
      if(idom[u] != semi[u]) {
	idom[u] = idom[idom[u]];
      }
    }
  }
  void solve() {
    for (int i = 1; i <= n; ++i) {
      bcj[i] = i;
      semi[i] = i;
      best[i] = i;
    }
    dfs_clock = 0;
    dfs(1);
    tarjan();
  }
} idom;

const int MAXN = N * 25;

long long t[MAXN];
int ls[MAXN];
int rs[MAXN];
long long tag[MAXN];
int tot = 4 * N;


int siz[N];
int son[N];
int f[N];
int dep[N];
int top[N];
int id[N];
int out[N];
int pre[N];
int cnt;
int a[N];

void update(int o) {
  t[o] = t[ls[o]] + t[rs[o]];
}

void build(int o, int ll, int rr) {
  if (ll == rr) {
    t[o] = a[pre[ll]];
    return;
  }
  int mid = ll + rr >> 1;
  ls[o] = o << 1;
  rs[o] = o << 1 | 1;
  build(o << 1, ll, mid);
  build(o << 1 | 1, mid + 1, rr);
  update(o);
}

void copy(int now, int o) {
  tag[now] = tag[o];
  ls[now] = ls[o];
  rs[now] = rs[o];
  t[now] = t[o];
}

int modify(int o, int ll, int rr, int l, int r, int v) {
  // cerr << l << " " << r << endl;
  // cerr << ll << " " << rr << endl;
  int now = ++tot;
  copy(now, o);
  if (ll >= l && rr <= r) {
    t[now] += (long long) (rr - ll + 1) * v;
    tag[now] += v;
    return now;
  }
  int mid = ll + rr >> 1;
  if (l <= mid) {
    ls[now] = modify(ls[o], ll, mid, l, r, v);
  }
  if (r > mid) {
    rs[now] = modify(rs[o], mid + 1, rr, l, r, v);
  }
  update(now);
  t[now] += (rr - ll + 1) * tag[now];
  return now;
}

long long sum(int o, int ll, int rr, int l, int r, int s = 0) {
  
  // cerr << l << " " << r << endl;
  // cerr << ll << " " << rr << endl;
  if (ll >= l && rr <=r) {
    return t[o] + (long long) s * (rr - ll + 1);
  }
  int mid = ll + rr >> 1;
  s += tag[o];
  if (r <= mid) {
    return sum(ls[o], ll, mid, l, r, s);
  } else if (l > mid) {
    return sum(rs[o], mid + 1, rr, l, r, s);
  } else {
    return sum(ls[o], ll, mid, l, r, s) + sum(rs[o], mid + 1, rr, l, r, s);
  }
}

void dfs1(int u,int fa) {
  f[u] = fa;
  siz[u] = 1;
  for (edge* o = head[u]; o; o = o->nxt) {
    int v = o->to;
    if (v == fa) {
      continue;
    }
    dep[v] = dep[u] + 1;
    dfs1(v, u);
    siz[u] += siz[v];
    if (son[u] == 0 || siz[v] > siz[son[u]]) {
      son[u] = v;
    }
  }
}
void dfs2(int u,int anc) {
  top[u] = anc;
  id[u] = ++cnt;
  pre[id[u]] = u;
  if (son[u] == 0) {
    out[u] = cnt;
    return;
  }
  dfs2(son[u], anc);
  for (edge* i = head[u]; i ; i = i->nxt) {
    int v = i->to;
    if (v != son[u] && v != f[u]) {
      dfs2(v, v);
    }
  }
  out[u] = cnt;
}

int root[N << 1];

long long askSum(int root, int x, int y) {
  int f1 = top[x];
  int f2 = top[y];
  long long ans = 0;
  while (f1 != f2) {
    if (dep[f1] < dep[f2]) {
      swap(f1, f2);
      swap(x, y);
    }
    ans += sum(root, 1, n, id[f1], id[x]);
    x = f[f1];
    f1 = top[x];
  }
  ans += (dep[x] > dep[y]) ? sum(root, 1, n, id[y], id[x]) : sum(root, 1, n, id[x], id[y]);
  return ans;
}

long long askRoot(int root, int x) {
  return sum(root, 1, n, id[x], out[x]);
}

int  modifySum(int root, int x, int y, int v) {
  int f1 = top[x];
  int f2 = top[y];
  while (f1 != f2) {
    if (dep[f1] < dep[f2]) {
      swap(f1, f2);
      swap(x, y);
    }
    root = modify(root, 1, n, id[f1], id[x], v);
    x = f[f1];
    f1 = top[x];
  }
  return (dep[x] > dep[y]) ? modify(root, 1, n, id[y], id[x], v) : modify(root, 1, n, id[x], id[y], v);
}

int modifyRoot(int root, int x, int v) {
  return modify(root, 1, n, id[x], out[x], v);
}

bool cmp(int a, int b) {
  return id[a] < id[b];
}

int lca(int x,int y) {
  for (;top[x]!=top[y];dep[top[x]]>dep[top[y]]?x=f[top[x]]:y=f[top[y]]);
  return dep[x]<dep[y]?x:y;
}

int calc(int root, vector <int> v) {
  if (v.size() == 1) {
    printf("%lld\n", askSum(root, 1, v[0]));
    return 0;
  }
  sort(v.begin(), v.end(), cmp);
  long long ans = askSum(root, 1, v[0]);
  for (int i = 1; i < v.size(); ++i) {
    int a = v[i];
    int b = v[i - 1];
    
    ans -= askSum(root, 1, lca(a, b));
    ans += askSum(root, 1, a);
  }
  printf("%lld\n", ans);
  return 0;
}

void solve() {
  dfs1(1, -1);
  dfs2(1, 1);
  // for (int i = 1; i <= n; ++i) cerr << out[i] << endl;
  //  return;
  build(1, 1, n);
  root[0] = 1;
  int q;
  scanf("%d", &q);
  int p = 0;
  for (int i = 1; i <= q; ++i) {
    static char o[2];
    scanf("%s", o);
    if (o[0] == 'C') {
      int t;
      scanf("%d", &t);
      int u, w;
      int k = p;
      if (t == 1) {
	scanf("%d %d", &u, &w);
	root[++p] = modify(root[k], 1, n, id[u], id[u], w);
      } else if (t == 2) {  
	scanf("%d %d", &u, &w);
	root[++p] = modifyRoot(root[k], u, w);
      } else {
	scanf("%d %d", &u, &w);
	root[++p] = modifySum(root[k], 1, u, w);
      }
    } else if (o[0] == 'Q') {
      int u;
      int t;
      // cerr << p << endl;
      scanf("%d", &t);
      if (t == 1) {
	scanf("%d", &u);
	printf("%lld\n", askRoot(root[p], u));
      } else if (t == 2) {
	scanf("%d", &u);
	printf("%lld\n", askSum(root[p], 1, u));
      } else if (t == 3) {
	int s;
	scanf("%d", &s);
	vector <int> v;
	for (int j = 0; j < s; ++j) {
	  int l;
	  scanf("%d", &l);
	  v.push_back(l);
	}
	calc(root[p], v);
      }
    } else {
      int k;
      scanf("%d", &k);
      // cerr << p - k << endl;
      root[i] = root[max(0, p - k)];
      p = max(0, p - k);
    }
  }
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    idom.addEdge(idom.head, u, v);
    idom.addEdge(idom.pre, v, u);
  }
  idom.solve();
  for (int i = 2; i <= n; ++i) {
    addEdge(idom.idom[i], i);
  }
  solve();
  return 0;
}
