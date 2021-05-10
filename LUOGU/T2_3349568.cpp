#include <cstdio>

using namespace std;
typedef long long ll;

inline ll read() 
{
  int f = 1;
  ll x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    f = (ch == '-') ? -1 : 1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}

int main()
{
  ll s, a, o;
  while (scanf("%lld", &a) != EOF) {
    o = read();
    s = read();
    printf("%lld %lld %lld\n", a, s - a - o, o);
  }
  return 0;
}
