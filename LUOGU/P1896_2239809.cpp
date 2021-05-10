#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int n, k;
long long f[11][95][(1 << 9) + 5];
vector<int> s;

inline int num(int x) {
  int cnt = 0;
  while (x) {
    x -= x & -x;
    cnt++;
  }
  return cnt;
}

bool fit(int a, int b)
{
  return !(((a<<1)&b||(a>>1)&b)||(a&b));
}

int main()
{
  scanf("%d%d", &n, &k);
  for (int i = 0; i < 1 << n; ++i) {
    if (!(i&i<<1)) {
      s.push_back(i);
    }
  }
  for (int i = 0; i < s.size();++i) {
    f[1][num(s[i])][s[i]] = 1;
  }
  for (int i = 2; i <= n;++i) {
    for (int c = 0; c <= k;++c) {
      for (int j = 0; j < s.size();++j) {
        if (f[i-1][c][s[j]]==0) {
          continue;
        }
        for (int l = 0;l<s.size();++l) {
          if (fit(s[j],s[l])) {
            f[i][c + num(s[l])][s[l]] += f[i - 1][c][s[j]];
          }
        }
      }
    }
  }
  long long ans = 0;
  for (int i = 0; i < s.size();++i) {
    ans += f[n][k][s[i]];
  }
  printf("%lld\n", ans);
  return 0;
}