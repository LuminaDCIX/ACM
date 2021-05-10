#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
inline int read()
{
	int f=0,s=1,ch;
	for(ch=getchar();!isdigit(ch);(ch=='-')?s=-1:s=1,ch=getchar());
	for(;isdigit(ch);f=(f<<1)+(f<<3)+ch-'0',ch=getchar());
	return f*s;
}
typedef long long ll;
const int maxn=1000;
const int maxm=10000*2;
const int inf=0x3f3f3f3f;
int n,m,c,tot;
int head[maxn+5];
int cost[maxn+5];
int e,s;
struct edge
{
	int nxt,to,val;
}
edges[maxm+5];
struct node
{
	int x,c,val;
	bool operator<(const node a)const{
		return val>a.val;
	}
};
inline void add_edge(int from,int to,int val)
{
	edges[++tot].to=to,
	edges[tot].nxt=head[from],
	edges[tot].val=val,
	head[from]=tot;
}
inline int dijkstra()
{
	int f[maxn+5][105];
	int vis[maxn+5][105];
	memset(f,0x3f3f,sizeof(f));
	memset(vis,0,sizeof(vis));
	f[s][0]=0;
	priority_queue<node> que;
	que.push((node){s,0,0});
	while(!que.empty()){
		node p=que.top();
		que.pop();
		if(vis[p.x][p.c]){
			continue;
		}
		vis[p.x][p.c]=1;
		if(p.x==e){
			return p.val;
		}
		if(p.c+1<=c&&!vis[p.x][p.c+1]&&f[p.x][p.c]+cost[p.x]<f[p.x][p.c+1]){
			f[p.x][p.c+1]=f[p.x][p.c]+cost[p.x];
			que.push((node){p.x,p.c+1,f[p.x][p.c+1]});
		}
		for(int i=head[p.x];i;i=edges[i].nxt){
			int v=edges[i].to;
			if(p.c-edges[i].val>=0&&!vis[v][p.c-edges[i].val]&&p.val<f[v][p.c-edges[i].val]){
				f[v][p.c-edges[i].val]=p.val;
				que.push((node){v,p.c-edges[i].val,f[v][p.c-edges[i].val]});
			}
		}
	}
	return inf;
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;cost[i]=read(),++i);	
	for(int i=1,u,v,val;i<=m;++i){
		u=read()+1,v=read()+1,val=read();
		add_edge(u,v,val);
		add_edge(v,u,val);
	}
	int q=read();
	while(q--){
		c=read(),s=read()+1,e=read()+1;
		int ans=dijkstra();
		if(ans==inf){
			puts("impossible");
		}
		else{
			printf("%d\n",ans);
		}
	}
	return 0;
}