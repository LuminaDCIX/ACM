#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read() 
{
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}
        
const int mod = 1000000007; 
const int N = 750 + 5;

int n, m, k;

vector < pair <int, int > > p[N * N];

int f[N][N];
int a[N][N];

vector <int> col;
bool vis[N * N];

int sum[N * N];
int all;

void solve(int l, int r) 
{
  if (l == r) {
    return;
  }
  int mid = (l + r) >> 1;
  solve(mid + 1, r);
  col.clear();
  all = 0;
  for (int i = n - 1; i >= 0; --i) {
    for (int j = l; j <= mid; ++j) {
      f[i][j] = (f[i][j] + all) % mod;
      f[i][j] = (f[i][j] - sum[a[i][j]]) % mod;
    }
    for (int j = mid + 1; j <= r; ++j) {
      if (!vis[a[i][j]]) {
        vis[a[i][j]] = 1;
        col.push_back(a[i][j]);
      }
      all = (all + f[i][j]) % mod;
      sum[a[i][j]] = (sum[a[i][j]] + f[i][j]) % mod;
    }
  }
  for (int i = 0; i < (int) col.size(); ++i) {
    sum[col[i]] = 0;
    vis[col[i]] = 0;
  }
  solve(l, mid);
}

int main() 
{
  n = read();
  m = read();
  k = read();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      a[i][j] = read();
    }
  }
  f[n - 1][m - 1] = 1;        
  solve(0, m - 1);
  printf("%d\n", f[0][0] < 0 ? f[0][0] + mod : f[0][0]);
  return 0;
}