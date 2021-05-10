#include <bits/stdc++.h>

using namespace std;


namespace XDYIMCMI0LY {

  const int N = 415000 * 2 + 5;
  const int M = N * 2 + 5;
  const int LOG = 21;

  int n;
  
  int m;

  int faval[N];
  
  int head[N];
  int tot;
  int ver[M];
  int val[M];
  int nxt[M];
  int del[M];
  int from[M];

  int mn[N * 2][LOG];
  int id[N * 2][LOG];
  int len[N];
  int in[N];
  int dfn;
  int seq[N * 2];
  
  long long dep[N];
  int deg[N];
  inline int lca(int a, int b) {
    int l = min(in[a], in[b]);
    int r = max(in[a], in[b]);
    int k = log(r - l + 1) / log(2);
    int ans = id[l][k];
    if (mn[r - (1 << k) + 1][k] < mn[l][k]) {
      ans = id[r - (1 << k) + 1][k];
    }
    return ans;
  }

  inline long long dist(int a, int b) {

    if (a == 0 ||  b == 0) {
      return -1e18;
    }
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
  }
  
  void add(int u, int v, int w) {
    ++tot;
    ver[tot] = v;
    nxt[tot] = head[u];
    val[tot] = w;
    from[tot] = u;
    head[u] = tot;
  }
  
  void add_edge(int u, int v, int w = 0) {
    add(v, u, w);
    add(u, v, w);
    ++deg[u];
    ++deg[v];
  }

  vector<int> g[N];

  void dfs(int u, int fa) {
    in[u] = ++dfn;
    seq[dfn] = u;
    len[u] = len[fa] + 1;
    for (int o = head[u]; o; o = nxt[o]) {
      int v = ver[o];
      if (v == fa) {
        continue;
      }
      dep[v] = dep[u] + val[o];
      dfs(v, u);
      
      seq[++dfn] = u;
    }
  }

  long long ans;
  
  int top;
  
  struct node *p[N * LOG];
  struct node *E;
  struct node {
    node *l, *r;
    int id;
    long long lmx;
    long long rmx;
    long long val;

    void* operator new(size_t) {
      static int flg = 0;
      static node pool[N * LOG];
      if (!flg) {
        flg = 1;
        for (int i = 0; i < N * LOG; ++i) {
          p[i] = &pool[i];
        }
        top = 1;
        E = p[0];
        E->l = E->r = E;
        E->val = E->lmx = E->rmx = -1e18;
      }
      p[top]->l = p[top]->r = E;
      p[top]->val = p[top]->lmx = p[top]->rmx = -1e18;
      return p[top++];
    }

    void operator delete(void* pp) {
      p[top--] = (node*) pp;
    }
  };

  
  int ch[N + M][2];
  int to[N + M][2];
  int pre[N + M];
  long long t[N];

  node* merge(node *a, node *b, long long p) {
    if (b == E) {
      return a;
    }
    if (a == E) {
      return b;
    }

    
    ans = max(ans, (a->lmx + b->rmx + a->val) / 2 - p);
    ans = max(ans, (a->rmx + b->lmx + a->val) / 2 - p);
    a->lmx = max(a->lmx, b->lmx);
    a->rmx = max(a->rmx, b->rmx);
    
    a->l = merge(a->l, b->l, p);
    a->r = merge(a->r, b->r, p);
    
    delete b;
    return a;
  }

  node* new_link(int x) {
    node *p = new node;
    p->id = x;
    int lef = x;
    x = pre[x];
    while (x) {
      int dir = 0;
      if (ch[x][1] == p->id) {
        dir = 1;
      }
      node *nw = new node;
      nw->id = x;
      nw->val = val[x - n];
      if (dir) {
        nw->r = p;
        nw->rmx = dist(lef, to[x][1]) + dep[lef];
      } else {
        nw->l = p;
        nw->lmx = dist(lef, to[x][0]) + dep[lef];
      }
      
      p = nw;
      x = pre[x];
    }
    return p;
  }


  int all_siz;
  int siz[N];
  int e_id;
  int bst;


  node *root[N];
  
