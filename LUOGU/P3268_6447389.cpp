// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;
const int MAX = (N * 4) * 4 + 5;
int n;

struct node {
  int op, x, id;
  bool operator < (const node &rhs) const {
    if (x == rhs.x) {
      return op < rhs.op;
    }
    return x < rhs.x;
  }

  node(int _op, int _x, int _id) {
    op = _op;
    x = _x;
    id = _id;
  }
};

double T;

double sqr(double x) {
  return x * x;
}


int x[N], y[N], r[N];


struct pir {
  int id, f;
  bool operator < (const pir &rhs) const {
    double xx = y[id] + f * sqrt(sqr(r[id]) - sqr(T - x[id]));
    double yy = y[rhs.id] + rhs.f * sqrt(sqr(r[rhs.id]) - sqr(T - x[rhs.id]));
    return xx == yy ? f < rhs.f : xx < yy;
  }

  pir(int _id, int _f) {
    id = _id;
    f = _f;
  }
};

vector <node> p;

map <int, int> id;

vector <int> ver[N];

inline void add(int u, int v) {
  ver[u].push_back(v);
}


long long ans;
int dep[N];

void dfs(int u) {
  if (dep[u] & 1) {
    ans += (long long) r[u] * r[u];
  } else {
    ans -= (long long) r[u] * r[u];
  }
  for (int o = 0; o < (int) ver[u].size(); ++o) {
    int v = ver[u][o];
    dep[v] = dep[u] + 1;
    dfs(v);
  }
 
}

set <pir> s;

int fa[N];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d %d", &x[i], &y[i], &r[i]);
  }
  vector <int> v;
  for (int i = 1; i <= n; ++i) {
    p.push_back(node(1, x[i] - r[i], i));
    p.push_back(node(-1, x[i] + r[i], i));
  }
  sort(p.begin(), p.end());
  for (int i = 0; i < p.size(); ++i) {
    int b = p[i].id;
    T = p[i].x;
    if (p[i].op == 1) {
      pir r = pir(b, 1);
      set <pir>::iterator it = s.lower_bound(r);
      if (it != s.end()) {
        if (it->f == -1) {
          fa[b] = fa[it->id];
        } else {
          fa[b] = it->id;
        }
      }
      add(fa[b], b);
      
      s.insert(pir(b, 1));
      s.insert(pir(b, -1));
    } else {
      s.erase(pir(b, 1));
      s.erase(pir(b, -1));
    }
  }
  dfs(0);
  printf("%lld\n", ans);
  return 0;
}
