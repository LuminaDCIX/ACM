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

struct item {
  int l = 0;
  int r = 0;
  item(int _l, int _r) : l(_l), r(_r){};
  bool operator<(const item& b) const { return r < b.r; }
};

bool cross(const item& a, const item& b) {
  return (b.l <= a.l && a.r <= b.r) || (a.l <= b.l && b.r <= a.r);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> so[n];
    vector<int> ke[n];
    for (int i = 1; i < n; ++i) {
      int x;
      cin >> x;
      --x;
      so[x].push_back(i);
    }
    for (int i = 1; i < n; ++i) {
      int x;
      cin >> x;
      --x;
      ke[x].push_back(i);
    }
    int dfn = 0;
    vector<array<int, 2> > seg(n);

    function<void(int)> dfs0 = [&](int u) {
      ++dfn;
      seg[u][0] = dfn;
      for (auto v : ke[u]) {
        dfs0(v);
      }
      ++dfn;
      seg[u][1] = dfn;
    };

    dfs0(0);
    set<item> c;
    int ans = 0;
    int tot = 0;
    for (int i = 0; i < n; ++i) {
      debug(i + 1, seg[i][0], seg[i][1]);
    }

    auto add = [&](item o) {
      auto L = c.lower_bound(o) == c.begin() ? c.end() : --c.lower_bound(o);
      auto R = c.lower_bound(o) == c.end() ? c.end() : c.lower_bound(o);
      if (L == c.end() && R == c.end()) {
        ++tot;
      } else if (L == c.end()) {
        tot += cross(*R, o) ? 0 : 1;
      } else if (R == c.end()) {
        tot += cross(*L, o) ? 0 : 1;
      } else {
        tot +=
            (cross(*R, *L) && cross(*R, o) && !cross(*L, o)) || !cross(*R, o);
      }
      c.insert(o);
      debug(tot, o.l, o.r, L == c.end(), R == c.end());
      ans = max(ans, tot);
    };
    auto remove = [&](item o) {
      auto L = c.lower_bound(o) == c.begin() ? c.end() : --c.lower_bound(o);
      auto R = c.lower_bound(o) == c.end() ? c.end() : ++c.lower_bound(o);
      if (L == c.end() && R == c.end()) {
        --tot;
      } else if (L == c.end()) {
        tot -= cross(*R, o) ? 0 : 1;
      } else if (R == c.end()) {
        tot -= cross(*L, o) ? 0 : 1;
      } else {
        tot -=
            (cross(*R, *L) && cross(*R, o) && !cross(*L, o)) || !cross(*R, o);
      }
      c.erase(o);
      ans = max(ans, tot);
    };
    function<void(int)> dfs = [&](int u) {
      add({seg[u][0], seg[u][1]});
      for (auto v : so[u]) {
        dfs(v);
      }
      remove({seg[u][0], seg[u][1]});
    };
    dfs(0);
    cout << ans << endl;
  }
  return 0;
}