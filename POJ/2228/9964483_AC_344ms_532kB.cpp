#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#define rep(i,a,n) for (int i=(a);i<(n);++i)
#define per(i,a,n) for (int i=(n)-1;i>=a;--i)
typedef long long ll;

using namespace std;

const int maxn=3830;
ll f[2][maxn+5][2];
int u[maxn+5];
int n,b;
int now,last;
inline void dp() {
	now=0,last=1;
	rep(i,0,n-1) {
		now^=1,last^=1;
		memset(f[now],0xcf,sizeof(f[now]));
		int to=min(b,i+1);
		rep(j,0,to+1) {
			f[now][j+1][1]=max(f[now][j+1][1],f[last][j][1]+u[i+1]);
			f[now][j+1][1]=max(f[now][j+1][1],f[last][j][0]);
			f[now][j][0]=max(f[now][j][0],f[last][j][1]);
			f[now][j][0]=max(f[now][j][0],f[last][j][0]);
		}
	}
}

int main() {
	scanf("%d%d",&n,&b);
	rep(i,0,n) scanf("%d",&u[i]);
	ll ans=0;
	memset(f,0xcf,sizeof(f));
	f[0][0][0]=0;
	dp(); ans=max(ans,max(f[now][b][0],f[now][b][1]));
	memset(f,0xcf,sizeof(f));
	f[0][1][1]=u[0];
	dp(); ans=max(ans,f[now][b][1]);
	memset(f,0xcf,sizeof(f));
	f[0][1][1]=0;
	dp(); ans=max(ans,f[now][b][0]);
	printf("%lld\n",ans);
	return 0;
}
