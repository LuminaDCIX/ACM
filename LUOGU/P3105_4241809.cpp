#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

inline int read() {
  int x;
  scanf("%d", &x);
  return x;
}

inline int read_col() {
  char o[4];
  scanf("%s", o);
  return o[0] == 'S';
}

const int N = 100000 + 5;

int n;

pair <int, int> p[N];

pair <int, int> x[N];

int main() {
  n = read();
  for (int i = 0; i < n; ++i) {
    int f = read();
    int s = read_col();
    p[i] = make_pair(f, s);
  }
  int cur = -1;
  sort(p, p + n);
  int cntw = 0;
  int cnts = 0;
  for (int i = 0; i < n; ++i) {
    if (p[i].second == 1) {
      ++cnts;
    } else {
      ++cntw;
    }
    x[i] = make_pair(cntw - cnts, i);
  }
  x[n++] = make_pair(0, -1);
  sort(x, x + n);
  int ans = 0;
  // for (int i = 0; i < n; ++i) {
  //   cerr << x[i].first << " " << x[i].second << endl;
  // }
  int que0top = 1e9;
  int que1top = 1e9;
  for (int i = 0; i < n; ++i) {
    if (x[i].first % 2) {
      if (que0top > x[i].second) {
        que0top = x[i].second;
      }
      if (que0top < x[i].second - 1) {
        // cerr << x[i].second << endl;
        ans = max(ans, p[x[i].second].first - p[que0top + 1].first);
      }
    } else {

      if (que1top > x[i].second) {
        que1top = x[i].second;
      }
      if (que1top < x[i].second - 1) {
        // cerr << x[i].second << endl;
        ans = max(ans, p[x[i].second].first - p[que1top + 1].first);
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
