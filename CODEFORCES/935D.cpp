#include <bits/stdc++.h>

using namespace std;

#define MP make_pair
#define PB push_back
#define FI first
#define SE second
#define SIZ(x) ((int)x.size())
#define SET(x,k) memset(x,k,sizeof(x))
#define ALL(x) x.begin(),x.end()

typedef long long LL;
typedef double DB;
typedef vector<int> VI;
typedef pair<int,int> PII;

inline LL read() {
	LL f=1,x=0;
	char ch=getchar();
	while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}

const int N=1e5+5;
const int P=1e9+7;

int n,m;
int s1[N],s2[N];

int add(int a,int b) {
	a+=b;
	return a>=P?a-P:a;
}
int sub(int a,int b) {
	a-=b;
	return a<0?a+P:a;
}
int mul(int a,int b) {
	return (LL)a*b%P;
}

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

int main() {
	n=read(),m=read();
	for (int i=0;i<n;++i)
		s1[i]=read();
	for (int i=0;i<n;++i)
		s2[i]=read();
	int ans=0,nw=1;
	for (int i=0;i<n;++i) {
		if (s1[i]==0&&s2[i]!=0)
			ans=add(ans,mul(nw,mul(m-s2[i],modexp(m,P-2)))),nw=mul(nw,modexp(m,P-2));
		else if (s1[i]!=0&&s2[i]==0)
			ans=add(ans,mul(nw,mul(s1[i]-1,modexp(m,P-2)))),nw=mul(nw,modexp(m,P-2));
		else if (s1[i]==0&&s2[i]==0)
			ans=add(ans,mul(nw,mul(sub(mul(mul(m,m+1),modexp(2,P-2)),m),modexp(mul(m,m),P-2)))),nw=mul(nw,modexp(m,P-2));
		else if (s1[i]>s2[i]) {
			ans=add(ans,nw);
			break;
		} else if (s1[i]<s2[i]) {
			break;
		}
	}
	cout<<ans<<endl;
	return 0;
}
