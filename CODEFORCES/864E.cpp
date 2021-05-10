#include <bits/stdc++.h>

using namespace std;

const int N = 100 + 5;

struct node {
  int t;
  int d;
  int p;
  int id;
} e[N];

bool cmp(node a, node b) {
  return a.d < b.d;
}

int n;

int f[2005][105];

int pre[2005][105];

vector <int> c;

inline void print(int i, int j)
{
  if (j == 0) {
    return;
  }
  c.push_back(j);
  print(i - e[j].t, pre[i][j]);
}

int main()
{
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d %d\n", &e[i].t, &e[i].d, &e[i].p);
    e[i].id = i;
  }
  sort(e + 1, e + n + 1, cmp);
  int ans = 0;
  int id = 0;
  int tim = 0;
  for (int i = 0; i <= 2000; ++i) {
    for (int j = 0; j <= n; ++j) {
      if (f[i][j] > ans) {
	ans = f[i][j];
	tim = i;
	id = j;
      }
      for (int k = j + 1; k <= n; ++k) {
	if (i + e[k].t < e[k].d) {
	  if (f[i + e[k].t][k] <  f[i][j] + e[k].p) {
	    f[i + e[k].t][k] =  f[i][j] + e[k].p;
	    pre[i + e[k].t][k] = j;
	  }
	}
      }
    }
  }
  printf("%d\n", ans);
  print(tim, id);
  reverse(c.begin(), c.end());
  printf("%d\n", c.size());
  for (int i = 0; i < c.size(); ++i) {
    printf("%d ", e[c[i]].id);
  }
  puts("");
  return 0;
}
