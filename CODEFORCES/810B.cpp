#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>

using namespace std;

long long add[100005];
long long k[100005];
long long c[100005];
int n,f;
unsigned long long ans;
int id[100005];

bool cmp(int a,int b)
{
	return add[a]>add[b];
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>f;
	for (int i=1;i<=n;++i) {
		cin>>k[i]>>c[i];
		id[i]=i;
		if (k[i]>=c[i]) {
			continue;			
		}	
		add[i]=min(k[i]*2ll,c[i])-k[i];
	}
	sort(id+1,id+1+n,cmp);
	for (int i=1;i<=f;++i) {
		ans+=add[id[i]]*1ll;
	}
	for (int i=1;i<=n;++i) {
		ans+=min(k[i],c[i]);								
	}
	cout<<ans<<endl;
	return 0;
}