  void find_e(int u, int fa) {
    siz[u] = 1;
    for (int o = head[u]; o; o = nxt[o]) {
      int v = ver[o];
      if (v == fa || del[o]) {
        continue;
      }
      find_e(v, u);
      siz[u] += siz[v];
      int cur = max(siz[v], all_siz - siz[v]);
      if (e_id == 0 || cur < bst) {
        e_id = o;
        bst = cur;
      }
    }
  }

  int solve(int u, int cur_siz) {
    all_siz = cur_siz;
    e_id = 0;
    find_e(u, 0);


    if (e_id == 0) {
      return u;
    }

    del[e_id] = del[e_id ^ 1] = 1;

    int a = from[e_id];
    int b = ver[e_id];

    // 
    // 

    // int siza = siz[a];
    // int sizb = siz[b];

    int siza, sizb;
    if (siz[a] < siz[b]) {
      siza = siz[a];
      sizb = cur_siz - siza;
    } else {
      sizb = siz[b];
      siza = cur_siz - sizb;
    }

    u = n + e_id;
    ch[u][0] = solve(a, siza);
    to[u][0] = a;
    ch[u][1] = solve(b, sizb);
    to[u][1] = b;
    pre[ch[u][0]] = u;
    pre[ch[u][1]] = u;

    return u;
  }


  void dfs0(int u, int fa) {
    for (int o = head[u]; o; o = nxt[o]) {
      int v = ver[o];
      if (v == fa) {
        continue;
      }
      dfs0(v, u);
      faval[v] = val[o];
      g[u].push_back(v);
    }
  }

  long long dep2[N];
  int head2[N];
  int nxt2[M];
  int ver2[M];
  int val2[M];

  void add2(int u, int v, int w) {
    static int T = 0;
    ++T;
    nxt2[T] = head2[u];
    ver2[T] = v;
    val2[T] = w;
    head2[u] = T;
  }


  void calc(int u, int fa) {
    root[u] = E;
    for (int o = head2[u]; o; o = nxt2[o]) {
      int v = ver2[o];
      if (v == fa) {
        continue;
      }
      dep2[v] = dep2[u] + val2[o];
      calc(v, u);
      root[u] = merge(root[u], root[v], dep2[u]);
    }
    root[u] = merge(root[u], new_link(u), dep2[u]);
  }

  void _main() {
    cin >> n;
    m = n;
    for (int i = 1; i < n; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      add_edge(u, v, w);
    }

    dfs0(1, 0); 

    
    tot = 1;
    memset(head, 0, sizeof(head));

    for (int i = 1; i <= n; ++i) {
      vector<int> x = g[i];
      vector<int> y;
      if (x.size() == 0) {
        continue;
      }
      while (x.size() > 2) {
        for (int j = 0; j < (int) x.size(); j += 2) {
          ++n;
          add_edge(n, x[j], faval[x[j]]);
          if (j + 1 < (int) x.size()) {
            add_edge(n, x[j + 1], faval[x[j + 1]]);
          }
          y.push_back(n);
        }
        swap(x, y);
        y.clear();
      }
      add_edge(i, x[0], faval[x[0]]);
      if (x.size() == 2) {
        add_edge(i, x[1], faval[x[1]]);
      }
    }
    


    dfs(1, 0);

    for (int i = 1; i <= dfn; ++i) {
      mn[i][0] = len[seq[i]];
      id[i][0] = seq[i];
    }
    for (int j = 1; j < LOG; ++j) {
      for (int i = 1; i <= dfn; ++i) {
        mn[i][j] = mn[i][j - 1];
        id[i][j] = id[i][j - 1];
        int v = i + (1 << j >> 1);
        if (v <= dfn && mn[v][j - 1] < mn[i][j]) {
          mn[i][j] = mn[v][j - 1];
          id[i][j] = id[v][j - 1];
        }
      }
    }


    cerr << n << endl;
    solve(1, n);

    new node;
    memcpy(t, dep, sizeof(t));
    for (int i = 1; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      add2(u, v, w);
      add2(v, u, w);
    }

    calc(1, 0);
    for (int i = 1; i <= m; ++i) {
      ans = max(ans, t[i] - dep2[i]);
    }
    cout << ans << endl;
  }
}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  XDYIMCMI0LY::_main();
  return 0;
}