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

const int N=400000+5;
const int LOG=19;

LL sum[N][LOG];
int fa[N][LOG],mx[N][LOG],to[N][LOG];

int lst,val[N];

int jump(int x,int w) {
	REP (i,0,LOG)
		if (mx[x][i]>=w) {
			if (i==0)
				return fa[x][0];
			else
				return jump(fa[x][i-1],w);
		}
	return 0;
}

void add(int u,int v,int w) {
	int x=v;val[v]=w;
	fa[x][0]=u;
	mx[x][0]=val[u];
	REP (i,1,LOG) 
		fa[x][i]=fa[fa[x][i-1]][i-1];
	REP (i,1,LOG)
		mx[x][i]=max(mx[x][i-1],mx[fa[x][i-1]][i-1]);
	int k=jump(x,w);
	sum[x][0]=val[k],to[x][0]=k;
	REP (i,1,LOG)
		to[x][i]=to[to[x][i-1]][i-1];
	REP (i,1,LOG)
		sum[x][i]=sum[x][i-1]+sum[to[x][i-1]][i-1];
}

int jump2(int x,LL s) {
	PER (i,0,LOG) {
		if (to[x][i]!=0) {
			if (sum[x][i]>s)
				continue;
			return jump2(to[x][i],s-sum[x][i])+(1<<i);
		}
	}
	return 0;
}

void query(int x,LL s) {
	int tot=0;
	s-=val[x];
	if (s<0) {
		printf("%d\n",tot);
		lst=tot;
		return;
	}
	++tot;
	tot+=jump2(x,s);
	printf("%d\n",tot);
	lst=tot;
}

int main() {
	int n=read();
	int cnt=1;
	while (n--) {
		int op=read();
		if (op==1) {
			int r=read()^lst,w=read()^lst;
			add(r,++cnt,w);
		} else {
			int r=read()^lst;LL w=read()^lst;
			query(r,w);
		}
	}
	return 0;
}
