// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define fi first
#define se second
#define rep(i,a,n) for (int i=(a);i<=(n);++i)
#define per(i,a,n) for (int i=(n);i>=(a);--i)
#define forg(u,o) for (int o=head[u];o;o=nxt[o])
typedef long long ll;
typedef pair<ll,ll> pii;
inline int read()
{
    int f=1,x=0,ch=getchar();
    while (!isdigit(ch)) f=(ch=='-')?-1:1,ch=getchar();
    while (isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return f*x;
}
const int N=3e5+5,M=N*2;
int n;
int head[N],nxt[M],ver[M],val[M];
void add(int u,int v,int w)
{
    static int tot=0;
    ++tot;
    nxt[tot]=head[u],ver[tot]=v,val[tot]=w,head[u]=tot;
}
int stk[N],top;
int pre[N];
void dfs(int u,int fa)
{
    pre[u]=fa;
    stk[++top]=u;
    forg (u,o) if (ver[o]!=fa) dfs(ver[o],u);
}
pii add(pii a,pii b,ll c,ll d)
{
    return mp(a.fi+b.fi+c,a.se+b.se+d);
}
pii dp[N][3];
pii work(ll &V) {
    pii ret=mp(-1e18,-1e18);
    per (i,1,n) {
        int u=stk[i];
        dp[u][0]=mp(-V,1);
        dp[u][1]=mp(-1e18,0);
        dp[u][2]=mp(0,0);
        static pii p[5];
        forg (u,o) {
            rep (i,0,2) p[i]=dp[u][i];
            int v=ver[o];
            if (v==pre[u]) continue;
            rep (a,0,2) rep (b,0,2) {
                p[a]=max(p[a],add(dp[u][a],dp[v][b],0,0));
                if (a<2&&b<2) p[a+1]=max(p[a+1],add(dp[u][a],dp[v][b],val[o]+V,-1));
            }
            rep (i,0,2) dp[u][i]=p[i];
        }
    }
    rep (i,0,2) ret=max(ret,dp[1][i]);
    return ret;
}
int main()
{
    n=read();
    int k=read()+1;
    rep (i,1,n-1) {
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
    }
    dfs(1,0);
    ll l=-1e12,r=1e12,ans=0;
    while (l<=r) {
        ll mid=(l+r)>>1;
        pii ret=work(mid);
        if (ret.se>=k) l=mid+1,ans=mid;
        else r=mid-1;
    }
    pii ret=work(ans);
    printf("%lld\n",ret.fi+ans*k);
    return 0;
}
