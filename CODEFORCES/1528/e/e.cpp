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

const int mod = 998244353;

inline int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }

inline int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }

inline int mul(int a, int b) { return (int)((long long)a * b % mod); }

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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;
  if (n == 1) {
    cout << 5 << endl;
    return 0;
  }
  vector<int> f(n + 1);
  vector<int> sum_f(n + 1);
  vector<int> g(n + 1);
  int sum = 0;
  f[0] = 1;

  f[1] = 2;
  sum_f[0] = 1;
  sum_f[1] = 3;
  g[1] = 1;
  for (int i = 2; i <= n; ++i) {
    f[i] = f[i - 1];
    f[i] = add(f[i], mul(f[i - 1], sum_f[i - 2]));
    f[i] = add(f[i], mul(inv(2), mul(f[i - 1], add(f[i - 1], 1))));
    sum_f[i] = add(sum_f[i - 1], f[i]);
    g[i] = sub(f[i], f[i - 1]);
  }
  sum = add(f[n], mul(inv(2),
                      mul(f[n - 1], mul(sum_f[n - 2], add(sum_f[n - 2], 1)))));
  sum =
      add(sum, mul(inv(2), mul(sum_f[n - 2], mul(f[n - 1], add(f[n - 1], 1)))));
  sum = add(
      sum, mul(inv(6), mul(f[n - 1], mul(add(f[n - 1], 1), add(f[n - 1], 2)))));
  sum = mul(sum, 2);
  sum = sub(sum, 1);
  int sum_t = 0;
  for (int i = 0; i <= n - 1; ++i) {
    sum_t = add(sum_t, mul(sub(f[i], 1), g[n - 1 - i]));
  }
  sum = add(sum, sum_t);
  cout << sum << endl;
  return 0;
}