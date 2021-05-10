#include<map>
#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
inline int read()
{
  int f=0,s=1,ch;
  for (ch=getchar();!isdigit(ch);(ch=='-')?s=-1:s=1,ch=getchar());
  for (;isdigit(ch);f=(f<<1)+(f<<3)+ch-'0',ch=getchar());
  return f*s;
}
typedef long long ll;
const int maxn=100000;
struct hash
{
	struct node
	{
		long long id,val;
		node(long long a,long long b)
		{
			id=a,
			val=b;
		}
	};
	vector<node> nodes[maxn+5];
	void clear()
	{
		for (int i=0;i<maxn;++i) {
			nodes[i].clear();
		}
	}
	void insert(long long val,long long id)
	{
		int t=val%maxn;
		for (int i=0;i<nodes[t].size();++i) {
			if (val==nodes[t][i].val) {
				return;
			}
		}
		nodes[t].push_back(node(id,val));
	}
	long long find(long long val)
	{
		int t=val%maxn;
		for (int i=0;i<nodes[t].size();++i) {
			if (nodes[t][i].val==val) {
				return nodes[t][i].id;
			}
		}
		return -1;
	}
}
h;
long long gcd(long long a,long long b)
{
	return !b?a:gcd(b,a%b);
}
void extgcd(long long a,long long b,long long &x,long long &y)
{
	if (b==0) {
		x=1;
		y=0;
		return;
	}
	extgcd(b,a%b,y,x);
	y-=(a/b)*x;
}
long long inv(long long a,long long p)
{
	long long x,y;
	extgcd(a,p,x,y);
	return (x%p+p)%p;
}
long long bsgs(long long a, long long b, long long c)
{
	h.clear();
	long long ans=1;
	long long tmp=1,cnt=0;
	for (int i=0;i<=64;++i) {
		if (tmp==b) {
			return i;
		}			
		tmp=tmp*a%c;
	}
	while ((tmp=gcd(a,c))!=1) {
		if (b%tmp) {
			return -1;
		}
		b/=tmp;
		c/=tmp;
		ans=ans*(a/tmp)%c;
		cnt++;
	}
	long long m=ceil(sqrt(1.0*c));
	long long t=1;
	for (int i=0;i<m;++i) {
		h.insert(t,i);
		if (ans*t%c==b) {
			return i+cnt;
		}
		t=t*a%c;
	}
	for (int i=0;i<m;++i) {
		long long val=inv(ans,c)*b%c;
		long long j=h.find(val);
		if (j!=-1) {
			return j+cnt+i*m;
		}
		ans=ans*t%c;
	}
	return -1;
}

int main()
{
  long long x,z,k;
  while (scanf("%lld%lld%lld",&x,&z,&k)&&x+z+k) {
    k%=z;
    x%=z;
 		long long ans=bsgs(x,k,z);
 		if (!(~ans)) {
 			puts("No Solution");
 		} 	
 		else {
 			printf("%lld\n",ans);
 		}
  }
  return 0;
}