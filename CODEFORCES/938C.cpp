#include <bits/stdc++.h>

using namespace std;

#define MP make_pair
#define PB push_back
#define FI first
#define SE second
#define SIZ(x) ((int)x.size())
#define SET(x,k) memset(x,k,sizeof(x))
#define ALL(x) x.begin(),x.end()
#define REP(i,a,n) for (int i=(a);i<(n);++i)
#define PER(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define FORG(o,u) for (edge* o=head[u];o;o=o->nxt)

typedef long long LL;
typedef long double DB;
typedef vector<int> VI;
typedef pair<int,int> PII;

inline LL read() {
	LL f=1,x=0;
	char ch=getchar();
	while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}

int n;

void solve() {
	if (n==0) {
		puts("1 1");
		return;
	}
	for (int i=1;i*i<=n;++i) {
		if (n%i==0) {
			int a=i,b=n/i;
			if ((a+b)&1)
				continue;
			int k=(a+b)/2;
			if (b-k==0)
				continue;
			int m=k/(b-k);
			if ((LL)k*k-(LL)(k/m)*(k/m)==n) {
				printf("%d %d\n",k,m);
				return;
			}
		}
	}
	puts("-1");
	return;
}

int main() {
	int t=read();
	while (t--) {
		n=read();
		solve();
	}
	return 0;
}
