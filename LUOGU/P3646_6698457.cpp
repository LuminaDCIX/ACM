// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
#define clr(a) memset(a,0,sizeof(a))
#define set(a,x) memset(a,x,sizeof(a))
#define rep(i,a,n) for (int i=(a);i<=(n);++i)
#define per(i,a,n) for (int i=(n);i>=(a);--i)
typedef long long ll;
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
int n;
namespace S1 {
    const int N=100+5;
    int a[N],A,B;
    ll ans,sum[N];
    bool dp[N][N];
    void calc(int x) {
        clr(dp);
        dp[0][0]=1;
        rep (i,1,n) {
            rep (j,1,n) {
                rep (k,0,j-1) {
                    if (dp[i-1][k]&&(((sum[j]-sum[k])>>x>>1)|(ans>>x>>1))==(ans>>x>>1)&&(!((sum[j]-sum[k])&(1ll<<x)))) dp[i][j]=1;
                }
            }
        }
    }
    void solve() {
        A=read();
        B=read();
        rep (i,1,n) a[i]=read();
        rep (i,1,n) sum[i]=sum[i-1]+a[i];
        per (i,0,62) {
            calc(i);
            bool flg=0;
            rep (j,A,B) flg|=dp[j][n];
            if (!flg) ans+=1ll<<i;
        }
        cout<<ans<<endl;
    }
}
namespace S2 {
    const int N=2000+5;
    int a[N],A,B;
    ll ans,sum[N];
    int dp[N];
    void calc(int x) {
        set(dp,0x3f);
        dp[0]=0;
        rep (i,1,n) {
            rep (j,0,i-1) {
                if ((((sum[i]-sum[j])>>x>>1)|(ans>>x>>1))==(ans>>x>>1)&&(!((sum[i]-sum[j])&(1ll<<x)))) dp[i]=min(dp[j]+1,dp[i]);
            }
        }
    }
    void solve() {
        A=read();
        B=read();
        rep (i,1,n) a[i]=read();
        rep (i,1,n) sum[i]=sum[i-1]+a[i];
        per (i,0,62) {
            calc(i);
            if (dp[n]>B) ans+=1ll<<i;
        }
        cout<<ans<<endl;
    }
}
int main() {
    n=read();
    if (n<=100) S1::solve();
    else S2::solve();
    return 0;
}
