#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

const int maxn=300000;

struct edge
{
  int nxt,to;
}
edges[maxn*2+5];
int head[maxn+5];
int tot,n,m;
int depth[maxn+5];
int pre[maxn+5][21];
int l[maxn+5],r[maxn+5];
int up[maxn*2+5],down[maxn*2+5];
int ans[maxn+5];
int acs[maxn+5],len[maxn+5];
int w[maxn+5];
int val[maxn*2+5];
int num[maxn*2+5];

vector<int> p1[maxn+5],p2[maxn+5],p3[maxn+5];

inline void add_edge(int from,int to)
{
  edges[++tot].to=to;
  edges[tot].nxt=head[from];
  head[from]=tot;
  return;
}

void dfs(int u,int fa)
{
  for (int i=head[u];i;i=edges[i].nxt) {
    int v=edges[i].to;
    if (v==fa) {
      continue;
    }
    depth[v]=depth[u]+1;
    pre[v][0]=u;
    dfs(v,u);
  }
  return;
}

int lca(int a,int b)
{
  if (depth[a]<depth[b]) {
    swap(a,b);
  }
  for (int i=19;i>=0;--i) {
    if (depth[pre[a][i]]>=depth[b]) {
      a=pre[a][i];
    }
  }
  if (a==b) {
    return a;
  }
  for (int i=19;i>=0;--i) {
    if (pre[a][i]!=pre[b][i]) {
      a=pre[a][i];
      b=pre[b][i];
    }
  }
  return pre[a][0];
}

void update(int u)
{
  int now=w[u]+depth[u];
  int c=up[now];
  for (int i=head[u];i;i=edges[i].nxt) {
    int v=edges[i].to;
    if (v!=pre[u][0]) {
      update(v);
    }
  }
  up[depth[u]]+=val[u];
  ans[u]+=up[now]-c;
  //printf("%d %d %d %d\n",now,up[now],u,ans[u]);
  for (int i=0;i<p1[u].size();++i) {
    up[p1[u][i]]--;
  }
}

void downdate(int u)
{
  int c=down[maxn+w[u]-depth[u]];
  int now=maxn+w[u]-depth[u];
  for (int i=head[u];i;i=edges[i].nxt) {
    int v=edges[i].to;
    if (v==pre[u][0]) {
      continue;
    }
    downdate(v);
  }
  for (int i=0;i<p2[u].size();++i) {
    down[maxn+p2[u][i]]++;
  }
  ans[u]+=down[now]-c;
  //printf("%d %d\n",down[now],c);
  for (int i=0;i<p3[u].size();++i) {
    down[maxn+p3[u][i]]--;
  }
  return;
}

int main()
{
  scanf("%d%d",&n,&m); 
  int from,to;
  for (int i=1;i<n;++i) {
    scanf("%d%d",&from,&to);
    add_edge(from,to);
    add_edge(to,from);
  }
  depth[1]=1;
  dfs(1,-1);
  for (int i=1;i<=n;++i) {
    scanf("%d",&w[i]);
  }
  for (int i=1;i<=19;++i) {
    for (int j=1;j<=n;++j) {
      pre[j][i]=pre[pre[j][i-1]][i-1];
    }
  }
  for (int i=1;i<=m;++i) {
    scanf("%d%d",&l[i],&r[i]);
    //up
    acs[i]=lca(l[i],r[i]);
    len[i]=depth[l[i]]+depth[r[i]]-depth[acs[i]]*2;
    val[l[i]]++;
    p1[acs[i]].push_back(depth[l[i]]);
  }
  for (int i=1;i<=m;++i) {
    p2[r[i]].push_back(len[i]-depth[r[i]]);
    p3[acs[i]].push_back(len[i]-depth[r[i]]);
  }
  update(1);
  downdate(1);
  for (int i=1;i<=m;++i) {
    if (depth[l[i]]-depth[acs[i]]==w[acs[i]]) {
      ans[acs[i]]--;
    }
  }
  for (int i=1;i<=n;++i) {
    printf("%d ",ans[i]);
  }
  return 0;
}