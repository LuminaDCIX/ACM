#include <cstdio>
#include <vector>
#include <cstdlib>
#include <stack>
#include <algorithm>
#include <cstring>
using namespace std;

int N,P,R,cost[3010],sccno[3010],pre[3010],lowlink[3010],dfs_clock,scc_cnt;
int mincost[3010],ans,vis[3010],ok,in[3010];
vector<int> G[3010],scc[3010];
stack<int> S;

void input() {
    scanf("%d%d",&N,&P);
    memset(cost,0x3f3f,sizeof(cost));
    int a,c;
    for(int i=1;i<=P;i++) {scanf("%d%d",&a,&c); cost[a]=c; vis[a]=1;}
    scanf("%d",&R);
    for(int i=1;i<=R;i++) {
        scanf("%d%d",&a,&c);
        G[a].push_back(c);
        if(cost[a]==1) vis[c]=1;
    }
}

void dfs(int u) {
    lowlink[u]=pre[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();i++) {
        int v=G[u][i];
        bool c=1;
        if(!pre[v]) dfs(v),lowlink[u]=min(lowlink[u],lowlink[v]);
        else if(!sccno[v]) lowlink[u]=min(pre[v],lowlink[u]);
    }
    if(pre[u]==lowlink[u]) {
        scc_cnt++;
        for(;;) {
            int x=S.top(); S.pop();
            sccno[x]=scc_cnt;
            scc[scc_cnt].push_back(x);
            mincost[sccno[x]]=min(mincost[sccno[x]],cost[x]);
            if(x==u) {break;}
        }
    }
    return;
}

void find_scc() {
    int c=0;
    for(int i=1;i<=N;i++) if(!pre[i]) dfs(i);
}

void dfs2(int u,int check) {
    vis[u]=check;
    for(int i=0;i<G[u].size();i++) {
        int v=G[u][i];
        if(vis[v]) continue;
        dfs2(v,check);
    }
}

bool check() {
    for(int i=1;i<=N;i++) if(cost[i]!=0x3f3f3f3f) dfs2(i,1);
    for(int i=1;i<=N;i++) if(vis[i]==0) {ok=1;return true;}
    return false;
}

void solve() {
    if(check()) return;
    memset(mincost,0x3f3f,sizeof(mincost));
    find_scc();
}

void output() {
    int mn=3010;
    if(scc_cnt==1) {
        printf("YES\n%d\n",mincost[1]);
        return;
    }
    for(int i=1;i<=N;i++) {
        if(vis[i]==0) {ok=1,mn=i;break;}
        for(int j=0;j<G[i].size();j++) {
            int v=G[i][j];
            if(sccno[i]!=sccno[v]) in[sccno[v]]=1;
        }
    }
    if(ok) {
        printf("NO\n");
        printf("%d\n",mn);
    } else {
        for(int i=1;i<=scc_cnt;i++) if(in[i]==0) ans+=mincost[i];
        printf("YES\n");
        printf("%d\n",ans);
    }
}

int main() {
    input();
    solve();
    output();
    return 0;
}