#include<bits/stdc++.h>

using namespace std;

const int maxn=400;
const int inf=(int)1e9;
int head[maxn*2+5],tot;
int cur[maxn*2+5],dis[maxn*2+5];
bool vis[maxn*2+5];

struct edge
{
  int nxt,to,cap;
}
edges[maxn*maxn*8+5];
int s[maxn+5],t[maxn+5];
int S=maxn*2+1,T=maxn*2+2;
struct point
{
  int x,y,val;
  int id;
}
lizzs[maxn+5],stone[maxn+5];
int n,m,d;
int ns,nl;
inline void add_edge(int from,int to,int cap)
{
  edges[++tot].to=head[from];
  edges[tot].to=to;
  edges[tot].nxt=head[from];
  edges[tot].cap=cap;
  head[from]=tot;
}
inline double dist(point a,point b)
{
  return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

inline bool bfs()
{
  queue<int> que;
  que.push(S);
  memset(vis,0,sizeof(vis));
  vis[S]=1;
  dis[S]=0;
  while(!que.empty()){
    int x=que.front();
    //printf("%d\n",x);
    que.pop();
    for(int i=head[x];i;i=edges[i].nxt){
      int v=edges[i].to;
      if(!vis[v]&&edges[i].cap){
        dis[v]=dis[x]+1;
        vis[v]=1;
        que.push(v);
      }
    }
  }
  //for(int i=0;i<10000000;++i);
  //puts("");
  return vis[T];
}

int dfs(int x,int f) 
{
  if(!f||x==T){
    return f;
  }
  int now=0,flow=0;
  for(int &i=cur[x];i;i=edges[i].nxt){
    int v=edges[i].to;
    if(dis[v]==dis[x]+1&&edges[i].cap&&(now=dfs(v,min(f,edges[i].cap)))>0){
      flow+=now;
      edges[i].cap-=now;
      edges[i^1].cap+=now;
      f-=now;
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
    ret+=dfs(S,inf);
  }
  return ret;
}

int main()
{
  ++tot;
  for(int i=0;i<maxn+5;++i){
    s[i]=i;
    t[i]=s[i]+maxn;
  }
  scanf("%d%d%d",&n,&m,&d);
  scanf("\n");
  for(int i=0;i<n;++i){
    for(int j=0;j<m;++j){
      char bar=getchar();
      if(bar!='0'){
        stone[ns].x=i;
        stone[ns].y=j;
        stone[ns].id=i*m+j;
        stone[ns++].val=bar-'0';
      }
    }
    scanf("\n");
  }
  for(int i=0;i<n;++i){
    for(int j=0;j<m;++j){
      char bar=getchar();
      if(bar=='L'){
        lizzs[nl].x=i;
        lizzs[nl].id=i*m+j;
        lizzs[nl++].y=j;
      }
    }
    scanf("\n");
  }//read
  //direct graph
  for(int i=0;i<ns;++i){
    add_edge(s[stone[i].id],t[stone[i].id],stone[i].val);
    add_edge(t[stone[i].id],s[stone[i].id],0);
  }
  for(int i=0;i<nl;++i){
    add_edge(S,s[lizzs[i].id],1);
    add_edge(s[lizzs[i].id],S,0);  
  }
  for(int i=0;i<ns;++i){
    for(int j=0;j<ns;++j){
      if(i==j){
        continue;
      }
      if(dist(stone[i],stone[j])<=d){
        add_edge(t[stone[i].id],s[stone[j].id],inf);
        add_edge(s[stone[j].id],t[stone[i].id],0);
      }
    }
  }
  for(int i=0;i<ns;++i){
    int x=stone[i].x;
    int y=stone[i].y;
    if(x<d||n-x<=d||y<d||m-y<=d){
      add_edge(t[stone[i].id],T,inf);
      add_edge(T,t[stone[i].id],0);
    }
  }
  printf("%d\n",nl-dinic());
  return 0;
}