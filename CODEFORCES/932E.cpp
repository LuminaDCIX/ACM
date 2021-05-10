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

const int P=1e9+7;
const int K=5000+5;

int k;
int S[K][K];

int add(int a,int b) {
	a+=b;
	return a>=P?a-P:a;
}

int mul(int a,int b) {
	return (LL)a*b%P;
}

int modexp(int a,int x) {
	int ret=1;
	if (x<0)
		return 0;
	while (x) {
		if (x&1) 
			ret=mul(ret,a);
		a=mul(a,a);
		x>>=1;
	}
	return ret;
}

int fac(int a,int j) {
	int ret=1;
	REP (i,a-j+1,a+1)
		ret=mul(ret,i);
	return ret;
}
	

int main() {
	int n=read(),k=read();
	S[0][0]=1;
	REP (i,1,k+1) {
		S[i][0]=0;
		REP (j,1,i+1)
			S[i][j]=add(S[i-1][j-1],mul(j,S[i-1][j]));
	}
	int ans=0;
	REP (i,1,k+1)
		ans=add(ans,mul(mul(S[k][i],fac(n,i)),modexp(2,n-i)));
	cout<<ans<<endl;
	return 0;
}
