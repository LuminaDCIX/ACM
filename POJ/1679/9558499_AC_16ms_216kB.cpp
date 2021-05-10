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
const int maxn=100;
int fa[maxn+5];
int n,m,ans,tot;
struct edge
{
	int from,to,val;
}
edges[maxn*maxn+5];
bool cmp(edge a,edge b)
{
	return a.val<b.val;
}
inline int find_fa(int x)
{
	return fa[x]==x?x:fa[x]=find_fa(fa[x]);
}
inline void add_edge(int from,int to,int val)
{
	edges[++tot].to=to,
	edges[tot].from=from,
	edges[tot].val=val;
}
inline bool judge(int x,int y)
{
	return (find_fa(edges[x].from)==find_fa(edges[y].from)&&find_fa(edges[x].to)==find_fa(edges[y].to))||(find_fa(edges[x].to)==find_fa(edges[y].from)&&find_fa(edges[x].from)==find_fa(edges[y].to));
}
inline bool kruskal()
{
	for(int i=1;i<=n;++i){
		fa[i]=i;
	}
	sort(edges+1,edges+1+m,cmp);
	for(int i=1;i<=m;++i){
		int tval=edges[i].val;
		int fx=find_fa(edges[i].from);
		int fy=find_fa(edges[i].to);
		if(fx==fy){
			continue;
		}
		int pos=i+1;
		while(edges[pos].val==tval){
			if(judge(i,pos)){
				return true;
			}
			pos++;
		}
		ans+=edges[i].val;
		fa[fx]=fy;
	}
	return false;
}
int main()
{
	int T=read();
	while(T--){
		tot=0;
		ans=0;
		n=read(),m=read();
		for(int i=1,u,v,w;i<=m;++i){
			u=read(),v=read(),w=read();
			add_edge(u,v,w);
		}
		if(kruskal()){
			puts("Not Unique!");
		}	
		else{
			printf("%d\n",ans);
		}
	}
	return 0;
}