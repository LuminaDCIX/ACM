// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define rep(i,a,n) for (int i=(a);i<=(n);++i)
#define per(i,a,n) for (int i=(n);i>=(a);--i)
#define forg(u,o) for (int o=head[u];o;o=nxt[o])
typedef long long ll;
typedef vector<int> vi;
inline int read() {
    int f=1,x=0,ch=getchar();
    while (!isdigit(ch)) {
        f=(ch=='-')?-1:1;
        ch=getchar();
    }
    while (isdigit(ch)) {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}
const int N=150000+5,M=N*2+5;
const int MAX=10000010;
int n,lev[N];
int head[N],ver[M],val[M],nxt[M];
inline void add(int u,int v,int w) {
    static int tot=0;
    ++tot;
    nxt[tot]=head[u];
    ver[tot]=v;
    val[tot]=w;
    head[u]=tot;
}
int dfn[N],dfs_cnt,pre[N],siz[N],son[N];
int top[N],fa[N];
ll faval[N];
ll dep[N],cnt[N],sumdep[N];
void dfs(int u) {
    siz[u]=1;
    forg (u,o) {
        int v=ver[o];
        if (v==fa[u]) continue;
        fa[v]=u;
        faval[v]=val[o];
        dep[v]=dep[u]+val[o];
        dfs(v);
        siz[u]+=siz[v];
        if (son[u]==0||siz[v]>siz[son[u]]) son[u]=v;
    }
}
ll edg[N];
void dfs2(int u,int anc) {
    dfn[u]=++dfs_cnt;
    pre[dfs_cnt]=u;
    edg[dfs_cnt]=faval[u];
    top[u]=anc;
    if (!son[u]) return;
    else dfs2(son[u],anc);
    forg (u,o) {
        int v=ver[o];
        if (v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}
struct sgt {
#define mid ((ll+rr)>>1)
    typedef long long LL;
    int lc[MAX],rc[MAX],tag[MAX];
    LL sum[MAX];
    int lst;
    void up(int o,int ll,int rr) {
        sum[o]=sum[lc[o]]+sum[rc[o]]+(edg[rr]-edg[ll-1])*tag[o];
    }
    int add(int o,int ll,int rr,int l,int r) {
        static int tot=0;
        int p=++tot;
        lc[p]=lc[o],rc[p]=rc[o],sum[p]=sum[o],tag[p]=tag[o];
        if (ll>=l&&rr<=r) {
            ++tag[p];
            up(p,ll,rr);
            return p;
        }
        if (l<=mid) lc[p]=add(lc[o],ll,mid,l,r);
        if (r>mid) rc[p]=add(rc[o],mid+1,rr,l,r);
        up(p,ll,rr);
        return p;
    }
    ll qry(int o,int ll,int rr,int l,int r,int old) {
        if (ll>=l&&rr<=r) return old*(edg[rr]-edg[ll-1])+sum[o];
        LL ans=0;
        if (l<=mid) ans+=qry(lc[o],ll,mid,l,r,old+tag[o]);
        if (r>mid) ans+=qry(rc[o],mid+1,rr,l,r,old+tag[o]);
        return ans;
    }
} s;
int q[N];
int rt[N];
bool cmp(int a,int b) {
    return lev[a]<lev[b];
}
int add(int p) {
    while (top[p]!=1) {
        s.lst=s.add(s.lst,1,n,dfn[top[p]],dfn[p]);
        p=fa[top[p]];
    }
    s.lst=s.add(s.lst,1,n,1,dfn[p]);
    return s.lst;
}
vi vv;
void init() {
    dfs(1);
    dfs2(1,1);
    rep (i,1,n) edg[i]+=edg[i-1];
    {
        vv.pb(0);
        rep (i,1,n) vv.pb(lev[i]);
        sort(vv.begin(),vv.end());
        vv.erase(unique(vv.begin(),vv.end()),vv.end());
        rep (i,1,n) lev[i]=lower_bound(vv.begin(),vv.end(),lev[i])-vv.begin();
    }
    rep (i,1,n) q[i]=i;
    sort(q+1,q+1+n,cmp);
    rep (i,1,n) {
        int x=q[i];
        rt[lev[x]]=add(x);
    }
    rep (i,1,n) cnt[lev[i]]++;
    rep (i,1,n) cnt[i]+=cnt[i-1];
    rep (i,1,n) sumdep[lev[i]]+=dep[i];
    rep (i,1,n) sumdep[i]+=sumdep[i-1];
}
inline ll calc(int x,int u) {
    if (x==0) return 0;
    ll ans=0;
    int nw=u;
    while (top[nw]!=1) {
        ans+=s.qry(rt[x],1,n,dfn[top[nw]],dfn[nw],0);
        nw=fa[top[nw]];
    }
    ans+=s.qry(rt[x],1,n,1,dfn[nw],0);
    ans*=-2;
    ans+=cnt[x]*dep[u];
    ans+=sumdep[x];
    return ans;
}
ll solve(int u,int L,int R) {
    int l=lower_bound(vv.begin(),vv.end(),L)-vv.begin();
    int r=upper_bound(vv.begin(),vv.end(),R)-vv.begin()-1;
    ll ans=calc(r,u)-calc(l-1,u);
    return ans;
}
int main() {
    // cerr<<(sizeof fa*18+sizeof s.lc*5)/1000/1000<<endl;
    n=read();
    int q=read();
    int A=read();
    rep (i,1,n) lev[i]=read()+1;
    rep (i,1,n-1) {
        int u=read(),v=read(),w=read();
        add(u,v,w);
        add(v,u,w);
    }
    init();
    ll ans=0;
    rep (i,1,q) {
        int u=read(),a=read(),b=read();
        int L=min((a+ans)%A,(b+ans)%A);
        int R=max((a+ans)%A,(b+ans)%A);
        ans=solve(u,L+1,R+1);
        printf("%lld\n",ans);
    }
    return 0;
}
