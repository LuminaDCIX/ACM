#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;
//Product by MiracleEEEE 
struct point { int x, y;}points[5010];
int n,vis[5010];
double dist[5010],ans;
double len ( int a, int b ) {
	return (double)sqrt( 1.0 * ( points[a].x - points[b].x ) * ( points[a].x - points[b].x ) + 1.0 * ( points[a].y - points[b].y ) * ( points[a].y - points[b].y ));
} 
inline int read(){
	char ch = getchar(); int re = 0; while (ch<'0' || ch>'9') ch=getchar();  
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool input(){
	n = read();
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d",&points[i].x, &points[i].y);
	}
	return true;
}
bool solve(){
	for (int i = 1; i <= n; ++i) { dist[i] = 99999999.0;}
	dist[1] = 0.0;
	for (int i = 1; i <= n; ++i) {
		double temp = 99999999.0 ; int k = 0;
		for ( int j = 1; j <= n; j ++ ) {
			if ( vis[j] ) continue;
			if ( dist[j] < temp ) {
				temp = dist[j];
				k = j;
			}
		}
		vis[k] = 1;
		ans += temp;
		for (int j = 1; j <= n; ++j) {
			if ( !vis[j] && len (k, j) < dist[j] )  dist[j] = len(k,j);
		}
	}
	printf("%.2f",ans);
	return true;
}
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	input();
	solve();
	return 0;
} 
