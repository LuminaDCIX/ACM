#include <bits/stdc++.h>

using namespace std;

#define MP make_pair
#define PB push_back
#define FI first
#define SE second
#define SIZ(x) ((int)x.size())
#define SET(x,k) memset(x,k,sizeof(x))
#define REP(i,a,n) for (int i=(a);i<(n);++i)
#define PER(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define FORG(o,u) for (edge* o=head[u];o;o=o->nxt)

typedef long long LL;
typedef long double DB;
typedef vector<int> VI;
typedef pair<int,int> PII;

inline int read() {
	int f=1,x=0;
	char ch=getchar();
	while (ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return f*x;
}


int main() {
	string ss;
	cin>>ss;
	string ans=ss;
	PER (i,0,ss.length())
		ans+=ss[i];
	cout<<ans<<endl;
	return 0;
}
