#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<queue>
using namespace std;
const int maxn=100;
int head[maxn*2+5];//people maxn+i project i
int cur[maxn*2+5];
int S=maxn*2+1,T=maxn*2+2;
int vis[maxn*2+5],dis[maxn*2+5];
struct edge
{
  int nxt,to,cap;
}
edges[maxn*maxn*4+5];
int tot,ans;
int c,n,m;

inline void add_edge(int from,int to,int cap)
{
  edges[++tot].to=to,
  edges[tot].cap=cap,
  edges[tot].nxt=head[from],
  head[from]=tot;
}

inline bool bfs()
{
  queue<int> que;
  que.push(S);
  memset(vis,0,sizeof(vis));
  dis[S]=0,
  vis[S]=1;
  while(!que.empty()){
    int x=que.front();
    que.pop();
    for(int i=head[x];i;i=edges[i].nxt){
      int v=edges[i].to;
      if(!vis[v]&&edges[i].cap){
        vis[v]=1,
        dis[v]=dis[x]+1,
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
  int now=0,flow=0;
  for(int &i=cur[x];i;i=edges[i].nxt){
    int v=edges[i].to;
    if(dis[v]==dis[x]+1&&edges[i].cap&&(now=dfs(v,min(f,edges[i].cap)))>0){
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
    for(int i=0;i<maxn*2+5;++i){
      cur[i]=head[i];
    }
    ret+=dfs(S,10000000);
  }
  return ret;
}

int main()
{
  scanf("%d",&c);
  while(c--){
    scanf("%d%d",&n,&m);
    int temp;
    memset(head,0,sizeof(head));
    memset(dis,0,sizeof(dis));
    tot=1,
    ans=0;
    for(int i=0;i<n;++i){
      scanf("%d",&temp),
      add_edge(S,i,temp),
      add_edge(i,S,0),
      ans+=temp;
    }
    for(int i=0;i<m;++i){
      scanf("%d",&temp);
      add_edge(i+maxn,T,temp);
      add_edge(T,i+maxn,0);
    }
    for(int i=0;i<n;++i){
      int cnt;
      scanf("%d",&cnt);
      for(int j=0;j<cnt;++j){
        int v;
        scanf("%d",&v);
        //printf("%d->%d\n",i,v);
        add_edge(i,v+maxn,1000000);
        add_edge(v+maxn,i,0);
      }
    }
    printf("%d\n",ans-dinic());
  }
  return 0;
}
