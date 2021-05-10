#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>

using namespace std;

const int maxn = 10000;
int que[maxn + 5], h, r;
long long T[maxn + 5], C[maxn + 5];
int n, S;
long long f[maxn + 5];

int main() {
	scanf("%d%d", &n, &S);
	scanf("%lld%lld", &T[0], &C[0]);
	for (int i = 1, c, t; i < n; ++i) {
		scanf("%d%d", &t, &c);
		C[i] = C[i - 1] + c;
		T[i] = T[i - 1] + t;
	}
	f[0] = C[n - 1] * S + C[0] * T[0];
	que[r++] = 0;
	for (int i = 1; i < n; ++i) {
		f[i] = C[n - 1] * S + C[i] * T[i];
		while (r - h > 1) {
			double t = ((double)f[que[h + 1]] - f[que[h]]) / (C[que[h + 1]] - C[que[h]]);
			if (t <= S + T[i]) {
				h++;
			}
			else {
				break;
			}
		}
		f[i] = min(f[i], f[que[h]] + T[i] * (C[i] - C[que[h]]) + S * (C[n - 1] - C[que[h]]));
		while (r - h > 1) {
			double t1 = (((double)f[que[r - 1]] - f[que[r - 2]]) / (C[que[r - 1]] - C[que[r - 2]]));
			double t2 = (((double)f[i] - f[que[r - 1]]) / (C[i] - C[que[r - 1]]));
			if (t1 >= t2) {
				r--;
			}
			else {
				break;
			}
		}
		que[r++] = i;
	}
	printf("%lld\n", f[n - 1]);
	return 0;
}
