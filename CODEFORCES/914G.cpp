#include <bits/stdc++.h>

using namespace std;

namespace XDYIMCMI0LY {
  
  struct reader {
    template <typename T> 
    reader &operator >> (T &x) {
      cin >> x;
      return *this;
    }
    reader &operator >> (int &x) {
      x = 0;
      int f = 1;
      char ch = cin.get();
      for (; !isdigit(ch); cin.get(ch)) {
        f = (ch == '-') ? - 1 : 1;
      }
      do {
        x = x * 10 + (ch & 15);
      } while (cin.get(ch) && isdigit(ch));
      x *= f;
      return *this;
    }
  } input;

  struct writer {
    template <typename T> 
    writer &operator << (T x) {
      cout << x;
      return *this;
    }
    writer &operator << (int x) {
      if (!x) {
        cout.put('0');
      } else {
        if (x < 0) {
          cout.put('-');
          x = -x;
        }
        static int s[81];
        register int t = 0;
        while (x) {
          s[++t] = x % 10;
          x /= 10;
        }
        while (t) {
          cout.put('0' + s[t--]);
        }
      }
      return *this;
    }
    writer &operator << (char x) {
      cout.put(x);
      return *this;
    }
  } output;

  const int N = 131072 + 5;
  const int mod = 1e9 + 7;
  const int M = 18;
  const int inv2 = (mod + 1) / 2;

  int n;
  int cnt[N];

  int add(int a, int b) {
    return (a + b >= mod) ? a + b - mod : a + b;
  }
  int sub(int a, int b) {
    return (a - b < 0) ? a - b + mod : a - b;
  }
  int mul(int a, int b) {
    return (long long) a * b % mod;
  }

