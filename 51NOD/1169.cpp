#include <bits/stdc++.h>

using namespace std;

namespace XDYIMCMI0LY {

  const int N = 100 + 5;
  const int M = 35;
  const int P = 1e9 + 7;

  inline int read() {
    int f = 1, x = 0, ch = getchar();
    for (; !isdigit(ch); ch = getchar()) f = (ch == '-') ? -1 : 1;
    for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
    return f * x;
  }

  inline int add(int a, int b) { return a + b >= P ? a + b - P : a + b; }
  inline int sub(int a, int b) { return a - b < 0 ? a - b + P : a - b; }
  inline int mul(int a, int b) { return (long long) a * b % P; }

  int n, a[N];
  int bit[M];

  int dp[N][2];

  int calc() {
    int ans = 0;
    for (int i = 31; i >= 0; --i) {
      memset(dp, 0, sizeof(dp));
      dp[0][0] = 1;
      for (int j = 1; j <= n; ++j) {
        if (a[j] & bit[i]) {
          dp[j][0] = add(mul(dp[j - 1][0], bit[i]), mul(dp[j - 1][1], a[j] % bit[i] + 1));
          dp[j][1] = add(mul(dp[j - 1][1], bit[i]), mul(dp[j - 1][0], a[j] % bit[i] + 1));
        } else {
          dp[j][0] = mul(dp[j - 1][0], a[j] % bit[i] + 1);
          dp[j][1] = mul(dp[j - 1][1], a[j] % bit[i] + 1);
        }
      }
      int nwbit = 0, prod = 1;
      for (int j = n; j >= 1; --j) {
        if (a[j] & bit[i]) ans = add(ans, mul(dp[j - 1][nwbit], prod)), nwbit ^= 1;
        prod = mul(prod, a[j] % bit[i] + 1);
      }
      if (nwbit == 1) return ans;
    }
    return ans - 1;
  }

  int solve() {
    n = read();
    for (int i = 1; i <= n; ++i) a[i] = read();
    for (int i = 0; i < 32; ++i) bit[i] = 1ll << i;
    int ans = calc();
    for (int i = 1; i <= n; ++i) --a[i];
    ans = sub(ans, calc());
    cout << ans << endl;
    return 0;
  }
}

int main() { return XDYIMCMI0LY::solve(); }