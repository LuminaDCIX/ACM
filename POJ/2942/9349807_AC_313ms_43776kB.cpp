#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<stack>
#include<vector>
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define per(i,a,n) for(int i=n;i>=a;--i)
using namespace std;
inline int read()
{
  int f=0;char ch=getchar();
  while(ch<'0'||ch>'9') ch=getchar();
  while(ch>='0'&&ch<='9') {f=f*10+ch-'0',ch=getchar();}
  return f;
}
const int maxn=1000;
const int maxm=1000000;
int n,m;
struct edge
{
  int u,v,nxt,id;
  bool exi;
  edge(int _u=0,int _v=0,int _id=0){
    u=_u,v=_v,id=_id;
    exi=0;
  }
}
edges[maxm*2+5];
int G[maxn+5][maxn+5];
int head[maxn+5],tot;
int dfn[maxn+5],low[maxn+5];
int bccno[maxn+5],nbcc,cnt;
vector<int> bcc[maxn+5];
stack<edge> s;
inline void add_edge(int u,int v)
{
  edges[++tot].v=v,edges[tot].nxt=head[u],edges[tot].u=u,head[u]=tot,edges[tot].exi=0;
}
int vis[maxn+5],ans;
bool succ,can[maxn+5];
void dfs2(int u,int col)
{
  vis[u]=col;
  for(int i=head[u];i;i=edges[i].nxt) if(edges[i].exi){
    int v=edges[i].v;
    if(vis[v]==col) {
      succ=0;
    }
    else if(!vis[v]) dfs2(v,col^1);
    edges[i].exi=0;
  }
}
int dfs(int u,int fa)
{
  int lowu,child=0;
  lowu=dfn[u]=++cnt;
  for(int i=head[u];i;i=edges[i].nxt){
    int v=edges[i].v;
    edge e=edge(u,v,i);
    if(!dfn[v]){
      s.push(e),child++;
      int lowv=dfs(v,u);
      lowu=min(lowu,lowv);
      //printf("%d %d %d\n",u,lowu,lowv);
      if(lowv>=dfn[u]){
        nbcc++;
        //printf("%d\n",nbcc);
        while(1){
          edge x=s.top();
          s.pop();
          //printf("%d %d\n",x.u,x.v);
          edges[x.id].exi=1;
          if(bccno[x.u]!=nbcc){
            bccno[x.u]=nbcc;
            bcc[nbcc].push_back(x.u);
          }
          if(bccno[x.v]!=nbcc){
            bccno[x.v]=nbcc;
            bcc[nbcc].push_back(x.v);
          }
          if(u==x.u&&v==x.v){
            memset(vis,0,sizeof(vis));
            succ=1;dfs2(u,2);
            if(!succ) rep(l,0,bcc[nbcc].size()-1) can[bcc[nbcc][l]]|=1; 
            break;
          }
        }
      }
    }
    else if(dfn[v]<dfn[u]&&v!=fa){
      s.push(e);
      lowu=min(lowu,dfn[v]);
    }
  }
  return low[u]=lowu;
}

int main()
{ 
  while(scanf("%d%d",&n,&m)&&n+m){
    int u,v;
    ans=0,memset(can,0,sizeof(can));
    while(!s.empty()) s.pop();
    memset(G,0,sizeof(G));
    memset(head,0,sizeof(head));
    tot=0;
    rep(i,1,m) u=read(),v=read(),G[u][v]=G[v][u]=1;
    rep(u,1,n) rep(v,1,n) if(u!=v&&!G[u][v]) add_edge(u,v);
    memset(dfn,0,sizeof(dfn));
    cnt=nbcc=0;
    rep(i,1,n) bcc[i].clear(),bccno[i]=0;
    rep(i,1,n) if(!dfn[i]) dfs(i,-1);
    //rep(i,1,nbcc) {rep(j,0,bcc[i].size()-1) printf("%d ",bcc[i][j]);puts("");}
    rep(i,1,n) if(!can[i]) ans++;
    printf("%d\n",ans);
  }
  return 0;
}