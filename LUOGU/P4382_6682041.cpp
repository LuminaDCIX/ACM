// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define set(x,c) memset(x,c,sizeof(x))
#define siz(x) ((int)x.size())
#define rep(i,a,n) for (int i=(a);i<=(n);++i)
#define per(i,a,n) for (int i=(n);i>=(a);--i)
#define forg(u,o) for (int o=head[u];o;o=nxt[o])
typedef vector<int> vi;
inline int read()
{
    int f=1,x=0,ch=getchar();
    while (!isdigit(ch)) f=(ch=='-')?-1:1,ch=getchar();
    while (isdigit(ch)) x=x*10+ch-'0',ch=getchar();
    return f*x;
}
const int N=200+5;
const int V=200*2+5;
const int E=35260817;    
int T,C,n,m;
int b[N];
vi p[N][N];
struct net
{
    int nxt[E],cap[E],ver[E],head[V],cur[V];
    int s,t,tot;
    void init()
    {
        set(head,0),tot=1;
        s=V-2,t=V-1;
    }
    inline void add_edge(int u,int v,int c)
    {
        ++tot;
        nxt[tot]=head[u],ver[tot]=v,cap[tot]=c,head[u]=tot;
    }
    inline void add(int u,int v,int c)
    {
        add_edge(u,v,c),add_edge(v,u,0);
    }
    bool vis[V];
    int dist[V];
    bool bfs()
    {
        queue<int>que;
        set(vis,0);
        vis[s]=1;
        que.push(s);
        while (!que.empty()) {
            int u=que.front();
            que.pop();
            forg (u,o) {
                int v=ver[o];
                if (cap[o]&&!vis[v]) {
                    vis[v]=1;
                    dist[v]=dist[u]+1;
                    que.push(v);
                }
            }
        }
        return vis[t];
    }
    int dfs(int u,int f)
    {
        if (u==t||f==0) return f;
        int sum=0;
        for (int &o=cur[u];o;o=nxt[o]) {
            int v=ver[o];
            if (dist[v]==dist[u]+1&&cap[o]) {
                int nw=dfs(v,min(f,cap[o]));
                cap[o]-=nw,cap[o^1]+=nw;
                f-=nw,sum+=nw;
                if (!f) break;
            }
        }
        return sum;
    }
    bool flow()
    {
        int ans=0;
        while (bfs()) {
            memcpy(cur,head,sizeof(head));
            ans+=dfs(s,1e9);
        }
        return ans>0;
    }
} s;
int org[N],ans[N];
void solve1()
{
    s.init();
    set(ans,-1);
    rep (i,1,m) s.add(i+n,s.t,b[i]);
    rep (i,1,n) s.add(s.s,i,1);
    rep (i,1,n) {
        rep (j,1,m) {
            vi v;
            rep (k,0,siz(p[i][j])-1) {
                s.add(i,p[i][j][k]+n,1);
                v.pb(s.tot);
            }
            if (s.flow()) {
                ans[i]=j;
                break;
            }
            rep (k,0,siz(v)-1) {
                s.cap[v[k]]=0;
                s.cap[v[k]^1]=0;
            }
        }
    }
    rep (i,1,n) {
        if (i!=1) putchar(' ');
        printf("%d",ans[i]==-1?m+1:ans[i]);
    }
    puts("");
}
int ok[N];
void solve2()
{
    memcpy(org,ans,sizeof(org));
    rep (i,1,n) {
        if (i!=1) putchar(' ');
        if (org[i]!=-1&&ok[i]>=org[i]) {
            printf("%d",0);
            continue;
        }
        s.init();
        bool flg=0;
        rep (j,1,i) s.add(s.s,j,1);
        rep (j,1,m) s.add(j+n,s.t,b[j]);
        rep (j,1,ok[i]) rep (k,0,siz(p[i][j])-1) s.add(i,p[i][j][k]+n,1);
        if (!s.flow()) {
            printf("%d",i); 
            continue;;
        }
        rep (j,1,i-1) {
            if (org[j]==-1) continue;
            rep (k,0,siz(p[j][org[j]])-1) s.add(j,p[j][org[j]][k]+n,1);
            if (!s.flow()) {
                printf("%d",i-j);
                flg=1;
                break;
            }
        }
        if (!flg) printf("%d",i);
    }
    puts("");
}
int main()
{
    T=read(),C=read();
    while (T--) {
        n=read(),m=read();
        rep (i,1,m) b[i]=read();
        rep (i,1,n) {
            rep (j,0,m) p[i][j].clear();
            rep (j,1,m) {
                int c=read();
                p[i][c].pb(j);
            }
        }
        solve1();
        rep (i,1,n) ok[i]=read();
        solve2();
    }
    
    return 0;
}
