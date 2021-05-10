#include <bits/stdc++.h>

using namespace std;

#define MP make_pair
#define PB push_back
#define FI first
#define SE second
#define SIZ(x) ((int)x.size())
#define SET(x,k) memset(x,k,sizeof(x))
#define ALL(x) x.begin(),x.end()

typedef long long LL;
typedef long double DB;
typedef vector<int> VI;
typedef pair<int,int> PII;

inline LL read() {
	LL f=1,x=0;
	char ch=getchar();
	while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}

const int N=1e4+5;
const int P=100+5;

char str[N];
int n,ls[N],rs[N];
int p,q;

int dp[N][P][2];

PII stk[N];

int build(int l,int r) {
	if (l==r)
		return l;
	int nw=0,num;
	int mx=n,k=-1;
	for (int i=l;i<=r;++i) {
		if (str[i]=='(')
			++nw;
		else if (str[i]==')')
			--nw;
		else if (str[i]=='?') {
			if (nw<mx)
				mx=nw,k=i;
		} else
			num=i;
	}
	if (k==-1)
		return num;
	ls[k]=build(l,k-1);
	rs[k]=build(k+1,r);
	return k;
}

void ckmin(int &a,int b) {
	if (a>b)
		a=b;
}

void ckmax(int &a,int b) {
	if (a<b)
		a=b;
}

void dfs(int u) {
	if (ls[u]==-1) {
		dp[u][0][0]=dp[u][0][1]=str[u]-'0';
		return;
	}
	int l=ls[u],r=rs[u];
	dfs(l),dfs(r);
	if (p<=100) {
		for (int i=0;i<=p;++i) {
			for (int j=0;j<=p-i;++j) {
				ckmax(dp[u][i+j][1],dp[l][i][1]-dp[r][j][0]);
				ckmax(dp[u][i+j+1][1],dp[l][i][1]+dp[r][j][1]);
				ckmin(dp[u][i+j][0],dp[l][i][0]-dp[r][j][1]);
				ckmin(dp[u][i+j+1][0],dp[l][i][0]+dp[r][j][0]);
			}
		}
	} else {
		for (int i=0;i<=q;++i) {
			for (int j=0;j<=q-i;++j) {
				ckmax(dp[u][i+j][1],dp[l][i][1]+dp[r][j][1]);
				ckmax(dp[u][i+j+1][1],dp[l][i][1]-dp[r][j][0]);
				ckmin(dp[u][i+j][0],dp[l][i][0]+dp[r][j][0]);
				ckmin(dp[u][i+j+1][0],dp[l][i][0]-dp[r][j][1]);
			}
		}
	}
}

int main() {
	scanf("%s",str);
	n=strlen(str);
	p=read(),q=read();
	SET(ls,-1),SET(rs,-1);
	int root=build(0,n-1);
	for (int i=0;i<N;++i)
		for (int j=0;j<P;++j)
			dp[i][j][0]=1e9,dp[i][j][1]=-1e9;
	dfs(root);
	if (p<=100)
		cout<<dp[root][p][1]<<endl;
	else
		cout<<dp[root][q][1]<<endl;
	return 0;
}
