#include <bits/stdc++.h>

using namespace std;

long long p;


const int N = 1e5 + 5;

long long a[N];

class segtree {
 public:

  struct tag {
    long long add;
    long long mul;

    tag(int _add = 0, int _mul = 1): add(_add), mul(_mul) {}
    
    inline void clear() {
      add = 0;
      mul = 1;
    }
  };

  struct node {
    /*
     * !!! default value (used for leaves)
     * !!! apply: merge a new tag
     * !!! apply: set a modify, make_tuple(v...) & get<0>, get<1>, etc
     * !!! clear: clear the tag
     */
    long long sum = 0;
    tag t;

    inline void apply(int l, int r, const tag &x) {
      sum = (sum * x.mul % p + (r - l + 1) * x.add % p) % p;
      t.add = (t.add * x.mul % p + x.add) % p;
      t.mul = t.mul * x.mul % p;
    }

    inline void unite(const node &a, const node &b) {
      /*
       * !!! unite: maintain the node
       */
      sum = (a.sum + b.sum) % p;
    }
  };
  

  inline int lc(int x) { return x << 1; };
  inline int rc(int x) { return (x << 1) | 1; }

  inline void push(int x, int l, int r) {
    int y = (l + r) >> 1;
    tree[lc(x)].apply(l, y, tree[x].t);
    tree[rc(x)].apply(y + 1, r, tree[x].t);
    tree[x].t.clear();
  }

  inline void pull(int x) { tree[x].unite(tree[lc(x)], tree[rc(x)]); }

  int n;
  vector<node> tree;

  void build(int x, int l, int r) {
    if (l == r) {
      tree[x].sum = a[l]; // MARK
      return;
    }
    int y = (l + r) >> 1;
    build(lc(x), l, y);
    build(rc(x), y + 1, r);
    pull(x);
  }

  node get(int x, int l, int r, int ll, int rr) {
    if (ll <= l && r <= rr) {
      return tree[x];
    }
    int y = (l + r) >> 1;
    push(x, l, r);
    node res{};
    if (rr <= y) {
      res = get(lc(x), l, y, ll, rr);
    } else {
      if (ll > y) {
        res = get(rc(x), y + 1, r, ll, rr);
      } else {
        res.unite(get(lc(x), l, y, ll, rr), get(rc(x), y + 1, r, ll, rr));
      }
    }
    pull(x);
    return res;
  }

  void modify(int x, int l, int r, int ll, int rr, tag v) {
    if (ll <= l && r <= rr) {
      tree[x].apply(l, r, v);
      return;
    }
    int y = (l + r) >> 1;
    push(x, l, r);
    if (ll <= y) {
      modify(lc(x), l, y, ll, rr, v);
    }
    if (rr > y) {
      modify(rc(x), y + 1, r, ll, rr, v);
    }
    pull(x);
  }

  int find_first_knowingly(int x, int l, int r,
                           const function<bool(const node &)> &f) {
    if (l == r) {
      return l;
    }
    push(x, l, r);
    int y = (l + r) >> 1;
    int res;
    if (f(tree[lc(x)])) {
      res = find_first_knowingly(lc(x), l, y, f);
    } else {
      res = find_first_knowingly(rc(x), y + 1, r, f);
    }
    pull(x);
    return res;
  }

  int find_first(int x, int l, int r, int ll, int rr,
                 const function<bool(const node &)> &f) {
    if (ll <= l && r <= rr) {
      if (!f(tree[x])) {
        return -1;
      }
      return find_first_knowingly(x, l, r, f);
    }
    push(x, l, r);
    int y = (l + r) >> 1;
    int res = -1;
    if (ll <= y) {
      res = find_first(lc(x), l, y, ll, rr, f);
    }
    if (rr > y && res == -1) {
      res = find_first(rc(x), y + 1, r, ll, rr, f);
    }
    pull(x);
    return res;
  }

  int find_last_knowingly(int x, int l, int r,
                          const function<bool(const node &)> &f) {
    if (l == r) {
      return l;
    }
    push(x, l, r);
    int y = (l + r) >> 1;
    int res;
    if (f(tree[rc(x)])) {
      res = find_last_knowingly(rc(x), y + 1, r, f);
    } else {
      res = find_last_knowingly(lc(x), l, y, f);
    }
    pull(x);
    return res;
  }

  int find_last(int x, int l, int r, int ll, int rr,
                const function<bool(const node &)> &f) {
    if (ll <= l && r <= rr) {
      if (!f(tree[x])) {
        return -1;
      }
      return find_last_knowingly(x, l, r, f);
    }
    push(x, l, r);
    int y = (l + r) >> 1;
    int res = -1;
    if (rr > y) {
      res = find_last(rc(x), y + 1, r, ll, rr, f);
    }
    if (ll <= y && res == -1) {
      res = find_last(lc(x), l, y, ll, rr, f);
    }
    pull(x);
    return res;
  }

  segtree(int _n) : n(_n) {
    assert(n > 0);
    tree.resize(n << 2);
    build(1, 0, n - 1);
  }

  node get(int ll, int rr) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return get(1, 0, n - 1, ll, rr);
  }

  node get(int p) {
    assert(0 <= p && p <= n - 1);
    return get(1, 0, n - 1, p, p);
  }

  void modify(int ll, int rr, tag v) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    modify(1, 0, n - 1, ll, rr, v);
  }

  int find_first(int ll, int rr, const function<bool(const node &)> &f) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return find_first(1, 0, n - 1, ll, rr, f);
  }

  int find_last(int ll, int rr, const function<bool(const node &)> &f) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return find_last(1, 0, n - 1, ll, rr, f);
  }
};

int main() {
  ios::sync_with_stdio(false);
  int n, m;
  cin >> n >> m >> p;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  segtree s(n);

  for (int i = 0; i < m; ++i) {
    int op, l, r;
    cin >> op >> l >> r;
    --l;
    --r;
    if (op != 3) {
      int add;
      cin >> add;
      if (op == 1) {
        s.modify(l, r, segtree::tag{0, add});
      } else {
        s.modify(l, r, segtree::tag{add, 1});
      }
    } else {
      cout << s.get(l, r).sum << endl;
    }
  }
  return 0;
}
