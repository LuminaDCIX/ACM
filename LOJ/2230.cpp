#include <bits/stdc++.h>
using namespace std;
namespace DEFINE {
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define SIZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define SET(x,v) memset(x,v,sizeof(x))
#define FORG(o,u) for (int o=head[u];o;o=nxt[o])
#define PER(i,a,n) for (int i=(n),_ed##i=(a);i>=_ed##i;--i)
#define REP(i,a,n) for (int i=(a),_ed##i=(n);i<=_ed##i;++i)
#define FOREACH(it,s) for (typeof__ it=(s).begin();it!=(s).end();++it)
    typedef double DB;
    typedef long long LL;
    typedef vector<int> VI;
    typedef pair<int,int> PII;
    const int P=1e9+7;
    const int INF=0x3f3f3f3f;
    const LL LLINF=0x3f3f3f3f3f3f3f3f;
    inline int ADD(int u,int v) {return (u+=v)>=P?u-P:u;}
    inline int SUB(int u,int v) {return (u-=v)<0?u+P:u;}
    inline int MUL(int u,int v) {return (LL)u*v%P;}
    inline int EXP(int a,LL x) {
        int ret=1;
        while (x) {
            if (x&1) ret=MUL(ret,a);
            a=MUL(a,a);
            x>>=1;
        }
        return ret;
    }
    inline LL RD() {
        LL x=0;int f=1,ch=getchar();
        for (;ch<'0'||ch>'9';ch=getchar()) f=(ch=='-')?-1:1;
        for (;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
        return f*x;
    }
    inline void FILEIO(string s) {
        freopen((s+"in").c_str(),"r",stdin);
        freopen((s+"out").c_str(),"w",stdout);
    }
}
using namespace DEFINE;

const int N=100000+5;

int n,m;

namespace lct {
    int siz[N],virsiz[N];
    int lc[N],rc[N],fa[N],rev[N];

    void getrev(int x) {
        swap(lc[x],rc[x]);
        rev[x]^=1;
    }
    
    void pushup(int x) {
        if (x!=0&&(lc[fa[x]]==x||rc[fa[x]]==x)) pushup(fa[x]);
        if (rev[x]) {
            getrev(lc[x]);
            getrev(rc[x]);
            rev[x]=0;
        }
    }
    
    void init() {
        REP (i,1,n) siz[i]=1;
    }

    inline void update(int x) {
        siz[x]=siz[lc[x]]+siz[rc[x]]+virsiz[x]+1;
    }

    void rot(int x) {
        int y=fa[x];
        int z=fa[y];
        int b=0;
        if (lc[y]==x) {
            b=rc[x];
            rc[x]=y;
            lc[y]=b;
        } else {
            b=lc[x];
            lc[x]=y;
            rc[y]=b;
        }
        fa[b]=y;
        fa[y]=x;
        if (lc[z]==y) lc[z]=x;
        else if (rc[z]==y) rc[z]=x;
        fa[x]=z;
        update(y);
    }

    void splay(int x) {
        pushup(x);
        while (lc[fa[x]]==x||rc[fa[x]]==x) {
            int y=fa[x];
            int z=fa[y];
            if ((lc[z]==y&&lc[y]==x)||(rc[z]==y&&rc[y]==x)) rot(y);
            rot(x);
        }
        update(x);
    }

    void access(int x) {
        int y=0;
        while (x!=0) {
            splay(x);
            virsiz[x]-=siz[y];
            virsiz[x]+=siz[rc[x]];
            rc[x]=y;
            y=x;
            x=fa[x];
        }
    }

    void make_root(int x) {
        access(x);
        splay(x);
        getrev(x);
    }

    void link(int u,int v) {
        make_root(u);
        access(v);
        splay(v);
        fa[u]=v;
        virsiz[v]+=siz[u];
    }

    LL query(int u,int v) {
        make_root(v);
        access(u);
        LL ans=virsiz[u]+1;
        make_root(u);
        access(v);
        ans*=(LL)(virsiz[v]+1);
        return ans;
    }
}

int main() {
    n=RD();
    m=RD();
    lct::init();
    REP (i,1,m) {
        char o[2];
        scanf("%s",o);
        if (o[0]=='A') {
            int u=RD();
            int v=RD();
            lct::link(u,v);
        } else {
            int u=RD();
            int v=RD();
            printf("%lld\n",lct::query(u,v));
        }
    }
    return 0;
}