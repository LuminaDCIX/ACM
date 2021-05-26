#include <bits/stdc++.h>

using namespace std;

std::string to_string(std::string s) { return '"' + s + '"'; }

std::string to_string(const char* s) { return to_string((std::string)s); }

std::string to_string(bool b) { return (b ? "true" : "false"); }

template <typename A, typename B>
std::string to_string(std::pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
std::string to_string(A v) {
  using ::to_string;
  using std::to_string;
  bool first = true;
  std::string res = "{";
  for (const auto& x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

void debug_out() { std::cerr << std::endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  using ::to_string;
  using std::to_string;
  std::cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...)                                    \
  std::cerr << __FUNCTION__ << "(" << __LINE__ << ")" \
            << "[" << #__VA_ARGS__ << "]:",           \
      debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

const int mod = 1e9 + 7;

template <typename T>
inline T modexp(T a, T b, T p = mod) {
  T res = 1;
  while (b > 0) {
    if (b & 1) {
      res = (__int128)res * a % p;
    }
    a = (__int128)a * a % p;
    b >>= 1;
  }
  return res;
}

template <typename T>
T exgcd(T a, T b, T& x, T& y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  T d = exgcd(b, a % b, x, y);
  T t = x;
  x = y;
  y = t - (a / b) * y;
  return d;
}

template <typename T>
bool diophantine(T a, T b, T c, T& x, T& y, T& g) {
  if (a == 0 && b == 0) {
    if (c == 0) {
      x = y = g = 0;
      return true;
    }
    return false;
  }
  if (a == 0) {
    if (c % b == 0) {
      x = 0;
      y = c / b;
      g = abs(b);
      return true;
    }
    return false;
  }
  if (b == 0) {
    if (c % a == 0) {
      x = c / a;
      y = 0;
      g = abs(a);
      return true;
    }
    return false;
  }
  g = exgcd(a, b, x, y);
  if (c % g != 0) {
    return false;
  }
  T dx = c / a;
  c -= dx * a;
  T dy = c / b;
  c -= dy * b;
  x = dx + (T)((__int128)x * (c / g) % b);
  y = dy + (T)((__int128)y * (c / g) % a);
  g = abs(g);
  return true;
}

bool crt(long long k1, long long m1, long long k2, long long m2, long long& k,
         long long& m) {
  k1 %= m1;
  if (k1 < 0) {
    k1 += m1;
  }
  k2 %= m2;
  if (k2 < 0) {
    k2 += m2;
  }
  long long x, y, g;
  if (!diophantine(m1, -m2, k2 - k1, x, y, g)) {
    return false;
  }
  long long dx = m2 / g;
  long long delta = x / dx - (x % dx < 0);
  k = m1 * (x - dx * delta) + k1;
  m = m1 / g * m2;
  assert(0 <= k && k < m);
  return true;
}

template <typename T>
inline T inv(T a, T p = mod) {
  a %= p;
  if (a < 0) {
    a += p;
  }
  T b = p;
  T u = 0;
  T v = 1;
  while (a) {
    T t = b / a;
    b -= t * a;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  assert(b == 1);
  if (u < 0) {
    u += p;
  }
  return u;
}

long long exlucas(long long n, long long m, long long mod) {
  function<long long(long long, long long, long long)> dfs =
      [&](long long n, long long x, long long mod) -> long long {
    if (!n) {
      return 1;
    }
    long long s = 1;
    for (long long i = 1; i <= mod; i++) {
      if (i % x) {
        s = (__int128)s * i % mod;
      }
    }
    s = modexp(s, n / mod, mod);
    for (long long i = n / mod * mod + 1; i <= n; ++i) {
      if (i % x) {
        s = (__int128)s * i % mod;
      }
    }
    return s * dfs(n / x, x, mod) % mod;
  };

  auto calc = [&](long long n, long long m, long long x,
                  long long mod) -> long long {
    long long cnt = 0;
    for (long long i = n; i; i /= x) {
      cnt += i / x;
    }
    for (long long i = m; i; i /= x) {
      cnt -= i / x;
    }
    for (long long i = n - m; i; i /= x) {
      cnt -= i / x;
    }
    return modexp(x, cnt, mod) % mod * dfs(n, x, mod) % mod *
           inv(dfs(m, x, mod), mod) % mod * inv(dfs(n - m, x, mod), mod) % mod;
  };

  vector<long long> p;
  vector<long long> ans;
  for (long long i = 2; i * i <= mod; ++i) {
    if (mod % i == 0) {
      p.push_back(1);
      while (mod % i == 0) {
        p.back() = p.back() * i;
        mod /= i;
      }
      ans.push_back(calc(n, m, i, p.back()));
    }
  }
  if (mod > 1) {
    p.push_back(mod);
    ans.push_back(calc(n, m, mod, mod));
  }
  long long k = ans[0];
  long long mm = p[0];
  for (int i = 1; i < (int)p.size(); ++i) {
    crt(k, mm, ans[i], p[i], k, mm);
  }
  return k;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  long long n, m, p;
  cin >> n >> m >> p;
  cout << exlucas(n, m, p) << endl;
  return 0;
}