#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <set>
#include <vector>
#include <map>
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

const int N = 200000 + 5;

const int mod = 98754321;
int n;
int k;

int a[N];
int b[N];

int pre[N];
int sub[N];
int fac[N];

inline void init(int s[], int t[]) {
  for (int i = 0; i < n; ++i) {
    t[i] = ((long long) t[i - 1] * 2333  + s[i]) % mod;
  }
}

inline int prephs(int l, int r) {
  if (l == 0) {
    return pre[r];
  }
  return (((pre[r] - (long long) pre[l - 1] * fac[r - l + 1])) % mod + mod) % mod;
}

inline int subphs(int l, int r) {
  if (l == 0) {
    return sub[r];
  }
  return  (((sub[r] - (long long) sub[l - 1] * fac[r - l + 1])) % mod + mod) % mod;
}

map <int, bool> mp;

int main()
{
  n = read();
  if (n == 0) {
    printf("%d %d\n", 0, 0);
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    a[i] = read();
    b[n - i - 1] = a[i];
  }
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = (long long) fac[i - 1] * 2333 % mod;
  }
  init(a, pre);
  init(b, sub);
  int mx = 0;
  vector <int> ans;
  for (int k = 1; k <= n; ++k) {
    int now = 0;
    for (int i = 0, l ,r, h1, h2; i + k - 1 < n; i += k) {
      l = i;
      r = i + k - 1;
      h1 = prephs(l, r);
      h2 = subphs(n - r - 1, n - l - 1);
      if (!mp[h1] || !mp[h2]) {
        ++now;
        mp[h1] = 1;
        mp[h2] = 1;
      }
    }
    if (now == mx) {
      ans.push_back(k);
    }
    if (now > mx) {
      mx = now;
      ans.clear();
      ans.push_back(k);
    }
    mp.clear();
  }

  printf("%d %d\n", mx, (int) ans.size());
  for (int i = 0; i < (int) ans.size() - 1; ++i) {
    printf("%d ", ans[i]);
  }
  printf("%d\n", ans[ans.size() - 1]);
  return 0;
}
