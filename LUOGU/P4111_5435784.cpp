// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

const int N = 9 + 5;
const int MAX = 81 + 5;
const int P = 1e9;

int n;
int m;
int lim;

int add(int a, int b) {
  a += b;
  return a >= P ? a - P : a;
}

int sub(int a, int b) {
  a -= b;
  return a < 0 ? a + P : a;
}

int mul(int a, int b) {
  return (long long) a * b % P;
}

struct Mat {
  int s[MAX][MAX];
  
  void init() {
    memset(s, 0, sizeof(s));
  }
  
  void unit() {
    init();
    for (int i = 0; i < lim; ++i) {
      s[i][i] = 1;  
    }
  }

  Mat operator - (const Mat a) const {
    Mat r;
    r.init();
    for (int i = 0; i < lim; ++i) {
      for (int j = 0; j < lim; ++j) {
        r.s[i][j] = sub(s[i][j], a.s[i][j]);  
      }
    }
    return r;
  }

  int det() {
    int o = 1;
    for (int i = 1; i < lim; ++i) {
      int r = i;
      for (int j = i; j < lim; ++j) { 
        if (s[j][i]) {
          r = j;
          break;
        } 
      }
      if (r != i) {
        o = -o;
        for (int j = i; j < lim; ++j) {
          swap(s[i][j], s[r][j]);
        }
      }
      for (int j = i; j < lim; ++j) {
        if (j == i || s[j][i] == 0) {
          continue;
        }
                                 
        while (s[j][i] != 0) {
          int t = s[i][i] / s[j][i];
          for (int k = 1; k < lim; ++k) {
            swap(s[i][k], s[j][k]);
          }
          o = -o;
          for (int k = 1; k < lim; ++k) {
            s[j][k] = sub(s[j][k], mul(t, s[i][k]));  
          }
        }
 
      }
    }
    int ans = 1;
    for (int k = 1; k < lim; ++k) {
      ans = mul(ans, s[k][k]);
    }
    return o < 0 ? P - ans : ans;
  } 

  void print() {
    cout << endl;
    for (int i = 1; i < lim; ++i) {
      for (int j = 1; j < lim; ++j) {
        printf("%9d ", s[i][j]);
      }
      cout << endl;
    }
    cout << endl;
  }
};

map < pair <int, int>, int> id;

char f[N][N];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};


int main() {  
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("\n");
    for (int j = 0; j < m; ++j) {
      f[i][j] = getchar();
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (f[i][j] != '*') {
	id[make_pair(i, j)] = lim++;
      }
    }
  }

  Mat d;
  Mat g;
  d.init();
  g.init();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (f[i][j] == '*'){
	continue;
      }
      int u = id[make_pair(i, j)];
      for (int o = 0; o < 4; ++o) {
        int x = dx[o] + i;
        int y = dy[o] + j;
        if (x >= 0 && x < n && y >= 0 && y < m && f[x][y] == '.') {
          ++g.s[u][id[make_pair(x, y)]];
          ++d.s[u][u];
        }
      }
    }
  }
  Mat c = d - g;

  int ans = c.det();
  printf("%d\n", ans);
  return 0;
}
