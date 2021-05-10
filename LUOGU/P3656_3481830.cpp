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

const int N = 100000 + 5;

int n;

int a[N];
int b[N];

int p[N];

int t[N];

inline long long sum(int x)
{
  ++x;
  long long ret = 0;
  while (x) {
    ret += t[x];
    x -= x & -x;
  }
  return ret;
}

inline void add(int x) {
  ++x;
  while (x <= n) {
    t[x] += 1;
    x += x & -x;
  }
}

int f[N];

inline long long  solve()
{
  for (int i = 0; i < n; ++i) {
    p[b[i]] = i;
  }
  for (int i = 0; i < n; ++i) {
    f[i] = p[a[i]];
  }
  long long ret = 0;
  memset(t, 0, sizeof(t));
  for (int i = 0; i < n; ++i) {
    ret += sum(n - 1) - sum(f[i]);
    add(f[i]);
  }
  long long now = ret;
  for (int i = n - 1; i >= 0; --i) {
    now -= n - 1 - f[i];
    now += f[i];
    ret = min(ret, now);
  }
  return ret;
}

int main()
{
  n = read();
  for (int i = 0; i < n; ++i) {
    a[i] = read();
  }
  for (int i = 0; i < n; ++i) {
    b[i] = read();
  }
  long long ret = solve();
  for (int i = 0; i < n; ++i) {
    swap(a[i], b[i]);
  }
  ret = min(solve(), ret);
  printf("%lld\n", ret);
  return 0;
}
	 
