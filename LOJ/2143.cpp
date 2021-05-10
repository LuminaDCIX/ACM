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
    int P=1e9+7;
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

const int K=50+5;

int n,k,r;

struct mat {
    int s[K][K];
    mat() {SET(s,0);}
    mat(int o) {
        SET(s,0);
        REP (i,0,k-1) s[i][i]=1;
    }

    mat operator*(const mat&b)const {
        mat c=mat();
        REP (l,0,k-1) REP (i,0,k-1) REP (j,0,k-1) c.s[i][j]=ADD(c.s[i][j],MUL(s[i][l],b.s[l][j]));
        return c;
    }
};

int C[K][K];

mat MatEXP(mat t,int x) {
    mat ret=mat(1);
    while (x) {
        if (x&1) ret=ret*t;
        t=t*t;
        x>>=1;
    }
    return ret;
}

int main() {
    n=read();
    P=read();
    k=read();
    r=read();
    C[0][0]=1;
    REP (i,1,k) {
        C[i][0]=1;
        REP (j,1,k) C[i][j]=ADD(C[i-1][j-1],C[i-1][j]);
    }
    
    mat t=mat();
    REP (i,0,k-1) REP (j,0,k) {
        // cerr<<((i-j)%k+k)%k<<" "<<i<<" "<<C[k][j]<<endl;
        t.s[((i-j)%k+k)%k][i]+=C[k][j];
    }
    // REP (i,0,k-1) {REP (j,0,k-1) cerr<<t.s[i][j]<<" ";cerr<<endl;}
    t=MatEXP(t,n);
    // REP (i,0,k-1) cerr<<t.s[0][i]<<endl;
    printf("%d\n",t.s[0][r]);
    return 0;
}