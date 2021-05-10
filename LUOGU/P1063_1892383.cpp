#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i,a,n) for (int i=a;i<=n;i++)
#define PER(i,a,n) for (int i=n;i>=a;i--)
#define MEM(a,b) memset(a,b,sizeof(a))
#define PAUSE system("pause")
#define DEBUG
typedef long long ll;
const ll mod=1000000007;
ll N,s[405],ans,DP[405][405];
inline ll read() {
	char ch=getchar(); ll re=0; while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') {re=re*10+ch-'0'; ch=getchar();} return re;
}

inline void input() {
	scanf("%lld",&N);
	REP(i,1,N) s[i]=read();//s[2*N-i+1]=s[i];
	//sort(s+1,s+N+1);
	REP(i,1,N) s[N+i]=s[i];
	return;
}

inline void solve() {
	REP(d,2,N) REP(i,1,2*N) {int j=i+d; REP(k,i+1,j-1) DP[i][j]=max(DP[i][j],DP[i][k]+DP[k][j]+s[i]*s[j]*s[k]);ans=max(ans,DP[i][j]);}
	//REP(i,1,2*N) REP(j,1,2*N) printf("%d %d %lld\n",i,j,DP[i][j]);
	printf("%lld\n",ans);
}

int main() {
	#ifdef FILE
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	input();
	solve();
	return 0;
}