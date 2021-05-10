#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

inline int read() {
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x;
}

const int N = 100000 + 5;

int n;

struct node {
  int id;
  int val;
  int dist;
  node *lc;
  node *rc;
  node *fa;
};

node pool[N];

inline int h(node *p) {
  return (p == NULL) ? 0 : p->dist;
}

inline void fix(node *p) {
  if (h(p->lc) < h(p->rc)) {
    swap(p->lc, p->rc);
  }
  p->dist = p->lc->dist + 1;
}

node* merge(node *a, node *b) {
  if (!b) {
    return a;
  }
  if (!a) {
    return b;
  }
  if (a->val > b->val || (a->val == b->val && a->id > b->id)) {
    swap(a, b);
  }
  node *p = merge(a->rc, b);
  a->rc = p;
  p->fa = a;
  fix(a);
  return a;
}

inline node* newnode(int v, int id) {
  static node *ptr = &pool[0];
  ptr->id = id;
  ptr->val = v;
  ptr->dist = 1;
  return ptr++;
}

bool del[N];


inline int pop(node *p) {
  int ret = p->val;
  del[p->id] = 1;
  if (p->lc) {
    p->lc->fa = NULL;
  } 
  if (p->rc) {
    p->rc->fa = NULL;
  }
  p = merge(p->lc, p->rc);
  return ret;
}

int m;

node *l[N];

inline node* getroot(node *o) {
  while (o->fa) {
    o = o->fa;
  }
  return o;
}

int main() {
  n = read();
  m = read();
  for (int i = 0; i < n; ++i) {
    int v = read();
    l[i] = newnode(v, i);
  }
  // for (int i = 0; i < n; ++i) {
  //   cerr << l[i]->val << endl;
  // }
  for (int i = 0; i < m; ++i) {
    // cerr << i << endl;
    int o = read();
    if (o == 1) {
      int x = read() - 1;
      int y = read() - 1;

      if (!del[x] && !del[y]) {
        node *hx = getroot(l[x]);
        node *hy = getroot(l[y]);
        // cerr << hx->val << " " << hy->val << endl;
        if (hx != hy) {
          merge(hx, hy);
        }
      }
    } else {
      int x = read() - 1;
      if (del[x]) {
        puts("-1");
        continue;
      }
      printf("%d\n", pop(getroot(l[x])));
    }
  }
  return 0;
}
