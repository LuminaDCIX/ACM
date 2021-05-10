#include<cstdio>  
#include<iostream>  
using namespace std;  
  
int n,x,y,fi[100001],w[200001],ne[200001],du[100001],cnt,ans;  
  
int read()  
{  
    int x=0,f=1;char ch=getchar();  
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1;ch=getchar();}  
    while(ch>='0' && ch<='9') {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}  
    return x*f;   
}  
  
void add(int u,int v)  
{  
    w[++cnt]=v;ne[cnt]=fi[u];fi[u]=cnt;du[u]++;  
    w[++cnt]=u;ne[cnt]=fi[v];fi[v]=cnt;du[v]++;  
}  
  
int dfs(int u,int fa)  
{  
    if(du[u]==1) return 1;  
    int now,aa=0,bb=0;  
    for(int i=fi[u];i;i=ne[i])  
      if(w[i]!=fa)  
      {  
        now=dfs(w[i],u);  
        if(now==1) aa++;  
        else if(now==2) bb++;  
      }  
    while(aa>2) ans++,aa-=2;  
    while(bb>1) ans++,bb-=2;  
    while(aa>1 && bb) ans++,aa--,bb--;  
    aa+=bb*2;  
    return aa<2 ? aa:2;  
}  
  
int main()  
{  
    n=read();  
    if(n<=3)  
    {  
        puts("1");return 0;  
    }  
    for(int i=1;i<n;i++) x=read(),y=read(),add(x,y);  
    for(int i=1;i<=n;i++) if(du[i]>1)  
    {  
        if(dfs(i,0)==2) ans++;break;  
    }  
    printf("%d\n",ans);  
    return 0;  
}  