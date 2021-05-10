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
const int maxm=5000;
int n,m,tot;
int val[maxn+5];
int head[maxn+5];
bool inq[maxn+5];
int cnt[maxn+5];
double dist[maxn+5];
struct edge
{
	int nxt,from,to,p;
	double val;
}
edges[maxm+5];
inline void add_edge(int from,int to,int val)
{
	edges[++tot].to=to,
	edges[tot].from=from,
	edges[tot].nxt=head[from],
	edges[tot].p=val;
	head[from]=tot;
}

inline bool spfa()
{
	memset(inq,0,sizeof(inq));
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;dist[i]=1e9,++i);
	cnt[1]=1,
	inq[1]=1;
	dist[1]=0.0;
	queue<int> que;
	que.push(1);
	while(!que.empty()){
		int u=que.front();
		que.pop();
		inq[u]=0;
		for(int i=head[u];i;i=edges[i].nxt){
			int v=edges[i].to;
			if(dist[u]+edges[i].val<dist[v]){
				dist[v]=dist[u]+edges[i].val;
				cnt[v]++;
				if(cnt[v]>n){
					return true;
				}
				if(!inq[v]){
					que.push(v);
					inq[v]=1;
				}
			}
		}
	}
	return false;
}

int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;val[i]=read(),++i);
	for(int i=1;i<=m;++i){
		int u=read(),v=read(),val=read();
		add_edge(u,v,val);
	}
	double l=0.0,r=2000.00;
	int times=0;
	while(times<=25){
		double mid=(l+r)/2;
		for(int i=1;i<=m;edges[i].val=mid*edges[i].p-val[edges[i].from],++i);
		if(spfa()){//has nagative cir		
			l=mid;
		}
		else{
			r=mid;
		}
		times++;
	}
	printf("%.2f\n",l);
	return 0;
}