#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 50000 + 5;
const int MAX = 4 * 50000 + 5;
const int MAXP = 100000 * 6 * 5;;

int read() {
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

int n;
int m;

struct node {
  node *lc;
  node *rc;
  int v;
  int siz;
  int fix;
  void update();
};

node pool[MAXP];
node *t[MAX];

node* newnode(int v) {
  static node* ptr = pool;
  static int fix = 20010330;
  fix += fix << 2 | 1;
  ptr->fix = fix;
  ptr->v = v;
  ptr->siz = 1;
  return ptr++;
}

int SIZ(node *o) {
  return !o ? 0 : o->siz;
}

void node::update() {
  siz = SIZ(lc) + SIZ(rc) + 1;
}

node* merge(node *a, node *b) {
  if (!a) {
    return b;
  }
  if (!b) {
    return a;
  }
  if (a->fix < b->fix) {
    a->rc = merge(a->rc, b);
    a->update();
    return a;
  } else {
    b->lc = merge(a, b->lc);
    b->update();
    return b;
  }
}

pair <node*, node*> split(node *t, int k) {
  if (!t) {
    return pair <node*, node*> (NULL, NULL);
  }
  pair <node*, node*> droot;
  if (SIZ(t->lc) >= k) {
    droot = split(t->lc, k);
    t->lc = droot.second;
    droot.second = t;
  } else {
    droot = split(t->rc, k - SIZ(t->lc) - 1);
    t->rc = droot.first;
    droot.first = t;
  }
  t->update();
  return droot;
}

int get_rank(node *x, int v) { //the last one 
  if (!x) {
    return 0;
  }
  return v <= x->v ? get_rank(x->lc, v) : get_rank(x->rc, v) + SIZ(x->lc) + 1;
}

node* insert(node *x, int v) {
  int k = get_rank(x, v);
  pair <node*, node*> droot = split(x, k);
  return merge(droot.first, merge(newnode(v), droot.second));
}

node* erase(node *x, int v) {
  int k = get_rank(x, v);
  pair <node*, node*> droot0 = split(x, k);
  pair <node*, node*> droot1 = split(droot0.second, 1);
  return merge(droot0.first, droot1.second);
}

node* pre(node *x, int v, int &ans) {
  int k = get_rank(x, v);
  if (k == 0) {
    return x;
  }
  pair <node*, node*> droot0 = split(x, k - 1);
  pair <node*, node*> droot1 = split(droot0.second, 1);
  ans = droot1.first->v;
  return merge(droot0.first, merge(droot1.first, droot1.second));
}

node* nxt(node *x, int v, int &ans) {
  int k = get_rank(x, v + 1) + 1;
  if (k - 1 == SIZ(x)) {
    return x;
  }
  pair <node*, node*> droot0 = split(x, k - 1);
  pair <node*, node*> droot1 = split(droot0.second, 1);
  ans = droot1.first->v;
  return merge(droot0.first, merge(droot1.first, droot1.second));
}

void add(int o, int ll, int rr, int p, int v) {
  t[o] = insert(t[o], v);
  if (ll == p && rr == p) {
    return ;
  }
  int mid = ll + rr >> 1;
  if (p <= mid) {
    add(o << 1, ll, mid, p, v);
  } else {
    add(o << 1 | 1, mid + 1, rr, p, v);
  }
}

void del(int o, int ll, int rr, int p, int v) {
  t[o] = erase(t[o], v);
  if (ll == p && rr == p) {
    return ;
  }
  int mid = ll + rr >> 1;
  if (p <= mid) {
    del(o << 1, ll, mid, p, v);
  } else {
    del(o << 1 | 1, mid + 1, rr, p, v);
  }
}

int _rank(int o, int ll, int rr, int l, int r, int v) {
  if (ll >= l && rr <= r) {
    return get_rank(t[o], v);
  }
  int mid = ll + rr >> 1;
  int sum = 0;
  if (l <= mid) {
    sum += _rank(o << 1, ll, mid, l, r, v);
  }
  if (r > mid) {
    sum += _rank(o << 1 | 1, mid + 1, rr, l, r, v);
  }
  return sum;
}

int a[N];

void find_pre(int o, int ll, int rr, int l, int r, int v, int &ans) {
  if (ll >= l && rr <= r) {
    int k = ans;
    t[o] = pre(t[o], v, k);
    ans = max(ans, k);
    return;
  }
  int mid = ll + rr >> 1;
  if (l <= mid) {
    find_pre(o << 1, ll, mid, l, r, v, ans);
  }
  if (r > mid) {
    find_pre(o << 1 | 1, mid + 1, rr, l, r, v, ans);
  }
}

void find_nxt(int o, int ll, int rr, int l, int r, int v, int &ans) {
  if (ll >= l && rr <= r) {
    int k = ans;
    t[o] = nxt(t[o], v, k);
    ans = min(ans, k);
    return;
  }
  int mid = ll + rr >> 1;
  if (l <= mid) {
    find_nxt(o << 1, ll, mid, l, r, v, ans);
  }
  if (r > mid) {
    find_nxt(o << 1 | 1, mid + 1, rr, l, r, v, ans);
  }
}

// void dfs(node *o) {
//   if (!o) {
//     return ;
//   }
//   dfs(o->lc);
//   printf("%d\n", o->v);
//   dfs(o->rc);
// }

int main() {
  n = read();
  m = read();

  for (int i = 0; i < n; ++i) {
    a[i] = read();
    add(1, 0, n - 1, i, a[i]);
    // cerr << t[1]->siz << endl;
  }
  for (int i = 0, x, y, k, low, high, ans; i < m; ++i) {
    // cerr << "siz = " << t[1]->siz << endl;
    // dfs(t[1]);
    int op = read();
    switch (op) {
    case 1:
      x = read();
      y = read();
      k = read();
      printf("%d\n", _rank(1, 0, n - 1, x - 1, y - 1, k) + 1);
      break;
    case 2:
      low = 0;
      high = 1e8;
      x = read() - 1;
      y = read() - 1;
      k = read();
      // cerr << x << " " << y << endl;
      while (low <= high) {
        int mid = low + high >> 1;
        // cerr << _rank(1, 0, n - 1, x, y ,mid + 1) << " " << mid << endl;
        if (_rank(1, 0, n - 1, x, y, mid + 1) < k) {
          low = mid + 1;
        } else {
          ans = mid;
          high = mid - 1;
        }
      }
      printf("%d\n", ans);
      break;
    case 3:
      x = read() - 1;
      k = read();
      y = a[x];
      a[x] = k;
      del(1, 0, n - 1, x, y);
      add(1, 0, n - 1, x, k);
      break;
    case 4:
      x = read() - 1;
      y = read() - 1;
      k = read();
      ans = -2147483647;
      find_pre(1, 0, n - 1, x, y, k, ans);
      printf("%d\n", ans);
      break;
    case 5:
      x = read() - 1;
      y = read() - 1;
      k = read();
      ans = 2147483647;
      find_nxt(1, 0, n - 1, x, y, k, ans);
      printf("%d\n", ans);
      break;
    }
  }
  return 0;
}
