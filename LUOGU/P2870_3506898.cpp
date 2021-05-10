#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 30000 + 5;
//const int mod = 19961993;
const int mod = 1e9 + 7;

char str[N];
char rstr[N];

int n;

int a[N];
int b[N];

int fac[N];

inline int hsh1(int l, int r) {
  return ((a[r] - 1ll * a[l - 1] * fac[r - l + 1]) % mod + mod) % mod;
}

inline int hsh2(int l, int r) {
  return ((b[r] - 1ll * b[l - 1] * fac[r - l + 1]) % mod + mod) % mod;
}

inline int lowerbd(int l, int r)
{
  int low = 0;
  int high = (r - l + 1) / 2;
  int ret = 0;
  int mid = 0;
  while (low <= high) {
    mid = low + high >> 1;
    if (hsh1(l, l + mid - 1) == hsh2(n - r - 1, n - r + mid - 2)) {
      ret = mid;
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return ret; 
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("\n");
    scanf("%c", &str[i]);
    rstr[i] = str[i];
  }
  reverse(rstr, rstr + n);
  for (int i = 0; i < n; ++i) {
    a[i] = (1ll * a[i - 1] * 26 + str[i] - 'A' + 1) % mod;
    b[i] = (1ll * b[i - 1] * 26 + rstr[i] - 'A' + 1) % mod;
  }
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = 1ll * fac[i - 1] * 26 % mod;
  }
  int cnt = 0;
  int l = 0;
  int r = n - 1;
  for (int i = 0, len; i < n; ++i) {
    len = lowerbd(l, r);
    if (str[l + len] <= str[r - len]) {
      putchar(str[l]);
      ++l;
    } else {
      putchar(str[r]);
      --r;
    }
    ++cnt;
    if (cnt == 80) {
      puts("");
      cnt = 0;
    }
  }
  return 0;
  
}
