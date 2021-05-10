#include <map>
#include <set>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1000 + 5;
const int MAX = 1000005;
const int M = 2000005;

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

int amt;

int s;
int t;

int x0;
int y0;
int x1;
int y1;

struct squ {
  int x0;
  int y0;
  int x1;
  int y1;

  squ(int _x0 = 0, int _y0 = 0, int _x1 = 0, int _y1 = 0) {
    x0 = _x0;
    y0 = _y0;
    x1 = _x1;
    y1 = _y1;
  }
};

squ q[N];

int T;

int tot;
int head[MAX];

struct edge {
  int nxt;
  int to;
  int w;
};

edge e[M];


int max0;
int max1;

inline void add(int u, int v, int w) {
  e[tot].to = v;
  e[tot].nxt = head[u];
  e[tot].w = w;
  head[u] = tot++;
}

int pre0[N << 1];
int pre1[N << 1];

struct atom {
  int x;
  int y;
  int v;
  int id;

  atom(int _x = 0, int _y = 0, int _v = 0, int _id = 0) {
    x = _x;
    y = _y;
    v = _v;
    id = _id;
  }
};

atom pnt[MAX];

int cnt;

bool flg1;
bool flg2;

inline void _ins(int x, int y, int v, int id) {
  if (x == x0 && y == y0) {
    s = id;
    flg1 = 1;
  }
  if (x == x1 && y == y1) {
    t = id;
    flg2 = 1;
  }
  pnt[cnt++] = atom(x, y, v, id);
}


bool cmp0(const atom &a, const atom &b) {
  return a.x == b.x ? a.y < b.y : a.x < b.x;
}

bool cmp1(const atom &a, const atom &b) {
  return a.y == b.y ? a.x < b.x : a.y < b.y;
}

int k = 0;
int v[N << 1];

inline int lbd(int low, int high, int x) {
  int ret = low;
  while (low <= high) {
    int mid = low + high >> 1;
    if (v[mid] >= x) {
      ret = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return ret + 1;
}

void build() {
  k = 0;
  for (int i = 0; i < n; ++i) {
    v[k++] = q[i].x0;
    v[k++] = q[i].x1;
  }
  v[k++] = x0;
  v[k++] = x1;
  sort(v, v + k);
  int sz = unique(v, v + k) - v;
  for(int i = 0; i < sz; ++i) {
    pre0[i + 1] = v[i];
  }
  max0 = sz;
  x0 = lbd(0, max0 - 1, x0);
  x1 = lbd(0, max0 - 1, x1);
  for (int i = 0; i < n; ++i) {
    q[i].x0 = lbd(0, max0 - 1, q[i].x0);
    q[i].x1 = lbd(0, max0 - 1, q[i].x1);
  }

  k = 0;
  for (int i = 0; i < n; ++i) {
    v[k++] = q[i].y0;
    v[k++] = q[i].y1;
  }
  v[k++] = y0;
  v[k++] = y1;
  sort(v, v + k);
  sz = unique(v, v + k) - v;
  for (int i = 0; i < sz; ++i) {
    pre1[i + 1] = v[i];
  }
  max1 = sz;
  y0 = lbd(0, max1 - 1, y0);
  y1 = lbd(0, max1 - 1, y1);
  for (int i = 0; i < n; ++i) {
    q[i].y0 = lbd(0, max1 - 1, q[i].y0);
    q[i].y1 = lbd(0, max1 - 1, q[i].y1);
  }

  for (int i = 0; i < n; ++i) {
    squ t = q[i];
    _ins(t.x0, t.y0, -1, ++amt);
    _ins(t.x1, t.y0, -1, ++amt);
    _ins(t.x0, t.y1, -1, ++amt);
    _ins(t.x1, t.y1, -1, ++amt);
    for (int j = t.x0 + 1; j < t.x1; ++j) {
      _ins(j, t.y0, 1, ++amt);
      _ins(j, t.y1, 3, ++amt);
    }
    for (int j = t.y0 + 1; j < t.y1; ++j) {
      _ins(t.x0, j, 2, ++amt);
      _ins(t.x1, j, 4, ++amt);
    }
  }

  if (!flg1) {
    _ins(x0, y0, -1, ++amt);
    s = amt;
  }

  if (!flg2) {
    _ins(x1, y1, -1, ++amt);
    t = amt;
  }
  
  sort(pnt, pnt + cnt, cmp0);
  for (int i = 0; i < cnt; ++i) {
    int l = i;
    int r = i;
    while (r + 1 < cnt && pnt[r + 1].x == pnt[l].x) {
      ++r;
    }
    int x = pnt[l].x;
    for (int j = l; j < r; ++j) {
      atom p = pnt[j];
      if (p.v == 1) {
        continue;
      }
      add(p.id, pnt[j + 1].id, pre1[pnt[j + 1].y] - pre1[p.y]);
    }

    for (int j = r; j > l; --j) {
      atom p = pnt[j];
      if (p.v == 3) {
        continue;
      }
      add(p.id, pnt[j - 1].id, pre1[p.y] - pre1[pnt[j - 1].y]);
    }
    i = r;
  }

  sort(pnt, pnt + cnt, cmp1);
  for (int i = 0; i < cnt; ++i) {
    int l = i;
    int r = i;
    while (r + 1 < cnt && pnt[r + 1].y == pnt[l].y) {
      ++r;
    }
    int y = pnt[l].y;
    for (int j = l; j < r; ++j) {
      atom p = pnt[j];
      if (p.v == 2) {
        continue;
      }
      add(p.id, pnt[j + 1].id, pre0[pnt[j + 1].x] - pre0[p.x]);
    }
    for (int j = r; j > l; --j) {
      atom p = pnt[j];
      if (p.v == 4) {
        continue;
      }
      add(p.id, pnt[j - 1].id, pre0[p.x] - pre0[pnt[j - 1].x]);
    }
    i = r;
  }
  return;
}


priority_queue < pair <long long, int> > que;
long long dist[MAX];
bool vis[MAX];


void spfa() {
  memset(dist, 0x3f3f, sizeof(dist));
  memset(vis, 0, sizeof(vis));
  dist[s] = 0;
  que.push(make_pair(0, s));
  while (!que.empty()) {
    int u = que.top().second;
    que.pop();
    if (vis[u]) {
      continue;
    }
    vis[u] = 1;
    if (u == t) {
      return;
    }
    for (int o = head[u]; ~o; o = e[o].nxt) {
      int v = e[o].to;
      if (dist[v] > dist[u] + e[o].w) {
        dist[v] = dist[u] + e[o].w;
        que.push(make_pair(-dist[v], v));
      }
      
    }
  }
}

inline void init() {
  memset(head, -1, sizeof(head));
  tot = 0;
  cnt = 0;
  flg1 = 0;
  flg2 = 0;
  amt = 0;
  s = 0;
  t = 0;
  while (!que.empty()) {
    que.pop();
  }
}
                 

int main() {
  T = read();
  while (T--) {
    init();
    x0 = read();
    y0 = read();
    x1 = read();
    y1 = read();
    n = read();
    for (int i = 0; i < n; ++i) {
      int a = read();
      int b = read();
      int c = read();
      int d = read();
      q[i] = squ(min(a, c), min(b, d), max(a, c), max(b, d));
    }
    build();

    spfa();
    if (dist[t] == 0x3f3f3f3f3f3f3f3f) {
      puts("No Path");
    } else {
      printf("%lld\n", dist[t]);
    }
  }
  return 0;
}
