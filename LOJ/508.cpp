#include <bits/stdc++.h>

#define st first
#define nd second
#define make_pair com
#define sz(x) ((int)x.size())
#define mem(x, v) memset(x, v, sizeof(x))
#define rep(x, n) for (int x = 0      ; x <  (n); ++x)
#define per(x, n) for (int x = (n) - 1; i >= 0  ; --x)
#define exc(x, a, b) for (auto x = (a); x <  (b); ++x)
#define inc(x, a, b) for (auto x = (a); x <= (b); ++x)
#define cxe(x, a, b) for (auto x = (b) - 1; x >= (a); --x)
#define cni(x, a, b) for (auto x = (b)    ; x >= (a); --x)

using namespace std;

const int mod = (int) 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef double dbl;
typedef pair<int, int> mti;

namespace math {
  inline void add(int &a, int b, int p = mod) {
    a + b >= p ? a = a + b - p : a = a + b;
  }
  inline void sub(int &a, int b, int p = mod) {
    a - b < 0 ? a = a - b + p : a = a - b;
  }
  inline int mul(int a, int b, int p = mod) {
    return (long long) a * b % p;
  }
  inline int modexp(int a, int x, int p = mod) {
    int res = 1;
    for (; x; x >>= 1) {
      if (x & 1) {
        res = mul(res, a, p);
      }
      a = mul(a, a, p);
    }
    return res;
  }
};
using namespace math;

namespace io {
  template <typename T = int>
  inline T read() {
    T x = 0;
    int f = 1;
    // char ch = cin.get();
    // for (; !isdigit(ch) && !cin.eof(); cin.get(ch)) {
    //   f = (ch == '-') ? -1 : 1;
    // }
    // for (; isdigit(ch) && !cin.eof(); cin.get(ch)) {
    //   x = x * 10 + ch - '0';
    // }
    char ch = getchar();
    for (; !isdigit(ch); ch = getchar()) {
      f = (ch == '-') ? -1 : 1;
    }
    for (; isdigit(ch); ch =getchar()) {
      x = x * 10 + ch - '0';
    }
    return f * x;
  }

  template <typename T = int>
  inline void write(T x, char ch = '\n') {
    static char stk[255];
    static int top = 0;
    if (x < 0) {
      cout.put('-');
      x = -x;
    }
    if (x == 0) {
      cout.put('0');
      cout.put(ch);
      return;
    }
    top = 0;
    while (x) {
      stk[top++] = x % 10 + '0';
      x /= 10;
    }
    while (top) {
      cout.put(stk[--top]);
    }
    cout.put(ch);
  }
}
using namespace io;
template <typename T>
vector<T>& operator << (vector<T> &v, T x) {
  return v.push_back(x), v;
}

//head;

const int N = 1e6 + 5;

int n;
int m;
int q;

inline int gcd(int a, int b) {
  return !b ? a : gcd(b, a % b);
}

void exgcd(int a, int b, long long &x, long long &y) {
  if (!b) {
    x = 1;
    y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y -= (a / b) * x;
}

class dsu {
public:
  int fa[N];
  int g[N];
  int r[N];

  int find(int x) {
    if (fa[x] == x) {
      return x;
    }
    int pre = fa[x];
    int now = find(fa[x]);
    math::add(r[x], r[pre], m);
    fa[x] = now;
    return now;
  }

  void add(int u, int v, int w) {
    int fx = find(u);
    int fy = find(v);
    int len = (r[u] + (ll)r[v] + w) % m;
    if (fx == fy) {
      g[fx] = gcd(g[fx], len);
      g[fx] = gcd(g[fx], w * 2 % m);
    } else {
      r[fx] = (w + r[u]) % m;
      fa[fx] = v;
      g[fx] = gcd(g[fx], w * 2 % m);
      g[fy] = gcd(g[fy], g[fx]);
    } 
  }

  int getlen(int u, int v) {
    int fx = find(u);
    int fy = find(v);
    if (fx == fy) {
      return (r[u] + r[v]) % m;
    } else {
      return -1;
    }
  }

  int getg(int u) {
    return g[find(u)];
  }
      

  dsu() {
    rep (i, N) {
      fa[i] = i;
    }
  }
} d;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  n = read();
  m = read();
  q = read();
  rep (i, q) {
    int op;
    op = read();
    if (op == 1) {
      int u, v, w;
      u = read();
      v = read();
      w = read();
      --u;
      --v;
      d.add(u, v, w);
    } else {
      int u, v, x, b, c;
      u = read();
      v = read();
      x = read();
      b = read();
      c = read();

      --u;
      --v;
      int w = d.getlen(u, v);
      if (w == -1) {
        write(0);
      } else {
        w = (w - x) % m;
        int p = gcd(d.getg(u), m);
        long long s, t;
        exgcd(b, p, s, t);
        int l = gcd(b, p);
        s = s % p;
        if (w % l == 0) {
          s = s * (w / l);
          l = p / l;
          s %= l;
          if (s < 0) {
            s += l;
          }
          if (s > c - 1) {
            write(0);
          } else {
            write((c - 1 - s) / l + 1);
          }
        } else {
          write(0);
        }
      }
    }
  }
  flush(cout);
  return 0;
}