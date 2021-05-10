#include <bits/stdc++.h>

using namespace std;
#define int long long 
inline long long read() {
  int f = 1;
  long long x = 0;
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

const int N = 100000 + 5;
const int LOG = 19;
const int MAX = N * LOG * 2 + 5;

int n;

struct Sgt {
  int tot;
  int siz[MAX], lc[MAX], rc[MAX];
  int root[N];

  int add(int o, int ll, int rr, int v) {
    int p = ++tot;
    siz[p] = siz[o];
    lc[p] = lc[o];
    rc[p] = rc[o];
    if (ll == rr) {
      ++siz[p];
      return p;
    }
    int mid = (ll + rr) >> 1;
    if (v <= mid) {
      lc[p] = add(lc[o], ll, mid, v);
    } else {
      rc[p] = add(rc[o], mid + 1, rr, v);
    }
    siz[p] = siz[lc[p]] + siz[rc[p]];
    return p;
  }

  int find(int x, int y, int ll, int rr, int k) {
    if (ll == rr) {
      return ll;
    }
    int mid = (ll + rr) >> 1;
    int t = siz[lc[y]] - siz[lc[x]];
    if (t >= k) {
      return find(lc[x], lc[y], ll, mid, k);
    } else {
      return find(rc[x], rc[y], mid + 1, rr, k - t);
    }
  }
  
  int kth(int l, int r, int k) {
    return find(root[l - 1], root[r], 1, n, k);
  }

  void add(int p, int v) {
    root[p] = add(root[p - 1], 1, n, v);
  }
} sgt;

struct orgtree {
  vector <int> ver[N];
  int fa[N][LOG], dep[N];
  
  inline int len(int u, int v) {
    return abs(dep[v] - dep[u]);
  }
  
  void add(int u, int v) {
    ver[v].push_back(u);
    ver[u].push_back(v);
  }

  int dfs_cnt;
  int b[N], e[N], siz[N];

  void dfs(int u) {
    b[u] = ++dfs_cnt;
    sgt.add(dfs_cnt, u);
    siz[u] = 1;
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
    e[u] = dfs_cnt;
  }

  int kth(int r, int k) {
    return sgt.kth(b[r], e[r], k);
  }

  int lca(int x, int y) {
    if (dep[x] < dep[y]) {
      swap(x, y);
    }
    for (int i = LOG - 1; i >= 0; --i) {
      if (dep[fa[x][i]] >= dep[y]) {
        x = fa[x][i];
      }
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

  int solve(int x, int y) {
    return dep[x] + dep[y] - dep[lca(x, y)] * 2;
  }

  void init() {
    for (int i = 1; i < LOG; ++i) {
      for (int j = 1; j <= n; ++j) {
        fa[j][i] = fa[fa[j][i - 1]][i - 1];
      }
    }
  }
} ori;

struct bigtree {
  int topfa[N], top[N];
  int blkfa[N][LOG], tar[N][LOG];
  int tot;
  int len[N][LOG];
  int dep[N];
  
  void init() {
    memset(topfa, -1, sizeof(topfa));
    memset(blkfa, -1, sizeof(blkfa));
    memset(tar, -1, sizeof(tar));
    memset(top, -1, sizeof(top));
    memset(len, -1, sizeof(len));
    
    top[0] = 1;
    dep[0] = 1;
  }
  
  void inc(int x, int bid, int v) {
    ++tot;
    // cerr << x << " " << bid << " " << v << endl;
    top[tot] = x;
    topfa[tot] = v;
    dep[tot] = dep[bid] + 1;
    
    blkfa[tot][0] = bid;
    len[tot][0] = 1;
    tar[tot][0] = v;
    
    for (int i = 1 ; i < LOG; ++i) {
      if (blkfa[tot][i - 1] == -1 || blkfa[blkfa[tot][i - 1]][i - 1] == -1) {
        continue;
      }
      int nwblk = blkfa[tot][i - 1];
      int nwnod = tar[tot][i - 1];
      int cur = len[tot][i - 1];
      cur += ori.len(top[nwblk], nwnod);
      cur += len[nwblk][i - 1];
      
      len[tot][i] = cur;
      blkfa[tot][i] = blkfa[nwblk][i - 1];
      tar[tot][i] = tar[nwblk][i - 1];
    }
  }

  int lca(int x, int y) {
    if (dep[x] < dep[y]) {
      swap(x, y);
    }
    for (int i = LOG - 1; i >= 0; --i) {
      if (blkfa[x][i] != -1 && dep[blkfa[x][i]] >= dep[y]) {
        x = blkfa[x][i];
      }
    }
    if (x == y) {
      return x;
    }
    for (int i = LOG - 1; i >= 0; --i) {
      if (blkfa[x][i] != -1 && blkfa[y][i] != -1 && blkfa[x][i] != blkfa[y][i]) {
        x = blkfa[x][i];
        y = blkfa[y][i];
      }
    }
    return blkfa[x][0];
  }

  int gettar(int x, int l, int &ans) {
    int v = -1;
    int p = x;
    for (int i = LOG - 1; i >= 0; --i) {
      if (blkfa[p][i] != -1 && (l & (1 << i))) {
        l -= (1 << i);
        v = tar[p][i];
        ans += len[p][i];
        p = blkfa[p][i];
        if (l) {
          ans += ori.len(top[p], v);
        }
      }
    }
    return v;
  }
} nw;

long long sum[N];

signed main() {
  n = read();
  int m = read();
  int q = read();
  for (int i = 1; i < n; ++i) {
    int u = read();
    int v = read();
    ori.add(u, v);
  }
  ori.dep[1] = 1;
  ori.dfs(1);
  ori.init();
  sum[0] = n;
  sum[-1] = 0;
  nw.init();
  for (int i = 1; i <= m; ++i) {
    int a = read();
    int b = read();
    int blkid = lower_bound(sum, sum + i, b) - sum;
    sum[i] = sum[i - 1] + ori.siz[a];
    // cerr << " b = " << ori.kth(nw.top[blkid], b - (blkid == 0 ? 0 : sum[blkid - 1])) << endl;
    nw.inc(a, blkid, ori.kth(nw.top[blkid], b - (blkid == 0 ? 0 : sum[blkid - 1])));
  }
  // cerr << "hi" << endl;
  for (int i = 1; i <= q; ++i) {
    long long x = read();
    long long y = read();
    int blkx = lower_bound(sum, sum + m + 1, x) - sum;
    int blky = lower_bound(sum, sum + m + 1, y) - sum;
    int orix = ori.kth(nw.top[blkx], x - (blkx == 0 ? 0 : sum[blkx - 1]));
    int oriy = ori.kth(nw.top[blky], y - (blky == 0 ? 0 : sum[blky - 1]));
    // cerr << orix << " " << oriy << endl;
    // cerr << blkx << " " << blky << endl;
    if (blkx == blky) {
      printf("%lld\n", ori.solve(orix, oriy));
    } else {
      if (nw.lca(blkx, blky) == blkx) {
        swap(blkx, blky);
        swap(orix, oriy);
        swap(x, y);
      }
      if (nw.lca(blkx, blky) == blky) {
        // cerr << "1" << endl;
        int ans = ori.len(nw.top[blkx], orix);
        // cerr << ans << endl;
        int tar = nw.gettar(blkx, nw.dep[blkx] - nw.dep[blky], ans);
        // cerr << tar << endl;
        // cerr << ans << endl;
        // cerr << oriy << " " << tar << endl;
        // cerr << ori.solve(tar, oriy) << endl;
        ans += ori.solve(tar, oriy);
        printf("%lld\n", ans);
      } else {
        // cerr << "---------------" << i << "------------------" << endl;
        // cerr << orix << " " << oriy << endl;
        // cerr << blkx << " " << blky << endl;
        int ans = ori.len(nw.top[blkx], orix);
        ans += ori.len(nw.top[blky], oriy);
        int c = nw.lca(blkx, blky);
        // cerr << "c = " << c << endl;
        int f1 =  nw.gettar(blkx, nw.dep[blkx] - nw.dep[c], ans);
        int f2 =  nw.gettar(blky, nw.dep[blky] - nw.dep[c], ans);
        // cerr << "f1 = " << f1 << " " << "f2 = " << f2 << endl;
        ans += ori.solve(f1, f2);
        printf("%lld\n", ans);
      }
    }
  }
  return 0;
}