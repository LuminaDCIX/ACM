#include <algorithm>
#include <iomanip>
#include <iostream>
#include <istream>
#include <map>
#include <numeric>
#include <ostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <cstring>

using namespace std;


class Solution {
 public:

  static const int N = 1e5 + 5;
  static const int M = 262144 + 5;
  static const int P = 998244353;

  static inline int add(int a, int b) {
    return a + b >= P ? a + b - P : a + b;
  }
  static inline int sub(int a, int b) {
    return a - b < 0 ? a - b + P : a - b;
  }
  static inline int mul(int a, int b) {
    return (long long) a * b % P;
  }
  static inline int modexp(int a, int x) {
    int ret = 1;
    while (x) {
      if (x & 1) {
        ret = mul(ret, a);
      }
      a = mul(a, a);
      x >>= 1;
    }
    return ret;
  }


  int n, m;
  int c[N];


  struct poly {
    int g[M];

    inline int rev(int x, int m) {
      int ret = 0;
      for (int i = 0; i < m; ++i) {
        ret <<= 1;
        ret |= x & 1;
        x >>= 1;
      }
      return ret;
    }

    inline void init(int lim) {
      g[0] = 1;
      g[1] = modexp(3, (P - 1) / lim);
      for (int i = 2; i < lim; ++i) {
        g[i] = mul(g[i - 1], g[1]);
      }
    }

    inline void dft(vector <int> &p, int m, int lim, int mod, int o) {
      p.resize(mod);
      p.resize(lim, 0);
      for (int i = 0; i < lim; ++i) {
        if (i < rev(i, m)) {
          swap(p[i], p[rev(i, m)]);
        }
      }
      for (int i = 0; i < m; ++i) {
        int len = 1 << i;
        for (int j = 0; j < lim; j += len * 2) {
          int wn = 0;
          for (int k = j; k < j + len; ++k) {
            int t = mul(p[k + len], g[wn]);
            p[k + len] = sub(p[k], t);
            p[k] = add(p[k], t);
            wn += o * (1 << (m - i - 1));
            if (wn < 0) {
              wn += lim;
            }
          }
        }
      }
      if (o == -1) {
        int inv = modexp(lim, P - 2);
        for (int i = 0; i < lim; ++i) {
          p[i] = mul(p[i], inv);
        }
      }
    }
    vector <int> inv(vector <int> &a, int mod) {
      if (mod == 1) {
        return vector <int>(1, modexp(a[0], P - 2));
      }
      vector <int> p = inv(a, (mod + 1) / 2);
      vector <int> q = a;
      int m = 0;
      while ((1 << m) < 2 * mod) {
        ++m;
      }
      int lim = 1 << m;
      init(lim);
      dft(p, m, lim, mod, 1);
      dft(q, m, lim, mod, 1);
      vector <int> ret;
      for (int i = 0; i < lim; ++i) {
        ret.push_back(mul(sub(2, mul(p[i], q[i])), p[i]));
      }
      dft(ret, m, lim, lim, -1);
      ret.resize(mod);
      return ret;
    }

    vector <int> sqrt(vector <int> &a, int mod) {
      if (mod == 1) {
        return vector <int>(1, 1);
      }
      vector <int> p = sqrt(a, (mod + 1) / 2);
      vector <int> q = a;
      vector <int> f = p;
      f.resize(mod, 0);
      for (int i = 0; i < mod; ++i) {
        f[i] = mul(2, f[i]);
      }
      f = inv(f, mod);
      int m = 0;
      while ((1 << m) < mod * 2) {
        ++m;
      }
      int lim = 1 << m;
      dft(p, m, lim, mod, 1);
      dft(q, m, lim, mod, 1);
      dft(f, m, lim, mod, 1);
      vector <int> ret;
      for (int i = 0; i < lim; ++i) {
        ret.push_back(mul(add(mul(p[i], p[i]), q[i]), f[i]));
      }
      dft(ret, m, lim, lim, -1);
      ret.resize(mod);
      return ret;
    }
  }
  p;


  void solve(std::istream & in, std::ostream & out) {
    in >> n;
    in >> m;
    ++m;
    for (int i = 1; i <= n; ++i) {
      int x;
      in >> x;
      c[x] = 1;
    }
    vector <int> C;
    for (int i = 0; i < m; ++i) {
      C.push_back(sub(0, 4 * c[i]));
    }
    C[0]++;
    C = p.sqrt(C, m);
    C[0]++;
    C = p.inv(C, m);
    for (int i = 1; i < m; ++i) {
      out << mul(2, C[i]) << endl;
    }
  }
};

Solution solution;

void solve(std::istream & in, std::ostream & out) {
  out << std::setprecision(12);
  solution = *(new Solution());
  solution.solve(in, out);
}


#include <fstream>


int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);


  istream& in = cin;


  ostream& out = cout;

  solve(in, out);
  return 0;
}


