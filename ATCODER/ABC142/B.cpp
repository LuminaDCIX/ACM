#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, k;
  int ans = 0;
  cin >> n >> k;
  for (int i = 1; i <= n; ++i) {
    int a = 0;
    cin >> a;
    if (a >= k) {
      ans++;
    }
  }
  cout << ans << endl;

  return 0;
}