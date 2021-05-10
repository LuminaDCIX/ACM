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
#define prtelm(x) {cerr<<#x<<": "<<x<<endl;}
#define prtarr(a,l,r) {cerr<<#a<<": ";rep (i,l,r)cerr<<a[i]<<" ";cerr<<endl;}
void getre() {assert(0);}
void gettle() {while(1);}
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
template<typename T,typename S> inline bool ckmin(T&a,const S&b) {return a>b?a=b,1:0;}
template<typename T,typename S> inline bool ckmax(T&a,const S&b) {return a<b?a=b,1:0;}
template<typename N,typename PN> inline N flo(N a,PN b) {return a>=0?a/b:-((-a-1)/b)-1;}
template<typename N,typename PN> inline N cei(N a,PN b) {return a>0?(a-1)/b+1:-(-a/b);}
template<typename N> N gcd(N a,N b) {return b?gcd(b,a%b):a;}
template<typename N> inline N sqr(N a) {return a*a;}
typedef long long ll;
typedef double db;
const int inf=0x3f3f3f3f;
const ll llinf=0x3f3f3f3f3f3f3f3fll;
const db pi=3.14159265358979323846264338327950288L;
const db eps=1e-6;
const int mod=1e9+7;
inline int modadd(int a,int b) {a+=b;return a>=mod?a-mod:a;}
inline int modsub(int a,int b) {a-=b;return a<0?a+mod:a;}
inline int modmul(int a,int b) {return (ll)a*b%mod;}
inline int modexp(int a,ll b) {int ret=1;while(b){if(b&1)ret=modmul(ret,a);a=modmul(a,a);b>>=1;}return ret;}
template<typename T> inline void read(T&x) {
    x=0;int f=1,ch=getchar();while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();x*=f;
}
// head

const int N=100000+5;

int n,c,a[N];
ll dp[N],val[N];

int main() {
    read(n),read(c);
    rep (i,0,n) read(a[i]);
    multiset<int> st;
    ll sum=0;
    rep (i,0,c-1) {
        sum+=a[i];
        st.insert(a[i]);
    }
    rep (i,c-1,n) {
        st.insert(a[i]);
        sum+=a[i];
        val[i]=sum-*st.begin();
        sum-=a[i-c+1];
        multiset<int>::iterator it=st.find(a[i-c+1]);
        st.erase(it);
    }
    rep (i,0,c-1) dp[i]=dp[i-1]+a[i];
    rep (i,c-1,n) dp[i]=min(dp[i-1]+a[i],dp[i-c]+val[i]);
    cout<<dp[n-1]<<endl;
    return 0;
}
