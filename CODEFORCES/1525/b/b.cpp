#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    bool ok = true;
    for (int i = 1; i < n; ++i) {
      if (a[i] < a[i - 1]) {
        ok = false;
      }
    }
    if (ok) {
      cout << 0 << endl;
      continue;
    }
    if (a[0] == 1 || a[n - 1] == n) {
      cout << 1 << endl;
      continue;
    }
    if (a[0] == n && a[n - 1] == 1) {
      cout << 3 << endl;
      continue;
    }
    cout << 2 << endl;
  }
  return 0;
}
