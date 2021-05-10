#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<queue>

using namespace std;

const int maxn=750;

struct edge
{
  int to,nxt,cap,flow;
}
edges[20*50*7*10+1005];
int head[1505];
int tot,n;
int S=1,T=1500;
bool vis[1505];
int cur[1505];
int dist[1505];
bool exi[55][9];

inline void add_edge(int from,int to,int cap)
{
  edges[++tot]=(edge){to,head[from],cap,0};
  head[from]=tot;
  edges[++tot]=(edge){from,head[to],0,0,};
  head[to]=tot;
}


inline bool bfs()
{
  memset(vis,0,sizeof(vis));
  queue<int> que;
  que.push(S);
  dist[S]=0;
  vis[S]=1;
  while (!que.empty()) {
    int x=que.front();
    que.pop();
    for (int i=head[x];i;i=edges[i].nxt) {
      if ((!vis[edges[i].to])&&edges[i].cap>edges[i].flow) {
        dist[edges[i].to]=dist[x]+1;
        //printf("%d %d\n",edges[i].to,vis[edges[i].to]);
        vis[edges[i].to]=1;
        que.push(edges[i].to);
      }
    }
  }
  return vis[T];
}

int dfs(int u,int f)
{
//printf("%d %d\n",u,f);
  if (u==T||f==0) {
    return f;
  }
  int flw=0;
  int now=0;
  for (int &i=cur[u];i;i=edges[i].nxt) {
    int v=edges[i].to;
    if (dist[v]==dist[u]+1&&(now=dfs(v,min(f,edges[i].cap-edges[i].flow)))>0) {
      //printf("now=%d\n",now);
      edges[i].flow+=now;
      edges[i^1].flow-=now;
      flw+=now;
      f-=now;
      if (!f) {
        break;
      }
    }
  }
  //printf("u=%d %d\n",u,flw);
  return flw;
}

inline int dinic()
{
  int f=0;
  while (bfs()) {
    for (int i=1;i<=1504;++i) {
      cur[i]=head[i];
    }
    f+=dfs(S,10000000);
    //printf("%d\n",f);
  }
  //printf("%d\n",f);
  return f;
}


int main()
{
  int cT;
  scanf("%d",&cT); 
  while (cT--) {
    scanf("%d",&n);
    memset(head,0,sizeof(head));
    memset(exi,0,sizeof(exi));
    tot=1;
    int ans=0;
    for (int i=1;i<=n;++i) {
      int bar[9];
      int w,d;
      for (int j=1;j<=7;++j) {
        scanf("%d",&bar[j]);
      }
      scanf("%d%d",&d,&w);
      ans+=d;
      for (int j=1;j<=w;++j) {
        for (int k=1;k<=7;++k) {
          if (bar[k]==0) {
            continue;
          }
          add_edge(maxn+i,7*j+k,1);
          if (!exi[j][k]) {
            exi[j][k]=1;
            add_edge(7*j+k,T,1);
          }
        }
      }
      add_edge(S,maxn+i,d);
    }
    if (dinic()==ans) {
      puts("Yes");
    }
    else {
      puts("No");
    }
  }
  return 0;
}