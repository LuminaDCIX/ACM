#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

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

struct vec {
  double x, y;

  double det(const vec &b) const {
    return x * b.y - y * b.x;
  }
  double slope(const vec &b) const {
    return (b.y - y) / (b.x - x);
  }
  vec operator - (const vec &b) const {
    vec ret;
    ret.x = x - b.x;
    ret.y = y - b.y;
    return ret;
  }
  bool operator < (const vec &b) const {
    return x == b.x ? y < b.y : x < b.x;
  }
};

int n;

vec v[N];

vec stk[N];
int top;

void build() {
  stk[++top] = v[n];
  for (int i = n - 1; i >= 1; --i) {
    while (top >= 2 && (stk[top] - stk[top - 1]).det(v[i] - stk[top]) <= 0) {

      --top;
    }
    stk[++top] = v[i];
  }
  if (stk[top].x == stk[top - 1].x) {
    --top;
  }
}

double getval(double k, vec t) {
  if (k == 0) {
    return 2e18;
  }
  return t.x + t.y - k * t.x - t.y / k;
}

double update(double l, double r, vec t) {
  r = min(0.0, r);
  if (l > r) {
    return 2e18;
  }
  double ans = 2e18;
  ans = min(getval(l, t), ans);
  ans = min(getval(r, t), ans);
  double best = -sqrt(t.x / t.y);
  if (best >= l && best <= r) {
    ans = min(ans, getval(best, t));
  }
  return ans;
}

int main() {
  n = read();
  for (int i = 1; i <= n; ++i) {
    v[i].x = read();
    v[i].y = read();
  }
  sort(v + 1, v + n + 1);
  build();
  n = top;
  reverse(stk + 1, stk + 1 + n);
  double ans = 4e8;
  double t = stk[1].slope(stk[2]);
  for (int i = 2; i < n; ++i) {    
    double l = stk[i - 1].slope(stk[i]);
    double r = stk[i].slope(stk[i + 1]);
    ans = min(ans, update(r, l, stk[i]));
  }
  t = stk[n].slope(stk[n - 1]);
  ans = min(ans, update(-2e18, t, stk[n]));
  printf("%.4f\n", ans);
  return 0;
}