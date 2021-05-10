#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
inline int read()
{
  int f=0,s=1,ch;
  for(ch=getchar();!isdigit(ch);(ch=='-')?s=-1:s=1,ch=getchar());
  for(;isdigit(ch);f=(f<<1)+(f<<3)+ch-'0',ch=getchar());
  return f*s;
}
typedef long long ll;
long long mind;
long long gcd(long long a, long long b)
{
  return !b ? a : gcd(b, a % b);
}
long long modsub(long long a, long long b, long long p)
{
  long long ans = 0;
  while (b) {
    if (b & 1) {
      ans = (ans + a) % p;
    }
    b >>= 1;
    a = (a + a) % p;
  }
  return ans;
}
long long modexp(long long a, long long x, long long p)
{
  long long ret = 1;
  a %= p;
  while (x) {
    if (x & 1) {
      ret = modsub(a, ret, p);
    }
    a = modsub(a, a, p);
    x >>= 1;
  }
  return ret;
}
bool check(long long a, long long n, long long r, long long s)
{
  long long x = modexp(a, r, n);
  long long p = x;
  for (int i = 1; i <= s; ++i) {
    x = modsub(x, x, n);
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
inline long long miller(long long n)
{
  if (n == 2) {
    return 1;
  }
  if (n <= 1 || (!(n & 1))) {
    return 0;
  }
  long long s = 0, r = n - 1;
  while (!(r & 1)) {
    r >>= 1;
    s++;
  }
  for (int i = 0; i < 10; ++i) {
    if (check(rand() % (n - 1) + 1, n, r, s)) {
      return 0;
    }
  }
  return 1;
}
inline long long rho(long long n)
{
  long long x = rand() % (n - 1) + 1;
  long long y = x, p = 1;
  long long k = 2;
  long long a = rand() % n;
  for (long long i = 1; p == 1; ++i) {
    x = (modsub(x, x, n) + a) % n;
    p = gcd((x - y + n) % n, n);
    if (i == k) {
      k <<= 1;
      y = x;
    }
  }
  return p;
}
void solve(long long x)
{ 
  if (x == 1) {
    return;
  }
  if (miller(x)) {
    mind = min(mind, x);
    return;
  }
  long long t = rho(x);
  solve(x / t);
  solve(t);
}
int main()
{
  srand(20010609);
  int T;
  scanf("%d", &T);
  while (T--) {
    long long x;
    scanf("%lld", &x);
    if (miller(x)) {
      puts("Prime");
    }
    else {
      mind = x;
      solve(x);
      printf("%lld\n", mind);
    }
  }
  return 0;
}
//300239975158033