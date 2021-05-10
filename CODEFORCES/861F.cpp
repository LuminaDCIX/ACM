#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

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

const int N = 2 * 1e5 + 5;

int n;
int m;

int head[N];
int tot;

struct edge {
  int nxt;
  int v;
  bool c;
} e[N << 1];

inline void add(int u, int v) {
  e[tot].v = v;
  e[tot].nxt = head[u];
  head[u] = tot++;
}

int vis[N];
int fa[N];

vector <int> a;
vector <int> b;
vector <int> c;

void dfs(int u, int pre)
{
  vis[u] = 1;
  fa[u] = pre;
  for (int o = head[u], v; ~o; o = e[o].nxt) {
    v = e[o].v;
    if (v == pre) {
      continue;
    }
    if (!vis[v]) {
      dfs(v, u);
    }
  }
}

inline void chs(int x) {
  e[x].c = 1;
  e[x ^ 1].c = 1;
}

int ptr;

vector <int> s[N];

void build(int u, int id)
{
  int cnt = 0;
  int k = ++ptr;
  for (int o = head[u], v; ~o; o = e[o].nxt) {
    v = e[o].v;
    if (fa[v] == u) {
      build(v, o);
    }
    if (!e[o].c && v != fa[u]) {
      ++cnt;
      s[k].push_back(v);
      chs(o);
    }
  }
  if ((cnt & 1) && id != -1) {
    chs(id);
    a.push_back(fa[u]);
    b.push_back(u);
    c.push_back(s[k][0]);
    for (int i = 1; i < s[k].size(); i += 2) {
      a.push_back(s[k][i]);
      b.push_back(u);
      c.push_back(s[k][i + 1]);
    }
  } else {
    if (id == -1 && s[k].size() == 1) {
      return;
    }
    for (int i = 1; i < s[k].size(); i += 2) {
      a.push_back(s[k][i - 1]);
      b.push_back(u);
      c.push_back(s[k][i]);
    }
  }
}


int main()
{
  memset(head, -1, sizeof(head));

  n = read();
  m = read();
  for (int i = 0, u, v; i < m; ++i) {
    u = read();
    v = read();
    add(u, v);
    add(v, u);
  }
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) {
      dfs(i, -1);
      build(i, -1);
    }
  }
  printf("%d\n", a.size());
  for (int i = 0; i < (int) a.size(); ++i) {
    printf("%d %d %d\n", a[i], b[i], c[i]);
  }
  return 0;
}
