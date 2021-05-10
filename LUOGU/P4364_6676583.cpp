// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,n) for (int i=(a);i<=(n);++i)
#define per(i,a,n) for (int i=(n);i>=(a);--i)

inline int read() {
    int f=1,x=0;
    char ch=getchar();
    while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return f*x;
}

const int N=5e5+5;
const int MAX=(N<<2)+5;

int n,a[N];
map <int,int> pos;
map <int,int> cnt;

struct seg {
#define lc (o<<1)
#define rc (o<<1|1)

    int tag[MAX],mn[MAX];

    inline void settag(int o,int v) {
        tag[o]+=v,mn[o]+=v;
    }
  
    inline void down(int o) {
        if (tag[o]) settag(lc,tag[o]),settag(rc,tag[o]),tag[o]=0;
    }

    inline void up(int o) {
        mn[o]=min(mn[lc],mn[rc]);
    }
  
    void build(int o,int ll,int rr) {
        if (ll==rr) {
            mn[o]=ll;
            return;
        }
        int mid=(ll+rr)>>1;
        build(lc,ll,mid),build(rc,mid+1,rr);
        up(o);
    }

    int qry(int o,int ll,int rr,int k) {
        if (ll==rr) return mn[o]>=k?ll:ll+1;
        down(o);
        int mid=(ll+rr)>>1;
        if (mn[rc]>=k) return qry(lc,ll,mid,k);
        else return qry(rc,mid+1,rr,k);
        up(o);
    }

    void add(int o,int ll,int rr,int l,int r,int v) {
        if (ll!=rr) down(o);
        if (ll>=l&&rr<=r) {
            settag(o,v);
            return;
        }
        int mid=(ll+rr)>>1;
        if (l<=mid) add(lc,ll,mid,l,r,v);
        if (r>mid) add(rc,mid+1,rr,l,r,v);
        up(o);
    }
} s;

int fa[N],siz[N];
int chs[N];

int main() {
    n=read();
    double k;scanf("%lf",&k);
    rep (i,1,n) {
        a[i]=read();
    }
    sort(a+1,a+n+1);
    reverse(a+1,a+n+1);
    rep (i,1,n) {
        pos[a[i]]=i;
    }
    s.build(1,1,n);
    rep (i,1,n) {
        fa[i]=i/k;
        siz[i]=1;
    }
    per (i,1,n) {
        siz[fa[i]]+=siz[i];
    }
    rep (i,1,n) {
        // if (fa[i]) {
        //     s.add(1,1,n,chs[fa[i]],n,siz[i]);
        // }
        if (fa[i]&&fa[i]!=fa[i-1]) {
            s.add(1,1,n,chs[fa[i]],n,siz[fa[i]]-1);
        }
        int x=s.qry(1,1,n,siz[i]);
        x=pos[a[x]]-cnt[a[x]];
        ++cnt[a[x]];
        s.add(1,1,n,x,n,-siz[i]);
        chs[i]=x;
    }
    rep (i,1,n) {
        printf("%d ",a[chs[i]]);
    }
    return 0;
}
