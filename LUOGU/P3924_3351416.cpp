#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long ll;

inline ll read() 
{
  int f = 1;
  ll x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}

const int N = 1e6 + 5;

int n, m, p;
int dep[N];
int num1[N];
int num2[N];
int a[N];
int maxdep;

inline void build(int l, int r,int depth) 
{
  if (l == r) {
    dep[l] = depth;
    maxdep = max(maxdep, depth);
    return;
  }
  int mid = l + r >> 1;
  build(l, mid, depth + 1);
  build(mid + 1, r, depth + 1);
}
 
int main()
{
  n = read();
  m = read();
  p = read();
  build(1, n, 1);
  for (int i = 1; i <= n; ++i) {
    a[i] = read();
  }
  ll ans = 0;
  ll fac1 = 0;
  ll fac2 = 0;
  for (int i = 1; i <= n; ++i) {
    num1[i] = num1[i - 1] + (dep[i] == maxdep);
    num2[i] = num2[i - 1] + (dep[i] == maxdep - 1);
  }
  //init ans
  for (int i = 1; i <= n; ++i) {
    ans += 2 * a[i];
    if (dep[i] == maxdep) {
      fac1 += 2 * a[i];
    } else {
      fac2 += 2 * a[i];
    }
  }
  for (int i = 0, l, r, v; i < m; ++i) {
    l = read();
    r = read();
    v = read();
    ans += 2 * (r - l + 1) * v;
    fac1 += 2 * v * (num1[r] - num1[l - 1]);
    fac2 += 2 * v * (num2[r] - num2[l - 1]);
    printf("%lld\n", ans * p - ((fac1 * p + (fac2 * p << 1)) >> maxdep));
  }
  return 0;
}
