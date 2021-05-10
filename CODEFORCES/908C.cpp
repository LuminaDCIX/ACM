#include <bits/stdc++.h>

using namespace std;

const int N = 1000 + 5;

int n;

int r;

int x[N];
double y[N];

int main() {
  scanf("%d %d", &n, &r);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &x[i]);
  }
  for (int i = 0; i < n; ++i) {
    double ans = r;
    int nl = x[i] - r;
    int nr = x[i] + r;
    for (int j = 0; j < i; ++j) {
      int l = x[j] - r;
      int rx = x[j] + r;
      if ((rx >= nl && rx <= nr) || (l >= nl && l <= nr)) {
        double det = sqrt((2 * r) * (2 * r) - (x[i] - x[j]) * (x[i] - x[j]));
        ans = max(ans, det + y[j]);
      }
    }
    y[i] = ans;
  }
  for (int i = 0; i < n; ++i) {
    printf("%.8f ", y[i]);
  }
  return 0;
}
