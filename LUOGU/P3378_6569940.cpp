// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;

struct leftist_tree {
  int lc[N], rc[N];
  int val[N];
  int dist[N];
  int root;

  inline void init() {
    val[0] = 1e9;
  }
  
  inline void fix(int x) {
    if (dist[lc[x]] < dist[rc[x]]) {
      swap(lc[x], rc[x]);
    }
    dist[x] = dist[rc[x]] + 1;
  }
  
  inline int top(int root) {
    return val[root];
  }

  int merge(int x, int y) {
    if (!x) {
      return y;
    }
    if (!y) {
      return x;
    }
    if (val[x] > val[y]) {
      swap(x, y);
    }
    rc[x] = merge(rc[x], y);
    fix(x);
    return x;
  }

  inline int pop(int root) {
    return merge(lc[root], rc[root]);
  }

  inline int newnode(int x) {
    static int tot = 0;
    ++tot;
    val[tot] = x;
    return tot;
  }

  inline int push(int root, int x) {
    return merge(root, newnode(x));
  }
    
} h;


int fa[N];

int find(int x) {
  return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int n, m;

int main() {
  scanf("%d", &n);
  h.init();
  int r = 0;
  for (int i = 1; i <= n; ++i) {
    int x, y;
    scanf("%d", &x);
    if (x == 1) {
      scanf("%d", &y);
      r = h.push(r, y);
    } else if (x == 2) {
      printf("%d\n", h.top(r));
    } else {
      r = h.pop(r);
    }
  }
  return 0;
}
