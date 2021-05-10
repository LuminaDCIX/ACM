#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<vector>

using namespace std;

const int maxn=100;
struct edge
{
  int nxt,to;
}
edges[maxn*2+5];
int tot,head[maxn+5];
int n,p,w[maxn+5];
int f[maxn+5][maxn*2+5][2];

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
    dfs(v,u);
   // f[u][0][0]=f[u][0][1]=w[u];
    for (int j=p;j>=1;--j) {
      for (int k=1;k<=j;++k) {
        if (k-2>=0) {
          f[u][j][0]=max(f[u][j][0],f[v][k-2][1]+f[u][j-k][0]);
        }
        f[u][j][0]=max(f[u][j][0],f[v][k-1][0]+f[u][j-k][1]);
        if (k-2>=0) {
          f[u][j][1]=max(f[u][j][1],f[u][j-k][1]+f[v][k-2][1]);
        }
      }
    }
  }
  return;
}

int main()
{
  while (scanf("%d",&n)!=EOF) {
    memset(head,0,sizeof(head));
    tot=0;
    scanf("%d",&p);
    int from,to;
    for (int i=1;i<=n;++i) {
      scanf("%d",&w[i]);
      for (int j=0;j<=p;++j) {
        f[i][j][0]=f[i][j][1]=w[i];
      }
    }
    for (int i=1;i<=n-1;++i) {
      scanf("%d%d",&from,&to);
      add_edge(from,to);
      add_edge(to,from);
    }
    dfs(1,0);
    printf("%d\n",max(f[1][p][0],f[1][p][1]));
  }
  return 0;
}