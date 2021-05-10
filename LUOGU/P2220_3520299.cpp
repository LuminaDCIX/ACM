#include <set> 
#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

inline int read()
{
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

const long long mod = 1000000007;

inline long long modexp(long long a, int x)
{
    long long ret = 1;
    while (x) {
        if (x & 1) {
             ret = ret * a % mod;
        }    
        a = a * a % mod;
        x >>= 1;
    }
    return ret;
}

int n;
int m;
int k;

struct atom {
    int x;
    int y;

    bool operator < (const atom &rhs) const {
        return x == rhs.x ? y < rhs.y : x < rhs.x;
    }
    atom(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

set <atom> s;
map <int, long long> mp;

int main()
{
  n = read();
  m = read();
  k = read();
  long long t = (1ll + n) * n / 2;
  for (int i = 0, x, y; i < k; ++i) {
      x = read();
      y = read();
      if (s.find(atom(x, y)) != s.end()) {
          continue;
      }
      s.insert(atom(x, y));
      if (mp[x] == 0) {
          mp[x] = t;
      }
      long long k = mp[x];
      mp[x] = k - y;
      if (mp[x] == 0) {
          puts("0");
          return 0;
    }
  }
  map <int, long long>::iterator it = mp.begin();
  long long ans = 1;
  while (it != mp.end()) {
         ans = ans * ((*it).second % mod) % mod;
         ++it;    
  }
  ans = ans * modexp(t % mod, m - (int) mp.size()) % mod;
  if (ans < 0) {
      ans += mod;
  }
  printf("%lld\n", ans);
  return 0;
}