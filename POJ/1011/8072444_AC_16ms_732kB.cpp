#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n,a[70],L,sum,s[70];
bool vis[70];

bool cmp ( int a, int b ) { return a > b;}

bool dfs ( int l, int pos , int tot ) {
	//cout << a[pos] << endl ;
	if ( l == 0 ) {
		if ( tot == n ) return true;
		else return dfs( L, 0, tot );
	}
	//cout << l << " " << tot << endl;
	//for (int i = 1; i <= n; i ++) cout << vis[i];puts("");
	if (l == L) {
			for ( int i = pos + 1; i <= n; i ++ ) {
			if ( a[i] == a[i-1] && !vis[i-1]) continue;
			if ( !vis[i] ){
				if ( l - a[i] >= 0) {
					vis[i] = 1;
					if(dfs( l - a[i], i, tot + 1 )) return true;
					vis[i] = 0;
				}
				return false;
			} 
		}
	}
	if (s[n] - s[pos] < l) return false;
	for ( int i = pos + 1; i <= n; i ++ ) {
		if ( a[i] == a[i-1] && !vis[i-1]) continue;
		if ( !vis[i] ){
			if ( l == a[i] ){
				 vis[i] = 1;
				 if (dfs(0, i,tot + 1)) return true;
				 vis[i] = 0;
				 return false;
			}
			if ( l - a[i] > 0) {
				vis[i] = 1;
				if(dfs( l - a[i], i, tot + 1 )) return true;
				vis[i] = 0;
			}
			
		} 
	}
	return false;
}

int main() {
	while ( cin >> n && n ) {
		memset(vis, 0 ,sizeof ( vis ) ); sum = 0;
		for ( int i = 1; i <= n; i ++ ) {
			scanf( "%d", &a[i] );
			sum += a[i];
		}
		sort( a + 1, a + n + 1,cmp );
		for (int i = 1; i <= n; i ++) s[i] = s[i-1] + a[i];
		for (  L = a[1]; L < sum; L ++ ) {
			if ( sum % L != 0 ) continue;
			memset( vis, 0, sizeof(vis));
			if ( dfs ( L, 0, 0 )) break;
		}
		printf("%d\n", L);
	}

	return 0;
}