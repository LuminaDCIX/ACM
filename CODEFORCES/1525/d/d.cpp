#include <bits/stdc++.h>

#include <limits>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  vector<int> a(n);
  vector<int> used(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  vector<array<int, 2>> val(n);
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i]) {
      int mink = -1;
      int mind = numeric_limits<int>::max();
      int k = i;
      int d = 0;
      while (k > 0) {
        if (val[k][0] < 0) {
          d += -1;
        } else {
          d += 1;
        }
        --k;
        if (!used[k] && a[k] == 0 && d < mind) {
          mind = d;
          mink = k;
        }
      }
      k = i;
      d = 0;
      while (k < n - 1) {
        if (val[k][1] < 0) {
          d += -1;
        } else {
          d += 1;
        }
        ++k;
        if (!used[k] && a[k] == 0 && d < mind) {
          mind = d;
          mink = k;
        }
      }
      ans += mind;
      used[mink] = 1;
      k = i;
      if (mink < i) {
        while (k != mink) {
          val[k][0]++;
          val[k - 1][1]--;
          --k;
        }
      } else {
        while (k != mink) {
          val[k][1]++;
          val[k + 1][0]--;
          ++k;
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
