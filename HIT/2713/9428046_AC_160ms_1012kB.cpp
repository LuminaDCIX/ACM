#include<cstring>
#include<cmath>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

const int maxn=50;
const int inf=100000000;
int n,m,c,tot;
int val[maxn+5][maxn+5];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
int color[maxn+5][maxn+5];
int head[2505],cur[2505];
int S=2500+1,T=2500+2;
int dis[2505],vis[2505];
struct edge
{
	int nxt,to,cap;
}
edges[12005];
inline void add_edge(int from,int to,int cap)
{
	edges[++tot].to=to,
	edges[tot].cap=cap,
	edges[tot].nxt=head[from],
	head[from]=tot;
}
inline int id(int x,int y)
{
	return x*m+y;
}
void draw(int x,int y,int col)
{
	color[x][y]=col;
	if(col==2){
		add_edge(S,id(x,y),val[x][y]);
		add_edge(id(x,y),S,0);
	}
	else{
		add_edge(id(x,y),T,val[x][y]);
		add_edge(T,id(x,y),0);	
	}
	for(int i=0;i<4;++i){
		int tx=x+dx[i];
		int ty=y+dy[i];
		if(tx<0||tx>=n||ty<0||ty>=m){
			continue;
		}
		if(!color[tx][ty]){
			draw(tx,ty,col^1);
		}
		if(col==2){
			add_edge(id(x,y),id(tx,ty),inf);
			add_edge(id(tx,ty),id(x,y),0);
		}
	}
}


inline bool bfs()
{
	queue<int> que;
	memset(vis,0,sizeof(vis));
	vis[S]=1;
	dis[S]=0;
	que.push(S);
	while(!que.empty()){
		int x=que.front();
		que.pop();
		for(int i=head[x];i;i=edges[i].nxt){
			int v=edges[i].to;
			if(!vis[v]&&edges[i].cap){
				dis[v]=dis[x]+1,
				vis[v]=1;
				que.push(v);
			}
		}	
	}
	return vis[T];
}

int dfs(int x,int f)
{
	if(x==T||f==0){
		return f;
	}
	int flow=0,now=0;
	for(int &i=cur[x];i;i=edges[i].nxt){
		int v=edges[i].to;
		if(dis[v]==dis[x]+1&&edges[i].cap&&(now=dfs(v,min(f,edges[i].cap)))>0){
			f-=now;
			flow+=now;
			edges[i].cap-=now;
			edges[i^1].cap+=now;
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
		for(int i=0;i<2505;++i){
			cur[i]=head[i];
		}
		ret+=dfs(S,inf);
	}
	return ret;
}

int main()
{
	scanf("%d",&c);
	while(c--){
		scanf("%d%d",&n,&m);
		int ans=0;
		memset(head,0,sizeof(head));
		tot=1;
		memset(color,0,sizeof(color));
		memset(dis,0,sizeof(dis));
		for(int i=0;i<n;++i){
			for(int j=0;j<m;++j){
				scanf("%d",&val[i][j]);
				ans+=val[i][j];
			}	
		}
		draw(0,0,2);
		printf("%d\n",ans-dinic());
	}
	return 0;
}