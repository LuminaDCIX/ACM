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

const int N=4e5+5;

int n,k;

char s[N];
int str[N];
int sa[N],rk[N],c[N],xx[N],yy[N];
int ht[N];

int endpos[N];

void build(int len) {
    str[len++]=0;
    int m=N-2;
    int *x=xx;
    int *y=yy;
    REP (i,0,len-1) {
        x[i]=str[i];
        ++c[x[i]];
    }
    REP (i,1,m) c[i]+=c[i-1];
    REP (i,0,len-1) sa[--c[x[i]]]=i;
    for (int k=1;k<=len;k<<=1) {
        int p=0;
        REP (i,len-k,len-1) y[p++]=i;
        REP (i,0,len-1) if (sa[i]>=k) y[p++]=sa[i]-k;
        REP (i,0,m) c[i]=0;
        REP (i,0,len-1) ++c[x[i]];
        REP (i,1,m) c[i]+=c[i-1];
        PER (i,0,len-1) sa[--c[x[y[i]]]]=y[i];
        p=1;
        swap(x,y);
        x[sa[0]]=0;
        REP (j,1,len-1) {
            if (y[sa[j]]==y[sa[j-1]]&&y[sa[j]+k]==y[sa[j-1]+k]) x[sa[j]]=p-1;
            else x[sa[j]]=p++;
        }
        m=p;
        if (m>=len) break;
    }
    --len;
    // REP (i,1,len) ++sa[i];
    REP (i,0,len-1) sa[i]=sa[i+1];
    REP (i,0,len-1) rk[sa[i]]=i;
    int k=0;
    REP (i,0,len-1) {
        if (k) --k;
        if (rk[i]==0) {
            k=0;
            continue;
        }
        int j=sa[rk[i]-1];
        while (str[j+k]==str[i+k]) ++k;
        ht[rk[i]]=k;
    }
}

int bel[N];


int lth[N];

VI v[N];
map<int,int> mp[N];
LL tag[N],ans[N];
int fa[N];
LL nw;

int findfa(int x) {
    return fa[x]==x?x:fa[x]=findfa(fa[x]);
}

set<int> ss;
LL alltag;

void merge(int x,int y,int len) {
    x=findfa(x);
    y=findfa(y);
    if (SIZ(mp[x])>SIZ(mp[y])) swap(x,y);
    
    LL sumy=0;
    if (ss.find(y)!=ss.end()) sumy=alltag;
    LL sumx=0;
    if (ss.find(x)!=ss.end()) sumx=alltag;
    for (map<int,int>::iterator it=mp[x].begin();it!=mp[x].end();++it) {
        ans[it->FI]+=(sumx+tag[x]-sumy-tag[y])*(it->SE);
        mp[y][it->FI]+=it->SE;
    }
    if (SIZ(mp[y])>=k) {
        if (ss.find(y)==ss.end()) {
            tag[y]-=alltag;
            ss.insert(y);
        }
    }
    fa[x]=y;
}

bool ok[N];

void solve(int tot) {
    int mx=0;
    REP (i,0,tot) {
        v[ht[i]].PB(i);
        mx=max(mx,ht[i]);
    }
    REP (i,0,tot) mp[i][bel[i]]=1;
    REP (i,0,tot) fa[i]=i;
    PER (i,1,mx) {
        REP (j,0,SIZ(v[i])-1) merge(v[i][j],v[i][j]-1,i);
        ++alltag;
    }
    REP (i,0,tot) if (!ok[findfa(i)]) {
        int x=findfa(i);
        ok[x]=1;
        if (SIZ(mp[x])>=k) {
            // cerr<<x<<endl;
            for (map<int,int>::iterator it=mp[x].begin();it!=mp[x].end();++it) {
                ans[it->FI]+=(tag[x]+alltag)*(it->SE);
            }
        }
    }
}

void print(int s,int t) {
    REP (i,s,t) cerr<<str[i];
    cerr<<"  "<<ht[rk[s]];
    cerr<<endl;
}

int main() {
    n=RD();
    k=RD();
    int tot=0;
    REP (i,1,n) {
        scanf("%s",s+1);
        int len=strlen(s+1);
        REP (j,1,len) str[tot++]=s[j];
        endpos[i]=tot;
        str[tot++]=i+1e5;
        lth[i]=len;
    }
    if (k==1) {
        REP (i,1,n) printf("%lld ",(LL)lth[i]*(lth[i]+1)/2);
        puts("");
        return 0;
    }
    build(tot);
    --tot;

    // REP (i,0,tot) print(sa[i],tot);
    tot-=n;
    REP (i,0,tot) bel[i]=lower_bound(endpos+1,endpos+n+1,sa[i])-endpos;
    solve(tot);
    REP (i,1,n) printf("%lld ",ans[i]);
    puts("");
    
    return 0;
}
