#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

const int maxn=150;
int root;
struct edge
{
  int to,nxt;
}
edges[maxn+5];
int n,fa[maxn+5],p;
int tot,head[maxn+5];
int f[maxn+5][maxn+5];

inline void add_edge(int from,int to)
{
  edges[++tot].to=to;
  edges[tot].nxt=head[from];
  head[from]=tot;
  return;
}

void dfs(int u)
{
  int ud=0;
  for (int i=head[u];i;i=edges[i].nxt) {
    if (edges[i].to!=fa[u]) {
      ud++;
    }
  }
  f[u][1]=ud+1;
  for (int i=2;i<=p;++i) {
    f[u][i]=maxn<<1;
  }
  for (int i=head[u];i;i=edges[i].nxt) {
    int v=edges[i].to;
    dfs(v);
    for (int j=p;j>1;--j) {
      for (int k=1;k<j;++k) {
        f[u][j]=min(f[u][j],f[v][k]+f[u][j-k]-2);
      }
    }
  }
  return;
}

int main()
{
  scanf("%d%d",&n,&p);
  int fr,t;
  for (int i=1;i<=n-1;++i) {
    scanf("%d%d",&fr,&t);
    fa[t]=fr;
    add_edge(fr,t);
  }
  root=1;
  while (fa[root]) {
    root=fa[root];
  }
  dfs(root);
  int ans=maxn;
  f[root][p]--;
  for (int i=1;i<=n;++i) {
    ans=min(ans,f[i][p]);
  }
  printf("%d\n",ans);
  return 0;
}