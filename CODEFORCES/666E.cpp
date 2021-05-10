#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 5;
const int MAX = N * 2 + 5;
const int MAXSN = N * 19 + 5;

int n;
int m;

struct SuffixAutomaton {
  int fa[MAX];
  int nxt[MAX][26];
  int len[MAX];
  int root;
  int last;
  int tot;

  void init() {
    root = 1;
    last = root;
    tot = 2;
  }

  int newnode(int x) {
    len[tot] = x;
    return tot++;
  }

  void extend(int x) {
    int p = last;
    int t = nxt[p][x];
    if (t && len[t] == len[p] + 1) {
      last = t;
      return;
    }
    int np = newnode(len[p] + 1);
    while (p && nxt[p][x] == 0) {
      nxt[p][x] = np;
      p = fa[p];
    }
    if (!p) {
      fa[np] = root;
    } else {
      int q = nxt[p][x];
      if (len[q] == len[p] + 1) {
        fa[np] = q;
      } else {
        int nq = newnode(len[p] + 1);
        memcpy(nxt[nq], nxt[q], sizeof(nxt[q]));
        fa[nq] = fa[q];
        fa[q] = nq;
        fa[np] = nq;
        while (p && nxt[p][x] == q) {
          nxt[p][x] = nq;
          p = fa[p];
        }
      }
    }
    last = np;
  }
};

SuffixAutomaton s;

struct SegmentTree {
  int l[MAXSN];
  int r[MAXSN];
  int mx[MAXSN];
  int id[MAXSN];
  int tot;

  void init() {
    tot = 1;
  }
  
  int newnode(int _id) {
    id[tot] = _id;
    return tot++;
  }

  void update(int o) {
    int lc = l[o];
    int rc = r[o];
    if (mx[lc] >= mx[rc]) {
      mx[o] = mx[lc];
      id[o] = id[lc];
    } else {
      mx[o] = mx[rc];
      id[o] = id[rc];
    }
  }
  
  int insert(int o, int ll, int rr, int p, int v) {
    if (!o) {
      o = newnode(ll);
    }
    if (ll == p && rr == p) {
      mx[o] += v;
      return o;
    }
    int mid = ll + rr >> 1;
    if (p <= mid) {
      l[o] = insert(l[o], ll, mid, p, v);
    } else {
      r[o] = insert(r[o], mid + 1, rr, p, v);
    }
    update(o);
    return o;
  }

  int merge(int o1, int o2, int ll, int rr) {
    if (!o1) {
      return o2;
    }
    if (!o2) {
      return o1;
    }
    if (ll == rr) {
      mx[o1] += mx[o2];
      id[o1] = ll;
      return o1;
    }
    int mid = ll + rr >> 1;
    l[o1] = merge(l[o1], l[o2], ll, mid);
    r[o1] = merge(r[o1], r[o2], mid + 1, rr);
    update(o1);
    return o1;
  }

  void query(int o, int ll, int rr, int li, int ri, int &pos, int &ans) {
    if (!o) {
      return;
    }
    if (ll >= li && rr <= ri) {
      if (mx[o] == ans) {
        pos = min(pos, id[o]);
      } else if (mx[o] > ans) {
        pos = id[o];
        ans = mx[o];
      }
      return;
    }
    int mid = ll + rr >> 1;
    if (li <= mid) {
      query(l[o], ll, mid, li, ri, pos, ans);
    }
    if (ri > mid) {
      query(r[o], mid + 1, rr, li, ri, pos, ans);
    }
  }
};

SegmentTree t;

char str[N];
char ins[N];

vector <int> g[MAX];

int c[MAX];
int l[MAX];
int lim[MAX];

int fa[MAX][20];

int pos[N];

void init() {
  int (*nxt)[26] = s.nxt;
  int *fa = s.fa;
  int len = strlen(str);
  int now = s.root;
  int nowlen = 0;
  for (int i = 0; i < len; ++i) {
    int x = str[i] - 'a';
    while (now && nxt[now][x] == 0) {
      now = fa[now];
      nowlen = s.len[now];
    }
    if (!now) {
      now = s.root;
    } else {
      now = nxt[now][x];
      ++nowlen;
    }
    pos[i] = now;
    lim[i] = nowlen;
  }
}

int find(int now, int len) {
  for (int i = 19; i >= 0; --i) {
    int k = fa[now][i];
    if (k != 0) {
      if (l[k] >= len) {
        now = k;
      }
    }
  }
  return now;
}

int ans[N][2];

struct node {
  int l;
  int r;
  int id;

  node (int _l, int _r, int _id) {
    l = _l;
    r = _r;
    id = _id;
  }
};

vector <node> f[MAX];

void dfs(int u) {
  for (int i = 0; i < g[u].size(); ++i) {
    int v = g[u][i];
    dfs(v);
    c[u] = t.merge(c[u], c[v], 0, n - 1);
  }
  for (int i = 0; i < f[u].size(); ++i) {
    int p = f[u][i].l;
    int a = 0;
    t.query(c[u], 0, n - 1, f[u][i].l, f[u][i].r, p, a);
    ans[f[u][i].id][0] = p;
    ans[f[u][i].id][1] = a;
  }
}

int main() {
  s.init();
  t.init();
  scanf("%s", str);
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%s", ins);
    s.last = s.root;
    int len = strlen(ins);
    for (int j = 0; j < len; ++j) {
      s.extend(ins[j] - 'a');
      int now = s.last;
      if (!c[now]) {
        c[now] = t.newnode(i);
      }
      c[now] = t.insert(c[now], 0, n - 1, i, 1);
    }
  }
  init();
  for (int i = 2; i < s.tot; ++i) {
    int u = s.fa[i];
    int v = i;
    l[v] = s.len[i];
    g[u].push_back(v);
    fa[v][0] = u;
  }

  for (int i = 1; i < 19; ++i) {
    for (int j = 2; j < s.tot; ++j) {
      fa[j][i] = fa[fa[j][i - 1]][i - 1];
    }
  }
  scanf("%d", &m);
  for (int i = 0, li, r, pl, pr; i < m; ++i) {
    scanf("%d %d %d %d", &li, &r, &pl, &pr);
    --li;
    --r;
    --pl;
    --pr;
    if (lim[pr] < pr - pl + 1) {
      ans[i][0] = li;
      continue;
    }
    int k = find(pos[pr], pr - pl + 1);
    f[k].emplace_back(li, r, i);
  }
  dfs(s.root);
  for (int i = 0; i < m; ++i) {
    printf("%d %d\n", ans[i][0] + 1, ans[i][1]);
  }
  return 0;
}
