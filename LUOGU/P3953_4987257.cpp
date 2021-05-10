#include <ctime>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<pii> vii;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define clr(x,k) memset(x,k,sizeof(x))
#define siz(x) ((int)x.size())
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define forg(u,o) for (int o=head[u];~o;o=e[o].nxt) 

const int N=100000+5;
const int M=200000+5;
const int K=50+5;
const int inf=0x3f3f3f3f;

int read() {
  int f=1,x=0; char ch=getchar();
  while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
  while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
  return f*x;
}

int n,m,k,p,T;

struct edge {
  int nxt,to,val;
} e0[M],e1[M],e2[M];

void add(int u,int v,int w,int *head,edge *e,int &tot) {
  e[tot].to=v,e[tot].nxt=head[u],e[tot].val=w,head[u]=tot++;
}

int head0[N];
int head1[N];
int head2[N];
int tot0,tot1,tot2;

int f[N][K];

bool vis[N];
int dist[N];
bool vis1[N];
int dist1[N];

void dijkstra(bool *vis,int *dist,int *head,edge *e,int s) {
  priority_queue<pii> que;
  rep (i,0,n) dist[i]=inf,vis[i]=0;
  dist[s]=0;
  que.push(mp(0,s));
  while (!que.empty()) {
    int u=que.top().se;que.pop();
    if (vis[u]) continue;
    vis[u]=1;
    forg(u,o) {
      int v=e[o].to,val=e[o].val;
      if (vis[v]) continue;
      if (dist[v]>dist[u]+val) {
        dist[v]=dist[u]+val,que.push(mp(-dist[v],v));
      }
    }
  }
}

int in[N];
int q[N],hd,tl;
bool cur[N];

void topo(int *head,edge *e) {
  clr(in,0);
  hd=tl=0;
  rep (i,0,n) forg(i,o) ++in[e[o].to];
  rep (i,0,n) if (in[i]==0) q[tl++]=i;
  while (hd<tl) {
    int u=q[hd++];
    cur[u]=1;
    forg(u,o) {
      int v=e[o].to;
      --in[v];
      if (in[v]==0) q[tl++]=v;
    }
  }
}

bool solve() {
  clr(cur,0);
  topo(head2,e2);
  int lim=dist[n-1]+k;
  rep (i,0,n) if (!cur[i]&&dist[i]+dist1[i]<=lim) return false;

  rep (i,0,n) for (int o=head0[i];~o;o=e0[o].nxt) e0[o].val+=dist[i]-dist[e0[o].to];

  clr(in,0);
  hd=tl=0;
  rep (j,0,n) for (int o=head0[j];~o;o=e0[o].nxt) if (e0[o].val==0) ++in[e0[o].to];

  rep (j,0,n) if (in[j]==0) q[tl++]=j;
  clr(cur,0);
  while (hd<tl) {
    int u=q[hd++];
    cur[u]=1;
    for (int o=head0[u];~o;o=e0[o].nxt) {
      int v=e0[o].to;
      if (e0[o].val) continue;
      --in[v];
      if (in[v]==0) q[tl++]=v;
    }
  }
  rep (i,0,n) if (!cur[i]) q[tl++]=i;
  clr(f,0);
  f[0][0]=1;

  rep (i,0,k+1) {

    rep (j,0,tl) {
      int u=q[j],y=f[u][i];
      for (int o=head0[u];~o;o=e0[o].nxt) {
        int v=e0[o].to,c=e0[o].val+i;

        if (c<=k) f[v][c]=(f[v][c]+y)%p;
      }
    }
    // rep (j,0,n) {
    //   int u=j,y=f[u][i];
    //   for (int o=head0[u];~o;o=e0[o].nxt) {
    //     int v=e0[o].to,c=e0[o].val+i;
    //     if (c!=i&&c<=k) {
    //       f[v][c]=(f[v][c]+y)%p;
    //     }
    //   }
    // }
  }

  return true;
}

int main() {
  T=read();
  while (T--) {
    clock_t s=clock();
    n=read(),m=read(),k=read(),p=read();
    clr(head0,-1),tot0=0;
    clr(head1,-1),tot1=0;
    clr(head2,-1),tot2=0;
    rep (i,0,m) {
      int u=read()-1,v=read()-1,k=read();
      add(u,v,k,head0,e0,tot0);
      add(v,u,k,head1,e1,tot1);
      if (k==0) add(u,v,0,head2,e2,tot2);
    }
    dijkstra(vis,dist,head0,e0,0);
    dijkstra(vis1,dist1,head1,e1,n-1);

    if (!solve()) puts("-1");
    else {
      int ans=0;
      rep (i,0,k+1) ans+=f[n-1][i],ans%=p;
      printf("%d\n",ans);
    }
    clock_t t=clock();
  }
  return 0;
}
