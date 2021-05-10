#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#define rep(i,a,n) for(int i=a;i<=n;++i)
#define per(i,a,n) for(int j=n;j>=a;--i)
using namespace std;

const int maxn=1001;
const int maxm=6000;
int n,m,T;
struct edge
{
  int nxt,to;
}
edges[maxm*2+5];
int tot,head[maxn*2+5];
bool vis[maxn+5];
bool vis2[maxn+5];
int dfn[maxn+5],low[maxn+5];
int scc,cnt,s[maxn+5],p,t[maxn+5];
int f[maxn+5],ind[maxn+5];
inline void add_edge(int from,int to) 
{
  edges[++tot].to=to;edges[tot].nxt=head[from],head[from]=tot;
}

inline void init()
{
  memset(head,0,sizeof(head));tot=0;
  scc=0,cnt=0;
  memset(dfn,0,sizeof(dfn));
  memset(vis2,0,sizeof(vis2));
  memset(ind,0,sizeof(ind));
}
void tarjan(int x)
{
  dfn[x]=low[x]=++cnt;
  vis[x]=1,s[++p]=x;
  for(int i=head[x],v=edges[head[x]].to;i;i=edges[i].nxt,v=edges[i].to){
    if(!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
    else if(vis[v]) low[x]=min(low[x],dfn[v]);
  }
  if(low[x]==dfn[x]){
    int y;++scc;
    do{y=s[p--],t[y]=scc,vis[y]=0;}while(y!=x);
  }
}
void dfs(int x)
{
  vis2[x-maxn]=1;f[x-maxn]=1;
  for(int i=head[x],v=edges[head[x]].to;i;i=edges[i].nxt,v=edges[i].to){
    if(!vis2[v-maxn]) dfs(v);
    f[x-maxn]=max(f[x-maxn],f[v-maxn]+1);
  }
}
int main()
{
  ios::sync_with_stdio(false);
  cin>>T;
  while(T--){
    init();
    cin>>n>>m;
    int from,to;
    rep(i,1,m) cin>>from>>to,add_edge(from,to);
    rep(i,1,n) if(!dfn[i]) tarjan(i);
    rep(i,1,n) for(int j=head[i],v=edges[head[i]].to;j;j=edges[j].nxt,v=edges[j].to){
      if(t[i]!=t[v]) add_edge(t[i]+maxn,t[v]+maxn),ind[t[v]]++;
    }
    int ans=0;
    rep(i,1,scc) if(ind[i]==0){
      f[i]=1;
      dfs(i+maxn);
      ans=max(ans,f[i]);
    }
    cout<<(ans==scc?"Yes":"No")<<endl;
  }
  return 0;
}