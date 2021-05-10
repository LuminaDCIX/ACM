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
const int LOG=21;

int n,m;
int a[N];

int mnl[N],mnr[N];
LL suml[N],sumr[N];

int mn[N][LOG];
int mnid[N][LOG];
int log_2[N];

inline void init() {
    stack <pair <int,int> > stk;
    REP (i,1,n) {
        while (!stk.empty()&&stk.top().SE>=a[i]) {
            int id=stk.top().FI;
            mnr[id]=i;
            stk.pop();
        }
        stk.push(MP(i,a[i]));
    }
    while (!stk.empty()) {
        mnr[stk.top().FI]=n+1;
        stk.pop();
    }
    PER (i,1,n) {
        while (!stk.empty()&&stk.top().SE>=a[i]) {
            int id=stk.top().FI;
            mnl[id]=i;
            stk.pop();
        }
        stk.push(MP(i,a[i]));
    }
    while (!stk.empty()) {
        mnl[stk.top().FI]=0;
        stk.pop();
    }
    // REP (i,1,n) cerr<<mnl[i]<<" ";cerr<<endl;
    // REP (i,1,n) cerr<<mnr[i]<<" ";cerr<<endl;
    REP (i,1,n) suml[i]=suml[mnl[i]]+(LL)a[i]*(i-mnl[i]);
    PER (i,1,n) sumr[i]=sumr[mnr[i]]+(LL)a[i]*(mnr[i]-i);
    // REP (i,1,n) cerr<<sumr[i]<<" ";cerr<<endl;

    REP (i,1,n) {
        mnid[i][0]=i;
        mn[i][0]=a[i];
    }
    REP (i,1,LOG-1) REP (j,1,n) {
        mn[j][i]=mn[j][i-1];
        mnid[j][i]=mnid[j][i-1];
        int to=j+(1<<(i-1));
        if (to<=n&&mn[to][i-1]<mn[j][i]) {
            mn[j][i]=mn[to][i-1];
            mnid[j][i]=mnid[to][i-1];
        }
    }
    REP (i,2,n) log_2[i]=log_2[i>>1]+1;
}

inline int query(int l,int r) {
    int k=log_2[r-l+1];
    int lf=mnid[l][k];
    int rt=mnid[r-(1<<k)+1][k];
    if (a[lf]<a[rt]) return lf;
    else return rt;
}

LL ans[N];
int sizblk;

inline int blk(int x) {
    return x/sizblk+1;
}

struct Qry {
    int l,r,id;
    bool operator<(const Qry&rhs)const {
        if  (blk(l)==blk(rhs.l)) return r<rhs.r;
        else return l<rhs.l;
    }
};

Qry q[N];

int main() {
    n=RD();
    sizblk=sqrt(n);
    m=RD();
    REP (i,1,n) a[i]=RD();
    init();
    REP (i,1,m) {
        q[i].l=RD();
        q[i].r=RD();
        q[i].id=i;
    }
    sort(q+1,q+1+m);
    int l=1;
    int r=0;
    LL nw=0;
    REP (i,1,m) {
        while (r<q[i].r) {
            ++r;
            int k=query(l,r);
            nw+=(LL)(k-l+1)*a[k]+suml[r]-suml[k];
        }
        while (r>q[i].r) {
            int k=query(l,r);
            nw-=(LL)(k-l+1)*a[k]+suml[r]-suml[k];
            --r;
        }
        while (l<q[i].l) {
            int k=query(l,r);
            nw-=(LL)(r-k+1)*a[k]+sumr[l]-sumr[k];
            ++l;
        }
        while (l>q[i].l) {
            --l;
            int k=query(l,r);
            nw+=(LL)(r-k+1)*a[k]+sumr[l]-sumr[k];
        }
        ans[q[i].id]=nw;
    }
    REP (i,1,m) printf("%lld\n",ans[i]);
    return 0;
}
