#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 100000 + 5;
typedef long long ll;

int n;
int t[N << 1];
int lst[N];

inline int read() {
  int x = 0, f = 1;
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

inline void add(int x, int v) {
  while (x <= 2 * n) {
    t[x] += v;
    x += x & -x;
  }
  return;
}

inline ll sum(int x) {
  ll ret = 0;
  while (x) {
    ret += t[x];
    x -= x & -x;
  }
  return ret;
}

int main()
{
  n = read();
  ll ans = 0;
  for (int i = 1, a; i <= n * 2; ++i) {
    a = read();
    if (lst[a]) {
      ans += sum(i) - sum(lst[a]);
      add(lst[a], -1);
    } else {
      add(i, 1);
      lst[a] = i;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
