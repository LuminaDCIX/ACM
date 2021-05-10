#include <cstdio>
#include <cstring>

using namespace std;

int n;
int m;
int k;

const int N = 1000 + 5;
const int M = 200 + 5;

long long f[2][M][N];

char a[N];
char b[M];

long long sum[M][N];

const long long mod = 1000000007 ;

int main() {
  scanf("%d %d %d", &n, &m, &k);
  scanf("%s %s", a, b);
  int now = 1;
  int lst = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] == b[0]) {
      f[now][1][i] = 1;
    }
  }
  for (int i = 1; i < m; ++i) {
    now ^= 1;
    lst ^= 1;
    memset(f[now], 0, sizeof(f[now]));
    memset(sum, 0, sizeof(sum));
    for (int j = 1; j <= k; ++j) {
      sum[j][0] = f[lst][j][0];
      for (int x = 1; x < n; ++x) {
        sum[j][x] =( sum[j][x - 1] + f[lst][j][x]) % mod;
      }
    }
    for (int j = 0; j < n; ++j) {
      if (a[j] == b[i]) {
        for (int x = 1; x <= k; ++x) {
          f[now][x][j] = (sum[x - 1][j - 1] + f[lst][x][j - 1]) % mod;
        }
      }
    }
  }
  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += f[now][k][i];
    if (sum > mod) {
      sum -= mod;
    }
  }
  printf("%lld\n", sum);
  return 0;
}
