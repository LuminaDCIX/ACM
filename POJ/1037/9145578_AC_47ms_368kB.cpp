#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
typedef long long ll;
using namespace std;

int T;
ll n,k;
ll f[23][23][2];
bool used[23];
int ans[23],tot;

int num(int t)
{
	int p=0;
	for (int i=1;i<=n;++i) {
		if (!used[i]) {
			p++;
		}
		if (p==t) {
			used[i]=1;
			return i;
		}
	}
}

void dfs(ll k1,int x,bool l,int b)
{//printf("%d\n",k1);
	if (!x) {
		return;
	}
	int s,e;
	if (!l) {
		s=b;
		e=x;
	}
	else {
		s=1;
		e=b-1;
	}
	//printf("%d %d\n",s,e);
	for (int i=s;i<=e;++i) {
		for (int j=1;j>=0;--j) {
			if (j==l) {
				//k1-=f[x][i][j];
				continue;
			}
			if (k1<=f[x][i][j]) {
				ans[++tot]=num(i);
				dfs(k1,x-1,l^1,i);
				return;
			}
			k1-=f[x][i][j];
		}
	}
	return;
}

void solve()
{
	memset(f,0,sizeof(f));
	memset(used,0,sizeof(used));
	tot=0;
	f[1][1][0]=f[1][1][1]=1;
	for (int i=2;i<=n;++i) {
		for (int j=1;j<=i;++j) {
			for (int k=1;k<=j-1;++k) {
				f[i][j][1]+=f[i-1][k][0];
			}
			for (int k=j;k<=i-1;++k) {
				f[i][j][0]+=f[i-1][k][1];
			}
			//printf("f[%d][%d][0]=%d\n",i,j,f[i][j][0]);
			//printf("f[%d][%d][1]=%d\n",i,j,f[i][j][1]);
		}
	}
	for (int i=1;i<=n;++i) {
		for (int j=1;j>=0;--j) {
			if (k<=f[n][i][j]) {
				ans[++tot]=num(i);
				dfs(k,n-1,j,ans[tot]);
				return;
			}
			k-=f[n][i][j];
		}
	}
	return;
}

int main()
{
	scanf("%d",&T);
	while (T--) {
		scanf("%lld%lld",&n,&k);
		solve();
		printf("%d",ans[1]);
		for (int i=2;i<=n;++i) {
			printf(" %d",ans[i]);
		}
		puts("");
	}
	return 0;
}