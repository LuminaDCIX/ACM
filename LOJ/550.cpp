#include <bits/stdc++.h>

using namespace std;

int main() {
        int T;
        scanf("%d",&T);
        while (T--) {
                int n;
                int m;
                int k;
                scanf("%d %d %d",&n,&m,&k);
                printf("%lld\n",n*((long long)m*m/4)+m*((long long)n*n/4));
        }
}