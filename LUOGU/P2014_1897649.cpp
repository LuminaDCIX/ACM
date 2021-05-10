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

struct edge {
	int to,nxt;
}edges[305];
int N,M,cost[305],head[305],f[305][305],ans,tot;

inline int read() {
	char ch=getchar(); int re=0; while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') {re=re*10+ch-'0'; ch=getchar();} return re;
}

inline void add(int from,int to) {
	edges[++tot].to=to;edges[tot].nxt=head[from];head[from]=tot;
}

inline void input() {
	N=read(),M=read();
	int v,c;
	MEM(edges,-1);
	MEM(head,-1);
	REP(i,1,N) {
		v=read(),c=read();
		cost[i]=c;
		add(v,i);
	}
	return;
}

inline int dp(int u) {
	int t,now;
	f[u][1]=cost[u];
	t=1;
	for(int p=head[u];p!=-1;p=edges[p].nxt) {
		int v=edges[p].to;
		now=dp(v);
		t+=now;
		PER(i,1,t) REP(j,1,now) {if(i-j<=0)continue;f[u][i]=max(f[u][i],f[u][i-j]+f[v][j]);}
	}
	return t;
}

inline void solve() {
	dp(0);
	//REP(i,1,N) {PER(j,w[i],M) h[i][j]=max(h[i-1][j],h[i-1][j-w[i]]+v[i]); ans=max(ans,h[i][M]);}
	printf("%d",f[0][M+1]);
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