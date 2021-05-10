#include <cmath>
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


int modexp(int a, int x, int p) {
  int ret = 1;
  while (x) {
    if (x & 1) {
      ret = 1ll * ret * a % p;
    }
    a = 1ll * a * a % p;
    x >>= 1;
  }
  return ret;
}

bool check(int a, int n, int r, int s) {
  int x = modexp(a, r, n);
  int p = x;
  for (int i = 1; i <= s; ++i) {
    x = 1ll * x * x % n;
    if (x == 1 && p != 1 && p != n - 1) {
      return 1;
    }
    p = x;
  }
  if (x != 1) {
    return 1;
  }
  return 0;
}

bool miller(int x) {
  if (x == 2) {
    return 1;
  }
  if (x <= 1 || (!(x & 1))) {
    return 0;
  }
  int r = x - 1;
  int s = 0;
  while (!(r & 1)) {
    r >>= 1;
    s++;  
  }
  for (int i = 1; i <= 3; ++i) {
    if (check(rand() % (x - 1) + 1, x, r, s)) {
      return 0;
    }
  }
  return 1;
}


int main() {
  int n = read();
  int q = read();
  srand(20010609);
  for (int i = 0; i < q; ++i) {
    int v = read();
    if (!miller(v)) {
      putchar('N');
      putchar('o');
      putchar('\n');
    } else {
      putchar('Y');
      putchar('e');
      putchar('s');
      putchar('\n');
    }
  }
  return 0;
}
