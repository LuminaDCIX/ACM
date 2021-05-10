#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n;
int m;
int k;
int r;

struct node {
  int x;
  int y;
  long long cnt;
};

bool operator < (node a, node b) {
  return a.cnt < b.cnt;
}

priority_queue <node> que;

map < pair <int, int> , int> mp;

int dx[] = {0, 0, 1, -1};
int dy[] = {-1, 1, 0, 0};

long long calc(int x, int y) {
  long long l = max(y - r + 1, 0);
  int rr = min(y, m - r);
  int u = max(r - 1, x);
  long long d = min(n - 1, x + r  - 1);
  return (rr - l + 1) * (d - u + 1);
}

int main() {
  scanf("%d %d %d %d", &n, &m, &r, &k);
  int x = n / 2;
  int y = m / 2;
  que.push((node) {x, y, calc(x, y)});
  double sum = 0;
  while (!que.empty()) {       
    double add = que.top().cnt;
    x = que.top().x;
    y = que.top().y;
    que.pop();
    if (mp[make_pair(x, y)]) {
      continue;
    }
    mp[make_pair(x, y)] = 1;
    sum += add;
    --k;
    if (k == 0) {
      break;
    }
    for (int i = 0; i < 4; ++i) {
      int tx = x + dx[i];
      int ty = y + dy[i];
      if (tx >= 0 && tx <  n && ty >= 0 && ty < m) {
        que.push((node) {tx, ty, calc(tx, ty)});
      } 
    }
  }
  sum /= (double) (n - r + 1) * (m - r + 1);
  printf("%.10f\n", sum);
  return 0;
}