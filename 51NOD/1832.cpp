#include <set>
#include <map>
#include <cmath>
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
int cut=1e8;
struct bigint {
	int n;
	ll s[205];
	void init(ll x) {
		memset(s,0,sizeof(s));
		s[0]=x, n=1;
	}
};
bigint operator + (bigint a,bigint b) {
	bigint c; c.init(0);
	c.n=max(a.n,b.n)+1;
	rep(i,0,c.n) c.s[i]+=a.s[i]+b.s[i], c.s[i+1]+=c.s[i]/cut, c.s[i]%=cut;
	while (c.s[c.n-1]==0) --c.n;
	return c;
}
bigint operator * (bigint a,bigint b) {
	bigint c; c.init(0);
	c.n=a.n+b.n+2;
	rep(i,0,a.n) rep(j,0,b.n) c.s[i+j]+=a.s[i]*b.s[j], c.s[i+j+1]+=c.s[i+j]/cut, c.s[i+j]%=cut;
	while (c.s[c.n-1]==0) --c.n;
	return c;
}
const int N=10000+5;
typedef long long ll;
int a[N];
int b[N];
int n;

bigint solve(int al,int ar,int bl,int br)
{
	bigint p;
	if (al==ar) return a[al]==b[bl]?(p.init(1),p):(p.init(0),p);
	if (ar==al+1) return (a[al]==b[br]&&a[ar]==b[bl])?(p.init(2),p):(p.init(0),p);
	bigint ret;
	ret.init(0);
	int l1=al+1;
	int l2=bl;
	int r1=ar;
	int r2=br-1;
	int root=a[l1];
	//if (a[r1]==b[l2]) ret+=(l1,r1-1,l2+1,r2)<<1;
	rep(i,l2,r2) if (b[i]==root) {
		int len=i-l2+1;
		ret=ret+solve(l1,l1+len-1,l2,l2+len-1)*solve(l1+len,r1,l2+len,r2);
	}
	p.init(2);
	if (a[l1]==b[r2]) ret=ret+solve(l1,r1,l2,r2)*p;
	return ret;
}
int main()
{
	n=read();
	rep(i,0,n) a[i]=read();
	rep(i,0,n) b[i]=read();
	bigint ans=solve(0,n-1,0,n-1);
  printf("%lld",ans.s[ans.n-1]);
	per(i,0,ans.n-1) printf("%08lld",ans.s[i]);
	puts("");
	return 0;
}
