#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn = 10000000;
int inv[maxn+5], prime[5000000+5];
ll fun[maxn+5], phi[maxn+5];
bool not_prime[maxn+5];
int M, N, T, tot;
ll mod;

int read() {
	char ch = getchar(); int res = 0;
	while (ch<'0'||ch>'9') ch = getchar();
	while (ch>='0'&&ch<='9') res = res*10+ch-'0', ch = getchar();
	return res;
}
void extgcd(int a, int b, int &x, int &y) {
	if (b==0) {x = 1, y = 0; return;}
	extgcd(b, a%b, x, y);
	int t = x;
	x = y; y = t-a/b*x;
}

int getinv(int i) {
	int x, y;
	extgcd(i, mod, x, y);
	return (x%mod+mod)%mod;
}
void Euler() {
	inv[1] = 1;
	for (int i = 2; i <= maxn; ++i) {
		if (!not_prime[i]) {
			prime[++tot] = i;
			inv[i] = getinv(i);
		}
		for (int j = 1; (prime[j]*i <= maxn) && j <= tot; ++j) {
			not_prime[prime[j]*i] = true;
			if (!(i%prime[j])) break;
		}
	}
	phi[1] = 1;
	for (int i = 2; i <= maxn; i++) {
		phi[i] = phi[i-1];
		if (!not_prime[i]) phi[i] = phi[i]*(i-1)%mod*inv[i]%mod;
	}
	return;
}
void solve() {
	int T;
	T = read();
	scanf("%lld", &mod);
	Euler();
	fun[0] = 1;
	for (int i = 1; i <= maxn; ++i) fun[i] = fun[i-1]*i%mod;
	while (T--) {
		N = read(), M = read();
		printf("%lld\n", fun[N]*phi[M]%mod);
	}
	return;
}
int main() {
	solve();
	return 0;
}
