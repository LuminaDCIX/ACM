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
  for(ch=getchar();!isdigit(ch);(ch=='-')?s=-1:s=1,ch=getchar());
  for(;isdigit(ch);f=(f<<1)+(f<<3)+ch-'0',ch=getchar());
  return f*s;
}
typedef long long ll;
const int maxn=10007;
long long a,b,x1,p,t;
struct hash
{
	struct node
	{
		long long id,val;
		node(long long a,long long b)
		{
			val=a,
			id=b;
		}
	};
	vector<node> t[maxn];
	void clear()
	{
		for (int i=0;i<maxn;++i) {
			t[i].clear();
		}
	}
	void insert(long long val,long long id)
	{
		int s=val%maxn;
		for (int i=0;i<t[s].size();++i) {
			if (t[s][i].val==val) {
				return;
			}
		}
		t[s].push_back(node(val,id));
	}
	long long find(long long val)
	{
		int s=val%maxn;
		for (int i=0;i<t[s].size();++i) {
			if (t[s][i].val==val) {
				return t[s][i].id;
			}	
		}
		return -1;
	}	 
}
h;
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
long long bsgs(long long a,long long t,long long p)
{  
	h.clear();
	long long ans=(x1+b*inv(a-1,p)%p)%p;
	long long m=ceil(sqrt(1.0*p));
	long long s=1;
	for (int i=0;i<m;++i) {
		h.insert(s,i);
		s=s*a%p;
	}
	for (int i=0;i<m;++i) {
		long long val=inv(ans,p)*t%p;
		long long j=h.find(val);
		if (j!=-1) {
			return j+i*m;
		}
		ans=ans*s%p;
	}
	return -1;
}
int main()
{
  int T;
  scanf("%d",&T);
  while (T--) {
  	scanf("%lld%lld%lld%lld%lld",&p,&a,&b,&x1,&t);
  	if (x1==t) {
  		puts("1");
  		continue;	
  	}
  	if (a==0) {
  		if (b==t) {
  			puts("2");
  			continue;
  		}
  		else {
  			puts("-1");
  			continue;
  		}
  	}
  	if (a==1) {
  		if(b==0) {
  			puts("-1");
  			continue;
  		}
  		long long ans=((t+b-x1)%p+p)%p*inv(b,p)%p;
  		printf("%lld\n",ans==0?p:ans);
  		continue;
  	}

  	t=(t+inv(a-1,p)*b%p)%p;
  	long long ans=bsgs(a,t,p);
  	printf("%lld\n",ans==-1?-1:ans+1);
  }
  return 0;
}