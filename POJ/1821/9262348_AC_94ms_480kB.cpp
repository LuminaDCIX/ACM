#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxk = 100;
const int maxn = 16000;
int n, k;
int a[maxn + 5], b[maxn + 5], h, t;
int f[maxn + 5];

struct worker
{
  int b, e, p, l, s;
} w[maxk + 5];

bool cmp(worker a, worker b)
{
  return a.s < b.s;
}

int main()
{
  scanf("%d%d", &n, &k);
  int l, p, s;
  int ans = 0;
  for (int i = 1; i <= k;++i) {
    scanf("%d%d%d", &l, &p, &s);
    int b = max(1, s - l + 1)-1;
    int e = min(n, s + l - 1);
    w[i] = (worker){ b, e, p, l,s};
  }
  sort(w + 1, w + 1 + k, cmp);
  for (int i = 1; i <= k;++i) {
    h = t = 0;
    for (int j = w[i].b; j < w[i].s; ++j) {
      int x = j;
      int y = f[j] - j * w[i].p;
      while (h < t && y >= b[t - 1]) {
        t--;
      }
      a[t] = j;
      b[t++] = y;
    }
    for (int j = w[i].s; j <= w[i].e&&h<t; ++j) {
      while (h < t && j - a[h] > w[i].l) {
        h++;
      }
      f[j] = max(f[j],b[h] + j * w[i].p);
      //printf("f[%d]=%d\n", j, f[j]);
    }
    for (int j = 1; j <= n;++j) {
      f[j] = max(f[j], f[j - 1]);
    }
  }
  printf("%d\n",f[n]);
  return 0;
}
