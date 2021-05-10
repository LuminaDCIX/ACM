#include <bits/stdc++.h>

using namespace std;    

long long n;
long long k;

int main() {
  scanf("%lld %lld", &n, &k);
  if (k == 1) {
    printf("%lld\n", n);
  } else {
    bool flg = 0;
    for (int i = 63; i >= 0; --i) {
      if (n & (1ll << i)) {
        if (!flg) {
          flg = 1;
        }
      } else if (flg) {
        n ^= 1ll << i;
      }
    }
    printf("%lld\n", n);
  }
  return 0;
}