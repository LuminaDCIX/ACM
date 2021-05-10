// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=(a);i<=(n);++i)
#define per(i,a,n) for (int i=(n);i>=(a);--i)
typedef double db;
inline int read() {
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
const int N=13;
const int M=100+5;
const int MAX=1024+5;

int n,m;
db C[M][M];
int u[M],v[M];
int cnt[MAX];
inline int get(int s) {
    int ret=0;
    rep (i,1,m) if ((s&(1<<u[i]))&&(s&(1<<v[i]))) ++ret;
    return ret;
}
db con[MAX][M],dis[MAX][M];
int main() {
    n=read();
    m=read();
    C[0][0]=1;
    rep (i,1,M-1) {
        C[i][0]=1;
        rep (j,1,i) C[i][j]=C[i-1][j-1]+C[i-1][j];
    }
    rep (i,1,m) {
        u[i]=read()-1;
        v[i]=read()-1;
    }
    int all=(1<<n)-1;
    rep (s,0,all) cnt[s]=get(s);
    rep (i,0,n-1) con[1<<i][0]=1;
    rep (s,1,all) {
        int low=s&-s;
        for (int t=(s-1)&s;t;t=(t-1)&s) if (t&low) {
            rep (i,0,cnt[t]) rep (j,0,cnt[s^t]) dis[s][i+j]+=C[cnt[s^t]][j]*con[t][i];
        }
        rep (i,0,cnt[s]) con[s][i]=C[cnt[s]][i]-dis[s][i];
    }
    db ret=0;
    rep (i,0,m) ret+=dis[all][i]/C[m][i];
    ret/=m+1;
    printf("%.6f\n",ret);
    return 0; 
}
