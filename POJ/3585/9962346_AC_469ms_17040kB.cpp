#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
using namespace std;
const int maxn=200000;
int f[maxn+5],n;
int g[maxn+5];
int head[maxn+5],tot;
int ans;
struct edge {
	int nxt,to,cap;
}edges[2*maxn+5];
inline void add_edge(int from,int to,int cap) {
	edges[tot].to=to,edges[tot].cap=cap,edges[tot].nxt=head[from],head[from]=tot++;
}
void dfs1(int x,int fa) {
	int child=0;
	for (int i=head[x],v;~i;i=edges[i].nxt) {
		v=edges[i].to;
		if (v!=fa) dfs1(v,x),child++,f[x]+=min(f[v],edges[i].cap);
	}
	if (!child) f[x]=1e9;
}
void dfs2(int x,int fa) {
	int child=0;
	for (int i=head[x],v;~i;i=edges[i].nxt) {
		v=edges[i].to;
		if (v!=fa) g[v]=f[v]+min(g[x]-min(f[v],edges[i].cap),edges[i].cap),dfs2(v,x),++child;
	}
	if (child) ans=max(ans,g[x]);
	else ans=max(ans,g[x]-f[x]);
}
int main() {
	int T; scanf("%d",&T);
	while (T--) {
		scanf("%d",&n);
		memset(head,-1,sizeof(head));
		tot=0;
		rep(i,0,n-1) {
			int u,v,c; scanf("%d%d%d",&u,&v,&c);
			add_edge(u,v,c);
			add_edge(v,u,c);
		}
		int s;
		rep(j,1,n+1) {
			s=0;
			for (int i=head[j];~i;i=edges[i].nxt) ++s;
			if (s>1) {s=j;break;}
		}
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		dfs1(s,-1);
		g[s]=f[s];
		ans=0;
		dfs2(s,-1);
		printf("%d\n",ans);
	}
	return 0;
}
