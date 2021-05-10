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

const int N=1e5+5;

const int MAX=4*N+5;

int n,m,a[N];

int op[N],ql[N],qr[N];

int bit[N];

int sum[MAX],tag[MAX];

void build(int o,int ll,int rr) {
    tag[o]=-1;
    if (ll==rr) {
        sum[o]=bit[ll];
        return;
    }
    int mid=(ll+rr)>>1;
    build(o*2,ll,mid);
    build(o*2+1,mid+1,rr);
    sum[o]=sum[o*2]+sum[o*2+1];
}

int q;

inline void settag(int o,int ll,int rr,int t) {
    tag[o]=t;
    sum[o]=(rr-ll+1)*t;
}

inline void psd(int o,int ll,int rr) {
    if (ll==rr) return ;
    if (tag[o]==-1) return;
    int mid=ll+rr>>1;
    settag(o*2,ll,mid,tag[o]);
    settag(o*2+1,mid+1,rr,tag[o]);
    tag[o]=-1;
}

int query(int o,int ll,int rr,int l,int r) {
    psd(o,ll,rr);
    if (ll>=l&&rr<=r) return sum[o];
    int mid=ll+rr>>1;
    int ans=0;
    if (l<=mid) ans+=query(o*2,ll,mid,l,r);
    if (r>mid) ans+=query(o*2+1,mid+1,rr,l,r);
    sum[o]=sum[o*2]+sum[o*2+1];
    return ans;
}

void cover(int o,int ll,int rr,int l,int r,int p) {
    psd(o,ll,rr);
    if (ll>=l&&rr<=r) {
        tag[o]=p;
        sum[o]=p*(rr-ll+1);
        return;
    }
    int mid=ll+rr>>1;
    if (l<=mid) cover(o*2,ll,mid,l,r,p);
    if (r>mid) cover(o*2+1,mid+1,rr,l,r,p);
    sum[o]=sum[o*2]+sum[o*2+1];
}

bool check(int x) {
    REP (i,1,n) bit[i]=(a[i]>=x);
    build(1,1,n);
    REP (i,1,m) {
        int l=ql[i];
        int r=qr[i];
        int ret=query(1,1,n,l,r);
        if (op[i]==0) ret=r-l+1-ret;
        if (l+ret-1>=l) cover(1,1,n,l,l+ret-1,0^op[i]);
        if (r>=l+ret) cover(1,1,n,l+ret,r,1^op[i]);
    }
    return query(1,1,n,q,q)>=1;
}

int main() {
    n=RD();
    m=RD();
    REP (i,1,n) a[i]=RD();
    REP (i,1,m) {
        op[i]=RD();
        ql[i]=RD();
        qr[i]=RD();
    }
    q=RD();
    int ans=-1;
    int low=1;
    int high=n;
    while (low<=high) {
        int mid=(low+high)>>1;
        if (check(mid)) {
            ans=mid;
            low=mid+1;
        } else high=mid-1;
    }
    printf("%d\n",ans);
    return 0;
}