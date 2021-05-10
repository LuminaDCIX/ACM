#include <bits/stdc++.h>

using namespace std;

namespace XDYIMCMI0LY {

  const int N = 1000 + 5;
  
  int dp[N][2][2];
  char s[N];
  char g[N];
  int box[N][2];

  int main() {
    scanf("%s\n%s", s + 1, g + 1);
    int n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) {
      box[i][0] = s[i] == 'X';
      box[i][1] = g[i] == 'X';
    }
    memset(dp, 0xcfcf, sizeof(dp));
    dp[1][box[1][0]][box[1][1]] = 0;
    for (int i = 2; i <= n; ++i) {
      int u = box[i][0];
      int d = box[i][1];
      if (u == 0) {
        dp[i][1][d] = max(dp[i][1][d], dp[i - 1][0][0] + 1);
      }
      if (d == 0) {
        dp[i][u][1] = max(dp[i][u][1], dp[i - 1][0][0] + 1);
      }
      if (u == d && u == 0) {
        dp[i][1][1] = max(dp[i][1][1], max(max(dp[i - 1][0][1], dp[i - 1][0][0]), max(dp[i - 1][1][0], dp[i - 1][0][0])) + 1);
      }
      dp[i][u][d] = max(dp[i][u][d], max(max(dp[i - 1][0][1], dp[i - 1][0][0]), max(dp[i - 1][1][0], dp[i - 1][1][1])));
    }
    int ans = 0;
    int a, b;
    int s, t;
    if (box[n][0] == 0) {
      a = 0;
      b = 1;
    } else {
      a = b = 1;
    }
    if (box[n][1] == 0) {
      s = 0;
      t = 1;
    } else {
      s = t = 1;
    }
    for (int i = a; i <= b; ++i) {
      for (int j = s; j <= t; ++j) {
        ans = max(ans, dp[n][i][j]);
      }
    }
    cout << ans << endl;
  }
}

int main() {
  cin.tie(0);
  cout.tie(0);
  ios::sync_with_stdio(false);
  XDYIMCMI0LY::main();
  return 0;
}
