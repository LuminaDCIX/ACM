#include <bits/stdc++.h>

#define st first
#define nd second
#define com make_pair
#define lowbit(x) (x & -x)
#define sz(x) ((int)x.size())
#define all(x) x.begin(), x.end()
#define mem(x, v) memset(x, v, sizeof(x))
#define rep(x, n) for (int x = 0      ; x <  (n); ++x)
#define per(x, n) for (int x = (n) - 1; i >= 0  ; --x)
#define exc(x, a, b) for (auto x = (a); x <  (b); ++x)
#define inc(x, a, b) for (auto x = (a); x <= (b); ++x)
#define cxe(x, a, b) for (auto x = (b) - 1; x >= (a); --x)
#define cni(x, a, b) for (auto x = (b)    ; x >= (a); --x)
#define debug(x) cerr <<__LINE__ << " " << #x << " = " << x << endl;

using namespace std;

const int mod = (int) 1e9 + 7;

typedef long long ll;
typedef vector<int> vi;
typedef double dbl;
typedef pair<int, int> mti;

namespace math {
  inline void add(int &a, int b, int p = mod) { a + b >= p ? a = a + b - p : a = a + b; }
  inline void sub(int &a, int b, int p = mod) { a - b < 0 ? a = a - b + p : a = a - b; }
  inline int mul(int a, int b, int p = mod) { return (long long) a * b % p; }
  inline int modexp(int a, int x, int p = mod) {
    int res = 1;
    for (; x; x >>= 1, a = mul(a, a, p)) if (x & 1) res = mul(res, a, p);
    return res;
  }
};
using namespace math;

namespace io {
  template <typename T = int>
  inline T read() {
    T x = 0;
    int f = 1;
    char ch = cin.get();
    for (; !isdigit(ch) && !cin.eof(); cin.get(ch)) { f = (ch == '-') ? -1 : 1; }
    for (; isdigit(ch) && !cin.eof(); cin.get(ch)) { x = x * 10 + ch - '0'; }
    return f * x;
  }

  template <typename T = int>
  inline void write(T x, char ch = '\n') {
    static char stk[255];
    static int top = 0;
    if (x < 0) cout.put('-'), x = -x;
    if (x == 0) cout.put('0');
    else {
      top = 0;
      while (x) stk[top++] = x % 10 + '0', x /= 10;
      while (top) cout.put(stk[--top]);
    }
    cout.put(ch);
  }
}
using namespace io;

template<typename T>
struct arr {
  T *a;
  int n;
  inline void doubly(int x) {
    T *b = a;
    a = new T[x];
    copy(b, b + n, a);
    delete b;
  }
  inline arr<T>& operator << (T x) {
    if (lowbit(n) == n) doubly(n << 1);
    a[n++] = x;
    return *this;
  }
  inline void resize(int x) {
    if (n < x) doubly(1 << (32 - __builtin_clz(x)));
    n = x;
  }
  inline T& operator [] (int x) { return a[x]; }
  inline T* begin() { return a; }
  inline T* end() { return a + n; }
  inline void clear() { n = 0; }
  inline arr() { n = 0, a = NULL; };
  inline arr(int x) { n = 0, a = NULL, resize(x); }
};

const int N = 2e5 + 5;
const int MAX = (N << 2) + 5;

struct mat {
  int m[5][5];
  mat() { mem(m, 0x3f); }
};

mat operator * (mat a, mat b) {
  mat c;
  rep (k, 5) rep (i, 5) rep (j, 5) c.m[i][j] = min(c.m[i][j], a.m[i][k] + b.m[k][j]);
  return c;
}

mat d[MAX];

void build(int x, int ll, int rr, mat *m) {
  int mid = (ll + rr) >> 1;
  if (ll == rr) {
    d[x] = m[ll];
    return;
  }
  build(x + x, ll, mid, m);
  build(x + x + 1, mid + 1, rr, m);
  d[x] = d[x + x] * d[x + x + 1];
}

void query(int x, int ll, int rr, int l, int r, mat &m) {
  if (ll >= l && rr <= r) {
    int ans[5];
    mem(ans, 0x3f);
    rep (i, 5) rep (j, 5) ans[i] = min(ans[i], m.m[0][j] + d[x].m[j][i]);
    rep (i, 5) m.m[0][i] = ans[i];
    return;
  }
  int mid = (ll + rr) >> 1;
  if (l <= mid) query(x + x, ll, mid, l, r, m);
  if (r > mid) query(x + x + 1, mid + 1, rr, l, r, m);
}

mat v[N];
char s[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  int n = read();
  int m = read();
  cin >> s;
  rep (i, n) {
    auto &c = v[i];
    rep (j, 5) c.m[j][j] = 0;
    switch (s[i]) {
    case '2':
      c.m[0][0] = 1;
      c.m[0][1] = 0;
      break;
    case '0':
      c.m[1][1] = 1;
      c.m[1][2] = 0;
      break;
    case '1':
      c.m[2][2] = 1;
      c.m[2][3] = 0;
      break;
    case '6':
      c.m[3][3] = 1;
      c.m[4][4] = 1;
      break;
    case '7':
      c.m[3][3] = 1;
      c.m[3][4] = 0;
      break;
    }
  }
  build(1, 0, n - 1, v); 

  
  rep (i, m) {
    int l = read() - 1;
    int r = read() - 1;
    mat c;
    c.m[0][0] = 0;
    query(1, 0, n - 1, l, r, c);
    write(c.m[0][4] == 0x3f3f3f3f ? -1 : c.m[0][4]);
  }
  
  flush(cout);
  return 0;
}
