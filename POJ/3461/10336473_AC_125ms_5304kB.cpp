#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1000005;
int T, n, m;
char A[maxn];
char B[maxn];
int nxt[maxn];
int cnt;

inline void Getnxt() {
	cnt = 0;
	int j = 0;
	memset(nxt, 0, sizeof(nxt));
	nxt[1] = 0;
	for (int i = 2; i <= n; ++i) {
		while (j > 0 && A[j + 1] != A[i]) {
			j = nxt[j];
		}
		if (A[j + 1] == A[i]) {
			++j;
		}
		nxt[i] = j;
	}
}

inline void solve() {
	int j = 0;
	for (int i = 1; i <= m; ++i) {
		while (j > 0 && A[j + 1] != B[i]) {
			j = nxt[j];
		}
		if (A[j + 1] == B[i]) {
			++j;
		}
		if (j == n) {
			++cnt;
			j = nxt[j];
		}
	}
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%s", A + 1);
		scanf("%s", B + 1);
		n = strlen(A + 1);
		m = strlen(B + 1);
		Getnxt();
		solve();
		printf("%d\n", cnt);
	}
	return 0;
}
