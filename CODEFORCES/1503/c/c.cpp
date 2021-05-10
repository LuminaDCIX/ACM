#include <bits/stdc++.h>

using namespace std;

#define y1 _y1
#define all(x) x.begin(), x.end()



int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  vector<pair<int, int> > v;
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> v[i].first >> v[i].second;
  }
  sort(v.begin() + 1, v.end());
  v.push_back(v[0]);
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += max(v[i].second, v[i].first - v[i - 1].first);
  }
  cout << ans << endl;
  return 0;
}
