#include <bits/stdc++.h>

using namespace std;

const int N = (1 << 13) + 5;
const int M = 1e3 + 15;

int f[M][N];

int a[M];
int b[M];
int x[M];

int main() {
  int n, m;
  cin >> n >> m;
  memset(f, 0x3f3f, sizeof(f));
  for (int i = 1; i <= m; ++i) {
    cin >> a[i] >> b[i];
    int msk = 0;
    for (int j = 1; j <= b[i]; ++j) {
      int k;
      cin >> k;
      msk |= 1 << (k - 1);
    }
    
    x[i] = msk;
  }

  f[0][0] = 0;

  int ans = 0x3f3f3f3f;

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < (1 << n); ++j) {
      f[i + 1][j | x[i + 1]] = min(f[i + 1][j | x[i + 1]], f[i][j] + a[i + 1]);
    }
    for (int j = 0; j < (1 << n); ++j) {
      f[i + 1][j] = min(f[i + 1][j], f[i][j]);
    }
    ans = min(ans, f[i + 1][(1 << n) - 1]);
  }
  if (ans == 0x3f3f3f3f) {
    puts("-1");
    return 0;
  }
  cout << ans << endl;

  return 0;
}