#include <bits/stdc++.h>

using namespace std;

namespace UNIVERSE {

  template <typename T> 
  int sz(const T &x) {
    return x.size();
  }

  template <typename T> 
  T sqr(const T &x) {
    return x * x;
  }

  template <typename T> 
  inline int get_bit(const T &x, const int &p) {
    return (x >> p) & 1;
  }

  template <typename T> 
  inline void mod_bit(const T &x, const int &p, const int &v) {
    x = (x | (1ll << p)) & (((long long)v) << p);
  }

  template <typename T> 
  inline int cnt_bit(const T &x) {
    return __builtin_popcountll(x);
  }

  template <typename T> 
  inline int l_bit(const T &x) {
    return 63 - __builtin_clzll(x);
  }

  template <typename T> 
  inline int r_bit(const T &x) {
    return __builtin_ctzll(x);
  }

  inline void print_bit(int &x) {
    for (int i = 0; i < 32; ++i) {
      cerr << (x < 0);
      x <<= 1;
    }
    cerr << endl;
  }

  inline void print_bit(long long &x) {
    for (int i = 0; i < 64; ++i) {
      cerr << (x < 0);
      x <<= 1;
    }
    cerr << endl;
  }

  template <typename T> 
  inline T lowbit(const T x) {
    return x & -x;
  }

  template <typename A, typename B> 
  inline bool ckmin(A &a, const B &b) {
    return (a > b) ? (a = b, 1) : 0;
  }

  template <typename A, typename B> 
  inline bool ckmax(A &a, const B &b) {
    return (a < b) ? (a = b, 1) : 0;
  }

  inline void fileio(const string &ss) {
    freopen((ss + ".in").c_str(), "in", stdin);
    freopen((ss + ".out").c_str(), "out", stdout);
  }

}
#if __cplusplus >= 201103L
namespace DEBUG {

  using std::to_string;

  string to_string(string s) {
    return '"' + s + '"';
  }

  string to_string(const char* s) {
    return to_string((string) s);
  }


  string to_string(bool b) {
    return (b ? "true" : "false");
  }

  template <typename A, typename B>
  string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
  }

  template <typename A>
  string to_string(A v) {
    using std::begin;
    using std::end;
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
      if (!first) {
        res += ", ";
      }
      first = false;
      res += to_string(x);
    }
    res += "}";
    return res;
  }

  template <typename T> 
  string to_string(T *s, T *e) {
    bool first = true;
    string res = "{";
    for (; s <= e; ++s) {
      if (!first) {
        res += ", ";
      }
      first = false;
      res += to_string(*s);
    }
    res += "}";
    return res;
  }

  void debug_out() {
    cerr << endl;
  }

  template <typename Head, typename... Tail>
  void debug_out(Head *S, Head *E, Tail... T) {
    cerr << " " << to_string(S, E);
    debug_out(T...);
  }

  template <typename Head, typename... Tail>
  void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
  }


#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

}
#else 
#define debug(...) 42
#endif
namespace MATH {

  const int mod = (int)1e9 + 7;

  inline int add() {
    return 0;
  }
  inline int sub() {
    return 0;
  }
  inline int mul() {
    return 1;
  }

#if __cplusplus >= 201103L

  template <typename Head, typename... Tail>
  inline int add(Head H, Tail... T) {
    return (H += add(T...)) >= mod ? H - mod : H;
  }

  template <typename Head, typename... Tail>
  inline int sub(Head H, Tail... T) {
    return (H -= add(T...)) < 0 ? H + mod : H;
  }

  template <typename Head, typename... Tail>
  inline int mul(Head H, Tail... T) {
    return (int) ((long long) H * mul(T...) % mod);
    // unsigned long long x = (long long) H * mul(T...);
    // unsigned xh = (unsigned) (x >> 32);
    // unsigned xl = (unsigned) x;
    // unsigned d, m;
    // _del_asm(
    //   "divl %4; \n\t"
    //   : "=a" (d), "=d" (m)
    //   : "d" (xh), "a" (xl), "r" (mod)
    //   );
    // return m;
  }

#else
  
  template <typename A, typename B>
  inline int add(A H, B T) {
    return (H += T) >= mod ? H - mod : H;
  }

  template <typename A, typename B>
    inline int sub(A H, B T) {
    return (H -= T) < 0 ? H + mod : H;
  }

  template <typename A, typename B>
    inline int mul(A H, B T) {
    return (int) ((long long) H * T % mod);
    // unsigned long long x = (long long) H * T;
    // unsigned xh = (unsigned) (x >> 32);
    // unsigned xl = (unsigned) x;
    // unsigned d, m;
    // _del_asm(
    //   "divl %4; \n\t"
    //   : "=a" (d), "=d" (m)
    //   : "d" (xh), "a" (xl), "r" (mod)
    //   );
    // return m;
  }

#endif
  
  template <typename T> 
  inline T modexp(T a, long long x) {
    T ret = 1;
    while (x) {
      if (x & 1) {
        ret = mul(ret, a);
      }
      a = mul(a, a);
      x >>= 1;
    }
    return ret;
  }

