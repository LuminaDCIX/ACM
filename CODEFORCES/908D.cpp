#include <bits/stdc++.h>

using namespace std;

const int K = 1000 + 5;
const long long p = 1e9 + 7;

int k;
int pa;
int pb;

long long A;
long long B;
long long F;

void exgcd(long long a, long long b, long long &x, long long &y) {
  if (!b) {
    x = 1;
    y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y -= (a / b) * x;
}

long long inv(long long a) {
  long long x;
  long long y;
  exgcd(a, p, x, y);
  return (x % p + p) % p;
}

long long f[K][K];

long long calc(long long i, long long j) {
  if (j >= k) {
    return j;
  }
  if (i == k) {
    return (k + j + F) % p;
  }
  long long &ans = f[i][j];
  if (ans != -1) {
    return ans;
  }
  ans = A * calc(i + 1, j) + B * calc(i, j + i);
  ans %= p;
  return ans;
}

int main() {
  scanf("%d %d %d", &k, &pa, &pb);
  A = (long long) pa * inv(pa + pb) % p;
  B = (long long) pb * inv(pa + pb) % p;
  F = (long long) (pa) * inv(pb) % p;
  memset(f, -1, sizeof(f));
  printf("%lld\n", calc(1, 0));
  return 0;
}
