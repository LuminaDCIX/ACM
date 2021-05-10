#include <bits/stdc++.h>

using namespace std;

template <typename T>
class segment_tree {
 public:
  class node {
   public:
    T item;
    node* lc;
    node* rc;

    node(int l, int r) {
      lc = rc = nullptr;
      item = T(l, r);
    }
  };

  int n;
  node* root;
  const function<void(T&, T)> set_tag;
  const function<void(T&, T)> merge_tag;
  const function<T(T, T)> merge_val;
  const function<void(T&, T, T)> maintain;

  segment_tree(int _n, function<void(T&, T)> _set_tag,
               function<void(T&, T)> _merge_tag, function<T(T, T)> _merge_val,
               function<void(T&, T, T)> _maintain)
      : merge_val(_merge_val),
        merge_tag(_merge_tag),
        maintain(_maintain),
        set_tag(_set_tag) {
    n = _n;
    root = new node(1, n);
    build_tree(root, 1, n);
  }

  void build_tree(node* o, int ll, int rr) {
    if (ll == rr) {
      return;
    }
    int mid = (ll + rr) >> 1;
    o->lc = new node(ll, mid);
    o->rc = new node(mid + 1, rr);
    build_tree(o->lc, ll, mid);
    build_tree(o->rc, mid + 1, rr);
    maintain(o->item, o->lc->item, o->rc->item);
  }

  void _pushdown(node* o, int ll, int rr) {
    if (ll == rr) {
      return;
    }
    merge_tag(o->lc->item, o->item);
    merge_tag(o->rc->item, o->item);
    o->item.clear();
  }

  void _insert(node* o, int ll, int rr, int l, int r, T x) {
    _pushdown(o, ll, rr);
    if (ll >= l && rr <= r) {
      set_tag(o->item, x);
      return;
    }
    int mid = (ll + rr) >> 1;
    if (l <= mid) {
      _insert(o->lc, ll, mid, l, r, x);
    }
    if (r > mid) {
      _insert(o->rc, mid + 1, rr, l, r, x);
    }
    maintain(o->item, o->lc->item, o->rc->item);
  }

  T _query(node* o, int ll, int rr, int l, int r) {
    _pushdown(o, ll, rr);
    if (ll >= l && rr <= r) {
      return o->item;
    }
    int mid = (ll + rr) >> 1;
    T ret;
    if (r <= mid) {
      ret = _query(o->lc, ll, mid, l, r);
    } else if (l > mid) {
      ret = _query(o->rc, mid + 1, rr, l, r);
    } else {
      ret = merge_val(_query(o->lc, ll, mid, l, r),
                      _query(o->rc, mid + 1, rr, l, r));
    }
    maintain(o->item, o->lc->item, o->rc->item);
    return ret;
  }

  void insert(int l, int r, T x) { _insert(root, 1, n, l, r, x); }

  T query(int l, int r) { return _query(root, 1, n, l, r); }
};

int val[100005];

class item {
 public:
  int ll;
  int rr;
  int sum;
  int tag;
  item(){};
  item(int _ll, int _rr) {
    ll = _ll;
    rr = _rr;
    sum = tag = 0;
    if (ll == rr) {
      sum = val[ll];
    }
  }

  void clear() { tag = 0; }
};

int main() {
  typedef segment_tree<item>::node* snode;
  auto set_tag = [](item& a, item b) -> void {
    a.tag += b.tag;
    a.sum += b.tag * (a.rr - a.ll);
  };
  auto merge_tag = [](item& a, item b) -> void {
    a.tag += b.tag;
    a.sum += b.tag * (a.rr - a.ll);
  };
  auto merge_val = [](item a, item b) -> item {
    item ret(0, 0);
    ret.sum = a.sum + b.sum;
    return ret;
  };
  auto maintain = [](item& o, item a, item b) -> void {
    o.sum = a.sum + b.sum;
  };
  int n, m;
  cin >> n >> m;

  segment_tree<item> sgt(n, set_tag, merge_tag, merge_val, maintain);
  for (int i = 1; i <= n; ++i) {
    cin >> val[i];
  }

  for (int i = 0; i < m; ++i) {
    int op;
    cin >> op;
    if (op == 1) {
      int x, y, k;
      cin >> x >> y >> k;
      item t = item(0, 0);
      t.tag = k;
      sgt.insert(x, y, t);
    } else {
      int x, y;
      cout << sgt.query(x, y).sum << endl;
    }
  }
  return 0;
}