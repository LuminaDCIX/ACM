#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<queue>
using namespace std;
#define mkpr make_pair
#define psbk push_back
#define fst first
#define scd second
#define fill_(a,b) memset((a),(b),sizeof(a))
#define clear_(a) fill_(a,0)
#define size_(x) ((int)(x).size())
#define all_(x) (x).begin(),(x).end()
#define foreach(it,a) for(__typeof((a).begin()) it=(a).begin();it!=(a).end();it++)
#define rep(i,a,b) for (int i=(a);i<(b);++i)
#define per(i,a,b) for (int i=(b)-1;i>=(a);--i)
#define forout(i,head,link) for (int i=head;i;i=link[i].nxt)
#define power(x) (1ll<<(x))
#define pmod(a,b) (((a)=((a)+(b))%mod)<0?(a)+=mod:(a))
#define mmod(a,b) (((a)=1ll*(a)*(b)%mod)<0?(a)+=mod:(a))
void getre(){int x=0;printf("%d\n",1/x);}
void gettle(){int res=1;while(1)res<<=1;printf("%d\n",res);}
void step(){rep(sp,1,100000000);}
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
template<typename T,typename S>inline bool upmin(T&a,const S&b){return a>b?a=b,1:0;}
template<typename T,typename S>inline bool upmax(T&a,const S&b){return a<b?a=b,1:0;}
template<typename N,typename PN>inline N flr(N a,PN b){return a>=0?a/b:-((-a-1)/b)-1;}
template<typename N,typename PN>inline N cel(N a,PN b){return a>0?(a-1)/b+1:-(-a/b);}
template<typename N>N gcd(N a,N b){return b?gcd(b,a%b):a;}
#if ((_WIN32||__WIN32__)&&__cplusplus<201103L)
#define lld "%I64d"
#else
#define lld "%lld"
#endif
inline void read(long long&x){
	int f=1;char c;while(((c=getchar())<'0'||c>'9')&&c!='-');c=='-'?(f=-1,x=0):(x=c-'0');
	while((c=getchar())>='0'&&c<='9')x=x*10+c-'0';x*=f;
}
inline void read(int&x){long long t;read(t);x=t;}
inline void read(unsigned long long&x){long long t;read(t);x=t;}
inline void read(long double&x){double t;scanf("%lf",&t);x=t;}
#ifdef MiracleEEEE
#define cde(...) cout<<"LINE:"<<__LINE__<<" "<<__VA_ARGS__<<endl;
#define pde(format,...) printf("Line:%d: "format"\n",__LINE__,##__VA_ARGS__); 
#else 
#define cde(...)
#define pde(format,...)
#endif
typedef long long ll;
const int inf=0x3f3f3f3f;
const double pi=acos(-1.0);
const double eps=1e-6;
const int mod=inf;
int powmod(int a,ll b){int n=1;do{if(b&1)n=1ll*n*a%mod;a=1ll*a*a%mod;}while(b>>=1);return n;}
//head

const int maxn=100;
struct edge
{
  int nxt,to;
}
edges[maxn*maxn*2+5];
int head[maxn*2+5],tot;
int fa[maxn*2+5];
inline void add_edge(int from,int to)
{
  edges[++tot].to=to,edges[tot].nxt=head[from],head[from]=tot;
}
int n,m,k;
bool vis[maxn*2+5];
bool dfs(int x)
{
  forout(i,head[x],edges){
    int v=edges[i].to;
    cde(v<<" fa[v]="<<fa[v]);
    if(!vis[v]){
    vis[v]=1;
      if(!fa[v]||dfs(fa[v])){fa[v]=x;return 1;}
    }
  }
  return 0;
}
int main()
{
#ifdef MiracleEEEE
freopen("t.in","r",stdin);
#endif
  while (1){
    read(n); if(!n) break;
    read(m),read(k);
    clear_(head);
    clear_(fa);
    int idx,a,b,ans=0;
    rep(i,0,k){
      read(idx),read(a),read(b);
      if(a*b)add_edge(a,b+m);//add_edge(m+b,a);
    }
    rep(i,1,n) {clear_(vis); if(dfs(i)) ans++;}
    printf(lld"\n",(ll)ans);
  }
	return 0;
}
