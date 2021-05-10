#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

inline long long read() {
  long long x;
  scanf("%lld", &x);
  return x;
}

void exgcd(long long a, long long b, long long &x, long long &y) {
  if (!b) {
    x = 1;
    y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y -= (a / b) * x;
}

int main() {
  long long a = read();
  long long b = read();
  if (a > b) {
    swap(a, b);
  }
  long long x;
  long long y;
  exgcd(a, b, x, y);
  long long ans = 0;
  if (x < 0) {
    x += b;
    ans = (x - 1) * a + (y - 1) * b;
  } else {
    y += a;
    ans = (y - 1) * b + (x - 1) * a;
  }
  printf("%lld\n", ans - 1);
  return 0;
}
