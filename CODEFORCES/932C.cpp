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

inline int read() {
	int f=1,x=0;
	char ch=getchar();
	while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}

void exgcd(int a,int b,LL &x,LL &y) {
	if (!b) {
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,y,x),y-=(a/b)*x;
}

int gcd(int a,int b) {
	return !b?a:gcd(b,a%b);
}

int p[(int)1e6+5];

int main() {
	int n=read(),a=read(),b=read();
	int g=gcd(a,b);
	if (n%g) {
		puts("-1");
		return 0;
	}
	LL x,y;
	exgcd(a,b,x,y);
	x*=n/g,y*=n/g;
	LL lcm=(LL)a*b/g;
	if (x<0) {
		LL f=lcm/a;
		LL l=x;
		x=(x%f+f)%f;
		LL k=(x-l)/f;
		y-=k*(lcm/b);
	} else {
		LL f=lcm/b;
		LL l=y;
		y=(y%f+f)%f;
		LL k=(y-l)/f;
		x-=k*(lcm/a);
	}
	if (x<0||y<0) {
		puts("-1");
		return 0;
	}
	for (int i=0,k=0;k<x;i+=a,++k) {
		p[i]=i+a;
		REP (j,i+1,i+a)
			p[j]=j;
	}
	for (int i=a*x,k=0;k<y;i+=b,++k) {
		p[i]=i+b;
		REP (j,i+1,i+b)
			p[j]=j;
	}

	REP (i,0,n)
		printf("%d ",p[i]);
	puts("");
	return 0;
}
