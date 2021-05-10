#include <bits/stdc++.h>

using namespace std;

namespace XDYIMCMI0LY {


  long long check(long long k, long long n) {
    long long cnt = 0;
    while (n) {
      cnt += min(n, k);
      n -= min(n, k);
      n -= n / 10;
    }
    return cnt;
  }
      
  
  int main() {
    long long k;
    cin >> k;
    long long l = 1;
    long long r = k;
    long long ans = 0;
    while (l <= r) {
      long long x = (l + r) / 2;
      if (check(x, k) >= ((k + 1) / 2)) {
        r = x - 1;
        ans = x;
      } else {
        l = x + 1;
      }
    }
    cout << ans << endl;
  }
}

int main() {
  cin.tie(0);
  cout.tie(0);
  ios::sync_with_stdio(false);
  XDYIMCMI0LY::main();
  return 0;
}
