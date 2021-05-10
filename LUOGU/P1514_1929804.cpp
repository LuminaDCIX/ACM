#include <set>
#include <cstdio>
#include <cassert>
#include <vector>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i,a,n) for (int i=a;i<=n;i++)
#define PER(i,a,n) for (int i=n;i>=a;i--)
#define MEM(a,b) memset(a,b,sizeof(a))
#define PAUSE system("pause")
#define FILE
#define DEBUG
typedef long long ll;
const ll mod=1000000007;
const int INF=10000000;

int e[505][505],vis[505][505],f[505][505][7];
int N,M,cnt,tot,l,r;
bool nok;

struct line{
        int l,r;
        const bool operator<(line b) const {
                if(l==b.l) return r<b.r;
                return l<b.l;
        }
        line(int a,int b) {
                l=a,r=b;
        }
};
vector<line> val;
inline int getc() {
        static const int L=1<<15;static char buf[L],*S=buf,*T=buf;
        if(S==T) {T=(S=buf)+fread(buf,1,L,stdin);if(S==T) return EOF;}
        return *S++;
}
inline int read() {
        int c; while(!isdigit(c=getc())); int tem=c-'0';
        while(isdigit(c=getc())) tem=(tem<<1)+(tem<<3)+c-'0';
        return tem;
}

void dfs(int x,int y) {
        if(x==N) {
                l=min(l,y),r=max(r,y);
                if(vis[x][y]) return;
        }
        //printf("%d %d %d %d\n",x,y,f[x][y][0],f[x][y][1]);
        if(vis[x][y]) {
                l=min(l,f[x][y][0]),r=max(r,f[x][y][1]);
                return;
        }
        vis[x][y]=1;
        int xi=x,yi=y;
        REP(i,-1,1) REP(j,-1,1) {
                if((i==0||j==0)&&i+j!=0) {
                        x+=i,y+=j;
                        if(x!=0&&x!=N+1&&y!=0&&y!=M+1&&e[xi][yi]>e[x][y]) {
                                dfs(x,y);
                                f[xi][yi][0]=min(f[x][y][0],f[xi][yi][0]);
                                f[xi][yi][1]=max(f[x][y][1],f[xi][yi][1]);
                        }
                        x-=i,y-=j;
            }
        }
        return;
}

void input() {
        N=read(),M=read();
        REP(i,1,N) REP(j,1,M) e[i][j]=read();
}
void solve() {
        REP(i,0,N-1) REP(j,0,M) f[i][j][0]=INF,f[i][j][1]=0;
        REP(i,0,M) f[N][i][0]=i,f[N][i][1]=i;
        REP(i,1,M) if(!vis[1][i]) {
                //printf("%d\n",i);
                l=INF,r=0;dfs(1,i);
                //printf("l=%d r=%d\n",l,r);
                if(l!=INF&&r!=0) val.push_back(line(l,r));
        }
        REP(i,1,M) if(!vis[N][i]) {nok=1,cnt++;}
        if(nok) {printf("%d\n%d\n",0,cnt);return;}

        sort(val.begin(),val.end());
        //REP(i,1,val.size()-1)printf("%d %d \n",val[i].l,val[i].r);
        int L=0,k=0,m=val.size(),mx=0,p=0;
        while(k<m) {
                while(val[k].l<=L+1&&k<m) {{if(val[k].r>mx) mx=val[k].r,p=k;};k++;}
                //if(val[k].l>L+1) k--;
                L=mx;
                k=p+1;
                cnt++;
                if(L==M) break;
        }
        printf("%d\n%d\n",1,cnt);
}

int main() {
        input();
        solve();
        return 0;
}
