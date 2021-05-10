#include <bits/stdc++.h>

using namespace std;

inline int read()
{
  int f=0,s=1,ch;
  for(ch=getchar();!isdigit(ch);(ch=='-')?s=-1:s=1,ch=getchar());
  for(;isdigit(ch);f=(f<<1)+(f<<3)+ch-'0',ch=getchar());
  return f*s;
}

const int maxn = 100000;
long long f[maxn + 5][19][2];
int g[maxn + 5][19];
int n, m;
int to[maxn + 5][2];
struct node {
	node *nxt,*pre;
	long long h;
	int id;
};
struct city {
	int h,id;
};
city c[maxn + 5];
node *ptr[maxn + 5], t[maxn + 5];
int h[maxn + 5];
bool cmp(city a, city b) {
	return a.h < b.h;
}
inline void init() {
	long long lft, rgt;
	for (int i = 1; i <= n - 2; ++i) {
		lft = ptr[i]->h - ptr[i]->pre->h;
		rgt = ptr[i]->nxt->h - ptr[i]->h;
		if (lft <= rgt) {
			to[i][0] = ptr[i]->pre->id;
			if (ptr[i]->h - ptr[i]->pre->pre->h <= rgt) {
				to[i][1] = ptr[i]->pre->pre->id;
			}
			else {
				to[i][1] = ptr[i]->nxt->id;
			}
		}
		else {
			to[i][0] = ptr[i]->nxt->id;
			if (lft <= ptr[i]->nxt->nxt->h - ptr[i]->h) {
				to[i][1] = ptr[i]->pre->id;
			}
			else {
				to[i][1]=ptr[i]->nxt->nxt->id;
			}
		}
		ptr[i]->nxt->pre = ptr[i]->pre;
		ptr[i]->pre->nxt = ptr[i]->nxt;
	}
	lft = ptr[n - 1]->h - ptr[n - 1]->pre->h;
	rgt = ptr[n - 1]->nxt->h - ptr[n - 1]->h;
	if (lft <= rgt) {
		to[n - 1][0] = ptr[n - 1]->pre->id;
	}
	else {
		to[n - 1][0] = ptr[n - 1]->nxt->id;
	}
}
inline void init2() {
	memset(g, -1, sizeof(g));
	for (int i = 1; i <= n - 2; ++i) {
		if (to[i][1] == 0) {
			continue;
		}
		g[i][0] = to[i][1];
		f[i][0][0] = abs(ptr[to[i][1]]->h - ptr[i]->h);
		f[i][0][1] = 0;
	}
	for (int i = 1; i <= n - 1; ++i) {
		if (g[i][0] == -1 || to[g[i][0]][0] == 0) {
			continue;
		}
		g[i][1] = to[g[i][0]][0];
	  f[i][1][1] = abs(ptr[g[i][0]]->h - ptr[to[g[i][0]][0]]->h);
		f[i][1][0] = f[i][0][0];
	}
	for (int k = 2; k <= 18; ++k) {
		for (int i = 1; i <= n; ++i) {
			if (g[i][k - 1] == -1 || g[g[i][k - 1]][k - 1] == -1) {
				continue;
			}
			f[i][k][0] = f[i][k - 1][0] + f[g[i][k - 1]][k - 1][0];
			f[i][k][1] = f[i][k - 1][1] + f[g[i][k - 1]][k - 1][1];
			g[i][k] = g[g[i][k - 1]][k - 1];
		}
	}	
}
inline void query(int x, long long &a, long long &b,long long mx) {
	for (int i = 18; i >= 0; --i) {
		if (g[x][i] == -1 || (a + b + f[x][i][0] + f[x][i][1] > mx)) {
			continue;
		}
		a += f[x][i][0];
		b += f[x][i][1];
		x = g[x][i];
	}
}
int main() {
	n = read();
	for (int i = 1; i <= n; ++i) {
		c[i].h = read();
		c[i].id = i;
	}
	sort(c + 1, c + 1 + n, cmp);
	t[0].h = -2e10 - 7;
	t[n + 1].h = 2e10 + 7;
	t[0].nxt = &t[1];
	t[0].pre = &t[0];
	t[n + 1].pre = &t[n];
	t[n + 1].nxt = &t[n + 1];
	for (int i = 1; i <= n; ++i) {
		ptr[c[i].id] = &t[i];
		t[i].id = c[i].id;
		t[i].nxt = &t[i + 1];
		t[i].pre = &t[i - 1];
		t[i].h = c[i].h;
	}
	init();
	init2();
	long long x0 = read(), a = 0, b = 0;
	double ans = 2e9, now;
	int k = 0, h = 0;
	for (int i = 1; i <= n; ++i) {
		a = b = 0;
		query(i, a, b, x0);
		if (b == 0) {
			now = 2e9;
		}
		else {
			now = (double) a / b;
		}
		if (now < ans) {
			k = i;
			ans = now;
			h = ptr[i]->h;
		}
		if (now == ans && ptr[i]->h > h) {
			h = ptr[i]->h;
			k = i;
		}
	}
	printf("%d\n", k);
	m = read();
	for (int i = 1; i <= m; ++i) {
		scanf("%d%lld\n", &k, &x0);
		a = b = 0;
		query(k, a, b, x0);
		printf("%lld %lld\n", a, b);
	}
	return 0;
}