  template <typename T> 
  T gcd(T a, T b) {
    return !b ? a : gcd(b, a % b);
  }
                      
  template <typename T> 
  void exgcd(T a, T b, long long &x, long long &y) {
    if (!b) {
      x = 1;
      y = 0;
      return;
    }
    exgcd(b, a % b, y, x);
    y -= (a / b) * x;
  }

  template <typename T> 
  inline T inv(T a) {
    long long x;
    long long y;
    exgcd(a, mod, x, y);
    return ((x % mod) + mod) % mod;
  }

}
namespace FASTIO{
  const int BUF_SIZE = 102400; 
  const int OUT_SIZE = 102400;

  bool IOERR = 0;

  inline char nxt_char() {
    static char buf[BUF_SIZE];
    static char *p = buf;
    static char *pend = buf;

    if (p == pend) {
      p = buf; 
      pend = buf + fread(buf, 1, BUF_SIZE, stdin);
      if (pend == p) {
        IOERR = 1;
        return -1;
      }
    }
    return *p++;
  }

  inline void read(int &x) {
    bool sign = 0;
    char ch = nxt_char();
    x = 0;
    for (; isspace(ch); ch = nxt_char());
    if (IOERR) {
      x = INT_MAX;
      return;
    }
    if (ch == '-') {
      sign = 1;
      ch = nxt_char();
    }
    for (; isdigit(ch); ch = nxt_char()) {
      x = x * 10 + ch - '0';
    }
    if (sign) {
      x = -x;
    }
  }

  inline void read(long long &x) {
    bool sign = 0;
    char ch = nxt_char();
    x = 0;
    for (; isspace(ch); ch=nxt_char());
    if (IOERR) {
      x = LLONG_MAX;
      return;
    }
    if (ch == '-') {
      sign = 1;
      ch = nxt_char();
    }
    for (; isdigit(ch); ch = nxt_char()) {
      x = x * 10 + ch - '0';
    }
    if (sign) {
      x = -x;
    }
  }

  inline void read(double &x) {
    bool sign = 0;
    char ch = nxt_char();
    x = 0;
    for (; isspace(ch); ch=nxt_char());
    if (IOERR) {
      x = DBL_MAX;
      return;
    }
    if (ch == '-') { 
      sign = 1;
      ch = nxt_char();
    }
    for (; isdigit(ch); ch = nxt_char()) {
      x = x * 10 + ch - '0';
    }
    if (ch == '.') {
      double tmp = 1; 
      ch = nxt_char();
      for (; isdigit(ch); ch = nxt_char()) {
        tmp /= 10.0;
        x += tmp * (ch - '0');
      }
    }
    if (sign) {
      x = -x;
    }
  }

  inline void read(char *s) {
    char ch = nxt_char();
    for (; isspace(ch); ch = nxt_char());
    if (IOERR) {
      *s = 0;
      return;
    }
    for (; !isspace(ch) && !IOERR; ch = nxt_char()) {
      *s++ = ch;
    }
    *s = 0;
  }

  inline void read(char &c) {
    for (c = nxt_char(); isspace(c); c = nxt_char());
    if (IOERR) {
      c = -1;
      return;
    }
  }

  struct Ostream_fwrite{
    char *buf;
    char *p;
    char *pend;
    Ostream_fwrite() {
      buf = new char[BUF_SIZE];
      p = buf;
      pend = buf + BUF_SIZE;
    }
    
    inline void out(char ch) {
      if (p == pend) {
        fwrite(buf, 1, BUF_SIZE, stdout);
        p = buf;
      }
      *p++ = ch;
    }
    
    inline void print(int x){
      static char s[15];
      static char *s1;
      s1 = s;
      if (!x) {
        *s1++ = '0';
      }
      if (x < 0) {
        out('-');
        x = -x;
      }
      while (x) {
        *s1++ = x % 10 + '0';
        x /= 10;
      }
      while (s1-- != s) {
        out(*s1);
      }
    }

    inline void print(long long x) {
      static char s[25];
      static char *s1;
      s1 = s;
      if (!x) {
        *s1++ = '0';
      }
      if (x < 0) {
        out('-');
        x = -x;
      }
      while (x) {
        *s1++ = x % 10 + '0';
        x /= 10;
      }
      while (s1-- != s) {
        out(*s1);
      }
    }

    inline void print(double x, int y) {
      static long long mul[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,
                                1000000000,10000000000ll,100000000000ll,1000000000000ll, 10000000000000ll,
                                100000000000000ll,1000000000000000ll,10000000000000000ll, 100000000000000000ll};
      if (x < -1e-12) {
        out('-');
        x = -x;
      }
      x *= mul[y];
      long long x1 = (long long) floor(x); 
      if (x - floor(x) >= 0.5) {
        ++x1;
      }
      long long x2 = x1 / mul[y];
      long long x3 = x1 - x2 * mul[y];
      print(x2);
      if (y > 0) {
        out('.'); 
        for (int i = 1; i < y && x3 * mul[i] < mul[y]; out('0'), ++i); 
        print(x3);
      }
    }

