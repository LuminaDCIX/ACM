#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 1000 + 5;
int T;
int n;
int x[N];

int main()
{
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &x[i]);
		}
		sort(x + 1, x + 1 + n);
		for (int i = n; i >= 1; --i) {
			x[i] = x[i] - x[i - 1] - 1;
		}
		int v = 0;
		for (int i = n; i >= 1; i -= 2) {
			v ^= x[i];
		}
		puts(v != 0 ? "Georgia will win" : "Bob will win");
	}
	return 0;
}
