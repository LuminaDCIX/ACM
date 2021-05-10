#include <cstdio>
#include <iostream>
#include <cstdlib>
using namespace std;
typedef long long ll;
int N, K;
ll ans;
int main() {
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++) {
		int x;
		scanf("%d", &x);
		int foo = x / K;
		ans += foo;
		if (x % K) ans++;
	}
	printf("%I64d\n", (ans + 1) / 2);
	return 0;
}