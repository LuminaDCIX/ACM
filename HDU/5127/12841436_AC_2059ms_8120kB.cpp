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
#define prtelm(x) cerr<<#x<<": "<<x<<endl
template<typename N> N gcd(N a,N b) {return b?gcd(b,a%b):a;}
template<typename N> inline N sqr(N a) {return a*a;}
template<typename N,typename PN> inline N flo(N a,PN b) {return a>=0?a/b:-((-a-1)/b)-1;}
template<typename N,typename PN> inline N cei(N a,PN b) {return a>0?(a-1)/b+1:-(-a/b);}
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
inline int madd(int a,int b) {return (a+=b)>=mod?a-mod:a;}
inline int msub(int a,int b) {return (a-=b)<0?a+mod:a;}
inline int mmul(int a,int b) {return (ll)a*b%mod;}
inline int mexp(int a,ll b) {int ret=1;while(b){if(b&1)ret=mmul(ret,a);a=mmul(a,a),b>>=1;}return ret;}
template<typename T,typename S> inline bool ckmin(T&a,const S&b) {return a>b?a=b,1:0;}
template<typename T,typename S> inline bool ckmax(T&a,const S&b) {return a<b?a=b,1:0;}
void getre() {assert(0);}
void gettle() {while(1);}
template<typename T> inline void read(T&x) {
    x=0;int f=1,ch=getchar();while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();x*=f;
}
// head
const int N=50000+5;
int n;
struct query {
    int op,x,y;
    ll ans;
} q[N];
set<pii>s;/*
  动态凸包，支持
  1、查询点是否在凸包内
  2、插入一个点
  3、查询给定斜率的直线与凸包的切点
*/
template<typename T> struct hull {
    //up维护上凸壳，dn维护下凸壳
    map<T,T>up,dn;
    map<db,T>kup,kdn;
    db det(db x0,db y0,db x1,db y1) {
        return x0*y1-y0*x1;
    }
    db slope(db x0,db y0,db x1,db y1) {
        return (y1-y0)/(x1-x0);
    }
    bool in_hull(map<T,T>&m,T x,T y)
    {
        if (siz(m)==0||siz(m)==1) return false;
        if (m.find(x)!=m.end()) {
            if (m[x]<y) return true;
        } else {
            typename map<T,T>::iterator it=m.lower_bound(x);
            if (it!=m.end()&&it!=m.begin()) {
                typename map <T,T>::iterator p=it--;
                if (det(x-it->fi,y-it->se,p->fi-x,p->se-y)<=0) return true;
            }
        }
        return false;
    }
    void insert(map<T,T>&m,map<db,T>&k,T x,T y)
    {
        if (in_hull(m,x,y)) return ;
        if (siz(m)==0) {
            m[x]=y;
            return;
        }
        if (siz(m)==1) {
            if (m.begin()->fi==x) {
                m[x]=min(m[x],y);
                return;
            } else {
                int x0=m.begin()->fi,y0=m.begin()->se;
                k[slope(x0,y0,x,y)]=min(x0,x);
                m[x]=y;
                return;
            }
        }
        typename map<T,T>::iterator it=m.find(x),p;
        if (it!=m.end())
        {
            p=it++;
            if (it!=m.end()) k.erase(slope(it->fi,it->se,p->fi,p->se));
            it=p;
            if (it!=m.begin()) {
                p=it--;
                k.erase(slope(it->fi,it->se,p->fi,p->se));
            }
            m.erase(p);
        } else {
            it=m.lower_bound(x);
            if (it!=m.end()&&it!=m.begin()) {
                p=it--;
                k.erase(slope(it->fi,it->se,p->fi,p->se));
            }
        }
        it=m.upper_bound(x);
        if (it!=m.begin())
        {
            --it;
            if (it!=m.begin()) {
                p=it--;
                while (det(x-p->fi,y-p->se,p->fi-it->fi,p->se-it->se)>=0) {
                    k.erase(slope(it->fi,it->se,p->fi,p->se)),m.erase(p);
                    p=it;
                    if (it==m.begin()) break;
                    --it;
                }
                k[slope(p->fi,p->se,x,y)]=p->fi;
            } else k[slope(m.begin()->fi,m.begin()->se,x,y)]=m.begin()->fi;
        }
        it=m.upper_bound(x);
        if (it!=m.end())
        {
            p=it++;
            if (it!=m.end()) {
                while (det(p->fi-x,p->se-y,it->fi-p->fi,it->se-p->se)<=0) {
                    k.erase(slope(it->fi,it->se,p->fi,p->se)),m.erase(p);
                    p=it++;
                    if (it==m.end()) break;
                }
            }
            k[slope(x,y,p->fi,p->se)]=x;
        }
        m[x]=y;
    }
    pii find(map<T,T>&m,map<db,T>&k,db t)
    {
        if (siz(m)==1) return mp(m.begin()->fi,m.begin()->se);
        typename map<db,T>::iterator it=k.lower_bound(t);
        if (it==k.end()) {        
            typename map<T,T>::iterator p=m.end();--p;
            return mp(p->fi,p->se);
        }
        return mp(it->se,m[it->se]);
    }
    //查询点是否在凸包内
    bool in_hull(T x,T y) {
        return in_hull(up,x,-y)&&in_hull(dn,x,y);
    }
    //插入一个点
    void insert(T x,T y) {
        insert(up,kup,x,-y);
        insert(dn,kdn,x,y);
    }
    //查询凸包与斜率为t的直线的切点
    //k=0查询与上凸壳的切点，k=1查询与下凸壳的切点
    pii find(db t,int k) {
        if (k&1) return find(dn,kdn,t);
        else {
            pii p=find(up,kup,-t);
            return mp(p.fi,-p.se);
        }
    }
    void clear() {   
        up.clear(),dn.clear();
        kup.clear(),kdn.clear();
    }
    bool empty() {
        return siz(up)?0:1;
    }
};
hull<int> h;
bool cur[N];
void solve(int l,int r) {
    if (l==r) return;
    int mid=l+r>>1;
    solve(l,mid),solve(mid+1,r);
    s.clear();
    rep (i,l,mid+1) {
        if (q[i].op==1) s.insert(mp(q[i].x,q[i].y));
        if (q[i].op==-1) {
            set<pii>::iterator it=s.find(mp(q[i].x,q[i].y));
            if (it!=s.end()) s.erase(it);
        }
    }
    rep (i,mid+1,r+1) if (q[i].op==-1) {
        set<pii>::iterator it=s.find(mp(q[i].x,q[i].y));
        if (it!=s.end()) s.erase(it),cur[i]=1;
    }
    int mx=-1e9,mn=1e9;
    h.clear();
    foreach (it,s) {
        h.insert((*it).fi,(*it).se);
        ckmax(mx,(*it).fi),ckmin(mn,(*it).fi);
    }
    per (i,mid+1,r+1)
    {
        if (q[i].op==-1&&cur[i]) {
            h.insert(q[i].x,q[i].y);
            ckmax(mx,q[i].x),ckmin(mn,q[i].x);
        }
        if (q[i].op==0) {
            if (q[i].y==0) {
                if (mx!=-1e9) {
                    ckmax(q[i].ans,(ll)q[i].x*mx);
                    ckmax(q[i].ans,(ll)q[i].x*mn);
                }
                continue;
            }
            if (!h.empty()) {
                pii p;
                p=h.find(-(db)q[i].x/q[i].y,1);
                ckmax(q[i].ans,(ll)q[i].x*p.fi+(ll)q[i].y*p.se);
                p=h.find(-(db)q[i].x/q[i].y,0);
                ckmax(q[i].ans,(ll)q[i].x*p.fi+(ll)q[i].y*p.se);
            }
        }
        cur[i]=0;
    }
}
int main()
{
    while (true) {
        read(n);
        if (!n) break;
        rep (i,0,n) read(q[i].op),read(q[i].x),read(q[i].y);
        rep (i,0,n) q[i].ans=-2e18;
        solve(0,n-1);
        rep (i,0,n) if (q[i].op==0) printf("%lld\n",q[i].ans);
    }
    return 0;
}

