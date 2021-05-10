#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

const int maxn=200;
int n,m,T,tot;
char c[maxn*2+5];
int cnt[2];
bool G[maxn*2+5][maxn*2+5];
bool vis[maxn*2+5];
bool f[2][maxn+5][maxn+5];
bool now,last;


inline void input()
{
	scanf("%d%d",&n,&m);
	int from,to;
	memset(G,0,sizeof(G));
	for (int i=1;i<=m;++i) {
		scanf("%d%d",&from,&to);
		G[from][to+n]=1;
		G[to+n][from]=1;
	}
	return;
}

void dfs(int u,bool col)
{
	vis[u]=1;
	c[u]=col;
	cnt[col]++;
	for (int i=1;i<=2*n;++i) if (i!=u) {
		if (!vis[i]&&G[u][i]) {
			dfs(i,col^1);
		}
	}
	return;
}

inline void solve()
{
	memset(c,-1,sizeof(c));
	memset(vis,0,sizeof(vis));
	/*for (int i=0;i<=maxn;++i) {
		for (int j=0;j<=maxn*2;++j) {
			f[i][j]=-100000;
		}
	}
	tot=0;
	f[0][n]=0;*/
	memset(f,0,sizeof(f));
	tot=0;
	now=1;last=0;
	for (int i=1;i<=n*2;++i) if (!vis[i]) {
		now^=1;last^=1;
		memset(f[now],0,sizeof(f[now]));
		f[last][0][0]=1;
		cnt[0]=cnt[1]=0;
		dfs(i,i>n?1:0);
		++tot;
		//printf("%d %d\n",cnt[0],cnt[1]);
		//dp
		int w=0;
		for (int j=0;j<=n;++j) {
			for (int k=0;k<=n;++k) {
				if (j-cnt[0]>=0&&k-cnt[1]>=0) {
					f[now][j][k]|=f[last][j-cnt[0]][k-cnt[1]];
				}
				/*if (j-cnt[1]>=0&&k-cnt[0]>=0) {
					f[tot][j][k]|=f[tot-1][j-cnt[1]][k-cnt[0]];
				}*/
				f[now][j][k]|=f[last][j][k];
				//if (f[tot][j][k]) {
				//	printf("f[%d][%d][%d]=%d\n",tot,j,k,f[tot][j][k]);
				//}
			}
		}
	}
	int ans=0;
	for (int i=n/2;i>=0;i--) {
		if (f[now][i][i]) {
			ans=i;
			break;
		}
	}
	printf("%d\n",ans);
	return;
}

int main()
{
	int T;
	scanf("%d",&T);
	while (T--) {
		input();
		solve();
	}
	return 0;
}
