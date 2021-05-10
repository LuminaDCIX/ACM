#include <bits/stdc++.h>

using namespace std;

class dsu {
 public:
  vector<int> p;
  int n;

  dsu(int _n) : n(_n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x]))); }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      return true;
    }
    return false;
  }
};

namespace leftist {
/*
 * !!! operator < need to be defined
 */
typedef int typ;

class node {
 public:
  int id;
  typ val;
  int dis = 1;
  node *lc = nullptr;
  node *rc = nullptr;
  node(int _id, typ _val): id(_id), val(_val) {};
};

node* merge(node* x, node* y) {
  if (x == nullptr) {
    return y;
  }
  if (y == nullptr) {
    return x;
  }
  if (y->val > x->val) {
    swap(x, y);
  }
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

node *pop(node *r) { return merge(r->lc, r->rc); }

bool empty(node *r) {
  return r == nullptr;
}
};


using namespace leftist;


const int N = 3e5 + 5;

node *t[N];

int tag[N];
int siz[N];
multiset<int> s;


void force_update(node *x, int v) {
  if (x == nullptr) {
    return;
  }
  x->val += v;
  force_update(x->lc, v);
  force_update(x->rc, v);
}

void link(dsu &d, int x, int y) {
  x = d.get(x);
  y = d.get(y);
  if (x != y) {
    
    s.erase(s.find(top(t[x]) + tag[x]));
    s.erase(s.find(top(t[y]) + tag[y]));
    if (siz[x] > siz[y]) {
      swap(x, y);
    }
    //cerr << t[x]->id << " " << t[x]->lc << " " << t[4] << " " << t[x]->rc << endl;
    force_update(t[x], -tag[y] + tag[x]);
    int k = merge(t[x], t[y])->id;
    d.unite(x + y - k, k);
    tag[k] = tag[y];
    siz[k] += siz[x + y - k];
    s.insert(top(t[k]) + tag[k]);
  }
}

void add_node(dsu &d, int x, int v) {
  int fx = d.get(x);
  s.erase(s.find(top(t[fx]) + tag[fx]));
  int new_v = t[x]->val + v;
  node *l = merge(t[x]->lc, t[x]->rc);
  if (l == nullptr) {
    t[x]->val = -1e9;
    t[x]->id = -1;
  } else {
    *t[x] = *l;
    //cerr << "l->id = " << l->id << endl;
    //cerr << "l = " << l << " t[x] = " << " " << t[x] << endl;
    if (t[x]->id != -1) {
      t[t[x]->id] = t[x];
      l = t[x];
    }
  }
  t[x] = new node(x, new_v);
  //cerr << x << " " << fx << endl;
  if (fx != x) {
    int k = merge(t[fx], t[x])->id;
    d.p[x + fx - k] = k;
    d.p[k] = k;
    tag[k] = tag[fx];
    s.insert(top(t[k]) +tag[k]);
  } else {
    //cerr << "t[x] = " << t[x] << " " << " l = " << l<< endl;
    int k = merge(t[x], l)->id;
    d.p[x] = k;
    d.p[k] = k;
    tag[k] = tag[x];
    s.insert(top(t[k]) + tag[k]);
  }
}

void add_block(dsu &d, int x, int v) {
  x = d.get(x);
  s.erase(s.find(top(t[x]) + tag[x]));
  tag[x] += v;
  s.insert(top(t[x]) +tag[x]);
}


int n, q;

int main() {
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int a;
    cin >> a;
    t[i] = new node(i, a);
    s.insert(a);
  }
  for (int i = 0; i < n; ++i) {
    siz[i] = 1;
  }
  cin >> q;
  dsu d(n);
  int sum = 0;
  for (int i = 0; i < q; ++i) {
    string str;
    cin >> str;
    if (str == "U") {
      int x, y;
      cin >> x >> y;
      --x, --y;
      link(d, x, y);
    } else if (str == "A1") {
      int x, v;
      cin >> x >> v;
      --x;
      add_node(d, x, v);
    } else if (str == "A2") {
      int x, v;
      cin >> x >> v;
      --x;
      add_block(d, x, v);
    } else if (str == "A3") {
      int v;
      cin >> v;
      sum += v;
    } else if (str == "F1") {
      int x;
      cin >> x;
      --x;
      int fx = d.get(x);
      cout << t[x]->val + tag[fx] + sum << endl;
    } else if (str == "F2") {
      int x;
      cin >> x;
      --x;
      int fx = d.get(x);
      cout << top(t[fx]) + tag[fx] + sum << endl;
    } else {
      cout << *s.rbegin() + sum << endl;
    }
    int x = 4;
    int fx = d.get(x);
    //cerr << i + 1 << " val4 = " << t[x]->val + tag[fx] + sum<< " " << tag[fx] << endl;
    //cerr << "t[4] = " << t[4] << endl;
  }
  return 0;
}
