#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

 #include <bits/stdc++.h>

using namespace std;

const int N = 2000 + 5;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n; 
  for (int i = 0; i < n; ++i) {
    long long q = 0;
    cin >> q;
    long long low = 0;
    long long high = q;
    long long ans;
    while (low <= high) {
      long long mid = (low + high) / 2;
      if (mid * (mid + 1) <= 2 * q) {
        ans = mid;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
    cout << max(2 * (q - (ans + 1)), q - ans + ans * (ans - 1) / 2) << endl;
  }
  return 0;
}
  