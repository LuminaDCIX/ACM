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

inline int read() {
	int f=1,x=0;
	char ch=getchar();
	while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}

VI v[10];
const int N=1e6+5;

int G[N];

int f(int x) {
	int prod=1;
	while (x)
		prod*=(x%10==0?1:x%10),x/=10;
	return prod;
}

int g(int x) {
	if (G[x]!=-1)
		return G[x];
	return G[x]=x<10?x:g(f(x));
}

int main() {
	SET(G,-1);
	REP (i,1,1e6+1)
		v[g(i)].PB(i);
	int q=read();
	while (q--) {
		int l=read(),r=read(),k=read();
		printf("%d\n",upper_bound(ALL(v[k]),r)-lower_bound(ALL(v[k]),l));
	}
	return 0;
}
