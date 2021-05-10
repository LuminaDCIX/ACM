#include <bits/stdc++.h>

using namespace std;

namespace leftist {
/*
 * !!! operator < need to be defined
 */
typedef long long typ;

struct tag {
  typ mul = 1;
  typ add = 0;

  tag(int _mul = 1, int _add = 0): mul(_mul), add(_add){};
  
  inline void clear() {
    mul = 1;
    add = 0;
  }
};

class node {
 public:
  int id;
  typ val;
  int dis = 1;
  node *lc = nullptr;
  node *rc = nullptr;
  tag t;
  
  node(int _id, typ _val): id(_id), val(_val) {};

  void set(tag v) {
    val = val * v.mul + v.add;
    t.mul *= v.mul;
    t.add = t.add * v.mul + v.add;
  }
  
  void push() {
    if (lc != nullptr) {
      lc->set(t);
    }
    if (rc != nullptr) {
      rc->set(t);
    }
    t.clear();
  }
};

node* merge(node* x, node* y) {
  if (x == nullptr) {
    return y;
  }
  if (y == nullptr) {
    return x;
  }
  if (y->val < x->val) {
    swap(x, y);
  }
  x->push();
  x->rc = merge(x->rc, y);
  if (x->lc == nullptr || x->rc->dis > x->lc->dis) {
    swap(x->lc, x->rc);
  }
  x->dis = (x->rc == nullptr ? 0 : x->rc->dis) + 1;
  return x;
}

node* insert(node* r, typ x, int id) {
  node* t = new node(x, id);
  return merge(r, t);
}

typ top(node *r) {
  return r->val;
}

node *pop(node *r) {
  r->push();
  return merge(r->lc, r->rc);
}

bool empty(node *r) {
  return r == nullptr;
}
};


const int N = 3e5 + 5;

int n, m;

long long h[N];
int a[N];
long long v[N];

vector<int> g[N];

long long s[N];
int c[N];

int dep[N];

using namespace leftist;

node *t[N];
int dead[N];
int cnt[N];

void dfs(int u) {
  for (auto v:g[u]) {
    dep[v] = dep[u] + 1;
    dfs(v);
    t[u] = merge(t[u], t[v]);
  }
  if (t[u]) {
    while (!empty(t[u]) && top(t[u]) < h[u]) {
      int k = t[u]->id;
      dead[k] = u;
      t[u] = pop(t[u]);
      cnt[u]++;
    }
    if (t[u]) {
      if (a[u] == 0) {
        t[u]->set(tag{1, v[u]});
      } else {
        t[u]->set(tag{v[u], 0});
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> m;
  memset(dead, -1, sizeof(dead));
  for (int i = 0; i < n; ++i) {
    cin >> h[i];
  }
  for (int i = 1; i < n; ++i) {
    int f;
    cin >> f >> a[i] >> v[i];
    --f;
    g[f].push_back(i);
  }
  for (int i = 0; i < m; ++i) {
    cin >> s[i] >> c[i];
    --c[i];
    if (t[c[i]] == NULL) {
      t[c[i]]= new node(i, s[i]);
    } else {
      t[c[i]] = merge(t[c[i]], new node(i, s[i]));
    }
  }
  dep[0] = 1;
  dfs(0);
  for (int i = 0; i < n; ++i) {
    cout << cnt[i] << endl;
  }
  for (int i = 0; i < m; ++i) {
    if (dead[i] == -1) {
      cout << dep[c[i]] << endl;
    } else {
      cout << dep[c[i]] - dep[dead[i]] << endl;
    }
  }
  return 0;
}

