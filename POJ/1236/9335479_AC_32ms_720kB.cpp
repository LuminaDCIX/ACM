#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<cmath>
#define rep(i,a,n) for (int i=a;i<=n;++i)
#define per(i,a,n) for (int i=n;i>=a;--i)
using namespace std;

const int maxn=100;
int n,dfn[maxn+5],low[maxn+5];
struct edge
{
  int nxt,to;
}
edges[maxn*maxn*2+5];
int head[maxn+5],tot;
int s[maxn+5],p,t[maxn+5],cnt,vis[maxn+5],scc;
int ind[maxn+5],outd[maxn+5];
inline void add_edge(int from,int to)
{
  edges[++tot].to=to,edges[tot].nxt=head[from],head[from]=tot;
}
void dfs(int x)
{
  dfn[x]=low[x]=++cnt;
  vis[x]=1,s[p++]=x;
  for (int i=head[x],v=edges[head[x]].to;i;i=edges[i].nxt,v=edges[i].to) {
    if (!dfn[v]) dfs(v),low[x]=min(low[x],low[v]);
    else if (vis[v]) low[x]=min(low[x],low[v]);
  }
  if (low[x]==dfn[x]) {
    int y;++scc;
    do {y=s[--p];t[y]=scc,vis[y]=0;} while (x!=y);
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin>>n;
  rep(i,1,n) {
    int to; cin>>to;
    while (to) add_edge(i,to),cin>>to;
  }
  rep(i,1,n) if(!dfn[i]) dfs(i);
  rep(j,1,n) {
    for (int i=head[j],v=edges[head[j]].to;i;i=edges[i].nxt,v=edges[i].to) {
      if (t[j]!=t[v]) ind[t[v]]++,outd[t[j]]++;
    }
  }
  if (scc==1) {
    cout<<1<<endl<<0<<endl;
    return 0;
  }
  int cntin=0,cntout=0;
  //rep(i,1,n) cout<<i<<" "<<t[i]<<endl;
  rep(i,1,scc) {
    if (ind[i]==0) cntin++;
    if (outd[i]==0) cntout++;
  }
  cout<<cntin<<endl<<max(cntin,cntout)<<endl;
  return 0;
}