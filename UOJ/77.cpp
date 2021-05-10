#include <map>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 5000 + 5;
const int MAXNODE = 5000 * 32 + 5;
const int MAXN = 5000 * 2 + MAXNODE;
const int MAXM = 2700000 + 5;
const int S = MAXN - 2;
const int T = MAXN - 1;
const int inf = 1e9;

int n;

int read() {
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  };
  return x;
}

namespace G {
  
  struct edge {
    edge *nxt;
    edge *r;
    int cap;
    int to;

    edge *set(int _to, int _cap, edge* _nxt) {
      to = _to;
      cap = _cap;
      nxt = _nxt;
      return this;
    }
  };
  
  edge *head[MAXN];
  edge *cur[MAXN];
  edge e[MAXM];
  edge *top = e;

  edge *make(int u, int v, int cap) {
    return head[u] = (top++)->set(v, cap, head[u]);
  }

  edge *add(int u, int v, int cap) {
    edge *st = make(u, v, cap);
    edge *ts = make(v, u, 0);
    st->r = ts;
    ts->r = st;
  }
  
  int dist[MAXN];
  int vis[MAXN];

  bool bfs() {
    memset(vis, 0, sizeof(vis));
    vis[S] = 1;
    queue <int> que;
    que.push(S);
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      for (edge *o = head[u]; o; o = o->nxt) {
        int v = o->to;
        if (!vis[v] && o->cap) {
          dist[v] = dist[u] + 1;
          vis[v] = 1;
          que.push(v);
        }
      }
    }
    return vis[T];
  }

  int dfs(int u, int f) {
    if (u == T || f == 0) {
      return f;
    }
    int sum = 0;
    for (edge *&o = cur[u]; o; o = o->nxt) {
      int v = o->to;
      int s = 0;
      if (dist[v] == dist[u] + 1 && o->cap && (s = dfs(v, min(f, o->cap))) > 0) {
        o->cap -= s;
        o->r->cap += s;
        f -= s;
        sum += s;
        if (f == 0) {
          break;
        }
      }
    }
    return sum;
  }
  
  int dinic() {
    int ans = 0;
    while (bfs()) {
      for (int i = 0; i < MAXN; ++i) {
        cur[i] = head[i];
      }
      ans += dfs(S, inf);
    }
    return ans;
  }
}

namespace D {

  int top = 2 * 5000 + 5;

  struct node {
    node *lc;
    node *rc;
    int id;
  };

  node pool[MAXNODE];
  node *ptr = pool;
  node *t[N];
  node *null;

  node *newnode() {
    return ptr++;
  }

  node *insert(node *o, int ll, int rr, int v, int from) {
    node *p = newnode();
    *p = *o;
    p->id = top++;

    G::add(o->id, p->id, inf);
      
    if (ll == rr) {
      G::add(from, p->id, inf);
      return p;
    }

    int mid = ll + rr >> 1;
    if (v <= mid) {
      p->lc = insert(o->lc, ll, mid, v, from);
      G::add(p->lc->id, p->id, inf);
    } else {
      p->rc = insert(o->rc, mid + 1, rr, v, from);
      G::add(p->rc->id, p->id, inf);
    }
    return p;
  }

  void query(node *o, int ll, int rr, int l, int r, int to) {
    if (o == null) {
      return;
    }
    if (ll >= l && rr <= r) {
       G::add(o->id, to, inf);
       return;
    }
    int mid = ll + rr >> 1;
    if (l <= mid) {
      query(o->lc, ll, mid, l, r, to);
    }
    if (r > mid) {
      query(o->rc, mid + 1, rr, l, r, to);
    }
  }

  void init() {
    null = newnode();
    null->lc = null;
    null->rc = null;
    t[0] = null;
  }
}

int a[N];
int w[N];
int b[N];
int l[N];
int r[N];
int p[N];

int main() {  
  n = read();
  D::init();
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
    b[i] = read();
    w[i] = read();
    l[i] = read();
    r[i] = read();
    p[i] = read();
  }
  vector <int> v;
  for (int i = 1; i <= n; ++i) {
    v.push_back(a[i]);
    v.push_back(l[i]);
    v.push_back(r[i]);
  }
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  int lim = v.size();
  map <int, int> mp;
  for (int i = 0; i < lim; ++i) {
    mp[v[i]] = i;
  } 
  for (int i = 1, ai, wi, bi, li, ri, pi; i <= n; ++i) {
    ai = mp[a[i]];
    bi = b[i];
    wi = w[i];
    li = mp[l[i]];
    ri = mp[r[i]];
    pi = p[i];
    G::add(S, i, wi);
    G::add(i, T, bi);
    G::add(i + 5000, i, pi);
    D::query(D::t[i - 1], 0, lim, li, ri, i + 5000);
    D::t[i] = D::insert(D::t[i - 1], 0, lim, ai, i);
    ans += bi;
    ans += wi;
  } 
  ans -= G::dinic();
  printf("%d\n", ans);

  return 0;
}