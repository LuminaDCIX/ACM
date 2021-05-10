#include <bits/stdc++.h>

using namespace std;

namespace UNIVERSE {

  template <typename T> int sz(T x) {
    return x.size();
  }

  template <typename T> int get_bit(T x, int p) {
    return (x >> p) & 1;
  }

  template <typename T> void mod_bit(T &x, int p, int v) {
    x = (x | (1ll << p)) & ((long long)v << p);
  }

  template <typename T> int cnt_bit(T x) {
    return __builtin_popcount(x);
  }

  template <typename A, typename B> bool ckmin(A a, B b) {
    return (a > b) ? (a = b, 1) : 0;
  }

  template <typename A, typename B> bool ckmax(A a, B b) {
    return (a < b) ? (a = b, 1) : 0;
  }

}
#ifdef LOCAL
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
    for (; s != e; ++s) {
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
#endif
namespace MATH {

  const int P = (int)1e9 + 7;

  inline int add() {
    return 0;
  }
  inline int sub() {
    return 0;
  }
  inline int mul() {
    return 1;
  }

  template <typename Head, typename... Tail>
  inline int add(Head H, Tail... T) {
    return (H + add(T...)) % P;
  }

  template <typename Head, typename... Tail>
  inline int sub(Head H, Tail... T) {
    return ((H - add(T...)) % P + P) % P;
  }

  template <typename Head, typename... Tail>
  inline int mul(Head H, Tail... T) {
    return ((long long) H * mul(T...)) % P;
  }

  template <typename T> 
  T modexp(T a, long long x) {
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
  T inv(T a) {
    long long x;
    long long y;
    exgcd(a, P, x, y);
    return ((x % P) + P) % P;
  }

}
namespace FASTIO{
#define BUF_SIZE 102400
#define OUT_SIZE 102400

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

  inline bool blank(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
  }

  inline void read(int &x) {
    bool sign = 0;
    char ch = nxt_char();
    x = 0;
    for (; blank(ch); ch=nxt_char());
    if (IOERR) {
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
    for (; blank(ch); ch=nxt_char());
    if (IOERR) {
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
    for (; blank(ch); ch=nxt_char());
    if (IOERR) {
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
    for (; blank(ch); ch = nxt_char());
    if (IOERR) {
      return;
    }
    for (; !blank(ch) && !IOERR; ch = nxt_char()) {
      *s++ = ch;
    }
    *s = 0;
  }

  inline void read(char &c) {
    for (c = nxt_char(); blank(c); c = nxt_char());
    if (IOERR) {
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
    
    void out(char ch) {
      if (p == pend) {
        fwrite(buf, 1, BUF_SIZE, stdout);
        p = buf;
      }
      *p++ = ch;
    }
    
    void print(int x){
      static char s[15];
      static char *s1;
      s1 = s;
      if (!x) {
        *s1++ = '0';
        if (x < 0) {
          out('-');
          x = -x;
        }
      }
      while (x) {
        *s1++ = x % 10 + '0';
        x /= 10;
      }
      while (s1-- != s) {
        out(*s1);
      }
    }

    void print(long long x) {
      static char s[25];
      static char *s1;
      s1 = s;
      if (!x) {
        *s1++ = '0';
        if (x < 0) {
          out('-');
          x = -x;
        }
      }
      while (x) {
        *s1++ = x % 10 + '0';
        x /= 10;
      }
      while (s1-- != s) {
        out(*s1);
      }
    }

    void print(double x, int y) {
      static long long mul[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,
                                1000000000,10000000000ll,100000000000ll,1000000000000ll, 10000000000000ll,
                                100000000000000ll,1000000000000000ll,10000000000000000ll, 100000000000000000ll};
      if (x < -1e-12) {
        out('-');
        x = -x;
        x *= mul[y];
      }
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

    void print(char *s) {
      while (*s) {
        out(*s++);
      }
    }

    void flush() { 
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
#ifdef LOCAL
using namespace DEBUG;
#endif

namespace XDYIMCMI0LY {

  const int N = 1e5 + 5;

  int n,a[N];

  long long s[N];

  struct pnt {
    long long x;
    long long y;
    pnt(long long _x=0,long long _y=0):x(_x),y(_y){};

    bool operator < (const pnt &rhs) const {
      return x==rhs.x?y<rhs.y:x<rhs.x;
    }
    long long det(const pnt &rhs) const {
      return x*rhs.y-y*rhs.x;
    }
    pnt operator - (const pnt &rhs) const {
      return pnt(x-rhs.x,y-rhs.y);
    }
    long long val(long long k) {
      return y-x*k;
    }
  };
    
  vector <pnt> hull[N<<2];
  vector <pnt> q;
  vector <pnt> operator + (const vector <pnt> &a, const vector <pnt> &b) {
    vector <pnt> ret;
    q.clear();

    int i=0;
    int j=0;
    while (i<(int)a.size()&&j<(int)b.size()) {
      (a[i]<b[j])?q.push_back(a[i++]):q.push_back(b[j++]);
    }
    while (i<(int)a.size()) {
      q.push_back(a[i++]);
    }
    while (j<(int)b.size()) {
      q.push_back(b[j++]);
    }

    for (int i=0;i<(int)q.size();++i) {
      while (ret.size()>=2&&(ret[(int)ret.size()-1]-ret[(int)ret.size()-2]).det(q[i]-ret[(int)ret.size()-1])<=0) {
        ret.pop_back();
      }
      ret.push_back(q[i]);
    }
    return ret;
  }

  void build(int o,int ll,int rr) {
    if (ll==rr) {
      int i=ll;
      hull[o].push_back(pnt(-a[i],-s[i]+a[i]*(long long)i));
      return ;
    }
    int mid=(ll+rr)>>1;
    build(o*2,ll,mid);
    build(o*2+1,mid+1,rr);
    hull[o]=hull[o*2]+hull[o*2+1];
  }

  long long getmn(vector <pnt> &h,long long k) {
    int l=0;
    int r=(int)h.size()-1;
    long long ret=INT_MAX;
    while (r-l>3) {
      int lm=l+(r-l+1)/3;
      int rm=r-(r-l+1)/3;
      if (h[lm].val(k)>h[rm].val(k)) {
        l=lm;
      } else {
        r=rm;
      }
            
    }
    for (int i=l;i<=r;++i) {
      ret=min(ret,h[i].val(k));
    }
    return ret;
  }
    
  void qry(int o,int ll,int rr,int l,int r,long long k,long long &ans) {
    if (ll>=l&&rr<=r) {
      ans=min(getmn(hull[o],k),ans);
      return;
    }
    int mid=(ll+rr)>>1;
    if (l<=mid) {
      qry(o*2,ll,mid,l,r,k,ans);
    }
    if (r>mid) {
      qry(o*2+1,mid+1,rr,l,r,k,ans);
    }
  }
    
  int _main() {
    read(n);
    for (int i=1;i<=n;++i) {
      read(a[i]);
      s[i]=s[i-1]+a[i];
    }
    build(1,1,n);
    int q;
    read(q);
    while (q--) {
      int x, y;
      read(x),read(y);
      long long ans=INT_MAX;
      qry(1,1,n,max(1,y-x+1),y,x-y,ans);
      ans+=s[y];
      println(ans);
    }
    return 0;
  }
}

int main() {
  ios::sync_with_stdio(false);
  return XDYIMCMI0LY::_main();
}