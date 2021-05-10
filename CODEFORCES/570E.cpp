#include <bits/stdc++.h>

using namespace std;

#define MP make_pair
#define PB push_back
#define SIZ(x) ((int)x.size())
#define SET(x,k) memset(x,k,sizeof(x))
#define REP(i,a,n) for (int i=(a);i<(n);++i)
#define PER(i,a,n) for (int i=(n)-1;i>=(a);--i)

typedef long long LL;
typedef double DB;
typedef pair <int, int> PII;

inline int read() {
	int f=1,x=0;
	char ch=getchar();
	while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}

const int N=500+5;
const int P=1e9+7;

int n,m,len;

inline int add(int a,int b) {a+=b;return a>=P?a-P:a;}
inline int mul(int a,int b) {return (unsigned long long)a*b%P;}

char s[N][N];
int dp[2][N][N];

int dx1[]={0,1},dy1[]={1,0};
int dx2[]={0,-1},dy2[]={-1,0};

bool ok(int x,int y) {return x>=0&&x<n&&y>=0&&y<m;}

void solve_odd() {
	int u=0,v=1;
	dp[u][0][n-1]=1;
	len=(len+1)>>1;
	REP (i,0,len-1) {
		u^=1,v^=1,SET(dp[u],0);
		REP (j,0,n) REP (k,0,n) {
			int x1=j,y1=i-j;
			int x2=k,y2=m-1-(i-(n-1-x2));
			if (ok(x1,y1)&&ok(x2,y2)) {
				REP (p,0,2) REP (q,0,2) {
					int tx1=x1+dx1[p],ty1=y1+dy1[p];
					int tx2=x2+dx2[q],ty2=y2+dy2[q];
					if (ok(tx1,ty1)&&ok(tx2,ty2)&&s[tx1][ty1]==s[tx2][ty2]) {
						dp[u][tx1][tx2]=add(dp[u][tx1][tx2],dp[v][x1][x2]);
					}
				}
			}
		}
	}
	int ans=0;
	REP (i,0,n) ans=add(ans,dp[u][i][i]);
	cout<<ans<<endl;
}

void solve_even() {
	int u=0,v=1;
	dp[u][0][n-1]=1;
	len=(len)>>1;
	REP (i,0,len-1) {
		u^=1,v^=1,SET(dp[u],0);
		REP (j,0,n) REP (k,0,n) {
			int x1=j,y1=i-j;
			int x2=k,y2=m-1-(i-(n-1-x2));
			if (ok(x1,y1)&&ok(x2,y2)) {
				REP (p,0,2) REP (q,0,2) {
					int tx1=x1+dx1[p],ty1=y1+dy1[p];
					int tx2=x2+dx2[q],ty2=y2+dy2[q];
					if (ok(tx1,ty1)&&ok(tx2,ty2)&&s[tx1][ty1]==s[tx2][ty2]) {
						dp[u][tx1][tx2]=add(dp[u][tx1][tx2],dp[v][x1][x2]);
					}
				}
			}
		}
	}
	int ans=0;
	REP (i,0,n) ans=add(ans,add(dp[u][i][i],dp[u][i][i+1]));
	cout<<ans<<endl;
}
int main() {
	n=read(),m=read();
	REP (i,0,n) scanf("%s",s[i]);
	if (s[0][0]!=s[n-1][m-1]) {
		puts("0");
		return 0;
	}
	len=n+m-1;
	if (len&1) solve_odd();
	else solve_even();
	return 0;
}
