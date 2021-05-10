#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<queue>
#define rep(i,a,n) for (int i=(a);i<=(n);++i)
#define per(i,a,n) for (int i=(n);i>=(a);--i)
using namespace std;

const int maxn=230;
int G[maxn+5][maxn+5];
int k,c,m,ans;
int maxl,maxr,S,T,tot;
int head[maxn+5],cur[maxn+5],dist[maxn+5];
bool vis[maxn+5];
struct edge
{
  int to,nxt,cap,flow;
}
edges[maxn*maxn*2+maxn+5];

inline void add_edge(int from,int to,int cap)
{
  edges[++tot]=(edge){to,head[from],cap,0}; head[from]=tot;
  edges[++tot]=(edge){from,head[to],0,0}; head[to]=tot;
}

inline void floyd()
{
  rep(p,1,k+c) rep(i,1,k+c) rep(j,1,k+c) {
    G[i][j]=min(G[i][j],G[i][p]+G[p][j]);
    maxr=max(G[i][j],maxr);
  }
}

inline void init(int x)
{
  memset(head,0,sizeof(head)); tot=1;
  rep(i,1,k) add_edge(i,T,m);
  rep(i,k+1,k+c) add_edge(S,i,1);
  rep(i,k+1,k+c) rep(j,1,k) if (G[i][j]<=x) {
    add_edge(i,j,1);
  }
}

inline bool bfs()
{
  memset(vis,0,sizeof(vis));
  queue<int> que;
  que.push(S);
  vis[S]=1,dist[S]=0;
  while (!que.empty()) {
    int x=que.front(); que.pop();
    for (int i=head[x];i;i=edges[i].nxt) if (!vis[edges[i].to]&&edges[i].cap>edges[i].flow) {
      int v=edges[i].to;
      dist[v]=dist[x]+1,vis[v]=1;
      que.push(v);
    }
  }
  return vis[T];
}

int dfs(int u,int f)
{
  if (u==T||f==0) return f;
  int flow=0,now;
  for (int &i=cur[u];i;i=edges[i].nxt) if (dist[edges[i].to]==dist[u]+1&&(now=dfs(edges[i].to,min(f,edges[i].cap-edges[i].flow)))>0) {
    edges[i].flow+=now,edges[i^1].flow-=now;
    f-=now,flow+=now;
    if (!f) break;
  }
  return flow;
}

inline int dinic()
{
  int flow=0;
  while (bfs()) {
    rep(i,1,k+c+2) cur[i]=head[i];
    flow+=dfs(S,100000);
    
  }
  return flow;
}

int main()
{
  scanf("%d%d%d",&k,&c,&m);
  S=k+c+1,T=k+c+2;
  rep(i,1,k+c) rep(j,1,k+c) {
    scanf("%d",&G[i][j]);
    if (G[i][j]==0&&i!=j) G[i][j]=100000;
  }
  floyd();
  maxl=0;
  while (maxl<=maxr) {
    int mid=(maxl+maxr)>>1;
    init(mid);
    if (dinic()>=c) {
      ans=mid,maxr=mid-1;
    }
    else {
      maxl=mid+1;
    }
  }
  printf("%d\n",ans);
  return 0;
}