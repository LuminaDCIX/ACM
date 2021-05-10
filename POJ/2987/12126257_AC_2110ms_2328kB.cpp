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

using std::min;
using std::max;
using std::sort;
using std::unique;
using std::queue;

const int N=5000+5;
const int M=60000+5;
const ll BASE=10000;
const int MAX=5000+5;
const int MAXM=2*(60000+5000)+1005;
const ll inf=1e18;
const int S=MAX-2;
const int T=MAX-1;

int head[MAX];
int cur[MAX];
int tot;

struct edge {
  int nxt,to;
  ll cap;
};

edge e[MAXM];

void add(int u,int v,ll cap) {
  e[tot].to=v,e[tot].nxt=head[u],e[tot].cap=cap,head[u]=tot++;
  e[tot].to=u,e[tot].nxt=head[v],e[tot].cap=0,head[v]=tot++;
}

int dist[MAX];
int vis[MAX];

int n,m;

ll dfs(int u,ll f) {
  if (u==T||f==0) return f;
  ll sum=0;
  for (int &o=cur[u];~o;o=e[o].nxt) {
    int v=e[o].to;
    ll s=0;
    if (dist[v]==dist[u]+1&&e[o].cap&&(s=dfs(v,min(f,e[o].cap)))>0) {
      e[o].cap-=s,e[o^1].cap+=s;
      sum+=s,f-=s;
      if (!f) break;
    }
  }
  return sum;
}


bool bfs() {
  SET(vis,0);
  vis[S]=1;
  queue <int> que;
  que.push(S);
  while (!que.empty()) {
    int u=que.front();que.pop();
    FORG (u,head[u],e) {
      int v=e[o].to;
      if (!vis[v]&&e[o].cap) dist[v]=dist[u]+1,vis[v]=1,que.push(v);
    }
  }
  return vis[T];
}

ll dinic() {
  ll ans=0;
  while (bfs()) {
    REP (i,0,T+1) cur[i]=head[i];
    ans+=dfs(S,inf);
  }
  return ans;
}

ll val[N];

int main() {

  n=read(),m=read();
  SET(head,-1);
  REP (i,0,n) val[i]=read();
  ll ans=0;
  int num=0;
  REP (i,0,n) {
    if (val[i]>0) ans+=val[i]*BASE-1,add(S,i,BASE*val[i]-1);
    else add(i,T,-BASE*val[i]+1);
  }
  REP (i,0,m) {
    int u=read()-1,v=read()-1;
    add(u,v,inf);
  }
  ans-=dinic();
  int x1=0;
  while (ans%BASE) ++ans,++x1;
  ll x0=ans/BASE;
  printf("%d %lld\n",x1,x0);
  return 0;
}

