#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=(a);i<=(n);++i)
typedef long long ll;
int a,b,c;
inline int mu(int x) {
    if (x==1) return 1;
    int ret=1;
    for (int i=2;i*i<=x;++i) if (x%i==0) {
            x/=i;
            if (x%i==0) return 0;
            ret=-ret;
        }
    if (x>1) ret=-ret;
    return ret;
}
inline ll calc(int k,int A) {
    ll ret=0;
    rep (i,1,A) if (__gcd(k,i)==1) ret+=A/i;
    return ret;
}
int main() {
    scanf("%d%d%d",&a,&b,&c);
    int lim=min(a,b);
    ll ret=0;
    rep (d,1,lim) {
        ll m=mu(d);
        if (m) {
            rep (k,1,c) if (__gcd(k,d)==1) ret+=m*calc(k,a/d)*calc(k,b/d)*(c/k);
        }
    }
    cout<<ret%(1<<30)<<endl;
    return 0;
}
