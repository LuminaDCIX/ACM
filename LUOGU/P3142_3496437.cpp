#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <set>

inline int read()
{
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

using namespace std;

const int N = 50000 + 5;

int n;

struct point {
  int x;
  int y;

  bool operator < (const point &rhs) const {
    return x == rhs.x ? y < rhs.y : x < rhs.x;
  }

};

point p[N];

point t[N];

bool cmpx(const point &a, const point &b) {
  return a.x < b.x;
}

bool cmpy(const point &a, const point &b) {
  return a.y < b.y;
}

set <point> s;

int main()
{
  n = read();
  if (n <= 4) {
    puts("0");
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    p[i].x = read();
    p[i].y = read();
  }
  sort(p, p + n, cmpx);
  for (int i = 0; i < 4; ++i) {
    s.insert(p[i]);
  }
  for (int i = n - 1; i >= n - 4; --i) {
    s.insert(p[i]);
  }
  sort(p, p + n, cmpy);
  for (int i = 0; i < 4; ++i) {
    s.insert(p[i]);
  }
  for (int i = n - 1; i >= n - 4; --i) {
    s.insert(p[i]);
  }
  long long ans = 1e18;
  int siz = s.size();
  set <point>::iterator it = s.begin();
  for (int i = 0; i < siz; ++i) {
    t[i] = *it;
    ++it;
  }
  for (int i = 0; i < siz; ++i) {
    for (int j = i + 1; j < siz; ++j) {
      for (int k = j + 1; k < siz; ++k) {
	int u = 0;
	int d = 40001;
	int l = 40001;
	int r = 0;
	for (int o = 0; o < siz; ++o) {
	  if (o == i || o == j || o == k) {
	    continue;
	  }
	  u = max(u, t[o].x);
	  d = min(d, t[o].x);
	  l = min(l, t[o].y);
	  r = max(r, t[o].y);
	}
	ans = min(1ll * (u - d) * (r - l), ans);
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}
  
  
