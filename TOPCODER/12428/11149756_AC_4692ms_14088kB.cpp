#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

class CentaurCompany {
public:
	double getvalue(vector <int>, vector <int>);
};

const int N = 36 + 5;

int n;

int tot;
int head[N];

struct edge {
  int nxt;
  int to;
};

edge e[N << 1];

inline void add(int u, int v) {
  e[tot].to = v;
  e[tot].nxt = head[u];
  head[u] = tot++;
}

long double f[N][N][N][2];

long double t[N][N][2];

void dfs(int u, int fa) {
  f[u][0][0][0] = 1;
  f[u][1][1][1] = 1;
  for (int o = head[u]; ~o; o = e[o].nxt) {
    int v = e[o].to;
    if (v == fa) {
      continue;
    }
    dfs(v, u);
    memcpy(t, f[u], sizeof(t));
    memset(t, 0, sizeof(t));
    for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= n; ++j) {
        for (int k = 0; k <= n; ++k) {
          for (int l = 0; l <= n; ++l) {
            if (i + k > n || j + l > n) {
              continue;
            }
            double sum = 0;
            sum += f[u][i][j][1] * f[v][k][l][0];
            sum += f[u][i][j + 1][1] * f[v][k][l][1];
            //sum += f[u][i][j][1] * f[v][k][l + 1][1];
            // if (i + k == 2 && j + l == 1) {
            //   cerr << sum << endl;
            // }
            t[i + k][j + l][1] += sum;
            
            sum = 0;
            sum += f[u][i][j][0] * f[v][k][l][1];
            sum += f[u][i][j][0] * f[v][k][l][0];
            t[i + k][j + l][0] += sum;
          }
        }
      }
    }
    memcpy(f[u], t, sizeof(t));
  }
  // for (int i = 0; i <= n; ++i) {
  //   for (int j = 0; j <= n; ++j) {
  //     if (f[1][i][j][1] != 0) {
  //       cerr << 1  << "[" << i << "]" << "[" << j << "]" << "[1]" << " = " << f[1][i][j][1] << endl;
  //     }
  //     if (f[1][i][j][0] != 0) {
  //       cerr << 1 << "[" << i << "]" << "[" << j << "]" << "[0]" << " = " << f[1][i][j][0] << endl;
  //     }
  //   }
  // }
}

double CentaurCompany::getvalue(vector <int> a, vector <int> b) {
  n = a.size() + 1;
  memset(head, -1, sizeof(head));
  for (int i = 0; i < (int) a.size(); ++i) {
    add(a[i], b[i]);
    add(b[i], a[i]);
  }
  dfs(1, -1);
  double ans = 0;
  double exp = 1;
  for (int i = 1; i <= n; ++i) {
    exp = exp * 2;
  }
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= n; ++j) {
      // if (f[1][i][j][1] != 0) {
      //   cerr << "[" << i << "]" << "[" << j << "]" << "[1]" << " = " << f[1][i][j][1] << endl;
      // }
      // if (f[0][i][j][0] != 0) {
      //   cerr << "[" << i << "]" << "[" << j << "]" << "[0]" << " = " << f[1][i][j][0] << endl;
      // }
      ans += (f[1][i][j][0] + f[1][i][j][1]) * max(2 * j - i - 2, 0);
    }
  }
  return 2 * ans / exp;
}



