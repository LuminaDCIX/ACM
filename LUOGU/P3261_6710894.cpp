
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=(a);i<=(n);++i)
#define per(i,a,n) for (int i=(n);i>=(a);--i)
#define forg(u,o) for (int o=head[u];o;o=nxt[o])
typedef long long ll;
inline ll read() {
    int f=1,ch=getchar();
    ll x=0;
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
const int N=300000+5,M=N*2+5;
int n;
ll h[N];
int head[N],nxt[M],ver[M],a[M];
ll b[M];
int rt[N];
ll val[N];
inline void add(int u,int v,int _a,ll _b) {
    static int tot=0;
    ++tot;
    nxt[tot]=head[u];
    ver[tot]=v;
    a[tot]=_a;
    b[tot]=_b;
    head[u]=tot;
}
struct mh {
    int lc[N],rc[N],id[N],dist[N];
    ll m[N],p[N];
    inline int nw(int _id) {
        static int tot=0;
        ++tot;
        m[tot]=1;
        p[tot]=0;
        lc[tot]=rc[tot]=0;
        id[tot]=_id;
        return tot;
    }
    void set(int o,ll _m,ll _p) {
        if (o==0) return;
        val[id[o]]=_m*val[id[o]]+_p;
        m[o]=m[o]*_m;
        p[o]=_m*p[o]+_p;
    }
    void down(int x) {
        set(lc[x],m[x],p[x]);
        set(rc[x],m[x],p[x]);
        m[x]=1;
        p[x]=0;
    }
    int merge(int x,int y) {
        if (!x) return y;
        if (!y) return x;
        down(x);
        down(y);
        if (val[id[x]]>val[id[y]]) swap(x,y);
        rc[x]=merge(rc[x],y);
        if (dist[lc[x]]<dist[rc[x]]) swap(lc[x],rc[x]);
        dist[x]=dist[rc[x]]+1;
        return x;
    }
    int pop(int x) {
        down(x);
        return merge(lc[x],rc[x]);
    }
    ll top(int x) {
        return val[id[x]];
    }
} s;
int dep[N],ori[N];
int die[N],atk[N];
void dfs(int u) {
    forg (u,o) {
        dep[ver[o]]=dep[u]+1;
        dfs(ver[o]);
        if (a[o]==1) s.set(rt[ver[o]],b[o],0);
        else s.set(rt[ver[o]],1,b[o]);
        rt[u]=s.merge(rt[u],rt[ver[o]]);
    }
    while (s.top(rt[u])<h[u]) {
        ++die[u];
        atk[s.id[rt[u]]]=dep[ori[s.id[rt[u]]]]-dep[u];
        rt[u]=s.pop(rt[u]);
    }
}
int main() {
    // int size = 256 << 20; // 256MB
    // char *p = (char*)malloc(size) + size;
    // __asm__("movl %0, %%esp\n" :: "r"(p));
    n=read();
    val[0]=2e18;
    int m=read();
    rep (i,1,n) h[i]=read();
    rep (i,2,n) {
        int f=read(),_a=read();
        ll _b=read();
        add(f,i,_a,_b);
    }
    rep (i,1,m) {
        val[i]=read();
        int k=read();
        rt[k]=s.merge(rt[k],s.nw(i));
        ori[i]=k;
    }
    dfs(1);
    while (rt[1]) {
        int k=s.id[rt[1]];
        atk[k]=dep[ori[k]]+1;
        rt[1]=s.pop(rt[1]);
    }
    rep (i,1,n) printf("%d\n",die[i]);
    rep (i,1,m) printf("%d\n",atk[i]);
    return 0;
}
