#include <bits/stdc++.h>

using namespace std;

const int N = 200000 + 5;

int n;
int a[N];
int cnt[N];
int nxt[N];
int lst[N];
int num;
int rem;
bool ok[N];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    ++cnt[a[i]];
    nxt[lst[a[i]]] = i;
    lst[a[i]] = i;
  }
  for (int i = 1; i <= n; ++i) {
    if (!cnt[i]) {
      ++num;
    } else if (cnt[i] != 1) {
      rem += cnt[i] - 1;
    }
  }
  int now = 1;
  while (cnt[now]) {
    ++now;
  }
  int tim = 0;
  for (int i = 0; i < n; ++i) {
    if (cnt[a[i]] > 1 && ok[a[i]]) {
      --rem;
    }
    if (cnt[a[i]] > 1) {
      if (a[i] > now) {
	if (cnt[a[i]] > 1) {
	  --rem;
	}
	--cnt[a[i]];
	a[i] = now;
	++cnt[now];
	++tim;
	--num;
      } else {
	if (rem + 1 == num) {
	  --cnt[a[i]];
	  a[i] = now;
	  ++cnt[now];
	  ++tim;
	  --num;
	} else {
	  ok[a[i]] = 1;
	}
      }
    }
    while (cnt[now]) {
      ++now;
    }
  }
  printf("%d\n", tim);
  for (int i = 0; i < n; ++i) {
    printf("%d ", a[i]);
  }
  puts("");
  return 0;
}