  struct multi {
    int x[N];
    int y[N];
    int p[M][N];
    int q[M][N];
    int sum[M][N];
    int count[N];
    vector<int> multi_xor(const vector<int> &_x, const vector<int> &_y) {
      int m = max(_x.size(), _y.size());
      int n = 1;
      while (n < m) {
        n <<= 1;
      }
      for (int i = 0; i < n; ++i) {
        x[i] = (i < (int) _x.size()) ? _x[i] : 0;
        y[i] = (i < (int) _y.size()) ? _y[i] : 0;
      }
      for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += k * 2) {
          for (int j = i; j < i + k; ++j) {
            int a = x[j];
            int b = x[j + k];
            x[j] = add(a, b);
            x[j + k] = sub(a, b);
            a = y[j];
            b = y[j + k];
            y[j] = add(a, b);
            y[j + k] = sub(a, b);
          }
        }
      }
      for (int i = 0; i < n; ++i) {
        x[i] = mul(x[i], y[i]);
      }
      for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += k * 2) {
          for (int j = i; j < i + k; ++j) {
            int a = x[j];
            int b = x[j + k];
            x[j] = mul(add(a, b), inv2);
            x[j + k] = mul(sub(a, b), inv2);
          }
        }
      }
      vector<int> res;
      for (int i = 0; i < n; ++i) {
        res.push_back(x[i]);
      }
      return res;
    }
    vector<int> multi_or(const vector<int> &_x, const vector<int> &_y) {
      int m = max(_x.size(), _y.size());
      int n = 1;
      while (n < m) {
        n <<= 1;
      }
      for (int i = 0; i < n; ++i) {
        x[i] = (i < (int) _x.size()) ? _x[i] : 0;
        y[i] = (i < (int) _y.size()) ? _y[i] : 0;
      }
      for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += k * 2) {
          for (int j = i; j < i + k; ++j) {
            x[j + k] = add(x[j + k], x[j]);
            y[j + k] = add(y[j + k], y[j]);
          }
        }
      }
      for (int i = 0; i < n; ++i) {
        x[i] = mul(x[i], y[i]);
      }
      for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += k * 2) {
          for (int j = i; j < i + k; ++j) {
            x[j + k] = sub(x[j + k], x[j]);
          }
        }
      }
      vector<int> res;
      for (int i = 0; i < n; ++i) {
        res.push_back(x[i]);
      }
      return res;
    }

    vector<int> multi_and(const vector<int> &_x, const vector<int> &_y) {
      int m = max(_x.size(), _y.size());
      int n = 1;
      while (n < m) {
        n <<= 1;
      }
      for (int i = 0; i < n; ++i) {
        x[i] = (i < (int) _x.size()) ? _x[i] : 0;
        y[i] = (i < (int) _y.size()) ? _y[i] : 0;
      }
      for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += k * 2) {
          for (int j = i; j < i + k; ++j) {
            x[j] = add(x[j], x[j + k]);
            y[j] = add(y[j], y[j + k]);
          }
        }
      }
      for (int i = 0; i < n; ++i) {
        x[i] = mul(x[i], y[i]);
      }
      for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += k * 2) {
          for (int j = i; j < i + k; ++j) {
            x[j] = sub(x[j], x[j + k]);
          }
        }
      }
      vector<int> res;
      for (int i = 0; i < n; ++i) {
        res.push_back(x[i]);
      }
      return res;
    }
    
    vector<int> multi_sub(const vector<int> &_x, const vector<int> &_y) {
      int m = max(_x.size(), _y.size());
      int n = 1;
      int bit = 0;
      while (n < m) {
        n <<= 1;
        ++bit;
      }
      for (int i = 0; i <= bit; ++i) {        
        memset(p[i], 0, n << 2);
        memset(q[i], 0, n << 2);
        memset(sum[i], 0, n << 2);
      }
      for (int i = 1; i < n; ++i) {
        count[i] = count[i >> 1] + (i & 1);
      }
      for (int i = 0; i < n; ++i) {
        p[count[i]][i] = i < (int) _x.size() ? _x[i] : 0;
        q[count[i]][i] = i < (int) _y.size() ? _y[i] : 0;
      }
      for (int s = 0; s <= bit; ++s) {
        for (int k = 1; k < n; k <<= 1) {
          for (int i = 0; i < n; i += k * 2) {
            for (int j = i; j < i + k; ++j) {
              int a = p[s][j];
              int b = p[s][j + k];
              p[s][j] = add(a, b);
              p[s][j + k] = sub(a, b);
              a = q[s][j];
              b = q[s][j + k];
              q[s][j] = add(a, b);
              q[s][j + k] = sub(a, b);
            }
          }
        }
      }
      for (int i = 0; i <= bit; ++i) {
        for (int j = 0; j <= i; ++j) {
          for (int k = 0; k < n; ++k) {
            sum[i][k] = add(sum[i][k], mul(p[j][k], q[i - j][k]));
          }
        }
      }
      for (int s = 0; s <= bit; ++s) {
        for (int k = 1; k < n; k <<= 1) {
          for (int i = 0; i < n; i += k * 2) {
            for (int j = i; j < i + k; ++j) {
              int a = sum[s][j];
              int b = sum[s][j + k];
              sum[s][j] = mul(add(a, b), inv2);
              sum[s][j + k] = mul(sub(a, b), inv2);
            }
          }
        }
      }
      vector<int> res;
      for (int i = 0; i < n; ++i) {
        res.push_back(sum[count[i]][i]);
      }
      return res;
    }
  } calc;

  int fib[N];
  
  void _main() {
    input >> n;
    static int a[1000000 + 5];
    for (int i = 1; i <= n; ++i) {
      input >> a[i];
    }
    vector<int> s;
    int mx = *max_element(a + 1, a + 1 + n);
    int len = 1;
    while (len <= mx) {
      len <<= 1;
    }
    s.resize(mx + 1);
    for (int i = 1; i <= n; ++i) {
      ++s[a[i]];
    }
    fib[1] = 1;
    for (int i = 2; i < len; ++i) {
      fib[i] = add(fib[i - 1], fib[i - 2]);
    }
    vector<int> f1 = calc.multi_sub(s, s);
    vector<int> f2 = calc.multi_xor(s, s);
    s.resize(len, 0);
    mx = len;
    vector<int> f3 = s;
    for (int i = 0; i < mx; ++i) {
      f1[i] = mul(f1[i], fib[i]);
      f2[i] = mul(f2[i], fib[i]);
      f3[i] = mul(f3[i], fib[i]);
    }
    f1 = calc.multi_and(f3, (f1 = calc.multi_and(f1, f2)));
    int ans = 0;
    for (int i = 0; i < 17; ++i) {
      if ((1 << i) < (int) f1.size()) {
        ans = add(ans, f1[1 << i]);
      }
    }
    output << ans << '\n';
  }
}

int main() {
//  freopen("chocolate.in", "r", stdin);
//  freopen("chocolate.out", "w", stdout);
  cin.tie(0);
  ios::sync_with_stdio(false);

  XDYIMCMI0LY::_main();
  // fclose(stdin);
  // fclose(stdout);
  
  return 0;
}

