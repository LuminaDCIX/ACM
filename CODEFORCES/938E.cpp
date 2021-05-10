#include <bits/stdc++.h>

using namespace std;

#define MP make_pair
#define PB push_back
#define FI first
#define SE second
#define SIZ(x) ((int)x.size())
#define SET(x,k) memset(x,k,sizeof(x))
#define ALL(x) x.begin(),x.end()
#define REP(i,a,n) for (int i=(a);i<(n);++i)
#define PER(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define FORG(o,u) for (edge* o=head[u];o;o=o->nxt)

typedef long long LL;
typedef long double DB;
typedef vector<int> VI;
typedef pair<int,int> PII;

inline LL read() {
	LL f=1,x=0;
	char ch=getchar();
	while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}

const int N=1e6+5;
const int P=1e9+7;

int fac[N],inv[N];

int add(int a,int b) {
	a+=b;
	return a>=P?a-P:a;
}

int mul(int a,int b) {
	return (LL)a*b%P;
}

int sub(int a,int b) {
	a-=b;
	return a<0?a+P:a;
}

inline int C(int n,int m) {
	return mul(fac[n],mul(inv[m],inv[n-m]));
}

int a[N];

int modexp(int a,int x) {
	int ret=1;
	while (x) {
		if (x&1)
			ret=mul(ret,a);
		a=mul(a,a);
		x>>=1;
	}
	return ret;
}

int n;
int main() {
	n=read();
	REP (i,0,n)
		a[i]=read();
	fac[0]=1;
	REP (i,1,n+1)
		fac[i]=mul(fac[i-1],i);
	inv[n]=modexp(fac[n],P-2);
	PER (i,0,n)
		inv[i]=mul(inv[i+1],i+1);

	sort(a,a+n);
	int ans=0;
	REP (i,0,n) {
		int l=i,r=i;
		while (a[r]==a[l])
			++r;
		if (r==n)
			break;
		int L=i;
		ans=add(ans,mul(mul(fac[n-L-1],mul(fac[L],mul(a[i],C(n,n-L)))),r-l));
		i=r-1;
	}
	cout<<ans<<endl;
	return 0;
}
