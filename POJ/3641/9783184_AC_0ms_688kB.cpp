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
long long a, p;
long long modexp(long long a, long long x, long long p)
{
  a %= p;
  long long ans = 1;
  while (x) {
    if (x & 1) {
      ans = (ans * a) % p;
    }
    a = (a * a) % p;
    x >>= 1;
  }
  return ans;
}

inline bool check(long long a, long long n, long long r, long long s)
{
  long long x = modexp(a, r, n);
  long long p = x;
  for (int i = 1; i <= s; ++i) {
    x = (x * x) % n;
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

inline bool miller(long long x)
{
  if (x <= 1 || !(x & 1)) {
    return 0;
  }
  if (x == 2) {
    return 1;
  }
  int s = 0;
  long long r = x - 1;
  while (!(r & 1)) {
    r >>= 1;
    s++;
  }
  for (int i = 0; i < 10; ++i) {
    if (check(rand() % (x - 1) + 1, x, r, s)) {
      return 0;
    }
  }
  return 1;
}
int main()
{
  srand(20010609);
  while (scanf("%lld%lld", &p, &a) && a + p) {
    if (!miller(p) && modexp(a, p, p) == a) {
      puts("yes");
    }
    else {
      puts("no");
    }
  }
  return 0;
}