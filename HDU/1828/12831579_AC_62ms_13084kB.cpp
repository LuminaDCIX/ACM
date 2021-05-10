#include <bits/stdc++.h>
using namespace std;
#define y0 y0z
#define y1 y1z
#define yn ynz
#define j0 j0z
#define j1 j1z
#define jn jnz
#define tm tmz
#define buc1(x) (__builtin_popcountll(x))
#define bur1(x) (__builtin_ctzll(x))
#define bul1(x) (63-__builtin_clzll(x))
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define fil(a,b) memset((a),(b),sizeof(a))
#define cl(a) fil(a,0)
#define siz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define foreach(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();++it)
#define rep(i,a,b) for (int i=(a),_ed=(b);i<_ed;++i)
#define per(i,a,b) for (int i=(b)-1,_ed=(a);i>=_ed;--i)
#define forg(i,gu) for (int i=gu;~i;i=nxt[i])
#define pw2(x) ((ll(1))<<(x))
#define prtarr(a,l,r) cerr<<#a<<": ";rep(i,l,r)cerr<<a[i]<<" ";cerr<<endl
#define prtelm(x) cerr<<#x<<": "<<x<<endl;
template<typename T,typename S> inline bool ckmin(T&a,const S&b) {return a>b?a=b,1:0;}
template<typename T,typename S> inline bool ckmax(T&a,const S&b) {return a<b?a=b,1:0;}
template<typename N,typename PN> inline N flo(N a,PN b) {return a>=0?a/b:-((-a-1)/b)-1;}
template<typename N,typename PN> inline N cei(N a,PN b) {return a>0?(a-1)/b+1:-(-a/b);}
template<typename N> N gcd(N a,N b) {return b?gcd(b,a%b):a;}
template<typename N> inline N sqr(N a) {return a*a;}
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef long long ll;
typedef double db;
const int inf=0x3f3f3f3f;
const ll llinf=0x3f3f3f3f3f3f3f3fll;
const db pi=3.14159265358979323846264338327950288L;
const db eps=1e-6;
const int mod=1e9+7;
void getre() {assert(0);}
void gettle() {while(1);}
inline int modadd(int a,int b) {a+=b;return a>=mod?a-mod:a;}
inline int modsub(int a,int b) {a-=b;return a<0?a+mod:a;}
inline int modmul(int a,int b) {return (ll)a*b%mod;}
inline int modexp(int a,ll b) {int ret=1;while(b){if(b&1)ret=modmul(ret,a);a=modmul(a,a);b>>=1;}return ret;}
template<typename T> inline void read(T&x) {
    x=0;int f=1,ch=getchar();while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();x*=f;
}
// head
const int N=5000+5;
const int MAXR=200000+5;
const int MAXN=(MAXR<<2)+5;
int n;
int x0[N],y0[N],x1[N],y1[N];
struct seg {
    int x,y,h,op;
    seg(int _x,int _y,int _h,int _op):x(_x),y(_y),h(_h),op(_op){};
    bool operator<(const seg&s)const
    {
        return h==s.h?op>s.op:h<s.h;
    }
};
vector<seg> v0,v1;
int mn[MAXN],summn[MAXN],tag[MAXN];
int getlen(int t,int ll,int rr)
{
    return rr-ll+1-(mn[t]==0?summn[t]:0);
}
void pushdown(int o)
{
    if (!tag[o]) return;
    int lc=o<<1,rc=o<<1|1,k=tag[o];
    mn[lc]+=k,mn[rc]+=k,tag[lc]+=k,tag[rc]+=k;
    tag[o]=0;
}
void add(int o,int ll,int rr,int l,int r,int v)
{
    if (ll!=rr) pushdown(o);
    if (ll>=l&&rr<=r) {
        mn[o]+=v,tag[o]+=v;
        return;
    }
    int mid=ll+rr>>1,lc=o<<1,rc=o<<1|1;
    if (l<=mid) add(lc,ll,mid,l,r,v);
    if (r>mid) add(rc,mid+1,rr,l,r,v);
    mn[o]=min(mn[lc],mn[rc]);
    if (mn[lc]==mn[rc]) summn[o]=summn[lc]+summn[rc];
    else if (mn[lc]<mn[rc]) summn[o]=summn[lc];
    else summn[o]=summn[rc];
}
void build(int o,int ll,int rr)
{
    summn[o]=rr-ll+1;
    if (ll==rr) return;
    int mid=ll+rr>>1;
    build(o<<1,ll,mid),build(o<<1|1,mid+1,rr);
}
int solve(vector<seg>&v)
{
    sort(all(v));
    int ans=0,mx=0;
    cl(mn),cl(summn),cl(tag);
    rep (i,0,siz(v)) mx=max(mx,v[i].y);
    build(1,0,mx);
    rep (i,0,siz(v)) {
        int nw=getlen(1,0,mx);
        add(1,0,mx,v[i].x,v[i].y,v[i].op);
        ans+=abs(nw-getlen(1,0,mx));
    }
    return ans;
}
int main()
{
    while (~scanf("%d",&n)) {
        v0.clear(),v1.clear();
        rep (i,0,n) read(x0[i]),read(y0[i]),read(x1[i]),read(y1[i]);
        int lim=100000;
        rep (i,0,n) {
            x0[i]+=lim,x1[i]+=lim,y0[i]+=lim,y1[i]+=lim;
            v0.pb(seg(x0[i],x1[i]-1,y0[i],1));
            v0.pb(seg(x0[i],x1[i]-1,y1[i],-1));
            v1.pb(seg(y0[i],y1[i]-1,x0[i],1));
            v1.pb(seg(y0[i],y1[i]-1,x1[i],-1));
        }
        int ans=solve(v0);
        ans+=solve(v1);
        cout<<ans<<endl;
    }
    return 0;
}
