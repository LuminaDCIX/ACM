#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#define rep(i,a,n) for (int i=a;i<=n;++i)
#define per(i,a,n) for (int i=n;i>=a;--i)
using namespace std;

const int maxn=200;
const int maxm=40000;
int n,m,T;
struct edge
{
  int nxt,to;
}
edges[maxm*2+5];
int tot,head[maxn+5];
int cnt,vis[maxn+5],idx[maxn+5];
int ind[maxn+5];
inline void add_edge(int from,int to)
{
  edges[++tot].to=to;edges[tot].nxt=head[from],head[from]=tot;
  ind[to]++;
}
void toposort()
{
  rep(i,1,n) per(i,1,n) if (ind[i]==0&&!vis[i]) {
    vis[i]=1;
    idx[i]=cnt--;
    for (int j=head[i];j;j=edges[j].nxt) {
      ind[edges[j].to]--;
    }
    break;
  }
}

int main()
{
  ios::sync_with_stdio(false);
  cin>>T;
  while (T--) {
    cin>>n>>m;
    int s,t;
    memset(ind,0,sizeof(ind));
    memset(head,0,sizeof(head));
    tot=0;
    rep(i,1,m) cin>>s>>t,add_edge(t,s);
    memset(vis,0,sizeof(vis));
    memset(idx,0,sizeof(idx));
    cnt=n;
    toposort();
    if (cnt!=0) cout<<-1; 
    else rep(i,1,n) cout<<idx[i]<<" ";
    cout<<endl;
  }
  return 0;
}