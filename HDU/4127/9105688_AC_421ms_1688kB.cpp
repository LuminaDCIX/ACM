#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <queue>  
#define maxn 10  
#define INF 0x3f3f3f3f  
using namespace std;  
  
int n,m,ans,flag,depth;  
int mp[maxn][maxn];  
int dx[]={-1,1,0,0};  
int dy[]={0,0,-1,1};  
bool vis[maxn][maxn];  
struct Node  
{  
    int x,y;  
}cur,now,q[100];  
struct node  
{  
    int num;  
    Node xx[100];  
};  
  
void bfs(node &tt,int color[])  
{  
    int i,j,nx,ny,tx,ty;  
    int head=0,tail=-1;  
    tt.num=0;  
    memset(vis,0,sizeof(vis));  
    cur.x=cur.y=1;  
    vis[1][1]=1;  
    q[++tail]=cur;  
    while(head<=tail)  
    {  
        now=q[head];  
        head++;  
        tt.xx[++tt.num]=now;  
        nx=now.x;  
        ny=now.y;  
        for(i=0;i<4;i++)  
        {  
            tx=nx+dx[i];  
            ty=ny+dy[i];  
            if(tx<1||tx>n||ty<1||ty>n||vis[tx][ty]||mp[tx][ty]!=mp[nx][ny]) continue ;  
            cur.x=tx;  
            cur.y=ty;  
            vis[tx][ty]=1;  
            q[++tail]=cur;  
        }  
    }  
    for(i=1;i<=n;i++)    // 标记还剩几种颜色  
    {  
        for(j=1;j<=n;j++)  
        {  
            if(!vis[i][j]) color[mp[i][j]]=1;  
        }  
    }  
}  
void dfs(int c,int cnt,int step)   // 当前颜色 连通块大小 步数  
{  
    if(step>depth||flag) return ;  // 已经搜到结果就return  
    int i,j,t=0,num,color[6]={0};  
    node tt;  
    bfs(tt,color);  
    num=tt.num;  
    if(num<=cnt) return ;      // 保证每次都要向变多的方向搜索  
    for(i=0;i<6;i++)           // 计算还剩几种颜色  
    {  
        t+=color[i];  
    }  
    if(step+t>depth) return ;  // 当前步数+还剩颜色数>depth return  
    if(num==n*n)  
    {  
        flag=1;  
        ans=step;  
        return ;  
    }  
    for(i=0;i<6;i++)  
    {  
        if(i==c) continue ;  
        for(j=1;j<=num;j++)   // 改变颜色  
        {  
            mp[tt.xx[j].x][tt.xx[j].y]=i;  
        }  
        dfs(i,num,step+1);  
        for(j=1;j<=num;j++)   // 还原颜色  
        {  
            mp[tt.xx[j].x][tt.xx[j].y]=c;  
        }  
    }  
}  
void IDA()  
{  
    int i,j;  
    flag=0;  
    depth=1;  
    while(!flag)  
    {  
        dfs(mp[1][1],0,0);  
        depth++;  
    }  
}  
int main()  
{  
    int i,j;  
    while(scanf("%d",&n),n)  
    {  
        for(i=1;i<=n;i++)  
        {  
            for(j=1;j<=n;j++)  
            {  
                scanf("%d",&mp[i][j]);  
            }  
        }  
        ans=INF;  
        IDA();  
        printf("%d\n",ans);  
    }  
    return 0;  
}  