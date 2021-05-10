#include <bits/stdc++.h>

using namespace std;

map<string, int> m;
int main() {
  int n;
  while (cin >> n && n) {
    m.clear();
    for (int i = 0; i < n; ++i) {
      string s;
      cin >> s;
      m[s]++;
    }
    int mx = 0;
    string ans;
    for (map<string, int>::iterator it = m.begin(); it != m.end(); ++it) {
      if (it->second > mx) {
        mx = it->second;
        ans = it->first;
      }
    }
    cout << ans << endl;
  }
  return 0;
}