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
    typedef long double DB;
    typedef long long LL;
    typedef vector<int> VI;
    typedef pair<int,int> PII;
    // const int P=1e9+7;
    const int INF=0x3f3f3f3f;
    const LL LLINF=0x3f3f3f3f3f3f3f3f;
    // inline int ADD(int u,int v) {return (u+=v)>=P?u-P:u;}
    // inline int SUB(int u,int v) {return (u-=v)<0?u+P:u;}
    // inline int MUL(int u,int v) {return (LL)u*v%P;}
    inline int EXP(int a,LL x,int P) {
        int ret=1;
        while (x) {
            if (x&1) ret=(LL)ret*a%P;
            a=(LL)a*a%P;
            x>>=1;
        }
        return ret;
    }
    inline LL read() {
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

const int N=50000+5;
const int MAX=N*4+5;

int cnt[N];
int n,m,c;
int a[N];
int P,s;

map<int,int> phi;
map<int,int> id;
int fac[25][700005];
int fac2[25][700005];
bool ok[25][700005];
bool ok2[25][700005];

int calcphi(int x) {
    int ret=x;
    for (int i=2;i*i<=x;++i) {
        if (x%i==0) {
            ret-=ret/i;
            while (x%i==0) x/=i;
        }
    }
    if (x>1) ret-=ret/x;
    return ret;
}

void sieve() {
    int nw=P;
    while (nw!=1) {
        id[nw]=++s;
        fac[s][0]=1;
        phi[nw]=calcphi(nw);
        REP (i,1,65535) {
            if (ok[s][i-1]||(LL)c*fac[s][i-1]>=nw) ok[s][i]=1;
            fac[s][i]=(LL)c*fac[s][i-1]%nw;
        }
        fac2[s][0]=1;
        if (ok[s][65535]||(LL)fac[s][65535]*c>=nw) ok2[s][1]=1;
        fac2[s][1]=(LL)fac[s][65535]*c%nw;
        REP (i,2,65535) {
            if (ok2[s][i-1]||(LL)fac2[s][i-1]*fac2[s][1]>=nw) ok2[s][i]=1;
            fac2[s][i]=(LL)fac2[s][i-1]*fac2[s][1]%nw;
        }
        nw=phi[nw];
    }
    id[1]=++s;
    phi[1]=1;
}
int EXP2(int x,int P) {
    if (P==1) return 0;
    return (LL)fac2[id[P]][x>>16]*fac[id[P]][x&65535]%P;
}

bool get(int c,int lim,int &r) {
    if (lim==1) return true;
    lim=id[lim];
    if (ok2[lim][c>>16]||ok[lim][c&65535]) return true;
    r=fac2[lim][c>>16]*fac[lim][c&65535];
    return false;
}

bool check(int x,int cnt,int lim) {
    int nw=x;
    if (x>=lim) return false;
    REP (i,1,cnt) if (get(nw,lim,nw)) return false;
    if (nw>=lim) return false;
    return true;
}

int calc(int x,int cnt,int P) {
    if (cnt==0) return x%P;
    if (!check(x,cnt-1,phi[P])) {
        int ret=calc(x,cnt-1,phi[P]);
        return EXP2(ret+phi[P],P);
    } else {
        int ret=calc(x,cnt-1,phi[P]);
        return EXP2(ret,P);
    }
}

int sum[MAX],lzy[MAX];
bool tag[MAX];

void build(int o,int ll,int rr) {
    if (ll==rr) {
        sum[o]=a[ll];
        return;
    }
    int mid=ll+rr>>1;
    build(o*2,ll,mid);
    build(o*2+1,mid+1,rr);
    sum[o]=(sum[o*2]+sum[o*2+1])%P;
}

void add(int o,int ll,int rr,int l,int r) {
    if (tag[o]) return;
    if (ll==rr) {
        ++cnt[ll];
        sum[o]=calc(a[ll],cnt[ll],P);
        if (cnt[ll]>=s+1) tag[o]=1;//,cerr<<"hi"<<endl;
        return;
    }
    int mid=ll+rr>>1;
    if (l<=mid) add(o*2,ll,mid,l,r);
    if (r>mid) add(o*2+1,mid+1,rr,l,r);
    tag[o]=(tag[o*2]&tag[o*2+1]);
    sum[o]=(sum[o*2]+sum[o*2+1])%P;
}

int query(int o,int ll,int rr,int l,int r) {
    int mid=ll+rr>>1;
    if (ll>=l&&rr<=r) return sum[o];
    int ans=0;
    if (l<=mid) ans+=query(o*2,ll,mid,l,r);
    if (r>mid) ans+=query(o*2+1,mid+1,rr,l,r);
    return ans%P;
}

int main() {
    n=read();
    m=read();
    P=read();
    c=read();
    REP (i,1,n) a[i]=read();
    sieve();
    build(1,1,n);
    while (m--) {
        int op=read();
        if (op==1) {
            int l=read(),r=read();
            printf("%d\n",query(1,1,n,l,r));
        } else {
            int l=read();
            int r=read();
            add(1,1,n,l,r);
        }
    }
    return 0;
}
