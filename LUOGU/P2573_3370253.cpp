#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define rep(i,a,n) for (int i=(a);i<(n);++i)

using namespace std;

inline int read() {
  int f=1, x=0;
  char ch=getchar();
  while (ch<'0'||ch>'9') f=(ch=='-')?-1:1, ch=getchar();
  while (ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
  return f*x;
}

const int N=100000+5;
const int M=1000000+5;

int n, m;
int val[N];
    
int head[N], tot;
  
struct edge {
  int nxt, to, from;
  int val, h;

  bool operator < (const edge &rhs) const {
    return h==rhs.h?val<rhs.val:h>rhs.h;
  }
} e[M<<1];

inline void add(int u,int v,int val,int h) {
  e[tot].to=v, e[tot].from=u, e[tot].nxt=head[u], e[tot].val=val, e[tot].h=h, head[u]=tot++;
}

bool vis[N];

inline int bfs() 
{
  queue <int> que;
  que.push(1);
  int ret=1;
  vis[1]=1;
  while (!que.empty()) {
    int u=que.front();
    que.pop();
    for (int i=head[u], v;~i;i=e[i].nxt) {
      v=e[i].to;
      if (!vis[v]) vis[v]=1, ++ret, que.push(v);
    }
  }
  return ret;
}

int fa[N];

int find(int x) {
  return x==fa[x]?x:fa[x]=find(fa[x]);
}

inline long long kruskal() 
{
  long long ret=0;
  sort(e,e+tot);
  rep (i,1,n+1) fa[i]=i;
  edge f;
  rep (i,0,tot) {
    f=e[i];
    if (!vis[f.from]||!vis[f.to]) continue;
    if (find(f.from)==find(f.to)) continue;
    fa[find(f.from)]=find(f.to);
    ret+=e[i].val;
  }
  return ret;
}

int main()
{
  memset(head,-1,sizeof(head));
  n=read(), m=read();
  rep (i,1,n+1) val[i]=read();
  int u, v, c;
  rep (i,0,m) {
    u=read(), v=read(), c=read();
    if (val[u]<val[v]) swap(u,v);
    add(u,v,c,val[v]);
    if (val[u]==val[v]) add(v,u,c,val[v]);
  }
  printf("%d ",bfs());
  printf("%lld\n",kruskal());
  return 0;
}
