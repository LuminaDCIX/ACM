#include <bits/stdc++.h>

using namespace std;

const int N = 55;

char mp[N][N];

int n;
int m;

int sx, sy;
int tx, ty;

int len;
char s[105];
int op[105];

int fx[] = {0, 0, 1, -1};
int fy[] = {1, -1, 0, 0};

int k[4];

int dx[4];
int dy[4];

bool judge() {
  int nx = sx;
  int ny = sy;
  for (int i = 0; i < len; ++i) {
    nx += dx[op[i]];
    ny += dy[op[i]];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
      return false;
    }
    if (mp[nx][ny] == '#') {
      return false;
    }
    if (mp[nx][ny] == 'E') {
      return true;
    }
  }
  if (mp[nx][ny] != 'E') {
    return false;
  }
  return true;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%s", mp[i]);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (mp[i][j] == 'S') {
        sx = i;
        sy = j;
      }
      if (mp[i][j] == 'E') {
        tx = i;
        ty = j;
      }
    }
  }
  scanf("%s", s);
  len = strlen(s);
  for (int i = 0; i < len; ++i) {
    op[i] = s[i] - '0';
  }
  int ans = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      for (int k = 0; k < 4; ++k) {
        for (int l = 0; l < 4; ++l) {
          if (i != j && j != k && k != l && i != k && i != l && j != l) {
            dx[0] = fx[i];
            dy[0] = fy[i];
            dx[1] = fx[j];
            dy[1] = fy[j];
            dx[2] = fx[k];
            dy[2] = fy[k];
            dx[3] = fx[l];
            dy[3] = fy[l];
            if (judge()) {
              ++ans;
              // for (int p = 0; p < 4; ++p) {
              //   printf("%d %d\n", dx[p], dy[p]);
              // }
              // cerr << endl;
            }
          }
        }
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
