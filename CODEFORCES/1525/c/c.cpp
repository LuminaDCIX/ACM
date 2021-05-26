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

const int N = 3e5 + 5;

int dir[N];
int x[N];
map<int, int> id;
int ans[N];

void solve(int n, int m, vector<int> t) {
  n = t.size();
  priority_queue<array<int, 2>> heap;
  vector<array<int, 2>> v;
  for (int i = 0; i < n; ++i) {
    v.push_back({t[i], id[t[i]]});
  }
  sort(v.begin(), v.end());
  for (int i = 0; i < n; ++i) {
    if (dir[v[i][1]] == 0) {  // left
      if (heap.empty()) {
        heap.push({-v[i][0], id[v[i][0]]});
      } else {
        auto x = heap.top();
        heap.pop();
        ans[x[1]] = (v[i][0] - x[0]) / 2;
        ans[v[i][1]] = (v[i][0] - x[0]) / 2;
        debug(x[1], v[i][1]);
      }
    } else {  // right
      heap.push({v[i][0], v[i][1]});
    }
  }
  priority_queue<array<int, 2>> que;
  while (!heap.empty()) {
    que.push(heap.top());
    heap.pop();
  }

  while (que.size() > 1) {
    auto r = que.top();
    que.pop();
    auto l = que.top();
    que.pop();
    ans[r[1]] = ans[l[1]] = (2 * m - r[0] - l[0]) / 2;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    debug(t);
    int n;
    int m;
    cin >> n >> m;
    id.clear();
    for (int i = 0; i < n; ++i) {
      cin >> x[i];
      id[x[i]] = i;
      ans[i] = -1;
    }
    string s;
    for (int i = 0; i < n; ++i) {
      cin >> s;
      if (s[0] == 'R') {
        dir[i] = 1;
      } else {
        dir[i] = 0;
      }
    }

    vector<int> t;
    for (int i = 0; i < n; ++i) {
      if (x[i] & 1) {
        t.push_back(x[i]);
      }
    }
    solve(n, m, t);
    t.clear();
    for (int i = 0; i < n; ++i) {
      if (!(x[i] & 1)) {
        t.push_back(x[i]);
      }
    }
    solve(n, m, t);
    for (int i = 0; i < n; ++i) {
      cout << ans[i] << " ";
    }
    cout << endl;
  }

  return 0;
}
