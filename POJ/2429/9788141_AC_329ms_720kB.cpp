#include<map>
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
vector<long long> t;
vector<long long> q;
vector<long long> h;
map<long long, long long> m;
long long x1, x2, a, b;
bool c[105];
long long gcd(long long a, long long b)
{
  return !b ? a : gcd(b, a % b);
}
long long modsub(long long a, long long b, long long p)
{
  long long ret = 0;
  while (b) {
    if (b & 1) {
      ret = (ret + a) % p;
    }
    a = (a + a) % p;
    b >>= 1;
  }
  return ret;
}
long long modexp(long long a, long long x, long long p)
{
  long long ret = 1;
  while (x) {
    if (x & 1) {
      ret = modsub(ret, a, p);
    }
    a = modsub(a, a, p);
    x >>= 1;
  }
  return ret;
}
long long fastexp(long long a, long long x)
{
  long long ret = 1;
  while (x) {
    if (x & 1) {
      ret = ret * a;
    }
    a = a * a;
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
bool miller(long long x)
{
  if (x == 2) {
    return 1;
  }
  if (x <= 1 || (!(x & 1))) {
    return 0;
  }
  long long r = x - 1, s = 0;
  while (!(r & 1)) {
    r >>= 1;
    s++;  
  }
  for (int i = 1; i <= 10; ++i) {
    if (check(rand() % (x - 1) + 1, x, r, s)) {
      return 0;
    }
  }
  return 1;
}
long long rho(long long n)
{
  long long x = rand() % (n - 1) + 1;
  long long y = x, p = 1;
  long long k = 2, a = rand() % n + 1;
  for (int i = 1; p == 1; ++i) {
    x = (modsub(x, x, n) + a) % n;
    p = gcd((y - x + n) % n, n);
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
    t.push_back(x);
    return;
  }
  long long t = rho(x);
  solve(x / t);
  solve(t);
}
void dfs(int p)
{
  if (p == h.size()) {
    long long t1 = a, t2 = a;
    for (int i = 0; i < h.size(); ++i) {
      if (c[i] == 0) {
        t1 *= h[i];
      }
      else{
        t2 *= h[i];
      }
    }
    if (t1 + t2 < x1 + x2) {
      x1 = min(t1, t2);
      x2 = max(t1, t2);
    }
    return;
  }
  c[p] = 1;
  dfs(p + 1);
  c[p] = 0;
  dfs(p + 1);
}
int main()
{
  while (~scanf("%lld%lld", &a, &b)) {
    x1 = x2 = b;
    solve(b);
    for (int i = 0; i < t.size(); ++i) {
      m[t[i]]++;
      q.push_back(t[i]);
    }
    sort(q.begin(), q.end());
    t.clear();
    solve(a);
    for (int i = 0; i < t.size(); ++i) {
      m[t[i]]--;
    }
    t.clear();
    for (int i = 0; i < q.size(); ++i) {
      if ((i == 0 || i > 0 && q[i] != q[i - 1]) && m[q[i]] != 0) {
        h.push_back(fastexp(q[i], m[q[i]]));
      }
    }
    q.clear();
    m.clear();
    dfs(0);
    h.clear();
    printf("%lld %lld\n", x1, x2);
  }
  return 0;
}