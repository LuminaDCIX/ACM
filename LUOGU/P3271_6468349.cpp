// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

inline int read() {
  int f = 1;
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return f * x;
}

const int N = 2000 + 5;
const int P = 1e8 + 7;

int n, m, k;

struct hash {
  vector <pair <int, int> > v[2333];

  void insert(pair <int, int> f) {
    
    int key = ((f.first + f.second) * (long long) f.second % 2333 + 2333) % 2333;
    v[key].push_back(f);
  }

  bool end() {
    return 0;
  }

  bool find(pair <int, int> f) {
    int key = ((f.first + f.second) * (long long) f.second % 2333 + 2333) % 2333;
    for (int i = 0; i < (int) v[key].size(); ++i) {
      if (v[key][i] == f) {
        return true;
      }
    }
    return false;
  }
} s;

int x[N], y[N];

inline int add(int a, int b) {
  return (a += b) >= P ? a - P : a;
}
inline int sub(int a, int b) {
  return (a -= b) < 0 ? a + P : a;
}
inline int mul(int a, int b) {
  return (long long) a * b % P;
}

int calcall() {
  int nw = 0;
  for (int i = 1; i <= m; ++i) {
    nw = add(nw, mul(i, mul(n - i + 1, m - i + 1)));
  }
  return nw;
}

int area(int l, int r, int h) {
  int z = min(l + r, h);
  if (z == 0) {
    return 0;
  }
  int ret = (long long) z * (z + 3) / 2 % P;
  if (z > l) {
    ret = sub(ret, (long long) (z - l) * (z - l + 1) / 2 % P);
  }
  if (z > r) {
    ret = sub(ret, (long long) (z - r) * (z - r + 1) / 2 % P);
  }
  return ret;
}

inline int calc1() {
  int nw = 0;
  for (int i = 1; i <= k; ++i) {
    nw = add(nw, area(y[i], m - y[i], x[i]));
    nw = add(nw, area(y[i], m - y[i], n - x[i]));
    nw = add(nw, area(x[i], n - x[i], y[i]));
    nw = add(nw, area(x[i], n - x[i], m - y[i]));
    nw = sub(nw, min(x[i], y[i]));
    nw = sub(nw, min(x[i], m - y[i]));
    nw = sub(nw, min(n - x[i], y[i]));
    nw = sub(nw, min(n - x[i], m - y[i]));
  }
  return nw;
}

bool ok(int x1, int y1) {
  return x1 >= 0 && x1 <= n && y1 >= 0 && y1 <= m;
}

inline int calc2() {
  int nw = 0;
  for (int i = 1; i <= k; ++i) {
    for (int j = 1; j <= k; ++j) {
      if (i == j) {
        continue;
      }
      int dx = x[i] - x[j];
      int dy = y[i] - y[j];

      if (ok(x[i] + dy, y[i] - dx) && ok(x[j] + dy, y[j] - dx)) {
        ++nw;
      }
      if (ok(x[i] - dy, y[i] + dx) && ok(x[j] - dy, y[j] + dx)) {
        ++nw;
      }
      if ((abs(dx) + abs(dy)) & 1) {
        continue;
      }
      int ddx = (dx + dy) / 2;
      int ddy = (dx - dy) / 2;

      if (ok(x[i] - ddy, y[i] - ddx) && ok(x[j] + ddy, y[j] + ddx)) {// /*ok(x[i] - ddx,  y[i] + ddy)*/) {
        ++nw;
      }
    }
  }
  return nw / 2;
}

inline int calc3() {
  int nw = 0;
  for (int i = 1; i <= k; ++i) {
    for (int j = 1; j <= k; ++j) {
      if (i == j) {
        continue;
      }
      int dx = x[i] - x[j];
      int dy = y[i] - y[j];
      
      int x1 = x[i] + dy;
      int y1 = y[i] - dx;
      int x2 = x[j] + dy;
      int y2 = y[j] - dx;
      if (s.find(make_pair(x1, y1)) != s.end() && ok(x2, y2)) {
        ++nw;
      }
      if (s.find(make_pair(x2, y2)) != s.end() && ok(x1, y1)) {
        ++nw;
      }
      x1 = x[i] - dy;
      y1 = y[i] + dx;
      x2 = x[j] - dy;
      y2 = y[j] + dx;
      if (s.find(make_pair(x1, y1)) != s.end() && ok(x2, y2)) {
        ++nw;
      }
      if (s.find(make_pair(x2, y2)) != s.end() && ok(x1, y1)) {
        ++nw;
      }
      if (abs(dx + dy) & 1) {
        continue;
      }
      int ddx = (dx + dy) / 2;
      int ddy = (dx - dy) / 2;
      x1 = x[i] - ddy;
      y1 = y[i] - ddx;
      x2 = x[j] + ddy;
      y2 = y[j] + ddx;
      if (s.find(make_pair(x1, y1)) != s.end() && ok(x2, y2)) {
        ++nw;
      }
      if (s.find(make_pair(x2, y2)) != s.end() && ok(x1, y1)) {
        ++nw;
      }
    }
  }
  return nw / 6;
}

inline int calc4() {
  int nw = 0;
  for (int i = 1; i <= k; ++i) {
    for (int j = 1; j <= k; ++j) {
      if (i == j) {
        continue;
      }
      int dx = x[i] - x[j];
      int dy = y[i] - y[j];
      
      int x1 = x[i] + dy;
      int y1 = y[i] - dx;
      int x2 = x[j] + dy;
      int y2 = y[j] - dx;
      if (s.find(make_pair(x1, y1)) != s.end() && s.find(make_pair(x2, y2)) != s.end()) {
        ++nw;
      }
      x1 = x[i] - dy;
      y1 = y[i] + dx;
      x2 = x[j] - dy;
      y2 = y[j] + dx;
      if (s.find(make_pair(x1, y1)) != s.end() && s.find(make_pair(x2, y2)) != s.end()) {
        ++nw;
      }
      if (abs(dx + dy) & 1) {
        continue;
      }
      int ddx = (dx + dy) / 2;
      int ddy = (dx - dy) / 2;
      x1 = x[i] - ddy;
      y1 = y[i] - ddx;
      x2 = x[i] - ddx;
      y2 = y[i] + ddy;
      if (s.find(make_pair(x1, y1)) != s.end() && s.find(make_pair(x2, y2)) != s.end()) {
        ++nw;
      }
    }
  }
  return nw / 12;
}

int main() {
  n = read();
  m = read();
  k = read();
  for (int i = 1; i <= k; ++i) {
    x[i] = read();
    y[i] = read();
  }
  if (n < m) {
    swap(n, m);
    for (int i = 1; i <=k; ++i) {
      swap(x[i], y[i]);
    }
  }
  for (int i = 1; i <= k; ++i) {
    s.insert(make_pair(x[i], y[i]));
  }
  int ans = calcall();
  ans = sub(ans, calc1());
  ans = add(ans, calc2());
  ans = sub(ans, calc3());
  ans = add(ans, calc4());
  printf("%d\n", ans);
  return 0;
}
