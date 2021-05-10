#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i,a,n) for (int i=a;i<=n;i++)
#define PER(i,a,n) for (int i=n;i>=a;i--)
#define MEM(a,b) memset(a,b,sizeof(a))
#define PAUSE system("pause")
typedef long long ll;
const ll mod=10007;
inline ll read() {
	char ch=getchar(); ll re=0;
	while (ch>='0'&&ch<='9') {re=re*10+ch-'0'; ch=getchar();} return re;
}

ll a,b,k,n,m,C[1500];

void input() {
	a=read(),b=read(),k=read(),n=read(),m=read();
}

ll powermod(ll x,ll n) {
	if(n==0) return 1ll;
	ll x1=powermod(x,n>>1);
	ll res=x1*x1%mod;
	if(n&1) res=res*x%mod;
	//assert(res>=0);
	return res;
}

void solve() {
	C[0]=1;
	REP(i,1,k) C[i]=(C[i-1]*(k-i+1)%mod)*powermod(i,mod-2)%mod;
	ll res=C[n]%mod;
	ll ra=powermod(a,n);
	ll rb=powermod(b,m);
	printf("%lld",(ra*rb%mod)*res%mod);
}

int main() {
	#ifdef FILE
	//freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	input();
	solve();
	return 0;
}
//1 1 323 123 200
