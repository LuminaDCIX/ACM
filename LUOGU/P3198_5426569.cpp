// luogu-judger-enable-o2
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e5 + 5;

int n;
double e;

int a[N];
long long sum[N];

int main () {
  scanf("%d", &n);
  scanf("%lf", &e);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + a[i];
  }
  for (int i = 1; i <= n; ++i) {
    int cnt = 0;
    double ans = 0;
    int j = floor(e * i);
    while (j >= 1 && cnt <= 500) {
      ++cnt;
      ans += (double) a[j] / (i - j);
      --j;
    }
    if (j != 0) {
      ans += (long long) sum[j] / (i - j / 2);
    }
    printf("%.6f\n", ans * a[i]);
  }
  return 0;
}
