#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n;
int m;
int k;
int bad[N];
int cost[N];

int pre[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m >> k;
  for (int i = 1; i <= m; ++i) {
    int c;
    cin >> c;
    bad[c] = 1;
  }
  for (int i = 1; i <= k; ++i) {
    cin >> cost[i];
  }
  if (bad[0]) {
    puts("-1");
    return 0;
  }
  pre[0] = 0;
  for (int i = 1; i <= n - 1; ++i) {
    if (bad[i]) {
      pre[i] = pre[i - 1];
    } else {
      pre[i] = i;
    }
  }
  long long ans = LLONG_MAX;
  for (int i = 1; i <= k; ++i) {
    int nw = 0;
    long long cur = 0;
    while (nw < n) {
      int old = nw;
      cur += cost[i];
      if (nw == n - 1) {
        nw = pre[n - 1];
      } else {
        nw = pre[nw];
      }
      nw += i;
      if (nw <= old) {
        cur = ans;
        break;
      }
    }
    ans = min(ans, cur);
  }
  cout << (ans == LLONG_MAX ? -1 : ans) << endl;
  return 0;
}
