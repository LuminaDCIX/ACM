// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

inline int read()
{
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (!isdigit (ch)) {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (isdigit (ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

namespace XDYIMCMI0LY
{
  const int N = 40 + 5;
  const int M = 100 + 5;
  const int V = 100005;
  const int E = 19260817;

  int n, m, p;
  int val[M][M];
  int need[N];

  int veg[N];
  int task[M][M];
  vector <int> node[M];
  vector <int> to[M];

  struct mcmf {
    int head[V], chef[V];
    int nxt[E], ver[E], cost[E], cap[E], from[E];
    int s, t, tot;

    inline int nw()
    {
      return ++tot;
    }

    inline int add_edge (int u, int v, int ca, int co)
    {
      static int tot = 1;
      ++tot;
      nxt[tot] = head[u], ver[tot] = v, cap[tot] = ca, cost[tot] = co, head[u] = tot, from[tot] = u;
      return tot;
    }

    inline int add (int u, int v, int ca, int co)
    {
      int k = add_edge (u, v, ca, co);
      add_edge (v, u, 0, -co);
      return k;
    }

    int dist[V];
    int inq[V];
    int pre[V];

    bool spfa()
    {
      for (int i = 0; i <= tot; ++i) dist[i] = 1e9, inq[i] = 0;
      dist[s] = dist[t] = 1e9;
      inq[s] = inq[t] = 0;
      dist[s] = 0, inq[s] = 0;
      queue <int> que; que.push(s);
      while (!que.empty()) {
        int u = que.front();
        que.pop(), inq[u] = 0;
        for (int o = head[u]; o; o = nxt[o]) {
          int v = ver[o];
          if (cap[o] && dist[v] > dist[u] + cost[o]) {
            dist[v] = dist[u] + cost[o], pre[v] = o;
            if (!inq[v]) inq[v] = 1, que.push(v);
          }
        }
      }
      return dist[t] != 1e9;
    }

    inline void getnewnode (int id)
    {
      int x = nw(), k = node[id].size() + 1;
      for (int i = 1; i <= n; ++i) add(task[i][id], x, 1, k * val[i][id]);
      node[id].push_back(x), to[id].push_back(add(x, t, 1, 0));
    }

    long long solve()
    {
      long long ans = 0;
      while (spfa()) {
        int x = 1e9;
        for (int o = pre[t]; o; o = pre[from[o]]) x = min(x, cap[o]);
        for (int o = pre[t]; o; o = pre[from[o]]) {
          ans += x * cost[o];
          cap[o] -= x, cap[o ^ 1] += x;
        }
        for (int i = 1; i <= m; ++i) {
          int k = to[i].back();
          if (cap[k] == 0) getnewnode(i);
        }
      }
      return ans;
    }
  } f;

  int main()
  {
    n = read();
    m = read();
    for (int i = 1; i <= n; ++i) need[i] = read(), veg[i] = f.nw();
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        val[i][j] = read();
        task[i][j] = f.nw();
      }
    f.s = V - 2;
    f.t = V - 1;
    for (int i = 1; i <= n; ++i) f.add(f.s, veg[i], need[i], 0);
    for(int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        f.add(veg[i], task[i][j], 1e9, 0);
      }
    for (int i = 1; i <= m; ++i) {
      int nw = f.nw();
      to[i].push_back(f.add (nw, f.t, 1, 0));
      node[i].push_back(nw);
      for (int j = 1; j <= n; ++j) {
        f.add(task[j][i], nw, 1, val[j][i]);
      }
    }
    cout << f.solve() << endl;
    return 0;
  }
}

int main()
{
  return XDYIMCMI0LY::main();
}

