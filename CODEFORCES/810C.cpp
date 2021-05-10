#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn=3*1e5;
typedef long long ll;
const ll mod=1e9+7;
ll k[maxn+5];
ll fac2[maxn+5];
ll sumfac2[maxn+5];
int n;


int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;++i) {
		scanf("%lld",&k[i]);
	}
	sort(k+1,k+1+n);
	fac2[0]=1ll;
	sumfac2[1]=1ll;
	for (int i=1;i<=n;++i) {
		fac2[i]=fac2[i-1]*2ll%mod;
		sumfac2[i+1]=(sumfac2[i]+fac2[i])%mod;
	}
	/*for (int i=0;i<=n;++i) {
		printf("%d,%lld\n",i,sumfac2[i]);
	}*/
	int l=n-1,r=0;
	ll ans=0ll;
	for (int i=n;i>=1;--i) {
		ans=(ans+(k[i]*sumfac2[l--]-k[i]*sumfac2[r++])%mod+mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}