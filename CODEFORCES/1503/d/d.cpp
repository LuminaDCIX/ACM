#include <bits/stdc++.h>

std::string to_string(std::string s) { return '"' + s + '"'; }

std::string to_string(const char *s) { return to_string((std::string)s); }

std::string to_string(bool b) { return (b ? "true" : "false"); }

template <typename A, typename B> std::string to_string(std::pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A> std::string to_string(A v) {
  using namespace std;
  bool first = true;
  std::string res = "{";
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

void debug_out() { std::cerr << std::endl; }

template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
  using ::to_string;
  using std::to_string;
  std::cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...)                                                             \
  std::cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

int main() {
  int n;
  std::cin >> n;
  std::vector<std::array<int, 2>> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i][0] >> a[i][1];
    if (a[i][0] <= n && a[i][1] <= n) {
      std::cout << -1 << std::endl;
      return 0;
    }
  }
  std::vector<int> f(n);
  std::vector<int> c(n);

  for (int i = 0; i < n; ++i) {
    if (a[i][0] <= n) {
      f[a[i][0] - 1] = a[i][1];
    } else {
      f[a[i][1] - 1] = a[i][0];
      c[a[i][1] - 1] = 1;
    }
  }
  std::vector<int> min(n);
  std::vector<int> max(n);
  min[0] = f[0];
  for (int i = 1; i < n; ++i) {
    min[i] = std::min(min[i - 1], f[i]);
  }
  max[n - 1] = f[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    max[i] = std::max(max[i + 1], f[i]);
  }

  std::vector<int> seg;
  for (int i = 0; i < n - 1; ++i) {
    if (min[i] > max[i + 1]) {
      seg.push_back(i);
    }
  }
  seg.push_back(n - 1);

  int ans = 0;
  int pre = -1;

  debug(seg);
  debug(f);
  debug(c);

  for (auto lst : seg) {
    int c0 = 0;
    int c1 = 0;
    int l0 = 0;
    int l1 = 0;
    int min0 = std::numeric_limits<int>::max();
    int min1 = std::numeric_limits<int>::max();
    auto update = [&](int x, int i) {
      if (x == 0) {
        min0 = std::min(min0, f[i]);
        c0 += c[i];
        ++l0;
      } else {
        min1 = std::min(min1, f[i]);
        c1 += c[i];
        ++l1;
      }
    };
    for (int i = pre + 1; i <= lst; ++i) {
      if (f[i] < min0 && f[i] < min1) {
        if (min0 <= min1) {
          update(0, i);
        } else {
          update(1, i);
        }
      } else if (f[i] < min0) {
        update(0, i);
      } else if (f[i] < min1) {
        update(1, i);
      } else {
        std::cout << -1 << std::endl;
        return 0;
      }
      debug(c0, l0, c1, l1);
    }

    ans += std::min(c0 + l1 - c1, c1 + l0 - c0);
    pre = lst;
  }
  std::cout << ans << std::endl;
  return 0;
}
