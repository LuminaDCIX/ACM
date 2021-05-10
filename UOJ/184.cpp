#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 2e4 + 5;
const int Q = 1e5 + 5;
const int M = N << 3;

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
int m;
int q;

int ans[Q];

struct query {
  int sx;
  int sy;
  int tx;
  int ty;
  int id;

  query(int _sx = 0, int _sy = 0, int _tx = 0, int _ty = 0, int _id = 0) {
    sx = _sx;
    sy = _sy;
    tx = _tx;
    ty = _ty;
    id = _id;
  };
};

query que[Q];
query q0[Q];
query q1[Q];

inline int point(int x, int y) {
  return x * m + y;
}

struct edge {
  int nxt;
  int to;
  int val;
  int x;
  int y;
};

edge e[M];

int tot;
int head[N];

inline void add(int u, int v, int val, int x, int y) {
  e[tot].to = v;
  e[tot].nxt = head[u];
  e[tot].val = val;
  e[tot].x = x;
  e[tot].y = y;
  head[u] = tot++;
}

int dist[N];
bool vis[N];

priority_queue <pair <int, int> > pq;

inline void dijkstra(int s, int x0, int y0, int x1, int y1, int lst) {
  if (lst == -1) {
    for (int i = y0; i <= y1; ++i) {
      for (int j = x0; j <= x1; ++j) {
        int p = point(j, i);
        dist[p] = 0x3f3f3f3f;
        vis[p] = 0; 
      }
    }
  } else {
    int val = 0;
    for (int i = head[s]; ~i; i = e[i].nxt) {
      if (e[i].to == lst) {
        val = e[i].val;
        break;
      }
    }
    for (int i = y0; i <= y1; ++i) {
      for (int j = x0; j <= x1; ++j) {
        int p = point(j, i);
        dist[p] += val;
        vis[p] = 0; 
      }
    }
  }
  dist[s] = 0;
  pq.push(make_pair(0, s));
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) {
      continue;
    }
    vis[u] = 1;
    for (int o = head[u]; ~o; o = e[o].nxt) {
      int v = e[o].to;
      int x = e[o].x;
      int y = e[o].y; 
      if (x < x0 || x > x1 || y < y0 || y > y1 || vis[v]) {
        continue;
      }
      if (dist[v] > dist[u] + e[o].val) {
        dist[v] = dist[u] + e[o].val;
        pq.push(make_pair(-dist[v], v));
      }
    }
  }
}

void solve(int x0, int y0, int x1, int y1, int h, int t) {
  // cerr << h << " " << t << endl;
  // cerr << x0 << " " << x1 << " " << y0 << " " << y1 << endl;
  // for (int i = 0; i < 1000000000; ++i);
  if (h == t) {
    return;
  }
  int len0 = x1 - x0 + 1;
  int len1 = y1 - y0 + 1;
  int t0 = 0;
  int t1 = 0;
  if (len0 <= len1) {
    int mid = y0 + y1 >> 1;
    int lst = -1;
    for (int i = x0; i <= x1; ++i) {
      int p = point(i, mid);
      dijkstra(p, x0, y0, x1, y1, lst);
      for (int j = h; j < t; ++j) {
        int s = point(que[j].sx, que[j].sy);
        int to = point(que[j].tx, que[j].ty);
        // cerr << dist[s] + dist[to] << endl;
        if (dist[s] + dist[to] < ans[que[j].id]) {
          ans[que[j].id] = dist[s] + dist[to];
        }
      }
      lst = p;
      // cerr << endl;
    }
    for (int i = h; i < t; ++i) {
      if (que[i].sy < mid && que[i].ty < mid) {
        q0[t0++] = que[i];
      } else if (que[i].sy > mid && que[i].ty > mid) {
        q1[t1++] = que[i];
      }
    }
    for (int i = 0; i < t0; ++i) {
      que[h + i] = q0[i];
    }
    for (int i = 0; i < t1; ++i) {
      que[h + t0 + i] = q1[i];
    }
    solve(x0, y0, x1, mid - 1, h, h + t0);
    solve(x0, mid + 1, x1, y1, h + t0, h + t0 + t1);
  } else {
    int mid = x0 + x1 >> 1;
    int lst = -1;
    for (int i = y0; i <= y1; ++i) {
      int p = point(mid, i);
      dijkstra(p, x0, y0, x1, y1, lst);
      for (int j = h; j < t; ++j) {
        int s = point(que[j].sx, que[j].sy);
        int to = point(que[j].tx, que[j].ty);
        if (dist[s] + dist[to] < ans[que[j].id]) {
          ans[que[j].id] = dist[s] + dist[to];
        }
      }
      lst = p;
    }
    for (int i = h; i < t; ++i) {
      if (que[i].sx < mid && que[i].tx < mid) {
        q0[t0++] = que[i];
      } else if (que[i].sx > mid && que[i].tx > mid) {
        q1[t1++] = que[i];
      }
    }
    for (int i = 0; i < t0; ++i) {
      que[h + i] = q0[i];
    }
    for (int i = 0; i < t1; ++i) {
      que[h + t0 + i] = q1[i];
    }
    solve(x0, y0, mid - 1, y1, h, h + t0);
    solve(mid + 1, y0, x1, y1, h + t0, h + t0 + t1);
  }
}


int main() {

  n = read();
  m = read();
  memset(head, -1, sizeof(head));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m - 1; ++j) {
      int w = read();
      int u = point(i, j);
      int v = point(i, j + 1);
      add(u, v, w, i, j + 1);
      add(v, u, w, i, j);
    }
  }
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < m; ++j) {
      int w = read();
      int u = point(i, j);
      int v = point(i + 1, j);
      add(u, v, w, i + 1, j);
      add(v, u, w, i, j);
    }
  }
  q = read();
  memset(ans, 0x3f3f, sizeof(ans));
  for (int i = 0; i < q; ++i) {
    int sx = read() - 1;
    int sy = read() - 1;
    int tx = read() - 1;
    int ty = read() - 1;
    que[i] = query(sx, sy, tx, ty, i);
  }
  solve(0, 0, n - 1, m - 1, 0, q);
  for (int i = 0; i < q; ++i) {
    printf("%d\n", ans[i]);
  }
  return 0;
}
