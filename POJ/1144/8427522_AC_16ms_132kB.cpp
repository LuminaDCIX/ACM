#include <cstdio>
#include <cstring>
#include <algorithm>
#define mem(a,b) memset(a,b,sizeof(a));
using namespace std;
int pre[105],low[105],iscut[105],dfs_clocks;
int nxt[20010],head[105],to[20010],tot,N;

void add_edge(int from,int t) {
    to[++tot]=t; nxt[tot]=head[from]; head[from]=tot;
}

void input() {
    int tem=0;
    tot=0; mem(head,0);
    while(scanf("%d",&tem)&&tem) {
        int t;
        while(getchar()!='\n') {
            scanf("%d",&t);
            add_edge(tem,t);
            add_edge(t,tem);
        }
    }
    return;
}

int dfs(int u,int fa) {
    int lowu=pre[u]=++dfs_clocks;
    int child=0;
    for(int t=head[u];t;t=nxt[t]) {
        int v=to[t];
        if(!pre[v]) {
            child++;
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
            if(lowv>=pre[u]) iscut[u]=true;
        } else if(pre[v]<pre[u]&&v!=fa) {
            lowu=min(lowu,pre[v]);
        }
    }
    if(fa<0&&child<=1) iscut[u]=0;
    return low[u]=lowu;
}  

void solve() {
    mem(pre,0);
    mem(low,0);
    mem(iscut,0);
    dfs_clocks=0;
    for(int i=1;i<=N;i++) if(!pre[i]) dfs(i,-1);
    int sum=0;
    for(int i=1;i<=N;i++) if(iscut[i]) sum++;
    printf("%d\n",sum);
    return;
}
int main() {
    while(scanf("%d",&N)&&N) {
        input();
        solve();
    }
    return 0;
}