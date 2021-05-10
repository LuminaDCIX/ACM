#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>

inline int read() {
  int x;
  scanf("%d", &x);
  return x;
}

using namespace std;

const int N = 1000 + 5;
const int M = 1000 * 1000 + 5;

int n;
long long r;
long long h;

int tot;
int head[N];

struct edge {
  int to;
  int nxt;
};

edge e[M];

inline void add(int u, int v) {
  e[tot].to = v;
  e[tot].nxt = head[u];
  head[u] = tot++;
}

int src = N - 2;
int tar = N - 1;

struct point {
  long long x;
  long long y;
  long long z;
};

point p[N];

inline unsigned long long sqr(unsigned long long x) {
  return x * x;
}

inline unsigned long long dist(point a, point b) {
  return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z);
}

bool vis[N];

queue <int> que;

inline void bfs() {
  memset(vis, 0, sizeof(vis));
  que.push(src);
  vis[src] = 1;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    for (int o = head[u]; ~o; o = e[o].nxt) {
      int v = e[o].to;
      if (vis[v]) {
	continue;
      }
      vis[v] = 1;
      que.push(v);
    }
  }
}

int main() {
  int ks = read();
  while (ks--) {
    n = read();
    h = read();
    r = read();
    memset(head, -1, sizeof(head));
    tot = 0;
    for (int i = 0; i < n; ++i) {
      p[i].x = read();
      p[i].y = read();
      p[i].z = read();
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
	if (i == j) {
	  continue;
	}
	if (dist(p[i], p[j]) <= 4 * r * r) {
	  add(i, j);
	}
      }
    }
    for (int i = 0; i < n; ++i) {
      if (abs(p[i].z) <= r) {
	add(i, src);
	add(src, i);
      }
    }
    for (int i = 0; i < n; ++i) {
      if (abs(p[i].z - h) <= r) {
	add(i, tar);
	add(tar, i);
      }
    }
    bfs();
    puts(vis[tar] ? "Yes" : "No");
  }
  return 0;
}
