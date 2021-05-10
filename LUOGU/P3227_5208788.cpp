#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N=40+5;
const int MAX=45*40*40+5;
const int MAXM=2*(40*40+4*40*40*40+40*40)+1000;
const int S=MAX-2;
const int T=MAX-1;
const int inf=1e9;

int read() {
  int f=1;
  int x=0;
  char ch=getchar();
  while (ch<'0'||ch>'9') {
    f=(ch=='-')?-1:1;
    ch=getchar();
  }
  while (ch>='0'&&ch<='9') {
    x=x*10+ch-'0';
    ch=getchar();
  }
  return f*x;
}

int p;
int q;
int r;
int d;
int val[N][N][N];

int id(int x,int y,int z) {
  return z*p*q+y*p+x;
}

int head[MAX];
int cur[MAX];
int tot;

struct edge {
  int nxt;
  int to;
  int cap;
};

edge e[MAXM];

int dx[]={0,0,1,-1};
int dy[]={-1,1,0,0};

void add(int u,int v,int cap) {
  e[tot].to=v;
  e[tot].nxt=head[u];
  e[tot].cap=cap;
  head[u]=tot++;
  e[tot].to=u;
  e[tot].nxt=head[v];
  e[tot].cap=0;
  head[v]=tot++;
}

int dist[MAX];
bool vis[MAX];

int dfs(int u,int f) {
  if (u==T||f==0) {
    return f;
  }
  int sum=0;
  for (int &o=cur[u],s;~o;o=e[o].nxt) {
    int v=e[o].to;
    if (dist[v]==dist[u]+1&&e[o].cap!=0&&(s=dfs(v,min(f,e[o].cap)))>0) {
      e[o].cap-=s;
      e[o^1].cap+=s;
      sum+=s;
      f-=s;
      if (f==0) {
        break;
      }
    }
  }
  return sum;
}

bool bfs(int S) {
  queue <int> que;
  que.push(S);
  memset(vis,0,sizeof(vis));
  vis[S]=1;
  while (!que.empty()) {
    int u=que.front();
    que.pop();
    for (int o=head[u];~o;o=e[o].nxt) {
      int v=e[o].to;
      if (!vis[v]&&e[o].cap) {
        dist[v]=dist[u]+1;
        vis[v]=1;
        que.push(v);
      }
    }
  }
  return vis[T];
}

int dinic(int S,int T) {
  int ret=0;
  while (bfs(S)) {
    for (int i=0;i<=T;++i) {
      cur[i]=head[i];
    }
    ret+=dfs(S,inf);
  }
  return ret;
}

int main() {
  memset(head,-1,sizeof(head));
  scanf("%d%d%d%d",&p,&q,&r,&d);
  for (int k=0;k<r;++k) {
    for (int i=0;i<p;++i) {
      for (int j=0;j<q;++j) {
        val[i][j][k]=read();
      }
    }
  }
  for (int i=0;i<p;++i) {
    for (int j=0;j<q;++j) {
      for (int k=0;k<r;++k) {
        int u=id(i,j,k);
        int v=id(i,j,k+1);
        add(u,v,val[i][j][k]);
      }
    }
  }
  for (int i=0;i<p;++i) {
    for (int j=0;j<q;++j) {
      for (int k=0;k<r;++k) {
        int now=id(i,j,k);
        int nxt=id(i,j,k+1);
        int l0=max(k-d,0);
        int l1=min(k+1+d,r);
        for (int o=0;o<4;++o) {
          int x=i+dx[o];
          int y=j+dy[o];
          if (x<0||x>=p||y<0||y>=q) {
            continue;
          }
          int v0=id(x,y,l0);
          int v1=id(x,y,l1);
          add(now,v0,inf);
          add(v1,nxt,inf);
        }
      }
    }
  }
  for (int i=0;i<p;++i) {
    for (int j=0;j<q;++j) {
      add(S,id(i,j,0),inf);
      add(id(i,j,r),T,inf);
    }
  }
  int ans=dinic(S,T);
  printf("%d\n",ans);
  return 0;
}
