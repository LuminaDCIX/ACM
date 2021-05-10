#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
//_CRT_SECURE_NO_WARNINGS
//Product by MiracleEEEE

unsigned long long a, b, n, ans;
long long Fab[1000100];
int l, r;
typedef long long ll;
typedef unsigned long long ull;
struct dat {
	ll data;
	int pos;

	dat(ll a, int b) :data(a), pos(b){}
};
vector<dat> Hash[1010];

inline int read() {
	char ch = getchar(); int re = 0; while (ch<'0' || ch>'9') ch = getchar();
	while (ch >= '0'&& ch <= '9') { re = re * 10 + ch - '0'; ch = getchar(); } return re;
}
inline void write(int re) {
	if (re < 0) { putchar('-'); re = -re; }
	if (re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool input() {
	scanf("%llu %llu", &a, &b);
	scanf("%lld", &n);
	return true;
}

ll Modexp(ull a, ull b, ull c) {
	ull res = 1;
	a %= c;
	while (b) {
		if (b & 1) res = res * a % c;
		a = a * a % c;
		b /= 2;
	}
	return res % c;
}

int Judge(ll x1, ll x2, int p) {
	for (int i = 0; i < Hash[x1].size(); i++) {
		if (x2 == Hash[x1][i].data) return Hash[x1][i].pos;
	}
	Hash[x1].push_back(dat(x2, p));
	return -1;
}
bool solve() {
	if (n == 1) {
		printf("%d\n", 0);
		return true;
	}
	int Debug = 0;
	Fab[0] = 0, Fab[1] = 1, Fab[2] = 1;
	Hash[0].push_back(dat(1, 1));
	Hash[1].push_back(dat(1, 2));
	for (int i = 3; i <= n * n; i++) {
		Fab[i] = (Fab[i - 1] + Fab[i - 2]) % n;
		//printf("%lld %d\n", Fab[i], i);
		//int ok = Judge(Fab[i - 1], Fab[i], i);
		if (Fab[i] == 1 && Fab[i - 1] == 0) {r = i - 2; break;}
	}
	ll M = Modexp(a, b, r + 1);
	//printf("r = %d l = %d M = %lld ", l ,r, M);
	printf("%lld\n", Fab[M]);
	return true;
}
int main()
{
	int kase = 0;
	scanf("%d", &kase);
	while (kase--) {
		for (int i = 0; i <= 1000; i++) Hash[i].clear();
		input();
		solve();
	}
	return 0;
}