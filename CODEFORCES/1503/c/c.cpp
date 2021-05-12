#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(), (x).end()
#define gid(x, id) (get<(id)>((x)))


int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<pair<int, int> > v(n);
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    cin >> v[i].first >> v[i].second;
    ans += gid(v[i], 1);
  }
  sort(v.begin(), v.end());
  int mx = gid(v[0], 0) + gid(v[0], 1);
  for (int i = 1; i < n; ++i) {
    ans += max(0, gid(v[i], 0) - mx);
    mx = max(mx, gid(v[i], 0) + gid(v[i], 1));
  }
  cout << ans << endl;
  return 0;
}
