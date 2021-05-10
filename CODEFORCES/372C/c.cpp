#include <bits/stdc++.h>

using namespace std;

const int N = 150000 + 5;
const int M = 300 + 5;
template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) { return '"' + s + '"'; }

string to_string(const char* s) { return to_string((string)s); }

string to_string(bool b) { return (b ? "true" : "false"); }

string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); ++i) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; ++i) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}

template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
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

template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " +
         to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " +
         to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

template <typename T>
class monotonous_queue {
 public:
  deque<T> que;

  template <typename F>
  void maintain(
      F const& legal) {  // maintain monotonous: legal(T) is false ==> pop
    while (!que.empty() && !legal(que.front())) {
      que.pop_front();
    }
  }

  template <typename F>
  void push(T x, F const& greater) {
    while (!que.empty() && greater(x, que.back())) {
      que.pop_back();
    }
    que.push_back(x);
  }

  T front() { return que.front(); }

  void clean() { que.clear(); }
};

int n, m, d;
int a[M];
int b[M];
int t[M];
long long f[2][N];

monotonous_queue<pair<int, long long> > que;

int main() {
  ios::sync_with_stdio(0);
  cin >> n >> m >> d;
  for (int i = 1; i <= m; ++i) {
    cin >> a[i] >> b[i] >> t[i];
  }

  auto greater = [](pair<int, long long> a, pair<int, long long> b) -> bool {
    return a.second >= b.second;
  };
  int now = 0;
  int old = 1;
  t[0] = 1;
  for (int i = 1; i <= m; ++i) {
    swap(now, old);
    que.clean();
    for (int j = 1; j <= n; ++j) {
      que.push(make_pair(j, f[old][j]), greater);
      que.maintain([&](pair<int, long long> x) -> bool {
        return x.first >= j - 1LL * d * (t[i] - t[i - 1]);
      });
      f[now][j] = que.front().second + b[i] - abs(a[i] - j);
    }

    que.clean();
    for (int j = n; j >= 1; --j) {
      que.push(make_pair(j, f[old][j]), greater);
      que.maintain([&](pair<int, long long> x) -> bool {
        return x.first <= j + 1LL * d * (t[i] - t[i - 1]);
      });
      f[now][j] = max(f[now][j], que.front().second + b[i] - abs(a[i] - j));
    }
  }

  long long ans = -1e18;
  for (int i = 1; i <= n; ++i) {
    ans = max(ans, f[now][i]);
  }
  cout << ans << endl;
}