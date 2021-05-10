#include <bits/stdc++.h>

using namespace std;

namespace XDYIMCMI0LY {

  const int N = 100 + 5;
  const int M = 15;
  const int V = (1 << 12) + 5;
  const int C = 7;
  const int P = 1e9 + 7;

  inline int ADD(int a, int b) { return a + b >= P ? a + b - P : a + b; }
  inline int SUB(int a, int b) { return a - b < 0 ? a - b + P : a - b; }
  inline int MUL(int a, int b) { return (long long) a * b % P; }
  inline int EXP(int a, int x) {
    int ret = 1;
    while (x) {
      if (x & 1) ret = MUL(ret, a);
      a = MUL(a, a), x >>= 1;
    }
    return ret;
  }

  int n, m, c, q;

  int id[256];

  int nxt[2][C][3];
  int fail[2][C];

  char s[2][C];
  int a[2][C];

  int f[V][C][C];
  int g[V][C][C];

  int solve() {
    id['X'] = 0;
    id['B'] = 1;
    id['W'] = 2;

    scanf("%d %d %d %d", &n, &m, &c, &q);
    while (q--) {
      scanf("%s %s", s[0] + 1, s[1] + 1);
      for (int i = 0; i <= 1; ++i) for (int j = 1; j <= c; ++j) a[i][j] = id[s[i][j]];
      for (int i = 0; i <= 1; ++i) {
        int k = 0;
        fail[i][1] = k;
        for (int j = 2; j <= c; ++j) {
          while (k && a[i][j] != a[i][k + 1]) k = fail[i][k];
          if (a[i][j] == a[i][k + 1]) ++k;
          fail[i][j] = k;
        }
      }
      for (int i = 0; i <= 1; ++i) {
        for (int j = 0; j < c; ++j) {
          for (int col = 0; col < 3; ++col) {
            int k = j;
            while (k != 0 && a[i][k + 1] != col) k = fail[i][k];
            if (a[i][k + 1] == col) ++k;
            nxt[i][j][col] = k;
          }
        }
      }
      int lim = 1 << (m - c + 1);
      memset(f, 0, sizeof(f));
      f[0][0][0] = 1;
      for (int i = 1; i <= n; ++i) {
        memset(g, 0, sizeof(g));
        for (int s = 0; s < lim; ++s) {
          for (int j = 0; j <= c; ++j) for (int k = 0; k <= c; ++k) g[s][0][0] = ADD(g[s][0][0], f[s][j][k]);
        }
        memcpy(f, g, sizeof(f));
        for (int j = 1; j <= m; ++j) {
          memset(g, 0, sizeof(g));
          for (int s = 0; s < lim; ++s) {
            for (int l1 = 0; l1 < c; ++l1) {
              for (int l2 = 0; l2 < c; ++l2) {
                for (int col = 0; col < 3; ++col) if (f[s][l1][l2]) {
                  int n1 = nxt[0][l1][col], n2 = nxt[1][l2][col], k = s;
                  if (j >= c && ((1 << (j - c)) & s)) k ^= 1 << (j - c);
                  if (n1 == c) k |= 1 << (j - c), n1 = fail[0][c];
                  if (n2 == c) {
                    if ((1 << (j - c)) & s) continue;
                    n2 = fail[1][c];
                  }
                  g[k][n1][n2] = ADD(g[k][n1][n2], f[s][l1][l2]);
                }
              }
            }
          }
          memcpy(f, g, sizeof(f));
        };
      }
      int ans = EXP(3, n * m);
      for (int s = 0; s < lim; ++s) {
        for (int i = 0; i < c; ++i) for (int j = 0; j < c; ++j) ans = SUB(ans, f[s][i][j]);
      }
      cout << ans << endl;
    }
    return 0;
  }
};

int main() { return XDYIMCMI0LY::solve(); }