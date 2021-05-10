#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;
const int maxn = 1e6;
int n, m;
int x[maxn + 5];
int sub[maxn + 5];
struct modify
{
  int l, r, val;
} modifys[maxn + 5];
void pre()
{
  for (int i = 1; i <= n; ++i) {
    sub[i] = x[i] - x[i - 1];
  }
  return;
}

void input()
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x[i]);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &modifys[i].val, &modifys[i].l, &modifys[i].r);
  }
  modifys[m + 1].val = 1000000000;
  modifys[m + 1].l = 1;
  modifys[m + 1].r = n;
  pre();
  return;
}
bool judge(int x) {
  for (int i = 1; i <= x; ++i) {
    sub[modifys[i].l] -= modifys[i].val;
    sub[modifys[i].r + 1] += modifys[i].val;
  }
  int _sum = 0;
  for (int i = 1; i <= n; ++i) {
    _sum += sub[i];
    if (_sum < 0) {
      return false;
    }
  }
  return true;
}
void solve()
{
  int l = 1, r = m + 1;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (judge(mid)) {
      l = mid + 1;
    }
    else {
      r = mid;
    }
    pre();
  }
  if (l == m + 1) {
    printf("%d\n", 0);
    return;
  }
  printf("-1\n%d\n", l);
  return;
}

int main()
{
  input();
  solve();

  return 0;
}

/*



*/