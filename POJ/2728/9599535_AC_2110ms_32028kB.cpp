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
const int maxn=1000;
int n,tot;
int x[maxn+5],y[maxn+5],h[maxn+5];
bool vis[maxn+5];
double dist[maxn+5];
int head[maxn+5];
struct edge
{
	int from,to,c,nxt;
	double b,val;
}
edges[maxn*maxn+5];
inline void add_edge(int from,int to,int c,double b)
{
	edges[++tot].from=from;
	edges[tot].to=to;
	edges[tot].c=c;
	edges[tot].b=b;
	edges[tot].nxt=head[from];
	head[from]=tot;
}
inline double dis(int i,int j)
{
	return sqrt(1.00*(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}
inline double prim()
{
	memset(vis,0,sizeof(vis));
	for(int i=2;i<=n;++i){
		dist[i]=1e9;
	}
	dist[1]=0;
	double ret=0.0;
	while(true){
		int j=-1;
		double mn=1e9;
		for(int l=1;l<=n;++l){
			if(!vis[l]&&dist[l]<mn){
				mn=dist[l];
				j=l;
			}
		}
		if(j==-1){
			return ret;
		}
		ret+=mn;
		vis[j]=1;
		for(int i=head[j];i;i=edges[i].nxt){
			int v=edges[i].to;
			if(!vis[v]&&dist[v]>edges[i].val){
				dist[v]=edges[i].val;
			}
		}
	}
	return ret;
}
int main()
{
	while((n=read())&&n){
		tot=0;
		memset(head,0,sizeof(head));
		for(int i=1;i<=n;++i){
			x[i]=read(),y[i]=read(),h[i]=read();
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				add_edge(i,j,abs(h[i]-h[j]),dis(i,j));
			}	
		}
		double l=0.0,r=1000.00;
		int cnt=1;
		while(cnt<=25){
			double mid=(l+r)/2;
			for(int i=1;i<=tot;++i){
				edges[i].val=edges[i].c-edges[i].b*mid;
			}
			double t=prim();
			if(t==0){
				l=mid;
				break;
			}
			if(t>=0){
				l=mid;
			}
			if(t<0){
				r=mid;
			}
			cnt++;
		}
		printf("%.3f\n",l);
	}	
	return 0;	
}
