#include <bits/stdc++.h>

using namespace std;

int n;
int len;
set<string> s;
string str;
string bar;

inline int init()
{
	int i = 0;
	int j = 1;
	int k = 0;
	len = str.length();
	while (i < len && j < len && k < len) {
		int t = str[(i + k) % len] - str[(j + k) % len];
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

int main()
{
	ios::sync_with_stdio(false);
	while (cin >> n) {
		s.clear();
		for (int i = 0; i < n; ++i) {
			cin >> str;
			int k = init();
			bar.clear();
			for (int j = 0; j < len; ++j) {
				bar = bar + str[(j + k) % len];
			}
			s.insert(bar);
		}
		printf("%d\n", s.size());
	}
	return 0;
}
