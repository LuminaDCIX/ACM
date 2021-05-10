#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n;

inline int read() {
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
struct Treap {
  struct node {
    node *l;
    node *r;
    int val;
    int siz;
    int fix;
    
    inline void update() {
      siz = 1 + (l ? l->siz : 0) + (r ? r->siz : 0);
    }
  };
  int siz;

  inline int Siz(node* x) {
    return x ? x->siz : 0;
  }

  node pool[N];
  node *root;

  inline int rnd() {
    static int seed = 19260817;
    seed += seed << 2 | 1;
    return seed;
  }
  
  inline node *newnode(int val) {
    static node *ptr = pool;
    ptr->fix = rnd();
    ptr->val = val;
    ptr->siz = 1;
    return ptr++;
  }

  node *merge(node *x, node *y) {
    if (!x) {
      return y;
    }
    if (!y) {
      return x;
    }
    if (x->fix < y->fix) {
      x->r = merge(x->r, y);
      x->update();
      return x;
    } else {
      y->l = merge(x, y->l);
      y->update();
      return y;
    }
  }

  pair <node*, node*> split(node *x, int k) {
    if (!x) {
      return pair <node*, node*> (NULL, NULL);
    }
    pair <node*, node*> droot;
    if (Siz(x->l) >= k) {
      droot = split(x->l, k);
      x->l = droot.second;
      droot.second = x;
      
    } else {
      droot = split(x->r, k - Siz(x->l) - 1);
      x->r = droot.first;
      droot.first = x;
    }
    x->update();
    return droot;
  }

  inline int findkth(int k) {
    pair <node*, node*> x = split(root, k - 1);
    pair <node*, node*> y = split(x.second, 1);
    int ans = y.first->val;
    root = merge(x.first, merge(y.first, y.second));
    return ans;
  }

  int getrank(node *o, int x) {
    if (!o) {
      return 0;
    } else {
      return o->val <= x ? getrank(o->l, x) : getrank(o->r, x) + 1 + (o->l ? o->l->siz : 0);
    }
  }
  
  inline void insert(int x) {
    int k = getrank(root, x);
    pair <node*, node*> droot = split(root, k);
    node *p = newnode(x);
    root = merge(droot.first, merge(p, droot.second));
    ++siz;
  }

  inline void erase(int x) {
    int k = getrank(root, x);
    pair <node*, node*> r0 = split(root, k);
    pair <node*, node*> r1 = split(r0.second, 1);
    root = merge(r0.first, r1.second);
    --siz;
  }
};


Treap z;
Treap f;

inline long long val(int x, int k) {
  if (x == 1) {
    return (long long) z.findkth(k * 2 - 1) * z.findkth(k * 2);
  } else {
    return (long long) f.findkth(k * 2 - 1) * f.findkth(k * 2);
  }
}

long long solve(int l1, int r1, int l2, int r2, int k) {
  // cerr << l1 << " " << r1 << " " << l2 << " " << r2 << " " << k << endl;
  if (l1 > r1) {
    return val(2, l2 + k - 1);
  }
  if (l2 > r2) {
    return val(1, l1 + k - 1);
  }
  int mid1 = l1 + r1 >> 1;
  int mid2 = l2 + r2 >> 1;
  long long v1 = val(1, mid1);
  long long v2 = val(2, mid2);
  int s = mid1 - l1 + 1 + mid2 - l2 + 1;
  // cerr << v1 << " " << v2 << endl;
  if (v1 > v2) {
    if (k < s) {
      return solve(l1, r1, l2, mid2 - 1, k);
    } else {
      return solve(mid1 + 1, r1, l2, r2, k - (mid1 - l1 + 1));
    }
  } else if (v2 > v1) {
    if (k < s) {
      return solve(l1, mid1 - 1, l2, r2, k);
    } else {
      return solve(l1, r1, mid2 + 1, r2, k - (mid2 - l2 + 1));
    } 
  } else if (v1 == v2) {
    if (k < s) {
      
      return solve(l1, mid1 - 1, l2, mid2, k);
    } else if (k == s) {
      return v1;
    } else {
      return solve(mid1 + 1, r1, mid2 + 1, r2, k - s);
    }
  }
}

int a[N];

void write(long long x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x > 9) {
    write(x/10);
  }
  putchar(x % 10 + '0');
}

int main() {
  n = read();
  int m = read();
  for (int i = 0; i < n; ++i) {
    int x = read();
    a[i] = x;
    if (x >= 0) {
      z.insert(x);
    } else {
      f.insert(-x);
    }
  }
  int t = n >> 1;
  for (int i = 0; i < m; ++i) {
    int typ = read();
    if (typ == 2) {
      int k = read();
      // cerr << k << endl;
      if (k != t) {
	long long check = solve(1, z.siz >> 1, 1, f.siz >> 1, k);
	write(check);
      } else {
	long long ans;
	if (z.Siz(z.root) & 1) {
	  ans = (long long) -z.findkth(z.siz) * f.findkth(f.siz);
	} else {
	  ans = solve(1, z.siz >> 1, 1, f.siz >> 1, k);
	}
	write(ans);
      }
      putchar('\n');
    } else {
      int k = read() - 1;
      int x = read();
      if (a[k] < 0) {
	f.erase(-a[k]);
      } else {
	z.erase(a[k]);
      }
      a[k] = x;
      if (x >= 0) {
	z.insert(x);
      } else {
	f.insert(-x);
      }
    }
    // return 0;
  }
  return 0;
}
