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

const int N = 300 + 5;

int l[N];
int c[N];

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

bool del[N];

typedef tuple<int, int, bitset<300>> node;

struct cmp {
  bool operator()(node& a, node& b) { return get<0>(a) > get<0>(b); }
};

unordered_set<int> s;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> l[i];
  }
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    cin >> c[i];
    ans += c[i];
  }
  int g = l[0];
  for (int i = 1; i < n; ++i) {
    g = gcd(g, l[i]);
  }
  if (g != 1) {
    cout << -1 << endl;
    return 0;
  }
  priority_queue<tuple<int, int, bitset<300>>, vector<node>, cmp> heap;
  for (int i = 0; i < n; ++i) {
    bitset<300> b;
    b[i] = 1;
    heap.push({c[i], l[i], b});
  }

  while (!heap.empty()) {
    auto cost = get<0>(heap.top());
    auto msk = get<2>(heap.top());
    auto g = get<1>(heap.top());
    heap.pop();
    if (s.find(g) != s.end()) {
      continue;
    }
    s.insert(g);
    if (g == 1) {
      cout << cost << endl;
      return 0;
    }
    for (int i = 0; i < n; ++i) {
      if (!msk[i]) {
        auto nw = msk;
        nw[i] = 1;
        if (s.find(gcd(g, l[i])) == s.end()) {
          heap.push({cost + c[i], gcd(g, l[i]), nw});
        }
      }
    }
  }
  return 0;
}