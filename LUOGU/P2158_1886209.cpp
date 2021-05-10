#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i,a,n) for (int i=a;i<=n;i++)
#define PER(i,a,n) for (int i=n;i>=a;i--)
#define MEM(a,b) memset(a,b,sizeof(a));
#define Pause system("pause");
typedef long long ll;
const ll mod=1000000007;
inline int read() {
	char ch=getchar(); int re=0;
	while (ch>='0'&&ch<='9') {re=re*10+ch-'0'; ch=getchar();} return re;
}

int N;
ll res,phi[40005];

void phi_table() {
	REP(i,2,N) phi[i]=0;
	phi[1]=1;
	REP(i,2,N) if(!phi[i]) {
		for(int j=i;j<=N;j+=i) {
			if(!phi[j]) phi[j]=j;
			phi[j]=phi[j]/i*(i-1);
		}
	}
	return;
}

void input() {
	N=read();
	N-=1;
}
//
void solve() {
	phi_table();
	REP(i,1,N) res+=phi[i];
	//REP(i,1,N) printf("%lld ",phi[i]);
	printf("%d",res*2+1);
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