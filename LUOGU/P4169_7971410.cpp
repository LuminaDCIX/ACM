// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

const int inf = 19260817;
const double alpha = 0.8;

inline int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar()) {
    f = (ch == '-') ? -1 : 1;
  }
  for (; isdigit(ch); ch = getchar()) {
    x = x * 10 + ch - '0';
  }
  return f * x;
}

class kdtree {
public:
  struct point {
    int v[2];
    point() {};
    point(int x, int y) {
      v[0] = x;
      v[1] = y;
    }
  };

  inline int dist(const point &a, const point &b) {
    return abs(a.v[0] - b.v[0]) + abs(a.v[1] - b.v[1]);
  }

  struct node {
    point p;
    int mx[2];
    int mn[2];
    int l;
    int r;
    int siz;
    node() {};
  };

  vector<node> tree;
  queue<int> pool;

  inline point& p(int x) {
    return tree[x].p;
  }
  inline int *mx(int x) {
    return tree[x].mx;
  }
  inline int *mn(int x) {
    return tree[x].mn;
  }
  inline int& l(int x) {
    return tree[x].l;
  }
  inline int& r(int x) {
    return tree[x].r;
  }
  inline int& siz(int x) {
    return tree[x].siz;
  }
  
  kdtree(int n) {
    tree.resize(n + 1);
    for (int i = 1; i <= n; ++i) {
      pool.push(i);
    }
    l(0) = r(0) = 0;
    siz(0) = 0;
    mn(0)[0] = mn(0)[1] = inf;
    mx(0)[0] = mx(0)[1] = -inf;
  }
  
  int newnode(point nw) {
    if (pool.empty()) {
      int n = tree.size();
      tree.resize(n + 1024);
      for (int i = n; i < n + 1024; ++i) {
        pool.push(i);
      }
    }
    int x = pool.front();
    pool.pop();
    p(x) = nw;
    l(x) = r(x) = 0;
    siz(x) = 1;
    mn(x)[0] = mx(x)[0] = nw.v[0];
    mn(x)[1] = mx(x)[1] = nw.v[1];
    return x;
  }

  void delnode(int x) {
    pool.push(x);
  }

  void update(int a) {
    int b = l(a);
    int c = r(a);
    mx(a)[0] = max(p(a).v[0], max(mx(b)[0], mx(c)[0]));
    mx(a)[1] = max(p(a).v[1], max(mx(b)[1], mx(c)[1]));
    mn(a)[0] = min(p(a).v[0], min(mn(b)[0], mn(c)[0]));
    mn(a)[1] = min(p(a).v[1], min(mn(b)[1], mn(c)[1]));
    siz(a) = siz(b) + siz(c) + 1;
  }

  static bool cmpx(const point &a, const point &b) {
    return a.v[0] < b.v[0];
  }
  static bool cmpy(const point &a, const point &b) {
    return a.v[1] < b.v[1];
  }

  vector<point> arr;

  int build(vector<point> v, int dim) {
    if (v.empty()) {
      return 0;
    }
    int n = (int) v.size() / 2;
    nth_element(v.begin(), v.begin() + n, v.end(), dim ? cmpy : cmpx);
    int x = newnode(v[n]);
    l(x) = build(vector<point>(v.begin(), v.begin() + n), dim ^ 1);
    r(x) = build(vector<point>(v.begin() + n + 1, v.end()), dim ^ 1);
    update(x);
    return x;
  }

  int build(int n) {
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
      arr[i].v[0] = read();
      arr[i].v[1] = read();
    }
    return build(arr, 0);
  }

  inline int bound(int x, const point &tar) {
    return max(tar.v[0] - mx(x)[0], 0) + max(mn(x)[0] - tar.v[0], 0)
      + max(tar.v[1] - mx(x)[1], 0) + max(mn(x)[1] - tar.v[1], 0);
  }

  void query(int x, const point &tar, int &ans) {
    ans = min(ans, dist(tar, p(x)));
    int lv = bound(l(x), tar);
    int rv = bound(r(x), tar);
    if (lv < rv) {
      if (lv < ans) {
        query(l(x), tar, ans);
      }
      if (rv < ans) {
        query(r(x), tar, ans);
      }
    } else {
      if (rv < ans) {
        query(r(x), tar, ans);
      }
      if (lv < ans) {
        query(l(x), tar, ans);
      }
    }
  }

  inline int query(int o, point tar) {
    int ans = inf;
    query(o, tar, ans);
    return ans;
  }

  int *bad;

  void travel(int x) {
    if (x == 0) {
      return;
    }
    travel(l(x));
    travel(r(x));
    arr.push_back(p(x));
    delnode(x);
  }

  void insert(int &x, const int &tar, int dim) {
    if (!x) {
      x = tar;
      return;
    }
    if (p(x).v[dim] < p(tar).v[dim]) {
      insert(r(x), tar, dim ^ 1);
    } else {
      insert(l(x), tar, dim ^ 1);
    }
    update(x);
    if (max(siz(l(x)), siz(r(x))) > siz(x) * alpha) {
      bad = &x;
    }
  }
  
  void insert(int &o, point x) {
    bad = NULL;
    int nw = newnode(x);
    insert(o, nw, 0);
    if (bad != NULL) {
      arr.clear();
      travel(*bad);
      *bad = build(arr, 0);
    }
  }
};

int main() {
  int n = read();
  int m = read();
  static kdtree kdt(n + m);
  int root = kdt.build(n);
  for (int i = 1, op, x, y; i <= m; ++i) {
    op = read();
    x = read();
    y = read();
    if (op == 1) {
      kdt.insert(root, kdtree::point(x, y));
    } else {
      printf("%d\n", kdt.query(root, kdtree::point(x, y)));
    }
  }
  return 0;
}
