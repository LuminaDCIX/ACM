#include <cstdio>
#include <cstdlib>
using namespace std;
typedef long long ll;
const ll mod=10001;
ll s[210],T;

void input() {
    scanf("%lld",&T);
    for (int i=1;i<=T;i++) scanf("%lld",&s[i*2-1]);
    return;
}

void Eu(ll a,ll b,ll &d,ll &x,ll &y) {
    if(!b) {d=a;x=1;y=0;return;}
    Eu(b,a%b,d,y,x); y-=x*(a/b); 
}
void solve() {
    ll b=0,k=0,d=0;
    for(ll a=0;a<=10001;a++) {
        bool ok=0;
        ll t=s[3]-a*a*s[1];
        Eu(10001l,a+1,d,k,b);
        if(t%d) continue;
        b=(b*t/d)%mod;
        if(b<0)continue;
        for (int i=2;i<=2*T;i++) {
            if (i&1) {
                int k=((a*s[i-1]+b)%mod);
                if(k!=s[i]) {ok=1; break;} 
            } else {
                s[i]=((a*s[i-1]+b)%mod);
            }
        }
        if(!ok) {break;} 
    }
}

void output() {
    for(int i=2;i<=2*T;i+=2) printf("%lld\n",s[i]);
}

int main() {
    input();
    solve();
    output();
    return 0;
}
