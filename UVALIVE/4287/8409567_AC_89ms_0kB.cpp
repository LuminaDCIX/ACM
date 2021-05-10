#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <stack>
using namespace std;

int T,N,M,in[20005],out[20005],inn,outn;
int lowlink[20005],pre[20005],sccno[20005],dfs_clock,scc_cnt;
vector<int> G[20005];
stack<int> S;

void dfs(int u) {
    pre[u]=lowlink[u]=++dfs_clock;
    S.push(u);
    for(int i=0;i<G[u].size();i++) {
        int v=G[u][i];
        if(!pre[v]) dfs(v),lowlink[u]=min(lowlink[u],lowlink[v]);
        else if(!sccno[v]) lowlink[u]=min(lowlink[u],pre[v]);
    }
    if(lowlink[u]==pre[u]) {
        scc_cnt++;
        for(;;) {
            int x=S.top(); S.pop();
            sccno[x]=scc_cnt;
            if(x==u) break;
        }
    }
    return;
}

void find_scc() {
    scc_cnt=dfs_clock=0;
    memset(sccno,0,sizeof(sccno));
    memset(pre,0,sizeof(pre));
    for(int i=1;i<=N;i++) if(!pre[i]) dfs(i);
    //for(int i=1;i<=N;i++) printf("%d ",sccno[i]);
    memset(out,0,sizeof(out));
    memset(in,0,sizeof(in));
    inn=scc_cnt,outn=scc_cnt;
    for(int i=1;i<=N;i++)
      for(int j=0;j<G[i].size();j++) {
          int v=G[i][j];
          if(sccno[i]!=sccno[v]) {
              if(out[sccno[i]]==0) outn--,out[sccno[i]]=1;
              if(in[sccno[v]]==0) inn--,in[sccno[v]]=1;
          }
      }
    if(scc_cnt==1) printf("%d\n",0);
    else printf("%d\n",max(outn,inn));
}

void input() {
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;i++) G[i].clear();
    for(int i=1;i<=M;i++) {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
    }
}

int main() {
    scanf("%d",&T);
    while(T--) {
        input();
        find_scc();
    }
    return 0;
}