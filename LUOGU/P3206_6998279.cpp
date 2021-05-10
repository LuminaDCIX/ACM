// luogu-judger-enable-o2
#include <cstring>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

inline int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (!isdigit(ch)) {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

const int N = 20000 + 5;
const int M = 50000 + 5;

int n, m, q;
int mod[M], val[M], to[M];

struct edge {
  int u, v, k, w;

  edge(int _u, int _v, int _k, int _w) {
    u = _u;
    v = _v;
    k = _k;
    w = _w;
  }

  bool operator < (const edge & rhs) const {
    return w < rhs.w;
  }
};

int top;
vector <edge> g[M];
vector <edge> tr;

bool del[M];
long long ans[M];


inline void set_edge(int v, vector <edge> &g) {
  for (int i = 0; i < (int) g.size(); ++i) {
    if (del[g[i].k]) {
      g[i].w = v;
    }
  }
}

inline void rec(vector <edge> &g) {
  for (int i = 0; i < (int) g.size(); ++i) {
    g[i].w = val[g[i].k];
  }
}

vector <int> t;

int fa[N];

int find(int x) {
  return fa[x] == x ? x : fa[x] = find(fa[x]);
}

bool merge(int x, int y) {
  int fx = find(x);
  int fy = find(y);
  if (fx == fy) {
    return false;
  }
  fa[fx] = fy;
  return true;
}


vector <int> mst(vector <edge> &g, long long &ret) {
  ret = 0;
  vector <int> t;
  sort(g.begin(), g.end());
  for (int i = 0; i < (int) g.size(); ++i) {
    fa[g[i].u] = g[i].u;
    fa[g[i].v] = g[i].v;
  }
  for (int i = 0; i < (int) g.size(); ++i) {
    int x = g[i].u;
    int y = g[i].v;
    if (merge(x, y)) {
      ret += g[i].w;
      t.push_back(i);
    }
  }
  return t;
}

int rem[M];
int inmst[M];

void solve(int l, int r, int id, long long nw) {
  if (l == r) {
    val[mod[l]] = to[l];
    rec(g[id]);
    mst(g[id], ans[l]);
    ans[l] += nw;
    return;
  }
  for (int i = l; i <= r; ++i) {
    del[mod[i]] = 1;
  }
  vector <edge> &cur = g[++top];
  vector <edge> &ori = g[id];
  cur = ori;
  {
    set_edge(-1e9, cur);
    long long bar;
    t = mst(cur, bar);
    for (int i = 0; i < (int) cur.size(); ++i) {
      fa[cur[i].u] = cur[i].u;
      fa[cur[i].v] = cur[i].v;
    }
    for (int i = 0; i < (int) t.size(); ++i) {
      if (!del[cur[t[i]].k]) {
        merge(cur[t[i]].u, cur[t[i]].v);
        nw += cur[t[i]].w;
      }
    }
    for (int i = 0; i < (int) cur.size(); ++i) {
      cur[i].u = find(cur[i].u);
      cur[i].v = find(cur[i].v);
    }
  }
  {
    set_edge(1e9, cur);
    long long bar;
    t = mst(cur, bar);
    for (int i = 0; i < (int) t.size(); ++i) {
      inmst[t[i]] = 1;
    }
    for (int i = 0; i < (int) cur.size(); ++i) {
      if (!inmst[i] && !del[cur[i].k]) {
        rem[i] = 1;
      }
    }
  }
  tr.clear();
  for (int i = 0; i < (int) cur.size(); ++i) {
    if (!rem[i]) {
      tr.push_back(cur[i]);
    }
    rem[i] = 0;
    inmst[i] = 0;
  }
  cur = tr;
  rec(cur);
  for (int i = l; i <= r; ++i) {
    del[mod[i]] = 0;
  }
  int nwg = top;
  int mid = (l + r) >> 1;
  solve(l, mid, nwg, nw);
  rec(g[nwg]);
  solve(mid + 1, r, nwg, nw);
}




int main() {
  n = read();
  m = read();
  q = read();
  ++top;
  for (int i = 1; i <= m; ++i) {
    int u = read();
    int v = read();
    int w = read();
    val[i] = w;
    g[top].push_back(edge(u, v, i, w));
  }
  for (int i = 1; i <= q; ++i) {
    mod[i] = read();
    to[i] = read();
  }
  solve(1, q, 1, 0);
  for (int i = 1; i <= q; ++i) {
    printf("%lld\n", ans[i]);
  }
  return 0;
}