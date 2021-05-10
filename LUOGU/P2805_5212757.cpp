#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <cassert>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define LB lower_bound
#define UB upper_bound
#define SIZ(x) ((int)x.size())
#define ALL(v) v.begin(),v.end()
#define SET(x,v) memset(x,v,sizeof(x))
#define REP(i,a,n) for (int i=(a);i<(n);++i)
#define PER(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define FORG(i,x,e) for (int o=x;~o;o=e[o].nxt)
#define FOREACH(e,x) for (__typeof(x.begin()) e=x.begin();e!=x.end();++e)
typedef long long ll;
typedef double db;
typedef map<int,int> mii;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

int read() {
  int f=1,x=0;char ch=getchar();
  while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
  while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
  return f*x;
}

const int N=20+5;
const int M=30+5;
const int MAX=20*30+5;
const int MAXM=MAX*5500;
const int S=MAX-2;
const int T=MAX-1;
const int inf=1e9;

int head[MAX];
int cur[MAX];
int tot;

struct edge {
  int nxt;
  int to;
  int cap;
};

edge e[MAXM];

vi g[MAX];

int del[MAX];

void add(int u,int v,int cap) {
  e[tot].to=v,e[tot].nxt=head[u],e[tot].cap=cap,head[u]=tot++;
  e[tot].to=u,e[tot].nxt=head[v],e[tot].cap=0,head[v]=tot++;
  g[u].PB(v);
}

int dist[MAX];

int dfs(int u,int f) {
  if (u==T||f==0) return f;
  int sum=0;
  for (int &o=cur[u];~o;o=e[o].nxt) {
    int v=e[o].to;
    if (del[v]==1) continue;
    int s=0;
    if (dist[v]==dist[u]+1&&e[o].cap&&(s=dfs(v,min(f,e[o].cap)))>0) {
      e[o].cap-=s,e[o^1].cap+=s;
      f-=s,sum+=s;
      if (!f) break;
    }
  }
  return sum;
}

int vis[MAX];

bool bfs() {
  queue <int> que;
  que.push(S);
  SET(vis,0);
  vis[S]=1;
  while (!que.empty()) {
    int u=que.front();
    que.pop();
    FORG (o,head[u],e) {
      int v=e[o].to;
      if (del[v]==1) continue;
      if (!vis[v]&&e[o].cap) dist[v]=dist[u]+1,vis[v]=1,que.push(v);
    }
  }
  return vis[T];
}

int dinic() {
  int ans=0;
  while (bfs()) {
    REP (i,0,T+1) cur[i]=head[i];
    ans+=dfs(S,inf);
  }
  return ans;
}

int n,m;

int val[N][M];

int id(int i,int j) {
  return i*m+j;
}

int low[MAX],dfn[MAX];
int stk[MAX],top,instk[MAX];
int dfs_cnt;


int ans=0;

void tarjan(int u) {
  low[u]=dfn[u]=++dfs_cnt;
  stk[top++]=u,instk[u]=1;
  int siz=SIZ(g[u]);
  REP (i,0,siz) {
    int v=g[u][i];
    if (!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
    else if (instk[v]) low[u]=min(low[u],dfn[v]);
  }
  if (low[u]==dfn[u]) {
    int cnt=0;
    while (true) {
      int y=stk[--top];
      ++cnt;
      instk[y]=0;
      if (cnt==1&&y==u) break;
      if (y!=T&&y!=S) {
        int i=y/m,j=y%m;
        del[y]=1;
        if (val[i][j]>0) ans-=val[i][j];
      }
      if (y==u) break;
    }
  }
}

bool dp(int u) {
  if (del[u]!=-1) return del[u];
  int siz=SIZ(g[u]);
  del[u]=0;
  REP (i,0,siz) {
    int v=g[u][i];
    del[u]|=dp(v);
  }
  if (u!=S&&del[u]) {
    int i=u/m,j=u%m;
    if (val[i][j]>0) ans-=val[i][j];
  }
  return del[u];
}

int main() {
  n=read(),m=read();
  SET(head,-1);
  REP (i,0,n) REP (j,0,m) {
    val[i][j]=read();
    int cnt=read();
    int now=id(i,j);
    REP (k,0,cnt) {
      int x=read(),y=read();
      add(id(x,y),now,inf);
    }
    if (val[i][j]>0) ans+=val[i][j],add(S,now,val[i][j]);
    else add(now,T,-val[i][j]);
  }
  REP (i,0,n) REP (j,0,m-1) {
    add(id(i,j),id(i,j+1),inf);
  }
  SET(del,-1);
  tarjan(S);
  dp(S);
  del[S]=0;
  ans-=dinic();
  printf("%d\n",ans);
  return 0;
}
