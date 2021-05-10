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
const int maxn=200;
int fa[maxn+5];
int tot,m,n,ks;
int x[maxn+5],y[maxn+5];
struct edge
{
	int from,to;
	double val;
}
edges[maxn*maxn+5];
inline void add_edge(int from,int to,double val)
{
	edges[++tot].to=to,
	edges[tot].from=from,
	edges[tot].val=val;
}
bool cmp(edge a,edge b)
{
	return a.val<b.val;
}
inline int find_fa(int x)
{
	return x==fa[x]?x:fa[x]=find_fa(fa[x]);
}
inline double dist(int i,int j)
{
	return sqrt(1.00*(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}
inline double solve()
{
	for(int i=1;i<=n;fa[i]=i,++i);
	sort(edges+1,edges+1+m,cmp);
	for(int i=1;i<=m;++i){
		edge e=edges[i];
		int fx=find_fa(e.from);
		int fy=find_fa(e.to);
		if(fx==fy){
			continue;
		}
		fa[fx]=fy;
		if(find_fa(1)==find_fa(2)){
			return e.val;
		}
	}
}
int main()
{
	while(1){
		n=read();
		if(!n){
			return 0;
		}
		tot=0;
		for(int i=1;i<=n;x[i]=read(),y[i]=read(),++i);
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(i!=j){
					add_edge(i,j,dist(i,j));
				}
			}
		}
		m=n*(n-1);
		printf("Scenario #%d\n",++ks);
		printf("Frog Distance = %.3f\n\n",solve());
	}
	return 0;
}
