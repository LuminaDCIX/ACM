#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 5;
const int MAX = N * 4 + 5;

vector<int> v[MAX];

bitset<N> ans;
bitset<N> now;

void push(int o, int ll, int rr, int l, int r, int x) {
  if (ll >= l && rr <= r) {
    v[o].push_back(x);
    return;
  }
  int mid = (ll + rr) / 2;
  if (l <= mid) {
    push(o + o, ll, mid, l, r, x);
  }
  if (r > mid) {
    push(o + o + 1, mid + 1, rr, l, r, x);
  }
}

void dfs(int o, int ll, int rr) {
  bitset<N> bak = now;
  for (auto val : v[o]) {
    now |= now << val;
  }
  if (ll == rr) {
    ans |= now;
    return;
  }
  int mid = (ll + rr) / 2;
  dfs(o + o, ll, mid);
  dfs(o + o + 1, mid + 1, rr);
  now = bak;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  int m;
  cin >> n >> m;
  for (int i = 0, l, r, x; i < m; ++i) {
    cin >> l >> r >> x;
    push(1, 0, n - 1, l - 1, r - 1, x);
  }
  now[0] = 1;
  dfs(1, 0, n - 1);
  int cnt = 0;
  for (int i = 1; i <= n; ++i) {
    cnt += ans[i];
  }
  cout << cnt << endl;
  for (int i = 1; i <= n; ++i) {
    if (ans[i]) {
      cout << i << " ";
    }
  }
  cout << endl;
  return 0;
}
