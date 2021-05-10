#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read()
{
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

const int N = 200000 + 5;

int n;
int q;


struct node
{
  node *lc;
  node *rc;
  int sum;

  inline void update() {
    sum = lc->sum + rc->sum;
  }
} pool[N * 19];

node *root[N];

node *null = &pool[0];

inline node* newnode() {
  static node* ptr = &pool[0];
  return ++ptr;
}

int a[N];

int real[N];

void build(node *o, int l, int r)
{
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  build(o->lc = newnode(), l, mid);
  build(o->rc = newnode(), mid + 1, r);
}

node* add(node* o, int l, int r, int v)
{
  node *p = newnode();
  *p = *o;
  if (l == r) {
    ++p->sum;
    return p;
  }
  int mid = l + r >> 1;
  if (v <= mid) {
    p->lc = add(o->lc, l, mid, v);
  } else {
    p->rc = add(o->rc, mid + 1, r, v);
  }
  p->update();
  return p;
}

int query(node *l, node *r, int ll, int rr, int k)
{
  if (ll == rr) {
    return ll;
  }
  
  //  printf("%d %d %d %d %d\n", l->l, l->r, k, l->lc->sum, r->lc->sum);
  int lft = r->lc->sum - l->lc->sum;
  int mid = ll + rr >> 1;
  if (lft >= k) {
    return query(l->lc, r->lc, ll, mid, k);
  } else {
    return query(l->rc, r->rc, mid + 1, rr, k - lft);
  }
}

int v[N];

int main()
{
  n = read();
  q = read();
  for (int i = 0; i < n; ++i) {
    a[i] = read();
  }
  int len;
  {
    len = 0;
    for (int i = 0; i < n; ++i) {
      v[len++] = a[i];
    }
    sort(v, v + len);
    len = unique(v, v + len) - v;
    for (int i = 0; i < len; ++i) {
      real[i] = v[i];
    }
    for (int i = 0; i < n; ++i) {
      a[i] = lower_bound(v, v + len, a[i]) - v;
    }
  }
  null->lc = null;
  null->rc = null;
  root[0] = null;
  for (int i = 0; i < n; ++i) {
    root[i + 1] = add(root[i], 0, len - 1, a[i]);
  }
  for (int i = 0, l, r, k; i < q; ++i) {
    l = read() - 1;
    r = read() - 1;
    k = read();
    printf("%d\n", real[query(root[l], root[r + 1], 0, len - 1, k)]);
  }
  return 0;
}
