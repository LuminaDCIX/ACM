#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
//_CRT_SECURE_NO_WARNINGS
//Product by MiracleEEEE 
#define lson (o << 1)
#define rson (o << 1 | 1)
#define M (l + ((r - l) >> 1))
const int Max = 100000;
int kase, n, H, res;
int maxt[(Max << 2) + 1], lazy[(Max << 2) + 1], setv[(Max << 2) + 1];
inline int read() {
	char ch = getchar(); int re = 0; while (ch<'0' || ch>'9') ch = getchar();
	while (ch >= '0'&& ch <= '9') { re = re * 10 + ch - '0'; ch = getchar(); } return re;
}
inline void write(int re) {
	if (re < 0) { putchar('-'); re = -re; }
	if (re > 9) write(re / 10); putchar(re % 10 + '0');
}
void pushdown(int o,int l, int r,int L, int R) {
	if (maxt[o] <= lazy[o]) {
		maxt[o] = max(maxt[o], lazy[o]); 
		if (l == L && r == R) setv[o] = 1; else setv[o] = 0;
	}
	if (l != r) {
		lazy[lson] = max(lazy[lson], lazy[o]);
		lazy[rson] = max(lazy[rson], lazy[o]);
	}
}
void query(int o, int l, int r, int L, int R,int ok) {
	//printf("%d %d %d %d lazy = %d\n", l, r, L, R, lazy[o]);
	pushdown(o, l, r, L, R);
	if (L == l && R == r) {
		if (maxt[o] <= H) {
			maxt[o] = H;
			lazy[o] = H;
			setv[o] = 1;
		}
		if (setv[o] && H >= maxt[o]) res += (r - l + 1);
		//printf("max  = %d %d\n",maxt[o], res);
	}{
		//printf("setv = %d\n", setv[o]);
		if (setv[o] || l == r) return;pushdown(o, l, r, L, R);
		if (R <= M) query(lson, l, M, max(L, l), R, ok); else if(L <= M)query(lson, l, M, max(l, L), M, ok);
		if (L > M) query(rson, M + 1, r, L, min(r, R), ok); else if(R > M) query(rson, M + 1, r, M + 1, min(r, R), ok);
		maxt[o] = max(maxt[lson], maxt[rson]);
		if (setv[o] == 1) setv[o >> 1] = -1;
	}
	//printf("%d %d %d\n", l, r, setv[o]);
}
bool solve() {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int L , R; res = 0;
		scanf("%d %d %d", &L, &R, &H);
		query(1, 1, 100001, L, R - 1, 0); //printf("%d\n", res);
		ans += res;
	}
	printf("%d\n", ans);
	return true;
}
int main()
{
#ifdef LOCAL
	freopen("TEXT.txt", "r", stdin);
	freopen("OUTPUT.txt", "w", stdout);
#endif
	while(scanf("%d", &kase) != EOF && kase)
	while (kase --) {
		memset(maxt, 0, sizeof(maxt));
		memset(lazy, 0, sizeof(lazy));
		memset(setv, 0, sizeof(setv));
		scanf("%d", &n);
		solve();
	}
	
	return 0;
}
