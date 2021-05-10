#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 150 + 5;
const int MAX = 300 + 5;

inline int read() {
  int x;
  scanf("%d", &x);
  return x;
}

int n;

int f[MAX][MAX];

int l[N];
int r[N];

int top;
int t[MAX];

vector <int> v[MAX];

int mxx[MAX][MAX];
int mxy[MAX][MAX];

int main() {
  n = read();
  for (int i = 0; i < n; ++i) {
    l[i] = read();
    r[i] = read() - 1;
    t[top++] = l[i];
    t[top++] = r[i];
  }
  sort(t, t + top);
  int len = unique(t, t + top) - t;
  for (int i = 0; i < n; ++i) {
    l[i] = lower_bound(t, t + len, l[i]) - t + 1;
    r[i] = lower_bound(t, t + len, r[i]) - t + 1;
  }
  for (int i = 0; i < n; ++i) {
    v[r[i]].push_back(l[i]);
  }
  int ans = 0;
  for (int i = 1; i <= len; ++i) {
    for (int j = 0; j < v[i].size(); ++j) {
      int lim = v[i][j];
      for (int k = 0; k <= i; ++k) {
        f[i][k] = max(f[i][k], mxy[lim - 1][k] + 1);
        f[k][i] = max(f[k][i], mxx[k][lim - 1] + 1);
      }
      mxx[i][0] = f[i][0];
      mxy[0][i] = f[0][i];
      mxx[0][i] = max(f[0][i], mxx[0][i - 1]);
      mxy[i][0] = max(f[i][0], f[i - 1][0]);
      for (int k = 1; k <= i; ++k) {
        mxx[i][k] = max(f[i][k], mxx[i][k - 1]);
        mxx[k][i] = max(f[k][i], mxx[k][i - 1]);
      }
      for (int k = 1; k <= i; ++k) {
        mxy[i][k] = max(f[i][k], mxy[i - 1][k]);
        mxy[k][i] = max(f[k][i], mxy[k - 1][i]);
      }
    }
    if (v[i].size() == 0) {
       for (int k = 0; k <= i; ++k) {
         mxx[k][i] = mxx[k][i - 1];
      }
      for (int k = 0; k <= i; ++k) {
        mxy[i][k] = mxy[i - 1][k];
      }
    }
  }
  for (int i = 0; i <= len; ++i) {
    for (int j = 0; j <= len; ++j) {
      ans = max(ans, f[i][j]);
    }
  }
  printf("%d\n", ans);
  return 0;
}
