#include <bits/stdc++.h>

using namespace std;

const int N = 100000 + 5;
const int W = 4e4 + 5;

int f[2][W];

int n;
int m;
int v[N];
int w[N];
int cnt[N];

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

  void clear() { que.clear(); }
};

monotonous_queue<pair<int, int> > que;

int main() {
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> v[i] >> w[i] >> cnt[i];
  }
  int now = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < w[i]; ++j) {
      que.clear();
      for (int k = 0; k * w[i] + j <= m; ++k) {
        que.push(make_pair(k, f[now ^ 1][k * w[i] + j] - k * v[i]),
                 [](pair<int, int> a, pair<int, int> b) -> bool {
                   return a.second >= b.second;
                 });
        que.maintain(
            [&](pair<int, int> x) -> bool { return k - x.first <= cnt[i]; });
        f[now][k * w[i] + j] =
            max(f[now][k * w[i] + j], que.front().second + k * v[i]);
      }
    }
    now ^= 1;
  }
  int ans = 0;
  for (int i = 1; i <= m; ++i) {
    ans = max(ans, f[now ^ 1][i]);
  }
  cout << ans << endl;

  return 0;
}