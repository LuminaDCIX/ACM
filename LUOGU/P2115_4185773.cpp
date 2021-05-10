#include <cstdio>
#include <algorithm>

using namespace std;

inline int read() {
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000 + 5;

int n;

int a[N];

int sum[N];

inline bool check(double x) {
  double S = sum[n - 1] - n * x;
  double mn = sum[0];
  double ret = 1e18;
  for (int i = 1; i < n - 1; ++i) {
    ret = min(S - (sum[i] - i * x) + mn, ret);
    mn = min(sum[i] - i * x, mn);
  }
  return ret >= 0;
}

int main() {
  n = read();
  for (int i = 0; i < n; ++i) {
    a[i] = read();
  }
  sum[0] = a[0];
  for (int i = 1; i < n; ++i) {
    sum[i] = sum[i - 1] + a[i];
  }
  double low = 0;
  double high = 1e18;
  for (int i = 0; i < 200; ++i) {
    double mid = (low + high) * 0.5;
    if (check(mid)) {
      low = mid;
    } else {
      high = mid;
    }
  }
  printf("%.3f\n", low);
  return 0;
}
