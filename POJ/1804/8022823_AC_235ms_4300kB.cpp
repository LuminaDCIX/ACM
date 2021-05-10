#include <cstdio>
#include <cstring>
using namespace std;
int n, s[500005], temp[500005],kase,m; long long ans;
//Product by MiracleEEEE
void merge ( int l, int mid, int r ) {
    int i = l, j = mid + 1 ,k = l ;
    while( i < j && i <= mid && j <= r ) {
        if ( s[i] <= s[j] ) temp[k++] = s[i++] ,ans += j - mid - 1;
        else temp[k++] = s[j++] ;//, ans += mid + 1 - i;
    }
    while ( i <= mid ) temp[k++] = s[i++], ans += j - mid - 1;
    while ( j <= r ) temp[k++] = s[j++];
    for(int t = l; t <= r ; t ++ ) s[t] = temp[t] ;
}
void mergesort ( int l, int r ) {
    if( l < r ) {
        int mid = ( l + r ) >> 1 ;
        mergesort ( l, mid );
        mergesort ( mid + 1, r );
        merge ( l, mid, r ) ;
    }
}
bool solve(){
    while ( m--) {
    	scanf ("%d", &n);
        memset ( s, 0, sizeof( s ) ) ; ans = 0 ; memset ( temp, 0, sizeof( temp )) ;
        for(int i = 0 ; i < n ; i ++ ) scanf("%d", &s[i] );
        mergesort( 0, n - 1 ) ;
        printf("Scenario #%d:\n",++kase);
        printf("%lld\n\n", ans );
    }
    return true;
}
int main()
{
	scanf("%d",&m);
    #ifdef LOCAL
    //freopen("TEXT.txt","r",stdin);
    //freopen("OUTPUT.txt","w",stdout);
    #endif
    solve();
    return 0;
}
