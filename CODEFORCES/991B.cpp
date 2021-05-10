#include <bits/stdc++.h>

using namespace std;

namespace XDYIMCMI0LY {

  const int N = 25;

  int main() {
    vector<int> v;
    int cnt = 0;
    int n;
    cin >> n;
    double sum = 0;
    for (int i = 1; i <= n; ++i) {
      int t;
      cin >>  t;
      v.push_back(t);
      sum += t;
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; ++i) {
      if (floor(sum / n + 0.5) == 5) {
        break;
      }
      sum -= v[i];
      sum += 5;
      ++cnt;
    }
    cout << cnt << endl;
  }
}

int main() {
  cin.tie(0);
  cout.tie(0);
  ios::sync_with_stdio(false);
  XDYIMCMI0LY::main();
  return 0;
}
