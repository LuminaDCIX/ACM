#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

const int K = 100 + 5;
const int N = 100 + 5;
const int S = 10000;
bool vis[K];
int sg[S + 5];
int n, k, T;
int s[K];
int x[N];
inline void init()
{
	for (int i = 0; i <= S; ++i) {
		memset(vis, 0, sizeof(vis));
		for (int j = 0; j < k; ++j) {
			int to = i - s[j];
			if (to < 0) {
				continue;
			}
			vis[sg[to]] = 1;
		}
		for (int j = 0; j <= 100; ++j) {
			if (!vis[j]) {
				sg[i] = j;
				break;
			}
		}
	}
	return;
}
int main()
{
	while (scanf("%d", &k) && k) {
		for (int i = 0; i < k; ++i) {
			scanf("%d", &s[i]);
		}
		init();
		scanf("%d", &T);
		while (T--) {
			scanf("%d", &n);
			int v = 0;
			for (int i = 0, x; i < n; ++i) {
				scanf("%d", &x);
				v ^= sg[x];
			}
			putchar(v == 0 ? 'L' : 'W');
		}
		puts("");
	}
	return 0;
}
