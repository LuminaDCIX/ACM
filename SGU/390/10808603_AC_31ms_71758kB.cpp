#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int LEN = 18 + 5;
const int SUM = 153 + 5;
const int K = 1000 + 5;

int n;

long long l;
long long r;
int k;

struct node {
  long long a;
  int rem;

  node(int _a = 0, int _rem = 0) {
    a = _a;
    rem = _rem;
  }
};

node operator + (const node &x, const node &y) {
  node ret;
  ret.a = x.a + y.a;
  ret.rem = y.rem;
  return ret;
}

int a[LEN];
int b[LEN];


node f[LEN][SUM][K];
int vis[LEN][SUM][K];

node dfs(int h, int sum, int rem, bool f1, bool f2)
{
  if (h == 0) {
    if (sum + rem >= k) {
      return node(1, 0);
    }
    return node(0, sum + rem);
  }
  if (!f1 && !f2 && vis[h][sum][rem]) {
    return f[h][sum][rem];
  }
  int low = f1 ? a[h] : 0;
  int high = f2 ? b[h] : 9;
  node res;
  res.a = 0;
  res.rem = rem;
  for (int i = low; i <= high; ++i) {
    res = res + dfs(h - 1, sum + i, res.rem, f1 && i == a[h], f2 && i == b[h]);
  }
  if (!f1 && !f2) {
    vis[h][sum][rem] = 1;
    f[h][sum][rem] = res;
  }
  return res;
}

int main()
{
  scanf("%lld%lld", &l, &r);
  scanf("%d", &k);
  for (int i = 1; i <= 19; ++i) {
    a[i] = l % 10;
    l /= 10;
  }
  for (int i = 1; i <= 19; ++i) {
    b[i] = r % 10;
    r /= 10;
  }
  printf("%lld\n", dfs(19, 0, 0, 1, 1).a);
  return 0;
}
