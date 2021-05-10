#include <cstdio>

using namespace std;

const int N = 1000000 + 5;
const int P = 1e9 + 7;

int n;
int m;

int fac[N];
int inv[N];

int C(int n, int m) {
	return (long long) fac[n] * inv[m] % P * inv[n - m] % P;
}

int modexp(int a, int x, int p) {
	int ret = 1;
	while (x) {
		if (x & 1) {
			ret = (long long) ret * a % p;
		}
		a = (long long) a * a % p;
		x = x >> 1;
	}
	return ret;
}

int main() {
  scanf("%d %d", &n, &m);
  if (m > n) {
  	printf("%d\n", 0);
  	return 0;
  }
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
  	fac[i] = (long long) fac[i - 1] * i % P;
  }
  inv[n] = modexp(fac[n], P - 2, P);
  for (int i = n - 1; i >= 0; --i) {
  	inv[i] = (long long) inv[i + 1] * (i + 1) % P;
  }
  int ans = 0;
  int o = 1;
  for (int i = 0; i <= m; ++i) {
  	ans += 	(long long) o * C(m, i) * modexp(m - i, n, P) % P;
  	ans %= P;
  	o *= -1;
	}
	if (ans < 0) {
		ans += P;
	}
	printf("%d\n", ans);
 	return 0;
}