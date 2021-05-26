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

int exgcd(int a, int b, int& x, int& y) {
  if (!b) {
    x = 1;
    y = 0;
    return a;
  }
  int d = exgcd(b, a % b, x, y);
  int t = x;
  x = y;
  y = t - (a / b) * y;
  return d;
}

bool lineq(int a, int b, int c, int& x, int& y) {
  int d = exgcd(a, b, x, y);
  if (c % d != 0) {
    return false;
  }
  x *= c / d;
  y *= c / d;
  int t = b / d;
  int xx = (x % t + t) % t;
  y -= a * ((xx - x) / (b / d));
  x = xx;
  return true;
}

vector<int> get_inv(int n, int p) {
  vector<int> inv(n + 1);
  inv[1] = 1;
  for (int i = 2; i <= n; ++i) {
    inv[i] = (p - (long long)p / i) * inv[p % i] % p;
  }
  return inv;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int a, b;
  cin >> a >> b;
  int x, y;
  lineq(a, b, 1, x, y);
  cout << x << endl;
  return 0;
}