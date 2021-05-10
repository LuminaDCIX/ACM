#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
__int64 d[100010],h,a,b,c,ans;
bool v[100010];
void bfs()
{
	queue<int> q;
	memset(d,0x7f,sizeof(d));
	d[1%a]=1; q.push(1%a); v[1%a]=1;
	while(q.size())
	{
		int x=q.front(),y; q.pop(); v[x]=0;
		if(d[y=(x+b)%a]>d[x]+b)
		{
			d[y]=d[x]+b;
			if(!v[y]) v[y]=1,q.push(y);
		}
		if(d[y=(x+c)%a]>d[x]+c)
		{
			d[y]=d[x]+c;
			if(!v[y]) v[y]=1,q.push(y);
		}
	}
}

int main()
{
	cin>>h>>a>>b>>c;
	swap(a,b);
	bfs();
	for(int i=0;i<a;i++)
		if(d[i]<=h) ans+=(h-d[i])/a+1;
	cout<<ans<<endl;
}
