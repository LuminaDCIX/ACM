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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> g[n];
    vector<int> l(n);
    vector<int> r(n);
    for (int i = 0; i < n; ++i) {
      cin >> l[i] >> r[i];
    }
    for (int i = 0; i < n - 1; ++i) {
      int u, v;
      cin >> u >> v;
      --u;
      --v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    vector<array<long long, 2> > dp(n);
    function<void(int, int)> dfs = [&](int u, int fa) {
      for (auto v : g[u]) {
        if (v != fa) {
          dfs(v, u);
          dp[u][0] +=
              max({dp[v][0] + abs(l[u] - l[v]), dp[v][1] + abs(l[u] - r[v])});
          dp[u][1] +=
              max({dp[v][0] + abs(r[u] - l[v]), dp[v][1] + abs(r[u] - r[v])});
        }
      }
    };
    dfs(0, -1);
    cout << max(dp[0][0], dp[0][1]) << endl;
  }
  return 0;
}