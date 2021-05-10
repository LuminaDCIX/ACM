// luogu-judger-enable-o2
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 100000 + 5;
const int M = N * 3 + 5;
const int LOG = 19;

int n;
int m;

int x[N];
int y[N];

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

struct edge {
  edge* nxt;
  int to;
};

edge *head[N];
edge e[M];

void addEdge(int u, int v) {
  static edge *ptr = e;
  ptr->to = v;
  ptr->nxt = head[u];
  head[u] = ptr++;
}

int col[N];

int cir[N];
int pos[N];
int tot;

bool dfs(int u, int fa) {
  col[u] = 1;
  for (edge *o = head[u]; o; o = o->nxt) {
    int v = o->to;
    if (v == fa) {
      continue;
    }
    if (col[v]) {
      col[v] = 2;
      col[u] = 2;
      pos[u] = tot;
      cir[tot++] = u;
      return true;
    }
    if (dfs(v, u)) {
      pos[u] = tot;
      cir[tot++] = u;
      if (col[u] == 2) {
	return false;
      } else {
	col[u] = 2;
	return true;
      }
    }
  }
  return false;
}

int pre[N][LOG];
int dep[N];
int top[N];

struct node {
  long long x;
  long long y;
  long long xy;
  long long x2;
  long long y2;
  int n;

  node operator + (const node rhs) const {
    node c;
    c.x = x + rhs.x;
    c.y = y + rhs.y;
    c.xy = xy + rhs.xy;
    c.x2 = x2 + rhs.x2;
    c.y2 = y2 + rhs.y2;
    c.n = n + rhs.n;
    return c;
  }

  node operator - (const node rhs) const {
    node c;
    c.x = x - rhs.x;
    c.y = y - rhs.y;
    c.xy = xy - rhs.xy;
    c.x2 = x2 - rhs.x2;
    c.y2 = y2 - rhs.y2;
    c.n = n - rhs.n;
    return c;
  }

  void init() {
    x = 0;
    y = 0;
    xy = 0;
    x2 = 0;
    y2 = 0;
    n = 0;
  }
};

node d[N];

int root;

void dfs2(int u, int fa) {
  pre[u][0] = fa;
  if (fa != -1) {
    dep[u] = dep[fa] + 1;
    d[u] = d[u] + d[fa];
    if (top[u] == -1) {
      top[u] = top[fa];
    }
  }
  for (edge *o = head[u]; o; o = o->nxt) {
    int v = o->to;
    if (v == fa || col[v] == 2) {
      continue;
    }
    dfs2(v, u);
  }
}

void initD() {
  for (int i = 1; i < LOG; ++i) {
    for (int j = 0; j < n; ++j) {
      if (pre[j][i - 1] != -1) {
	pre[j][i] = pre[pre[j][i - 1]][i - 1];
      }
    }
  }
}

int lca(int a, int b) {
  if (dep[a] < dep[b]) {
    swap(a, b);
  }
  for (int i = LOG - 1; i >= 0; --i) {
    if (pre[a][i] != -1 && dep[pre[a][i]] >= dep[b]) {
      a = pre[a][i];
    }
  }
  if (a == b) {
    return a;
  }
  for (int i = LOG - 1; i >= 0; --i) {
    if (pre[a][i] != -1 && pre[b][i] != -1 && pre[a][i] != pre[b][i]) {
      a = pre[a][i];
      b = pre[b][i];
    }
  }
  return pre[a][0];
}

node s[N];

node get(int l, int r) {
  node p;
  p.init();
  if (l > r) {
    return p;
  } else {
    if (l == 0) {
      return s[r];
    } else {
      return s[r] - s[l - 1];
    }
  }
}

