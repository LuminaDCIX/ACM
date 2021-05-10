#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int maxn = 1000000;
int N;
int cnt[maxn + 5];
int res[maxn + 5];
int a[maxn + 5];
void solve() {
	int x, mx;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &a[i]);
		cnt[a[i]]++;
		mx = max(mx, a[i]);
	}
	for (int i = 1; i <= mx; i++) {
		if (cnt[i]) {
			for (int j = i; j <= mx; j += i)
				res[j] += cnt[i];
		}
	}
	for (int i = 1; i <= N; i++)
		printf("%d\n", res[a[i]] - 1);
}
int main() {
	scanf("%d", &N);
	solve();
	return 0;
}

