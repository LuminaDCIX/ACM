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

const int N=2e5+5;
const LL inf=1e18;

int n,m;

struct edge {
	int nxt,to;
	LL val;
};

int head[N];

edge e[N*3];

void add(int u,int v,LL w) {
	static int tot=0;
	e[tot].to=v,e[tot].nxt=head[u],e[tot].val=w,head[u]=tot++;
}



LL ans[N],a[N];
LL dist[N];
bool vis[N];

void dijkstra(int s) {
	priority_queue<pair<LL,int> > que;
	que.push(MP(0,s));
	fill(dist,dist+N,(LL)1e18);
	dist[s]=0;
	while (!que.empty()) {
		int u=que.top().second;
		que.pop();
		if (vis[u])
			continue;
		vis[u]=1;
		for (int o=head[u];~o;o=e[o].nxt) {
			int v=e[o].to;
			if (dist[v]>dist[u]+e[o].val) {
				dist[v]=dist[u]+e[o].val;
				que.push(MP(-dist[v],v));
			}
		}
	}
}
int main() {
	n=read(),m=read();
	SET(head,-1);
	REP (i,0,m) {
		int u=read(),v=read();
		LL w=read();
		add(u,v,2*w),add(v,u,2*w);
	}
	REP (i,1,n+1) {
		a[i]=read();
		add(n+1,i,a[i]);
	}
	dijkstra(n+1);
	REP (i,1,n+1)
		printf("%lld ",dist[i]);
	puts("");
	return 0;
}
