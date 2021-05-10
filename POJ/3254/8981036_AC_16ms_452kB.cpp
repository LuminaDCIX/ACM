#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;
int m, n;
const int mod = 100000000;
int e[15];
int s[705], top;
int f[15][(1 << 12) + 5];
bool ok(int x) {
     if(x & (x << 1)) return false;
     return true;     
}
void init() 
{
     int tot = 1 << m;
     for (int i = 0; i < tot; ++i) {
         if (ok(i)) {
            s[++top] = i;
         }
     }  
     return;
}
bool fit(int x, int k)
{
     if (x & e[k]) return false;
     return true;     
}
void input()
{
     scanf("%d%d", &n, &m);
     for (int i = 1; i <= n; ++i)
         for (int j = 1; j <= m; ++j) {
             int k;
             scanf("%d", &k);
             if (k == 1) {
                continue;      
             }
             e[i] = e[i] | (1 << (m - j));
         }
     return;     
}
void solve()
{
     init();
     for (int i = 1; i <= top; ++i) {
         if (fit(s[i],1)) {
            f[1][s[i]] = 1;
         }
     }
     for (int i = 2; i <= n; ++i) {
         for (int k = 1; k <= top; ++k) {
             if (!fit(s[k], i)) {
                continue;
             }  
             for (int j = 1; j <= top; ++j) {
                 if (!fit(s[j], i - 1)) {
                    continue;
                 }    
                 if (s[k] & s[j]) {
                    continue;
                 }
                 f[i][s[k]] = (f[i][s[k]] + f[i - 1][s[j]]) % mod;
             }
         }
     }
     int ans = 0;
     for (int i = 1; i <= top; ++i) {
         ans = (ans + f[n][s[i]]) % mod;
     }
     printf("%d\n", ans);
     return;
}
int main()
{
    input();
    solve();
    return 0;
}
