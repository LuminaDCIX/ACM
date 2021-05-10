// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

class gauss {
public:
  vector<vector<double> > a;

  vector<double> solve() {
    int n = (int) a.size();
    int k = 0;
    for (int i = 0; i < n; ++i) {
      int pivot = k;
      for (int j = k + 1; j < n; ++j) {
        if (abs(a[j][i]) > abs(a[pivot][i])) {
          pivot = j;
        }
      }
      if (a[pivot][i] == 0) {
        continue;
      }
      if (pivot != k) {
        for (int j = i; j <= n; ++j) {
          swap(a[k][j], a[pivot][j]);
        }
      }
      for (int j = n; j >= i; --j) {
        a[k][j] /= a[k][i];
      }
      for (int x = 0; x < n; ++x) {
        if (x == k) {
          continue;
        }
        for (int y = n; y >= i; --y) {
          a[x][y] -= a[x][i] * a[k][y];
        }
      }
      ++k;
    }
    if (k != n) {
      return vector<double>();
    }
    vector<double> res;
    for (int i = 0; i < n; ++i) {
      res.push_back(a[i][n]);
    }
    return res;
  }
  
  gauss(const vector<vector<double> > &v, const vector<double> &x) {
    int n = x.size();
    a = vector<vector<double> >(n, vector<double>(n + 1));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        a[i][j] = v[i][j];
      }
      a[i][n] = x[i];
    }
  }
};

int main() {
  int n;
  cin >> n;
  vector<vector<double> > a;
  vector<double> x;
  for (int i = 0, t; i < n; ++i) {
    vector<double> v;
    for (int j = 0; j < n; ++j) {
      cin >> t;
      v.push_back(t);
    }
    a.push_back(v);
    cin >> t;
    x.push_back(t);
  }
  static gauss g = gauss(a, x);
  x = g.solve();
  if (x.size() == 0) {
    puts("No Solution");
    return 0;
  }
  
  for (int i = 0; i < n; ++i) {
    printf("%.2f\n", x[i] + 1e-7);
  }
  return 0;
}
    
    
