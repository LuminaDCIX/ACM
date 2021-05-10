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
const int maxn=500;
const int maxm=3000;
const int inf=1e9;
int n,m,tot;
int maxv;
int head[maxn+5],dist[maxn+5],col[maxn+5],vis[maxn+5];
int cur[maxn+5];
int a[maxn+5],val[maxn+5];
int S=maxn+1,T=maxn+2;
int u[maxm+5],v[maxm+5];
struct edge
{
	int nxt,to,val,cap;
}
edges[maxm*2+maxn*4+5];
inline void add_edge(int from,int to,int cap)
{
	edges[++tot].to=to,
	edges[tot].cap=cap,
	edges[tot].nxt=head[from];
	head[from]=tot;
}
inline void init()
{
	memset(head,0,sizeof(head));
	tot=1;
	memset(col,0,sizeof(col));
}
inline void build(int x)
{
	for(int i=1;i<=n;++i){
		if(a[i]>=0){
			if(a[i]&x){
				add_edge(S,i,inf);
				add_edge(i,S,0);
			}
			else{
				add_edge(T,i,0);
				add_edge(i,T,inf);
			}
		}
	}
	for(int i=1;i<=m;++i){
		add_edge(u[i],v[i],1);
		add_edge(v[i],u[i],1);
	}
}
inline bool bfs()
{
	memset(vis,0,sizeof(vis));
	queue<int> que;
	que.push(S);
	vis[S]=1;
	dist[S]=0;
	while(!que.empty()){
		int x=que.front();
		que.pop();
		for(int i=head[x];i;i=edges[i].nxt){
			int t=edges[i].to;
			if(!vis[t]&&edges[i].cap){
				dist[t]=dist[x]+1;
				vis[t]=1;
				que.push(t);
			}
		}
	}
	return vis[T];
}
inline int dfs(int x,int f)
{
	if(x==T||f==0){
		return f;
	}
	int flow=0,now=-1;
	for(int &i=cur[x];i;i=edges[i].nxt){
		int t=edges[i].to;
		if(dist[t]==dist[x]+1&&edges[i].cap&&(now=dfs(t,min(f,edges[i].cap)))>0){
			edges[i].cap-=now;
			edges[i^1].cap+=now;
			f-=now;
			flow+=now;
			if(!f){
				break;
			}
		}
	}
	return flow;
}
inline int dinic()
{
	int ret=0;
	while(bfs()){
		for(int i=1;i<maxn+5;++i){
			cur[i]=head[i];
		}
		ret+=dfs(S,inf);
	}
	return ret;
}
void color(int x)
{
	col[x]=1;
	for(int i=head[x];i;i=edges[i].nxt){
		int t=edges[i].to;
		if(!col[t]&&edges[i].cap){
			color(t);
		}
	}
}
int main()
{
int kase=read();
while(kase--){
	n=read(),m=read();	
	for(int i=1;i<=m;++i){
		u[i]=read(),v[i]=read();
	}
	int k=read();
	memset(a,-1,sizeof(a));
	memset(val,0,sizeof(val));
	maxv=0;
	for(int i=1,x;i<=k;++i){
		x=read();
		val[x]=a[x]=read();
		maxv=max(maxv,a[x]);
	}
	for(long long x=1;x<=maxv;x<<=1){
		init();
		build(x);
		int ret=dinic();
		color(S);
		for(int i=1;i<=n;++i){
		  if(col[i]&&a[i]<0){
		    val[i]+=x;
		  }
		}
	}
	for(int i=1;i<=n;++i){
	  printf("%d\n",val[i]);
	}
}
	return 0;
}