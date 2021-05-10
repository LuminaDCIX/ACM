#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 5;
const int LOG = 21;

typedef vector <int> vi;;

int n;

vi ver[N];
int siz[N];

inline int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  for (; ch < '0' || ch > '9'; ch = getchar()) {
    f = (ch == '-') ? -1 : 1;
  }
  for (; ch >= '0' && ch <= '9'; ch = getchar()) {
    x = x * 10 + ch - '0';
  }
  return f * x;
}

int fa[N][LOG], dep[N];
int dfn[N], dfs_cnt;

void dfs(int u) {
  siz[u] = 1;
  dfn[u] = ++dfs_cnt;
  for (int o = 0; o < (int) ver[u].size(); ++o) {
    int v = ver[u][o];
    if (v == fa[u][0]) {
      continue;
    }
    fa[v][0] = u;
    dep[v] = dep[u] + 1;
    dfs(v);
    siz[u] += siz[v];
  }
}

void init() {
  for (int j = 1; j < LOG; ++j) {
    for (int i = 1; i <= n; ++i) {
      fa[i][j] = fa[fa[i][j - 1]][j - 1];
    }
  }
}

int lca(int x, int y) {
  if (dep[x] < dep[y]) {
    swap(x, y);
  }
  for (int i = LOG - 1; i >= 0; --i) {
    x = (dep[fa[x][i]] >= dep[y]) ? fa[x][i] : x;
  }
  if (x == y) {
    return x;
  }
  for (int i = LOG - 1; i >= 0; --i) {
    if (fa[x][i] != fa[y][i]) {
      x = fa[x][i];
      y = fa[y][i];
    }
  }
  return fa[x][0];
}

bool cmp(int a, int b) {
  return dfn[a] < dfn[b];
}

inline int jump(int x, int len) {
  for (int i = LOG - 1; i >= 0; --i) {
    if (len & (1 << i)) {
      x = fa[x][i];
    }
  }
  return x;
}

struct virtual_tree {

  vi ver[N];
  vi val[N];
  bool p[N];
  
  int stk[N], top;

  void add(int u, int v, int c) {
    ver[u].push_back(v);
    val[u].push_back(c);
  }

  pair <int, int> dp0[N], dp1[N];
  int son0[N], son1[N];
  int ans[N];
  
  void dfs1(int u) {
    if (p[u]) {
      dp0[u] = dp1[u] = make_pair(0, u);
      son0[u] = son1[u] = u;
    } else {
      dp0[u] = dp1[u] = make_pair(1e9, 0);
      son0[u] = son1[u] = 0;
    }
    for (int o = 0; o < (int) ver[u].size(); ++o) {
      int v = ver[u][o];
      dfs1(v);
      pair <int, int> nw = make_pair(dp0[v].first + val[u][o], dp0[v].second);
      if (nw <= dp0[u]) {
        dp1[u] = dp0[u];
        son1[u] = son0[u];
        dp0[u] = nw;
        son0[u] = v;
      } else if (nw < dp1[u]) {
        dp1[u] = nw;
        son1[u] = v;
      }
    }
  }

  void dfs2(int u, pair <int, int> len) {
    dp0[u] = min(dp0[u], len);
    for (int o = 0; o < (int) ver[u].size(); ++o) {
      int v = ver[u][o];
      pair <int, int> x;
      if (son0[u] == v) {
        x = dp1[u];
      } else {
        x = dp0[u];
      }
      x = min(x, len);
      x.first += val[u][o];
      dfs2(v, x);
    }
    // ++ans[dp0[u].second];
    // cerr << u << " " << dp0[u].second << endl;
  }

  void calc(int u, int v, int len) {
    // 
    if (len == 1) {
      return;
    }
    // cerr << u << " " << v << " " << len;
    int tim = 0;
    int l = 1;
    int r = len - 1;
    while (l <= r) {
      int mid = (l + r) >> 1;
      int lv = mid + dp0[v].first;
      int lu = len - mid + dp0[u].first;
      if ((lv < lu) || (lv == lu && dp0[v].second <= dp0[u].second)) {
        tim = mid;
        l = mid + 1;
      } else r = mid - 1;
    }
    int x = jump(v, tim);
    // cerr << " " << x << endl;
    ans[dp0[v].second] += siz[x] - siz[v];
    // cerr << siz[x] - siz[v] << endl;
    int t = jump(v, len - 1);
    ans[dp0[u].second] += siz[t] - siz[x];
    // cerr << siz[u] - siz[v] << endl;
  }

  void dfs3(int u) {
    int sum = siz[u];
    for (int o = 0; o < (int) ver[u].size(); ++o) {
      int v = ver[u][o];
      calc(u, v, val[u][o]);
      int len = val[u][o] - 1;
      int t = jump(v, len);
      sum -= siz[t];
      dfs3(v);
    }
    ans[dp0[u].second] += sum;
  }

  void dfs4(int u) {
    for (int o = 0; o < (int) ver[u].size(); ++o) {
      int v = ver[u][o];
      dfs4(v);
    }
    p[u] = 0;
    ver[u].clear();
    val[u].clear();
  }
  
  void solve(vi &b) {
    // cerr << endl;
    vi x = b;
    sort(b.begin(), b.end(), cmp);
    top = 0;
    int t;
    if (b[0] != 1) {
      stk[top++] = 1;
      t = 0;
    } else {
      stk[top++] = b[0];
      t = 1;
    }
    p[b[0]] = 1;
    for (int i = t; i < (int) b.size(); ++i) {
      int nw = b[i];
      p[nw] = 1;
      if (!top) {
        stk[top++] = nw;
        continue;
      }
      int c = lca(nw, stk[top - 1]);
      while (dfn[c] < dfn[stk[top - 1]]) {
        if (top > 1 && dfn[c] >= dfn[stk[top - 2]]) {
          add(c, stk[top - 1], dep[stk[top - 1]] - dep[c]);
          --top;
          if (c != stk[top - 1]) {
            stk[top++] = c;
          }
          break;
        }
        if (top == 1) {
          add(c, stk[top - 1], dep[stk[top - 1]] - dep[c]);
          --top;
          stk[top++] = c;
          break;
        }
        add(stk[top - 2], stk[top - 1], dep[stk[top - 1]] - dep[stk[top - 2]]);
        --top;
        c = lca(nw, stk[top - 1]);
      }
      stk[top++] = nw;
    }
    while (top > 1){
      add(stk[top - 2], stk[top - 1], dep[stk[top - 1]] - dep[stk[top - 2]]);
      --top;
    }
    dfs1(1);
    dfs2(1, make_pair(1e9, 0));
    dfs3(1);
    dfs4(1);
    for (int i = 0; i < (int) b.size(); ++i) {
      printf("%d ", ans[x[i]]);
      ans[x[i]] = 0;
    }
    puts("");
  }
};

virtual_tree vitree;

int main() {
  n = read();
  for (int i = 1; i <= n - 1; ++i) {
    int u = read();
    int v = read();
    ver[u].push_back(v);
    ver[v].push_back(u);
  }
  dep[1] = 1;
  dfs(1);
  init();
  int q = read();
  while (q--) {
    int m = read();
    vi v;
    for (int i = 1; i <= m; ++i) {
      v.push_back(read());
    }
    vitree.solve(v);
  }
  return 0;
}