    inline void print(char *s) {
      while (*s) {
        out(*s++);
      }
    }

    inline void flush() { 
      if (p != buf) { 
        fwrite(buf, 1, p - buf, stdout);
        p = buf;
      } 
    }
    ~Ostream_fwrite() {
      flush();
    }
  } Ostream;

  inline void print(int x) {
    Ostream.print(x);
  }

  inline void println(int x) {
    Ostream.print(x);
    Ostream.out('\n');
  }

  inline void print(char x) {
    Ostream.out(x);
  }

  inline void println(char x) {
    Ostream.out(x);
    Ostream.out('\n');
  }

  inline void print(long long x) {
    Ostream.print(x);
  }

  inline void println(long long x) {
    Ostream.print(x);
    Ostream.out('\n');
  }

  inline void print(double x,int y) {
    Ostream.print(x, y);
  }

  inline void println(double x,int y) {
    Ostream.print(x, y);
    Ostream.out('\n');
  }

  inline void print(char *s) {
    Ostream.print(s);
  }

  inline void println(char *s) {
    Ostream.print(s);
    Ostream.out('\n');
  }

  inline void println() {
    Ostream.out('\n');
  }

  inline void flush() {
    Ostream.flush();
  }

};
using namespace FASTIO;
using namespace MATH;
using namespace UNIVERSE;
#if __cplusplus >= 201103L
using namespace DEBUG;
#endif

namespace XDYIMCMI0LY {

  const int N = 1e5 + 5;
  const int M = 4e5 + 5;

  int n;
  int m;
  int t;

  namespace sol1 {

    int head[N];
    int nxt[M];
    int ver[M];
    int id[M];

    int vis[M];
    int deg[N];

    inline void add_edge(int u, int v, int x) {
      static int tot = 0;
      ++tot;
      id[tot] = x;
      ver[tot] = v;
      nxt[tot] = head[u];
      head[u] = tot;
    }

    void dfs(int u, vector<int> &res) {
      for (int &o = head[u]; o; o = nxt[o]) {
        int k = id[o];
        int f = o & 1;
        if (!vis[k]) {
          vis[k] = 1;
          dfs(ver[o], res);        
          res.push_back(f ? k : -k);
        }
      }
    }

    vector<int> solve() {
      read(n);
      read(m);
      for (int i = 1, u, v; i <= m; ++i) {
        read(u);
        read(v);
        add_edge(u, v, i);
        add_edge(v, u, i);
        ++deg[u];
        ++deg[v];
      }
      for (int i = 1; i <= n; ++i) {
        if (deg[i] & 1) {
          return vector<int>();
        }
      }
      vector<int> res;
      for (int i = 1; i <= n; ++i) {
        if (deg[i]) {
          dfs(i, res);
          break;
        }
      }
      reverse(res.begin(), res.end());
      return res;
    }
  }

  namespace sol2 {

    int head[N];
    int nxt[M];
    int ver[M];
    int id[M];

    int vis[M];
    int in_deg[N];
    int out_deg[N];

    inline void add_edge(int u, int v, int x) {
      static int tot = 0;
      ++tot;
      id[tot] = x;
      ver[tot] = v;
      nxt[tot] = head[u];
      head[u] = tot;
    }

    void dfs(int u, vector<int> &res) {
      for (int &o = head[u]; o; o = nxt[o]) {
        int k = id[o];
        if (!vis[k]) {
          vis[k] = 1;
          dfs(ver[o], res);
          res.push_back(k);
        }
      }
    }

    vector<int> solve() {
      read(n);
      read(m);
      for (int i = 1, u, v; i <= m; ++i) {
        read(u);
        read(v);
        add_edge(u, v, i);
        ++out_deg[u];
        ++in_deg[v];
      }
      for (int i = 1; i <= n; ++i) {
        if (out_deg[i] != in_deg[i]) {
          return vector<int>();
        }
      }
      vector<int> res;
      for (int i = 1; i <= n; ++i) {
        if (out_deg[i]) {
          dfs(i, res);
          break;
        }
      }
      reverse(res.begin(), res.end());
      return res;
    }
  }

  void _main() {
    read(t);
    vector<int> res;
    if (t == 1) {
      res = sol1::solve();
    } else {
      res = sol2::solve();
    }
    debug(sz(res));
    static char r[] = "NO";
    static char f[] = "YES";
    if (sz(res) < m) {
      println(r);
    } else {
      println(f);
      for (int i = 0; i < sz(res); ++i) {
        if (i) {
          print(' ');
        }
        print(res[i]);
      }
      println();
    }
    return;
  }

}

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  
#if !LOCAL && !ONLINE_JUDGE
  fileio("");
#endif

  XDYIMCMI0LY::_main();

#if !LOCAL && !ONLINE_JUDGE
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
