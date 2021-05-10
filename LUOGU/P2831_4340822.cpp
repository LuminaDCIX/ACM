#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

inline double read() {
  double x;
  scanf("%lf", &x);
  return x;
}


const int N = 18 + 5;
const int MAX = (1 << 18) + 5;
const double eps = 1e-8;

int n;

double x[N];
double y[N];

pair <double, double> p[N];

int f[MAX];
int g[N][N];

inline void init() {
  memset(g, 0, sizeof(g));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        g[i][j] = 1 << i;
        continue;
      }
      double a = (y[i] / x[i] - y[j] / x[j]) / (x[i] - x[j]);
      if (a > 0) {
        continue;
      }
      double b = y[i] / x[i] - a * x[i];
      double b0 = y[j] / x[j] - a * x[j];
      // cerr << i << " " << j << "  " << a << " " << b << " " << b0 << endl;
      int s = 0;
      for (int k = 0; k < n; ++k) {
        if (abs(y[k] - x[k] * x[k] * a - b * x[k]) < eps) {
          s |= 1 << k;
        }
      }
      g[i][j] = s;
    }
  }
}

int main() {
  int T = read();
  while (T--) {
    memset(f, 0x3f3f, sizeof(f));
    n = read();
    read();
    for (int i = 0; i < n; ++i) {
      p[i].first = read();
      p[i].second = read();
    }
    // sort(p, p + n);
    for (int i = 0; i < n; ++i) {
      x[i] = p[i].first;
      y[i] = p[i].second;

     // cerr << x[i] << " " << y[i] << endl;
    }
    init();
    f[0] = 0;
    int lim = (1 << n) - 1;
    // for (int i = 0; i < n; ++i) {
    //   for (int j = 0; j < n; ++j) {
    //     cerr << g[i][j] << " " ;
    //   }
    //   cerr << endl;
    // }
    for (int s = 0; s < lim; ++s) {
      int i = 0;
      for (; i < n; ++i) {
        if (!(s & (1 << i))) {
          break;
        }
      }
      for (int j = 0; j < n; ++j) {
        f[s | g[i][j]] = min(f[s | g[i][j]], f[s] + 1);
      }
    }
    printf("%d\n", f[lim]);
  }
  return 0;
}
