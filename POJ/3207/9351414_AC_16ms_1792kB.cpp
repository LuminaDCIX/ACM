#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define per(i,a,n) for(int i=n;i>=a;--i)
using namespace std;
const int maxn=1000;
int n,m;
int x[maxn+5],y[maxn+5];
int vis[maxn+5];
int scc,t[maxn+5];
struct edge
{
  int nxt,to;
}
edges[4*maxn*maxn+5];
int head[maxn+5],tot;
int s[maxn+5],p;
inline void add_edge(int u,int v)
{
  edges[++tot].to=v,edges[tot].nxt=head[u],head[u]=tot;
}
int dfn[maxn+5],cnt,low[maxn+5];
void dfs(int u)
{
  dfn[u]=low[u]=++cnt;
  vis[u]=1,s[p++]=u;
  for(int i=head[u],v=edges[i].to;i;i=edges[i].nxt,v=edges[i].to){
    if(!dfn[v]) dfs(v),low[u]=min(low[u],low[v]);
    else if(vis[v]) low[u]=min(low[u],dfn[v]);
  }
  if(low[u]==dfn[u]){
    int y;++scc;
    do{y=s[--p],t[y]=scc,vis[y]=0;}while(y!=u);
  }
}
int main()
{
  scanf("%d%d",&n,&m);
  rep(i,1,m){
    int u,v;
    scanf("%d%d",&u,&v);
    x[i]=min(u,v),y[i]=max(u,v);
  }
  rep(i,1,m) rep(j,1,m) if(x[i]<x[j]&&y[i]>x[j]&&y[j]>x[i]&&y[j]>y[i]){
    add_edge(i,j+m),add_edge(j+m,i);
    add_edge(j,i+m),add_edge(i+m,j);
  }
  rep(i,1,2*m) if(!dfn[i]) dfs(i);
  bool succ=1;
  rep(i,1,m) if(t[i]==t[i+m]) succ=0;
  puts((succ?"panda is telling the truth...":"the evil panda is lying again"));
  return 0;
}