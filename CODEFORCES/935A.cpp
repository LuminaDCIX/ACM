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

int main() {
	int x=read();
	int cnt=1;
	for (int i=2;i*i<=x;++i) {
		if (x%i==0) {
			++cnt;
			if (x/i!=i)
				++cnt;
		}
	}
	printf("%d\n",cnt);
			
	return 0;
}
