#include <bits/stdc++.h>

using namespace std;

#define y1 _y1
#define all(x) x.begin(), x.end()

//123
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (s[0] == '0' || s[n - 1] == '0') {
      cout << "NO" << endl;
      continue;
    }
    int cnt1 = 0;
    for (int i = 0; i < n; ++i) {
      cnt1 += s[i] == '1';
    }
    if (cnt1 & 1) {
      cout << "NO" << endl;
      continue;
    }
    char o[2] = {'(', ')'};
    string a;
    string b;
    int cur[2];
    cur[0] = 0;
    cur[1] = 1;
    int now1 = 0;
    for (int i = 0; i < n; ++i) {
      now1 += s[i] == '1';
      if (s[i] == '0') {
        a += o[cur[0]];
        b += o[cur[1]];
        cur[0] ^= 1;
        cur[1] ^= 1;
      } else {
        a += o[now1 > cnt1 / 2];
        b += o[now1 > cnt1 / 2];
      }
    }
    cout << "YES" << endl;
    cout << a << endl;
    cout << b << endl;
  }
  return 0;
}
