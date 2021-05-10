#include <bits/stdc++.h>

using namespace std;

const int P = 1e9 + 7;
const int S = 10 + 3;
const int N = 100 + 5;

int add(int a, int b) {
  a += b;
  return a >= P ? a - P : a;
}

int mul(int a, int b) {
  return (unsigned long long) a * b % P;
}

int a[S];
int n;

int dp[S][N];

int C[N][N];

int main() {
  C[0][0] = 1;
  for (int i = 1; i < N; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
    }
  }

  scanf("%d", &n);
  for (int i = 0; i < 10; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = a[9]; i <= n; ++i) {
    dp[9][i] = 1;
  }

  for (int i = 8; i >= 1; --i) {
    for (int j = a[i]; j <= n; ++j) {
      for (int k = a[i]; k <= j; ++k) {
	dp[i][j] = add(dp[i][j], mul(dp[i + 1][j - k], C[j][k]));
      }
    }
  }

  int ans = 0;
  for (int i = a[0]; i <= n; ++i) {
    for (int j = a[0]; j <= i - 1; ++j) {
      dp[0][i] = add(dp[0][i], mul(dp[1][i - j], C[i - 1][j]));
    }
    ans = add(ans, dp[0][i]);
  }

  printf("%d\n", ans);
  return 0;
}