void query(int u, int v, node &a, node &b) {
  int c;
  a.init();
  b.init();
  if (col[u] != 2 && col[v] != 2) {
    c = lca(u, v);
  } else {
    c = root;
  }
  if (c != root) {
    a = d[u] + d[v] - d[c] - d[pre[c][0]];
    return;
  } else {
    int l = pos[top[u]];
    int r = pos[top[v]];
    if (l == r) {
      node x1 = get(l, r);
      a = x1 + d[u] + d[v];
      return;
    }
    if (l > r) {
      swap(l, r);
    }
    node x1 = get(l, r);
    node x2 = get(0, l) + get(r, tot - 1);
    // cerr << l << " " << r << endl;
    // cerr << x1.x << endl;
    // cerr << x2.x << endl;
    a = x1 + d[u] + d[v];
    b = x2 + d[u] + d[v];
    return;
  }
}

void init() {
  dfs(0, -1); 
  // cerr << "col" << " "; for (int i = 0; i < n; ++i) cerr << col[i] << " "; cerr << endl;
  // cerr << "cir" << " "; for (int i = 0; i < tot; ++i) cerr << cir[i] << " "; cerr << endl;
  // cerr << "pos" << " "; for (int i = 0; i < tot; ++i) cerr << pos[i] << " "; cerr << endl;
  memset(top, -1, sizeof(top));
  for (int i = 0; i < n; ++i) {
    int xx = x[i];
    int yy = y[i];
    d[i].x = xx;
    d[i].y = yy;
    d[i].xy = (long long) xx * yy;
    d[i].x2 = (long long) xx * xx;
    d[i].y2 = (long long) yy * yy;
    d[i].n = 1;
  }
  if (tot != 0) {
    root = n;
    for (int i = 0; i < n; ++i) {
      if (col[i] == 2) {
	top[i] = i;
	for (edge* o = head[i]; o; o = o->nxt) {
	  int v = o->to;
	  if (col[v] != 2) {
	    addEdge(root, v);
	    top[v] = i;
	    // cerr << root << "->" << v << endl;
	  }
	}
      }
    }
    s[0] = d[cir[0]];
    d[cir[0]].init();
    for (int i = 1; i < tot; ++i) {
      s[i] = s[i - 1] + d[cir[i]];
      d[cir[i]].init();
    }
  } else {
    memset(top, 0, sizeof(top));
    root = 0;
    s[tot++] = d[0];
    d[0].init();
    col[0] = 2;
  }
  memset(pre, -1, sizeof(pre));
  dfs2(root, -1);
  initD();
  // cerr << "top" << " " ; for (int i = 0; i <= n; ++i) cerr << top[i] << " "; cerr << endl;
  
  // node x;
  // node y;
  // query(0, 5, x, y);
}

double calc(node a) {
  double A = ((double) a.n * a.x2 - (double) a.x * a.x) / (double) a.n;
  double B = ((double) -2 * a.n * a.xy + 2 * a.x * a.y) / (double) a.n;
  double C = ((double) a.n * a.y2 - (double) a.y * a.y) / (double) a.n;
  double AA = -4;
  double BB = 4 * (A + C);
  double CC = -4 * A * C + B * B;
  double det = sqrt(BB * BB - 4 * AA * CC);
  double ans = (BB - det) / (-2 * AA);
  ans = min(ans, (BB + det) / (-2 * AA));
  return ans;
}

void solve() {
  init();
  int q = read();
  for (int i = 0; i < q; ++i) {
    int u = read() - 1;
    int v = read() - 1;
    node a;
    node b;
    query(u, v, a, b); 
    // cerr << a.n << " " << b.n << endl;
    double ans = min(calc(a), calc(b));
    printf("%.7f\n", ans);
  }
}

int main() {
  n = read();
  m = read();
  for (int i = 0; i < n; ++i) {
    x[i] = read();
    y[i] = read();
  }
  for (int i = 0; i < m; ++i) {
    int u = read() - 1;
    int v = read() - 1;
    addEdge(u, v);
    addEdge(v, u);
  }
  solve();
  return 0;
}
