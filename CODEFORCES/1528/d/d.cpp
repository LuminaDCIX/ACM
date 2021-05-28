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
  int n;
  int m;
  cin >> n >> m;
  vector<vector<array<int, 2>>> g(n + 1);
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    g[a].push_back({b, c});
  }
  vector<vector<int>> f(n + 1);
  for (int i = 0; i < n + 1; ++i) {
    f[i].resize(n + 1);
    for (int j = 0; j < n + 1; ++j) {
      f[i][j] = numeric_limits<int>::max();
    }
  }

  for (int st = 0; st < n; ++st) {
    vector<bool> ok(n + 1);
    g[n].clear();
    g[n] = g[st];
    for (int i = 0; i < n; ++i) {
      f[n][i] = numeric_limits<int>::max();
    }
    f[n][n] = 0;
    while (true) {
      int v = -1;
      int minv = numeric_limits<int>::max();
      for (int i = 0; i < n + 1; ++i) {
        if (!ok[i] && f[n][i] < minv) {
          minv = f[n][i];
          v = i;
        }
      }
      if (v == -1) {
        break;
      }
      ok[v] = 1;
      for (auto e : g[v]) {
        int to = (e[0] + f[n][v]) % n;
        f[n][to] = min(f[n][to], f[n][v] + e[1]);
      }
      if (v != n) {
        f[n][(v + 1) % n] = min(f[n][(v + 1) % n], f[n][v] + 1);
      }
    }
    for (int i = 0; i < n; ++i) {
      f[st][i] = f[n][i];
    }
    f[st][st] = 0;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        cout << 0 << " ";
      } else {
        cout << f[i][j] << " ";
      }
    }
    cout << endl;
  }

  return 0;
}