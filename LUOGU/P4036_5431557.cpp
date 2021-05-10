// luogu-judger-enable-o2
#include <cstdio>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

const int N = 200000 + 5;
const unsigned int BASE = 53;

using std::pair;
using std::make_pair;
using std::cerr;
using std::endl;

inline int rand() {
  static int seed = 19260817;
  return seed += seed << 2 | 1;
}

int n;

struct Treap {
  struct node {
    node *l;
    node *r;
    int fix;
    unsigned int sum;
    unsigned int mul;
    unsigned int val;
    int siz;

    void update() {
      siz = l->siz + r->siz + 1;
      sum = l->sum + r->sum + val;
    }

    void settag(unsigned int m) {
      mul *= m;
      val *= m;
      sum *= m;
    }

    void pushdown() {
      if (mul == 1) {
	return;
      }
      l->settag(mul);
      r->settag(mul);
      mul = 1;
    }
  };

  node pool[N];
  node *root;

  node* newnode(unsigned int x) {
    static node* ptr = pool + 1;
    ptr->l = pool;
    ptr->r = pool;
    ptr->fix = rand();
    ptr->sum = x;
    ptr->mul = 1;
    ptr->val = x;
    ptr->siz = 1;
    return ptr++;
  }

  node* merge(node* x, node* y) {
    if (x == pool) {
      return y;
    }
    if (y == pool) {
      return x;
    }
    if (x->fix < y->fix) {
      x->pushdown();
      x->r = merge(x->r, y);
      x->update();
      return x;
    } else {
      y->pushdown();
      y->l = merge(x, y->l);
      y->update();
      return y;
    }
  }

  pair <node*, node*> split(node* x, int k) {
    x->pushdown();
    if (x == pool) {
      return make_pair(pool, pool);
    }
    pair <node*, node*> droot;
    if (x->l->siz >= k) {
      droot = split(x->l, k);
      x->l = droot.second;
      droot.second = x;
    } else {
      droot = split(x->r, k - x->l->siz - 1);
      x->r = droot.first;
      droot.first = x;
    }
    x->update();
    return droot;
  }

  void init() {
    node* p = newnode(0);
    node* q = newnode(0);
    pool->l = pool;
    pool->r = pool;
    root = merge(p, q);
  }

  void insert(int x, unsigned int k) {
    ++x;
    pair <node*, node*> d = split(root, x);
    node* p = newnode(k);
    root = merge(merge(d.first, p), d.second);
  }

  unsigned int query(int l, int r) {
    ++l;
    ++r;
    pair <node*, node*> x = split(root, l);
    pair <node*, node*> y = split(x.second, r - l + 1);
    unsigned int ret = y.first->sum;
    
    root = merge(x.first, merge(y.first, y.second));
    return ret;
  }

  void modify(int l, int r, unsigned int k) {
    ++l;
    ++r;
    pair <node*, node*> x = split(root, l);
    pair <node*, node*> y = split(x.second, r - l + 1);
    y.first->settag(k);
    root = merge(x.first, merge(y.first, y.second));
  }

  void replace(int p, unsigned int k) {
    ++p;
    pair <node*, node*> x = split(root, p);
    pair <node*, node*> y = split(x.second, 1);
    y.first->val = k;
    y.first->update();
    root = merge(x.first, merge(y.first, y.second));
  }
} t;

unsigned int inv[N];
unsigned int fac[N];

unsigned int modexp(unsigned int a, unsigned int x) {
  unsigned int ret = 1;
  while (x) {
    if (x & 1) {
      ret = ret * a;
    }
    a = a * a;
    x >>= 1;
  }
  return ret;
}

bool judge(int l1, int r1, int l2, int r2) {
  unsigned int p = t.query(l1, r1);
  unsigned int q = t.query(l2, r2);
  p = p * inv[l1];
  q = q * inv[l2];
  
  return p == q;
}

int lowerbound(int x, int y) {
  if (x > y) {
    std::swap(x, y);
  }
  int low = 1;
  int high = n - y;
  int ans = 0;
  while (low <= high) {
    int mid = low + high >> 1;
    if (judge(x, x + mid - 1, y, y + mid - 1)) {
      low = mid + 1;
      ans = mid;
    } else {
      high = mid - 1;
    }
  }
  return ans;
}

void init() {
  t.init();
  static char s[N];
  scanf("%s",s);
  fac[0] = 1;
  for (int i = 1; i < N; ++i) {
    fac[i] = fac[i - 1] * BASE;
  }
  inv[0] = 1;
  inv[1] = 2350076445ull;
  for (int i = 2; i < N; ++i) {
    inv[i] = inv[i - 1] * inv[1];
  }
 
  n = strlen(s);
  for (int i = 0; i < n; ++i) {
    t.insert(i, fac[i] * (s[i] - 'a' + 1));
  }
}
int main() {
  init();
  int m;
  scanf("%d", &m);
  
  for (int i = 0; i < m; ++i) {
    static char o[4];
    scanf("%s", o);
    if (o[0] == 'Q') {
      int l, r;
      scanf("%d %d", &l, &r);
      printf("%d\n", lowerbound(l - 1, r - 1));
    } else if (o[0] == 'R') {
      int p;
      scanf("%d %s", &p, o);
      t.replace(p - 1, (o[0] - 'a' + 1) * fac[p - 1]);
    } else {
      int p;
      scanf("%d %s", &p, o);
      t.modify(p, n - 1, BASE);
      t.insert(p, (o[0] - 'a' + 1) * fac[p]);
      ++n;
    }
  }
  return 0;
}
