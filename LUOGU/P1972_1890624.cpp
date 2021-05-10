#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i,a,n) for (int i=a;i<=n;i++)
#define PER(i,a,n) for (int i=n;i>=a;i--)
#define MEM(a,b) memset(a,b,sizeof(a))
typedef long long ll;
const ll mod=1000000007;

inline int read() {
	char ch=getchar(); int re=0;
	while (ch>='0'&&ch<='9') {re=re*10+ch-'0'; ch=getchar();} return re;
}

struct Q {
	int l,r,id;
} Qs[200010];

bool cmp(Q a,Q b) {
	return a.l<b.l;
}

int s[50010],a[50010],appear[1000010],nxt[50010],N,M,now,ans[200010];

inline int lowbit(int x) { return x&-x; }

inline void add(int p,int x) {
	while(p!=0&&p<=N) s[p]+=x,p+=lowbit(p);
}

inline int sum(int p) {
	int res=0;
	while(p>0) res+=s[p],p-=lowbit(p);
	return res;
}
inline void input() {
	scanf("%d",&N);
	REP(i,1,N) {
		scanf("%d",&a[i]);
		if (appear[a[i]]) nxt[appear[a[i]]]=i,appear[a[i]]=i;
		else add(i,1),appear[a[i]]=i;
	}
	scanf("%d",&M);
	REP(i,1,M) {scanf("%d%d",&Qs[i].l,&Qs[i].r);Qs[i].id=i;}
	sort(Qs+1,Qs+1+M,cmp);
	return;
}

inline void solve() {
	now=1;
	int i=1;
	while(now<=M&&i<=N) if (Qs[now].l==i) {ans[Qs[now].id]=sum(Qs[now].r)-sum(Qs[now].l-1);now++;} 
			            else add(nxt[i],1),i++;
	REP(i,1,M-1) printf("%d\n",ans[i]);
	printf("%d",ans[M]);
	return;
}

int main() {
	input();
	solve();
	return 0;
}