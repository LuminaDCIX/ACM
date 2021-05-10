#include <bits/stdc++.h>

using namespace std;

#define MP make_pair
#define PB push_back
#define FI first
#define SE second
#define SIZ(x) ((int)x.size())
#define SET(x,k) memset(x,k,sizeof(x))
#define ALL(x) x.begin(),x.end()
#define REP(i,a,n) for (int i=(a);i<(n);++i)
#define PER(i,a,n) for (int i=(n)-1;i>=(a);--i)
#define FORG(o,u) for (edge* o=head[u];o;o=o->nxt)

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


string ss;

bool ok[256];

bool check() {
	REP (i,0,ss.length()-1)
		if (ok[ss[i]]&&ok[ss[i+1]])
			return true;
	return false;
}

string erase(int k) {
	string s;
	REP (i,0,ss.length())
		if (i!=k)
			s+=ss[i];
	return s;
}

int main() {
	ok['a']=ok['e']=ok['i']=ok['o']=ok['u']=ok['y']=1;
	int n=read();
	cin>>ss;
	while (check()) {
		REP (i,0,ss.length()-1)
			if (ok[ss[i]]&&ok[ss[i+1]]) {
				ss=erase(i+1);
				break;
			}
	}
	cout<<ss<<endl;
	return 0;
}
