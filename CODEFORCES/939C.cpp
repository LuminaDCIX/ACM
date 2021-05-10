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

const int N=100000+5;
int n;
int s[N],sum[N];

int main() {
	n=read();
	REP (i,1,n+1)
		s[i]=read(),sum[i]=sum[i-1]+s[i];
	int s=read(),t=read()-1;
	int len=t-s+1;
	int ans=0,k=0,mn=n;
	REP (i,1,len+1) {
		int nw=sum[i]+sum[n]-sum[n-(len-i)];

		if (nw==ans)
			k=n-(len-i)+1,mn=min(((s-k)%n+n)%n,mn);
		if (nw>ans)
			ans=nw,k=n-(len-i)+1,mn=((s-k)%n+n)%n;
	}
	REP (i,len,n+1) {
		int nw=sum[i]-sum[i-len];
		if (nw==ans)
			k=i-len+1,mn=min(((s-k)%n+n)%n,mn);
		if (nw>ans)
			ans=nw,k=i-len+1,mn=((s-k)%n+n)%n;
	}
	cout<<mn+1<<endl;
	return 0;
}
	
