#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef long long ll;

const int maxn=100010;
ll cost[maxn],fa[maxn];
int N,tag[maxn];

int main() {
    scanf("%d",&N);
    for (int i=1;i<=N;i++) scanf("%lld%lld",&fa[i],&cost[i]);
    memset(tag,-1,sizeof(tag));
    bool F=0;
    for (int i=1;i<=N;i++) {
        if(tag[i]!=-1) continue;
        int p=i;
        while(tag[p]==-1) {
            tag[p]=i;
            p=fa[p];
        }
        if(tag[p]==i) {
            int C=0;
            while(tag[p]!=-2) {
                tag[p]=-2;
                p=fa[p];
                C++;
            }
            if(C==N) F=1;
        }
    }
    ll ans=0ll;
    if(!F) {    
        for (int i=1;i<=N;i++) ans+=cost[i];
        static ll M1[maxn],M2[maxn];
        for (int i=1;i<=N;i++) {
            M1[fa[i]]=max(M1[fa[i]],cost[i]);
            if(tag[i]!=-2) M2[fa[i]]=max(M2[fa[i]],cost[i]);
        }
        for (int i=1;i<=N;i++) ans-=M1[i];
        for (int i=1;i<=N;i++) {
            if(tag[i]!=-2) continue;
            int p=i;
            ll M=10000000000ll;
            while(tag[p]==-2) {
                M=min(M,M1[p]-M2[p]);
                tag[p]=-3;
                p=fa[p];
            }
            ans+=M;
        }
    }
    printf("%lld\n",ans);
    return 0;
}