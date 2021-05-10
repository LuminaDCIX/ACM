#include <bits/stdc++.h>

using namespace std;

const int N = 200 + 5;

int cnt[205];

char a[N];

int n;

inline int solve(int l, int r)
{
  memset(cnt, 0, sizeof(cnt));
  int ret = 0;
  for (int i = l; i <= r; ++i) {
    if (!cnt[a[i]]) {
      ++cnt[a[i]];
      ++ret;
    }
  }
  return ret;
}

int main()
{
  scanf("%d", &n);
  scanf("%s", a);
  int ans = 0;
  bool flg = 1;
  for (int i = 0; i < n; ++i) {
    if (a[i] >= 'A' && a[i] <= 'Z') {
      ans = max(ans, solve(0, i - 1));
      flg = 0;
      break;
    }
  }
  if (flg) {
    ans = max(ans, solve(0, n - 1));
  }
  for (int i = 0; i < n; ++i) {
    if (a[i] >= 'A' && a[i] <= 'Z') {
      int l = i + 1;
      int r = n - 1;
      for (int j = i + 1; j < n; ++j) {
	if (a[j] >= 'A' && a[j] <= 'Z') {
	  r = j - 1;
	  break;
	}
      }
      ans = max(ans, solve(l, r));
    }
  }
  printf("%d\n", ans);
  return 0;
}
