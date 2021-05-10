#include <set>
#include <map>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
inline int read() {
	int x=0, f=1; char ch=getchar();
	while (ch<'0'||ch>'9') f=(ch=='-')?-1:1, ch=getchar();
	while (ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+ch-'0', ch=getchar();
	return x*f;
}
//head
const int mod=19961993;
const int base=31;
const int N=300000+5;
int n,T;
struct Hash {
	int a[27];
	int x;
} h[N];
int fac[N];
int d[N];
vector<int> x;
char str[N];
int s[27];
int fa[27];
int ch[14],cnt;
inline int findfa(int x) {
	return x==fa[x]?x:fa[x]=findfa(fa[x]);
}
inline void init() 
{
	fac[0]=1;
	rep(i,1,n+1) fac[i]=fac[i-1]*base%mod;
	h[0].x=str[0]-'a';
	h[0].a[str[0]-'a']=1;
	s[str[0]-'a']+=1;
	rep(i,1,n) {
		int c=str[i]-'a';
		h[i].x=h[i-1].x*base%mod+c;
		rep(j,0,26) s[j]=s[j]*base%mod;
		s[c]+=1;
		rep(j,0,26) h[i].a[j]=s[j];
	}
}
inline int trans(int p){
	if (d[p]) return d[p];
	int ret=h[p].x;
	rep(i,0,26) ret=((ret+1ll*(findfa(i)-i)*h[p].a[i])%mod+mod)%mod;
x.push_back(p), d[p]=ret;
	return ret;
}

inline int hash(int l,int r) {
	if (l-1<0) return trans(r);
	return ((trans(r)-1ll*trans(l-1)*fac[r-l+1])%mod+mod)%mod;
}

inline int lcp(int l1,int l2)
{
	if (l1>=n||l2>=n) return 1;
	int l=1,r=min(n-l2,n-l1);
	int ret=0;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (hash(l1,l1+mid-1)==hash(l2,l2+mid-1)) {
			ret=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return ret;
}
inline void cle()
{
	rep(i,0,x.size()) d[x[i]]=0;
	x.clear();
}
int main()
{
	//freopen("t.in","r",stdin);
	scanf("%s",str);
	n=strlen(str);
	init();
	//rep(i,0,27) fa[i]=i;
  T=read();
	//rep(i,0,n) rep(j,0,26) if (h[i].a[j]!=0) printf("%d %d %lld\n",i,j,h[i].a[j]);
	int l1,r1,l2,r2,k;
	char a,b;
	int fx,fy;
	while (T--) {
		k=read(), l1=read(), r1=read(), l2=read(), r2=read();
		--l1, --r1, --l2, --r2;
		rep(i,0,26) fa[i]=i;
		cnt=0;
		rep(i,0,k)  a=getchar(), b=getchar(), fx=findfa(a-'a'), fy=findfa(b-'a'), 
			fa[fx]=fy,getchar();
		if (r1-l1!=r2-l2) {
			puts("NO");
		  cle();
			continue;
		}
		int k=hash(l1,r1)-hash(l2,r2);
		//	printf("%d\n",k);
		//	printf("%d %d\n",hash(l1,r1),hash(l2,r2));
		if (k==0) {
			puts("YES");
			cle();
			continue;
		}
		int len=lcp(l1,l2);
		if (l1+len>=r1) {
			puts("YES");
		  cle();
			continue;
		}
		if (hash(l1+len+1,r1)==hash(l2+len+1,r2)) {
			puts("YES");
		}
		else puts("NO");
		cle();
	}
	return 0;
}
