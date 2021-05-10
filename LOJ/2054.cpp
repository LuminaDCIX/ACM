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

int n;
int q;

int fa[N];
int pre[N];

int getfa(int x) {
    return pre[x]==x?x:pre[x]=getfa(pre[x]);
}

int op[N],x[N];
bool tag[N];

int main() {
    n=RD();
    q=RD();
    pre[1]=1;
    REP (i,1,n-1) {
        int u=RD();
        int v=RD();
        fa[v]=u;
        pre[v]=u;
    }
    REP (i,1,q) {
        char o[2];
        scanf("%s",o);
        op[i]=(o[0]=='Q')?1:0;
        x[i]=RD();
    }
    REP (i,1,q) if (op[i]==0) {
        if (pre[x[i]]!=x[i]) tag[i]=1;
        pre[x[i]]=x[i];
    }
    PER (i,1,q) {
        if (op[i]==0) {
            if (tag[i]) pre[x[i]]=fa[x[i]];
        } else x[i]=getfa(x[i]);
    }
    REP (i,1,q) if (op[i]==1) printf("%d\n",x[i]);
    return 0;
}