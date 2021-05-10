#include <map>
#include <set>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

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
  return f * x;
}

const int N = 200000 + 5;

int n;

int head[N];
int tot;

struct edge 
{
  int nxt;
  int to;
  int val;
};

edge e[N << 1];

inline void add(int u, int v, int w)
{
  e[tot].to = v;
  e[tot].nxt = head[u];
  e[tot].val = w;
  head[u] = tot++;
}

int fa[N];

inline int find(int x) {
  return fa[x] == x ? x : fa[x] = find(fa[x]);
}

struct atom
{
  int from;
  int to;
  int val;

  bool operator < (const atom &rhs) const {
    return val < rhs.val;
  }
};

atom p[N];

int m;

inline void pre()
{
  sort(p, p + m);
  for (int i = 1; i <= n; ++i) {
    fa[i] = i;
  }
  for (int i = 0; i < m; ++i) {
    atom x = p[i];
    if (find(x.from) == find(x.to)) {
      continue;
    }
    fa[find(x.from)] = find(x.to);
    add(x.from, x.to, x.val);
    add(x.to, x.from, x.val);
  }
}

int col[N];

set < pair <int, int> > colmn[N];

map <int, multiset <int> > dis[N];

multiset <int> mn;

int f[N];
int l[N];

inline int getmn(int u)
{
  multiset < pair <int, int> >::iterator it = colmn[u].begin();
  if (it == colmn[u].end()) {
    return 1e9;
  }
  if ((*it).second != col[u]) {
    return (*it).first;
  }
  ++it;
  if (it == colmn[u].end()) {
    return 1e9;
  }
  return (*it).first;
}

bool vis[N];
void dfs(int u, int fa)
{
  f[u] = fa;
  vis[u] = 1;
  for (int o = head[u], v; ~o; o = e[o].nxt) {
    v = e[o].to;
    if (v == fa) {
      continue;
    }
    dfs(v, u);
    l[v] = e[o].val;
    dis[u][col[v]].insert(e[o].val);
  }
  map <int, multiset <int> >::iterator it = dis[u].begin();
  while (it != dis[u].end()) {
    colmn[u].insert(make_pair(*((*it).second.begin()), (*it).first));
    ++it;
  }

  mn.insert(getmn(u));
}

int q;

int z;

int main()
{
  n = read();
  m = read();
  z = read();
  q = read();
  for (int i = 0; i < m; ++i) {
    p[i].from = read();
    p[i].to = read();
    p[i].val = read();
  }
  memset(head, -1, sizeof(head));
  pre();
  for (int i = 1; i <= n; ++i) {
    col[i] = read();
  }
  dfs(1, -1);
  
  for (int i = 0, x, y, k, fa, c; i < q; ++i) {
    x = read();
    y = read();


    k = getmn(x);
    mn.erase(mn.find(k));

    c = col[x];
    col[x] = y;   

    mn.insert(getmn(x));

    fa = f[x];
    if (fa == -1) {
      printf("%d\n", *(mn.begin()));
      continue;
    }

    k = getmn(fa);
    mn.erase(mn.find(k));

    colmn[fa].erase(make_pair(*(dis[fa][c].begin()), c));
    colmn[fa].erase(make_pair(*(dis[fa][y].begin()), y));

    dis[fa][c].erase(dis[fa][c].find(l[x]));
    dis[fa][y].insert(l[x]);

    if (dis[fa][c].size() != 0) {
      colmn[fa].insert(make_pair(*(dis[fa][c].begin()), c));
    }    
    colmn[fa].insert(make_pair(*(dis[fa][y].begin()), y));

    mn.insert(getmn(fa));
    printf("%d\n", *(mn.begin()));
  }
  return 0;
}