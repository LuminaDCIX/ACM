// luogu-judger-enable-o2
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

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

const int N = 50000 + 5;

int n;

struct line {
  int k;
  int b;
  int id;
  
  bool operator < (const line &rhs) const {
    return k == rhs.k ? b > rhs.b : k < rhs.k;
  }
};

line l[N];
line r[N];
line stk[N];

bool judge(line a, line b, line x) {
  double c = (double) (a.b - b.b) / (b.k - a.k);
  double y = c * a.k + a.b;
  double yx = c * x.k + x.b;
  return y <= yx;
}

int main() {
  n = read();
  for (int i = 0; i < n; ++i) {
    l[i].k = read();
    l[i].b = read();
    l[i].id = i;
  }
  sort(l, l + n);
  int top = 0;
  r[top++] = l[0];
  for (int i = 1; i < n; ++i) {
    if (l[i].k == l[i - 1].k) {
      continue;
    }
    r[top++] = l[i];
  }
  n = top;
  top = 0;
  stk[top++] = r[n - 1];
  for (int i = n - 2; i >= 0; --i) {
    while (top > 1 && judge(stk[top - 1], stk[top - 2], r[i])) {
      --top;
    }
    stk[top++] = r[i];
  }
  vector <int> v;
  for (int i = 0; i < top; ++i) {
    v.push_back(stk[i].id);
  }
  sort(v.begin(), v.end());
  for (int i = 0; i < v.size(); ++i) {
    printf("%d ", v[i] + 1);
  }
  return 0;
}
