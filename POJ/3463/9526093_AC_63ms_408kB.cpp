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
const int maxm=10000;
struct node
{
	int x,val,p;
	bool operator<(const node a) const{
		return val>a.val;
	}
	node(int _x,int _p,int _val)
	{
		x=_x,val=_val;
		p=_p;
	}
};
priority_queue<node> que;
int dist[maxn+5][2];
int cnt[maxn+5][2];
int head[maxn+5];
int S,F,n,m,tot;
bool vis[maxn+5][2];
struct edge
{
	int nxt,to,val;
}
edges[maxm+5];

inline void add_edge(int from,int to,int val)
{
	edges[++tot].to=to,
	edges[tot].nxt=head[from],
	edges[tot].val=val;
	head[from]=tot;
}

inline void solve()
{
	memset(dist,0x3f3f,sizeof(dist));
	memset(cnt,0,sizeof(cnt));
	memset(vis,0,sizeof(vis));
	cnt[S][0]=1;
	dist[S][0]=0;
	que.push(node(S,0,0));//target dist
	while(!que.empty()){
		int u=que.top().x;
		int val=que.top().val;
		int now=que.top().p;
		que.pop();
		if(vis[u][now]){
			continue;
		}
		vis[u][now]=1;
		for(int i=head[u];i;i=edges[i].nxt){
			int v=edges[i].to;
			int x=edges[i].val+val;
			if(x<dist[v][0]){
				dist[v][1]=dist[v][0],
				cnt[v][1]=cnt[v][0],
				dist[v][0]=x,
				cnt[v][0]=cnt[u][now];
				que.push(node(v,0,dist[v][0]));
				que.push(node(v,1,dist[v][1]));
			}
			else if(x==dist[v][0]){
				cnt[v][0]+=cnt[u][now];
			}
			else if(x>dist[v][0]&&x<dist[v][1]){
				dist[v][1]=x,
				cnt[v][1]=cnt[u][now];
				que.push(node(v,1,dist[v][1]));
			}
			else if(x==dist[v][1]){
				cnt[v][1]+=cnt[u][now];
			}
		}
	}
}

int main()
{
	int T=read();
	while(T--){
		n=read(),m=read();
		tot=0;
		memset(head,0,sizeof(head));
		for(int i=1;i<=m;++i){
			int u=read(),v=read(),val=read();
			add_edge(u,v,val);
		}
		S=read(),F=read();
		solve();
		printf("%d\n",cnt[F][0]+(dist[F][1]==dist[F][0]+1?1:0)*cnt[F][1]);
	}		
	return 0;
}
