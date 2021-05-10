#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int lst[N];

int main() {
  int T;
  cin >> T;
  while (T--) { 
    string s;
    cin >> s;
    int ans = s[0] == '1';
    int n = s.length();
    lst[0] = s[0] == '1' ? 0 : -1;
    for (int i = 1; i < n; ++i) {
      lst[i] = s[i] == '1' ? i : lst[i - 1];
    }
    for (int r = 1; r < n; ++r) {
      int now = 0;
      for (int l = r; l >= max(0, r - 20); l = lst[l - 1]) {
        if (l < 0) {
          break;
        }
        now += (s[l] == '1' ? 1 : 0) << (r - l);
        if (now <= r - (l == 0 ? -1 : lst[l - 1]) && now >= r - l + 1) {
          ++ans;
        }
        if (l <= 0) {
          break;
        }
      }
    }
    cout << ans  << endl;

  }
  return 0;
}