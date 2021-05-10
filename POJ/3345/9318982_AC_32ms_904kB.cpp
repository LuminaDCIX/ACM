#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<map>
#include<cstdio>

using namespace std;

const int maxn=200;
const int inf=1e8;
int n,m,cnt;
map<string,int> id;
int w[maxn+5];
int fa[maxn+5];
int f[maxn+5][maxn+5];
int siz[maxn+5];
struct edge
{
  int nxt,to;
}
edges[maxn+5];
int head[maxn+5],tot;
inline void add_edge(int from,int to)
{
  edges[++tot].to=to;
  edges[tot].nxt=head[from];
  head[from]=tot;
  return;
}

inline int getid(string t)
{
  return id[t]==0?id[t]=++cnt:id[t];
}

void dfs(int u,int fa)
{
  siz[u]=1;
  f[u][0]=0;
  for (int i=head[u];~i;i=edges[i].nxt) {
    int v=edges[i].to;
    if (v==fa) {
      continue;
    }
    dfs(v,u);
    siz[u]+=siz[v];
    for (int j=n;j>=0;--j) {
    f[u][j]=min(f[u][j],f[v][j]);
      for (int k=1;k<=siz[v];++k) {
        if (j-k<0) {
          break;
        }
        f[u][j]=min(f[u][j],f[u][j-k]+f[v][k]);
      } 
    }
  }
  f[u][siz[u]]=w[u];
  /*for (int i=0;i<=n;++i) {
    printf("f[%d][%d]=%d\n",u,i,f[u][i]);
  }*/
  return;
}

inline void init()
{
  memset(head,-1,sizeof(head));
  memset(fa,0,sizeof(fa));
  memset(siz,0,sizeof(siz));
  tot=0;
  n=0;
  cnt=0;
  id.clear();
}

void solve()
{
  for (int i=0;i<=n;++i) {
    for (int j=0;j<=n;++j) {
      f[i][j]=inf;
    }
  }
  for (int i=1;i<=n;++i) {
    if (fa[i]==0) {
      add_edge(0,i);
    }
  }
  dfs(0,-1);
  int ans=inf;
    for (int j=m;j<=n;++j) {
      ans=min(ans,f[0][j]);
    }
  printf("%d\n",ans);
  return;
}

int main()
{
  ios::sync_with_stdio(false);
  char tn[5];
  char name[105];
  while (scanf("%s",tn)>0&&strcmp(tn,"#")!=0) {
    init();
    for (int i=0;tn[i]!='\0';++i) {
      n=n*10+tn[i]-'0';
    }
    scanf("%d",&m);
    string t;
    t.clear();
    char s=getchar();
    int p;
    for (int i=1;i<=n;++i) {
      scanf("%s%d",name,&p);
      int u=getid((string)name);
      w[u]=p;
      while (getchar()!='\n') {
        scanf("%s",name);
        int v=getid((string)name);
        add_edge(u,v);
        fa[v]=u;
      }
    }
    solve();
  }
  return 0;
}