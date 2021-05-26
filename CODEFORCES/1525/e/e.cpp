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

const int N = 20 + 5;
const int M = 5e4 + 5;

int d[N][M];

const int mod = 998244353;

inline int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }

inline int sub(int& a, int b) { return a - b < 0 ? a - b + mod : a - b; }

inline int mul(int a, int b) { return (int)((long long)a * b % mod); }

int n;
int m;

int calc(vector<int> l) {
  int ret = 1;
  int sum = 1;
  for (int i = 2; i <= n; ++i) {
    sum = mul(sum, i);
  }
  for (int i = 1; i <= n; ++i) {
    int cnt = 0;
    for (int j = 0; j < n; ++j) {
      if (i > l[j]) {
        ++cnt;
      }
    }
    if (cnt - (i - 1) <= 0) {
      return sum;
    }
    ret = mul(ret, cnt - (i - 1));
  }
  return sub(sum, ret);
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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> d[i][j];
    }
  }
  int ans = 0;
  for (int i = 0; i < m; ++i) {
    vector<int> l;
    for (int j = 0; j < n; ++j) {
      l.push_back(n + 1 - d[j][i]);
    }
    ans = add(ans, calc(l));
  }

  for (int i = 2; i <= n; ++i) {
    ans = mul(ans, inv(i));
  }
  cout << ans << endl;
  return 0;
}