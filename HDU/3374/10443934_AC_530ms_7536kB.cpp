#include <bits/stdc++.h>

using namespace std;

const int N = 1000000 + 5;
char s[N];
char t[N];
int nxt[N];
int n;

inline int init(int a, int b) 
{
	int i = 0;
	int j = 1;
	int k = 0;
	while (i < n && j < n && k < n) {
		int t = a * s[(i + k) % n] + b * s[(j + k) % n];
		if (t == 0) {
			++k;
		}
		else {
			if (t > 0) {
				i += k + 1;
			}
			else {
				j += k + 1;
			}
			k = 0;
		}
		if (i == j) {
			++j;
		}
	} 
	return min(i, j);
}
inline void kmp() 
{
	int j = -1;
	memset(nxt, 0, sizeof(nxt));
	nxt[0] = -1;
	for (int i = 1; i < n; ++i) {
		while (j != -1 && t[j + 1] != t[i]) {
			j = nxt[j];
		}
		if (t[j + 1] == t[i]) {
			++j;
		}
		nxt[i] = j;
	}
}
int main() 
{
	while (scanf("%s", s) != EOF) {
		n = strlen(s);
		int k = init(1, -1);
		printf("%d ", k + 1);
		for (int i = 0; i < n; ++i) {
			t[i] = s[(i + k) % n];
		}
		kmp();
		int cur = n - nxt[n - 1] - 1;
		printf("%d ", n / cur);
		k = init(-1, 1);
		printf("%d ", k + 1);
		for (int i = 0; i < n; ++i) {
			t[i] = s[(i + k) % n];
		}
		kmp();
		cur = n - nxt[n - 1] - 1;
		printf("%d\n", n / cur);
	}
	return 0;
}
