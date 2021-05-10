#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<queue>
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define per(i,a,n) for(int i=n;i>=a;--i)
using namespace std;
const int maxn=1000*20*2+20*2+1000*2;
const int maxh=1000+20;
int n,S=maxh+1,T=maxh+2,m,b[25];
int head[maxh+5],cur[maxh+5],tot;
int vis[maxh+5],dist[maxh+5],rank[1005][25];
struct edge
{
  int nxt,to,cap;
}
edges[maxn+5];
inline int read()
{
  int f=0;char ch=getchar();
  while(ch<'0'||ch>'9')ch=getchar();
  while(ch>='0'&&ch<='9') f=f*10+ch-'0',ch=getchar();
  return f;
}
inline void add_edge(int from,int to,int cap)
{
  edges[++tot].to=to,edges[tot].nxt=head[from],edges[tot].cap=cap,head[from]=tot;
}
void init(int l,int r)
{
  memset(head,0,sizeof(head));
  tot=1;
  rep(i,1,n) rep(j,l,r) add_edge(i,1000+rank[i][j],1),add_edge(1000+rank[i][j],i,0);
  rep(i,1,n) add_edge(S,i,1),add_edge(i,S,0);
  rep(i,1000+1,1000+m) add_edge(i,T,b[i-1000]),add_edge(T,i,0);//printf("%d %d\n",i,T);
}
inline bool bfs()
{
  queue<int> que;
  memset(vis,0,sizeof(vis));
  dist[S]=0,vis[S]=1;
  que.push(S);
  while(!que.empty()){
    int x=que.front();que.pop();
    //printf("%d\n",x);
    for(int i=head[x];i;i=edges[i].nxt){
      int v=edges[i].to;
      if(!vis[v]&&edges[i].cap){
        vis[v]=1,dist[v]=dist[x]+1;
        que.push(v);
      }
    }
  }
  return vis[T];
}
int dfs(int x,int f)
{
  if(x==T||f==0) return f;
  int flow=0,now=0;
  for(int &i=cur[x];i;i=edges[i].nxt){
    int v=edges[i].to;
    if(dist[v]==dist[x]+1&&edges[i].cap&&(now=dfs(v,min(f,edges[i].cap)))>0){
      edges[i].cap-=now,edges[i^1].cap+=now;
      flow+=now,f-=now;
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
    rep(i,1,maxh+2) cur[i]=head[i];
    ret+=dfs(S,1000000);
    //puts("1");
  }
  return ret;
}
int main()
{
  n=read(),m=read();
  rep(i,1,n) rep(j,1,m) rank[i][j]=read();
  rep(i,1,m) b[i]=read();
  int ans=m;
  rep(low,1,m){
    int l=low,r=m;
    while(l<=r){
      int mid=(l+r)>>1;
      init(low,mid);
      int k=1;
      //printf("l=%d r=%d",l,r);
      if((k=dinic())==n) ans=min(ans,mid-low+1),r=mid-1;
      else l=mid+1;
      //printf(" %d\n",k);
    }
    //printf("%d ans=%d\n",low,ans);
  }
  printf("%d\n",ans);
  return 0;
}