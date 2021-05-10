#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cmath>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#define y0 y0z
#define y1 y1z
#define yn ynz
#define j0 j0z
#define j1 j1z
#define jn jnz
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define siz(x) ((int)(x).size())
#define fil(a,b) memset((a),(b),sizeof(a))
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
#ifdef MiracleEEEE
#define debug(...) fprintf(stderr,__VA_ARGS__)
#else 
#define debug(...) 
#endif
using namespace std;

typedef long long ll;
typedef vector <int> vi;
typedef pair <int,int> pii;

char xB[1<<15],*xS=xB,*xT=xB;  
#define getc() (xS==xT&&(xT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xT)?0:*xS++)  
inline ll read() {
  ll x=0;
  int f=1;
  char ch=getc();
  for (;ch<'0'||ch>'9';f=(ch=='-')?-1:1,ch=getc());
  for (;ch>='0'&&ch<='9';x=x*10+ch-'0',ch=getc());
  return f*x;
}

inline void timer() {
#ifdef MiracleEEEE
  clock_t s_=clock();
  if (s_/1000<=5) {
  fprintf(stderr,"time=%ldmicrosecond\n",s_);
} else {
  fprintf(stderr,"time=%ldmillisecond\n",s_/1000);
}
#endif
}

inline void file(string name) {
  freopen((name+".in").c_str(),"r",stdin);
  freopen((name+".out").c_str(),"w",stdout);
}

//head


const int N=100000+5;

int n;
int m;

int siz[N];


int scc_cnt;



struct graph {
  int tot;
  int head[N];

  struct edge {
    int nxt;
    int to;
    int val;
  };

  edge e[N<<1];

  inline void add(int u,int v,int w) {
    e[tot].to=v;
    e[tot].nxt=head[u];
    e[tot].val=w;
    head[u]=tot++;
  }

  inline void build() {
    rep (i,0,m) {
      int w=read();
      int u=read();
      int v=read();
      if (w==1) {
        add(u,v,0);
        add(v,u,0);
        // debug("%d<-0->%d\n",u,v);
      } else if (w==2) {
        add(v,u,-1);
        // debug("%d--1>%d\n",v,u);
      } else if (w==3) {
        add(u,v,0);
        // debug("%d-0>%d\n",u,v);
      } else if (w==4) {
        add(u,v,-1);
        // debug("%d--1>%d\n",u,v);
      } else {
        add(v,u,0);
        // debug("%d-0>%d\n",v,u);
      }
    }
  }


  int que[N];
  int in[N];
  int f[N];
  
  inline ll toposort() {
    int h=0;
    int t=0;
    rep (i,1,scc_cnt+1) {
      if (!in[i]) {
        que[t++]=i;
      }
    }
    while (h!=t) {
      int u=que[h++];
      for (int o=head[u];~o;o=e[o].nxt) {
        int v=e[o].to;
        --in[v];
        if (!in[v]) {
          que[t++]=v;
        }
      }
    }
    per (i,0,scc_cnt) {
      int u=que[i];

      // debug("u=%d\n",u);
      if (head[u]==-1) {
        f[u]=1;
        continue;
      }
      for (int o=head[u];~o;o=e[o].nxt) {
        int v=e[o].to;
        f[u]=max(f[u],f[v]+e[o].val);
      }
    }
    ll ret=0;
    rep (i,1,scc_cnt+1) {
      ret+=(ll)siz[i]*f[i];
    }
    return ret;
  }
  
  inline void init() {
    tot=0;
    fil(head,-1);
  }

};

graph g1;
graph g2;

int low[N];
int dfn[N];
int vis[N];
int dfs_cnt;
int top;
int stk[N];

int scc[N];


void dfs(int u) {
  vis[u]=1;
  stk[top++]=u;
  dfn[u]=++dfs_cnt;
  low[u]=dfs_cnt;

  for (int o=g1.head[u];~o;o=g1.e[o].nxt) {
    int v=g1.e[o].to;
    if (!dfn[v]) {
      dfs(v);
      low[u]=min(low[u],low[v]);
    } else if (vis[v]) {
      low[u]=min(low[u],dfn[v]);
    }
  }

  if (low[u]==dfn[u]) {
    ++scc_cnt;
    int y;
    do {
      y=stk[--top];
      vis[y]=0;
      scc[y]=scc_cnt;
      ++siz[scc_cnt];
    } while (y!=u);
  }
}

int main() {
  n=read();
  m=read();
  g1.init();
  g1.build();
  rep (i,1,n+1) {
    if (!dfn[i]) {
      dfs(i);
    }
  }
  g2.init();
  rep (u,1,n+1) {
    for (int o=g1.head[u];~o;o=g1.e[o].nxt) {
      int v=g1.e[o].to;
      if (scc[u]==scc[v]&&g1.e[o].val!=0) {
        puts("-1");
        return 0;
      }
      if (scc[u]!=scc[v]) {
        g2.add(scc[u],scc[v],-g1.e[o].val);
        ++g2.in[scc[v]];
      }
    }
  }
  printf("%lld\n",g2.toposort());
  return 0;
}
