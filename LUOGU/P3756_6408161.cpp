// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

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

const int N = 1e5 + 5;
const int V = N + N + 5;
const int E = 9260817;

int n, m, k;

map <int, int> idc[N];
map <int, int> idb[N];

struct dinic {
  int head[V];
  int ver[E], nxt[E], cap[E];
  int s, t;
  void init(int _s, int _t) {
    s = _s;
    t = _t;
  }

  void add_edge(int u, int v, int c) {
    static int tot = 1;
    ++tot;
    nxt[tot] = head[u];
    ver[tot] = v;
    cap[tot] = c;
    head[u] = tot;                   
  }
  
  void add(int u, int v, int c) {
    // cerr << u << " " << v << " " << c << endl;
    add_edge(u, v, c);
    add_edge(v, u, 0);
  }

  bool vis[V];
  int dist[V];
  
  bool bfs() {
    memset(vis, 0, sizeof(vis));
    vis[s] = 1;
    dist[s] = 0;
    queue <int> que;
    que.push(s);
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      for (int o = head[u]; o; o = nxt[o]) {
        int v = ver[o];
        if (cap[o] && !vis[v]) {
          vis[v] = 1;
          dist[v] = dist[u] + 1;
          que.push(v);
        }
      }
    }
    return vis[t];
  }

  int cur[V];

  int dfs(int u, int f) {
    if (u == t || f == 0) {
      return f;
    }
    int sum = 0;
    for (int &o = cur[u]; o; o = nxt[o]) {
      int v = ver[o];
      if (cap[o] && dist[v] == dist[u] + 1) {
        int nw = dfs(v, min(f, cap[o]));
        cap[o] -= nw;
        cap[o ^ 1] += nw;
        f -= nw;
        sum += nw;
        if (!f) {
          break;
        }
      }
    }
    return sum;
  }

  int flow() {
    int ans = 0;
    while (bfs()) {
      for (int i = 0; i <= t; ++i) {
        cur[i] = head[i];
      }
      ans += dfs(s, 1e9);
    }
    return ans;
  }
} s;

int dx[] = {0, 0, -1 ,1};
int dy[] = {1, -1, 0, 0};

int a[N];

int main() {
  // cerr << sizeof(s.ver) * 3 / 1000 / 1000 << endl;
  n = read();
  m = read();
  k = read();
  s.init(V - 2, V - 1);
  for (int i = 1; i <= k; ++i) {
    int x = read();
    int y = read();
    swap(x, y);
    a[i] = read();
    if ((y / 2) & 1) {
      if (y & 1) {
        if (!(x & 1)) {
          idb[x][y] = i;
        } else {
          idc[x][y] = i;
        }
      } else {
        if (!(x & 1)) {
          idc[x][y] = i;
        } else {
          idb[x][y] = i;
        }
      }
    } else {
      if (!(y & 1)) {
        if (!(x & 1)) {
          idb[x][y] = i;
        } else {
          idc[x][y] = i;
        }
      } else {
        if (!(x & 1)) {
          idc[x][y] = i;
        } else {
          idb[x][y] = i;
        }
      }
    }
  }
  int T = V - 1;
  int S = V - 2;
  for (int i = 1; i <= n; ++i) {
    int x = i;
    for (map <int, int>::iterator it = idc[i].begin(); it != idc[i].end(); ++it) {
      int y = it->first;
      s.add(it->second, it->second + k, a[it->second]);
      if ((y / 2) & 1) {
        s.add(it->second + k, T, 1e9);
        for (int o = 0; o < 4; ++o) {
          int xx = x + dx[o];
          int yy = y + dy[o];
          if (xx >= 1 && xx <= n) {
            if (idb[xx].find(yy) != idb[xx].end()) {
              s.add(idb[xx][yy] + k, it->second, 1e9);
            }
          }
        }
      } else {
        s.add(S, it->second, 1e9);
        for (int o = 0; o < 4; ++o) {
          int xx = x + dx[o];
          int yy = y + dy[o];
          if (xx >= 1 && xx <= n) {
            if (idb[xx].find(yy) != idb[xx].end()) {
              s.add(it->second + k, idb[xx][yy], 1e9);
            }
          }
        }
      }
    } 
  }

  for (int i = 1; i <= n; ++i) {
    for (map <int, int>::iterator it = idb[i].begin(); it != idb[i].end(); ++it) {
      s.add(it->second, it->second + k, a[it->second]);
      int y = it->first;
      if (!((y / 2) & 1)) {
        if (!(y & 1)) {
          int yy = y - 1;
          int xx = i;
          if (idb[xx].find(yy) != idb[xx].end()) {
            s.add(it->second + k, idb[xx][yy], 1e9);
          }
        } else {
          int yy = y + 1;
          int xx = i;
          if (idb[xx].find(yy) != idb[xx].end()) {
            s.add(it->second + k, idb[xx][yy], 1e9);
          }
        }
      }
    }
  }
  printf("%d\n", s.flow());
  return 0;
}
