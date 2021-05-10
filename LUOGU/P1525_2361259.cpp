#include<bits/stdc++.h>
#define rep(i,a,n) for (int i=a;i<=n;++i)
#define per(i,a,n) for (int i=n;i>=a;--i)

using namespace std;

const int maxn=20000;
const int maxm=100000;
int n,m;
int vis[maxn+5];
int succ=0;
struct edge
{
  int from,nxt,to,val;
  bool operator < (const edge b) const
  {
    return val<b.val;
  }
}
edges[maxm*2+5],input[maxm+5];
int tot,head[maxn+5];
inline void add_edge(int from,int to,int val)
{
  edges[++tot].to=to,edges[tot].nxt=head[from],edges[tot].val=val,head[from]=tot;
}
inline void init(int mid)
{
  memset(head,0,sizeof(head));
  tot=0;
  rep(i,mid,m) add_edge(input[i].from,input[i].to,input[i].val),add_edge(input[i].to,input[i].from,input[i].val);
}

void dfs(int u,int col) 
{
  vis[u]=col;
  for (int i=head[u],v=edges[head[u]].to;i;i=edges[i].nxt,v=edges[i].to) {
    if (vis[v]==col) {
      succ=0;
      return;
    }
    else if (vis[v]) continue;
    else dfs(v,col^1);
  }
}
inline int judge()
{
  memset(vis,0,sizeof(vis));
  int cnt=0; succ=1;
  rep(i,1,n) if (!vis[i]) dfs(i,2);
  return succ;
}
int main()
{
  ios::sync_with_stdio(false);
  cin>>n>>m;
  if (n==2) {puts("0");return 0;}
  rep(i,1,m) cin>>input[i].from>>input[i].to>>input[i].val;
  sort(input+1,input+1+m);
  int l=2,r=m;
  int ans=m+1;
  while (l<=r) {
    int mid=(l+r)>>1;
    int p;
    init(mid);
    if ((p=judge())==1) ans=mid,r=mid-1;
    else l=mid+1;
    //cout<<"l="<<l<<"r="<<r<<endl;
    //cout<<"ans="<<ans<<endl;
  }
  cout<<input[ans-1].val<<endl;
  return 0;
}