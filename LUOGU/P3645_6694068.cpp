// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
#define set(x,a) memset(x,a,sizeof(x))
#define rep(i,a,n) for (int i=(a);i<=(n);++i)
#define per(i,a,n) for (int i=(n);i>=(a);--i)
#define forg(u,o) for (int o=head[u];o;o=nxt[o])
inline int read()
{
    int f=1,x=0,ch=getchar();
    while (!isdigit(ch)) {
        f=(ch=='-')?-1:1;
        ch=getchar();
    }
    while (isdigit(ch)) {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return f*x;
}
const int N=30000+5;
const int V=6307387;
const int E=35260817;
int n,m,lim;
int b[N],p[N];
struct spfa
{
    int head[V],nxt[E],ver[E],cost[E];
    inline int id(int i,int j)
    {//i=0 to lim
        return i*n+j;
    }
    void add(int u,int v,int w)
    {
        // cerr<<u<<" "<<v<<endl;
        static int tot=0;
        ++tot;
        nxt[tot]=head[u];
        ver[tot]=v;
        cost[tot]=w;
        head[u]=tot;
    }
    int dist[V],inq[V];
    int solve()
    {
        set(dist,0x3f3f);
        dist[b[1]]=0;
        inq[b[1]]=1;
        deque <int> que;
        que.push_back(b[1]);
        while (!que.empty())
        {
            int u=que.front();
            que.pop_front();
            inq[u]=0;
            forg (u,o)
            {
                int v=ver[o];
                if (dist[v]>dist[u]+cost[o]) {
                    dist[v]=dist[u]+cost[o];
                    if (!inq[v]) {
                        inq[v]=1;
                        if (!que.empty()&&dist[v]<dist[que.front()]) {
                            que.push_front(v);
                        } else {
                            que.push_back(v);
                        }
                    }
                }
            }
        }
        return dist[b[2]]==0x3f3f3f3f?-1:dist[b[2]];
    }
} s;
void build()
{
    rep (i,1,m)
    {
        if (p[i]>lim)
        {
            rep (j,1,n) {
                if (b[i]+j*p[i]<=n) {
                    s.add(b[i],b[i]+j*p[i],j);
                } else {
                    break;
                }
            }
            per (j,-n,-1) {
                if (b[i]+j*p[i]>=1) {
                    s.add(b[i],b[i]+j*p[i],-j);
                } else {
                    break;
                }
            }
        } else {
            s.add(b[i],s.id(p[i],b[i]),0);
        }
    }
    rep (i,1,lim)
    {
        rep (j,0,i-1) {
            rep (k,0,n) {
                if (j+(k+1)*i>n) {
                    break;
                } else {
                    if (j+k*i==0) continue;
                    int u=s.id(i,j+k*i);
                    int v=s.id(i,j+(k+1)*i);
                    s.add(u,v,1);
                    s.add(v,u,1);
                }
            }
        }
        rep (j,1,n) {
            s.add(s.id(i,j),j,0);
        }
    }
}
int main()
{
    n=read();
    m=read();
    lim=min(100.00,sqrt(n));
    rep (i,1,m) {
        b[i]=read();
        p[i]=read();
        ++b[i];
    }
    build();
    printf("%d\n",s.solve());
    return 0;
}
