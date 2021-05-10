#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i,a,n) for (int i=a;i<=n;i++)
#define PER(i,a,n) for (int i=n;i>=a;i--)
#define MEM(a,b) memset(a,b,sizeof(a))
#define PAUSE system("pause")
#define FILE
#define DEBUG
typedef long long ll;
const int INF=0x3f3f3f3f;
const int maxn=10005;
int dwn[maxn],up[maxn],mn[maxn],mx[maxn],f[maxn][1005],pipe[maxn];
//f[i,j] 到达横坐标为i，高度为j时所需要的最少步数
//f[i,j]:=INF->min
//f[i,j-dwn[i]]=min(f[i][j],f[i][j+dwm[i]])
//f[i,j+up[i]*k]=min(f[i][j]+k,f[i][j+up[i]*k]) O(k)
//f[i,j]
inline int read(){
	char ch=getchar();int f=1,x=0;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return f*x;
}
int N,M,K;
void input() {
	N=read(),M=read(),K=read();
	REP(i,0,N-1) up[i]=read(),dwn[i]=read();
	REP(i,1,M) mx[i]=M+1;
	REP(i,1,K) {
		int p=read();
		pipe[p]=1;
		mn[p]=read();
		mx[p]=read();
	}
	return;
}
void print(int j) {
	REP(i,1,M) printf("%d ",f[j][i]);
	putchar('\n');
}
int ans,t[1005];
bool ok[1005];
bool solve() {
	MEM(f,0x3f3f);
	REP(i,1,M) f[0][i]=0;
	//REP(i,1,M) if(i-up[0]>0) f[0][i]=min(f[0][i],f[0][i-up[0]]+1);
	REP(i,1,N) {
		REP(j,1,M) {
			if(j-up[i-1]>0) f[i][j]=min(f[i-1][j-up[i-1]]+1,f[i][j-up[i-1]]+1);
		}
		REP(j,M-up[i-1],M) f[i][M]=min(f[i][M],min(f[i-1][j],f[i][j])+1);
		REP(j,1,M-dwn[i-1]) f[i][j]=min(f[i-1][j+dwn[i-1]],f[i][j]);
		if(pipe[i]) {
			REP(j,1,mn[i]) f[i][j]=INF;
			REP(j,mx[i],M) f[i][j]=INF;
		}
		int k=1;
		//print(i);
		REP(j,1,M) if(f[i][j]<INF) k=0;
		if(k) {return false;}
		if(pipe[i]) ans++;
		//print();
	}
	ans=INF;
	REP(i,1,M) ans=min(ans,f[N][i]);
	return true;
}
int main() {
	input();
	if(solve()) printf("1\n%d\n",ans);
	else {printf("0\n%d\n",ans);}
	return 0;
}