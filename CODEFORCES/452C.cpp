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

const int MAXN=1e6+5;

int n,m;
unordered_map<int,int> fac;
int mindiv[MAXN];

void add(int k,int o) {
	while (mindiv[k]) {
		int f=mindiv[k];
		k/=f,fac[f]+=o;
	}
}

void addC(int n,int m,int o) {
	REP (i,m+1,n+1) add(i,1*o);
	REP (i,2,n-m+1) add(i,-1*o);
}

bool notP[MAXN];
int p[MAXN],tot;

void init() {
	REP (i,2,MAXN) {
		if (!notP[i]) p[tot++]=i,mindiv[i]=i;
		REP (j,0,tot) {
			int k=p[j]*i;
			if (k>=MAXN) break; 
			mindiv[k]=p[j],notP[k]=1;
			if (i%p[j]==0) break;
		}
	}
}


int main() {
	init();
	n=read(),m=read();

	if (n==0||m==0) {
		puts("0");
		return 0;
	}

	add(n,1),add(m,1),addC(n*m-1,n-1,1);
	add(n,-1),add(n,-1),addC(n*m,n,-1);
	double ans1=1;
	REP (i,2,MAXN) {
		int k=fac[i];
		if (k>0) {
			while (k--) ans1*=i;
		} else if (k<0) {
			while (k++) ans1/=i;
		}
	}
	fac.clear();
	double ans2=1;
	if (n>=2&&n*m-2>0&&m>=2) {
		add(2,1),add(n,1),addC(m,2,1),addC(n*m-2,n-2,1);
		add(n,-1),add(n,-1),addC(n*m,n,-1);
		REP (i,2,MAXN) {
			int k=fac[i];
			if (k>0) {
				while (k--) ans2*=i;
			} else if (k<0) {
				while (k++) ans2/=i;
			}
		}
	} else ans2=0;
	printf("%.7f\n",ans1+ans2);
	return 0;
}
