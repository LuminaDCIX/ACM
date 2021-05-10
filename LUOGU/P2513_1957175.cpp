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
const ll mod=10000;

inline int read(){
	char ch=getchar();int f=1,x=0;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return f*x;
}
int N,K;
void input() {
	N=read(),K=read();
	return;
}
ll dp[1005][1005],sum[1005];
void solve() {
	dp[1][0]=1;
	REP(i,0,K) sum[i]=1;
	REP(i,2,N) {	
		REP(j,0,K) {	
			int t=j-i;
			dp[i][j]=(sum[j]-(t<0?0:sum[t])+mod)%mod;
		}
		sum[0]=1;
		REP(j,1,K) sum[j]=(sum[j-1]+dp[i][j])%mod;
	}
	printf("%lld\n",dp[N][K]);
	return;
}
int main() {
	input();
	solve();
	return 0;
}

