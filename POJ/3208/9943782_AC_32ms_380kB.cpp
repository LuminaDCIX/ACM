#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=(a);--i)
typedef long long ll;
using namespace std;
ll f[21][4];
int g[4][11]={
{0,0,0,0,0,0,0,0,0,0},
{3,3,3,3,3,3,0,3,3,3},
{3,3,3,3,3,3,1,3,3,3},
{3,3,3,3,3,3,2,3,3,3}};
int main() {
	f[0][0]=1;
	rep(i,1,21) {
		f[i][0]=9*(f[i-1][0]+f[i-1][1]+f[i-1][2]);
		f[i][1]=f[i-1][0];
		f[i][2]=f[i-1][1];
		f[i][3]=f[i-1][2]+10*f[i-1][3];
	}
	int T; scanf("%d",&T);
	while (T--) {
		ll n; scanf("%lld",&n);
		int d=0,u=3;
		while (f[d][3]<n) ++d;
		while (d) {
			ll k=0;
			rep(i,0,10) {
				ll t=0;
				per(j,g[u][i],4) t+=f[d-1][j];
				if (k+t>=n) {
					printf("%d",i);
					u=g[u][i];
					break;
				}
				k+=t;
			}
			n-=k,d--;
		}
		puts("");
	}
	return 0;
}