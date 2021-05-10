#include <cstdio>
#include <cstring>
using namespace std;
//Product by MiracleEEEE 
int T, N, vis[505], e[505][505];
long long dist[505], ans;
inline int read(){
	char ch = getchar(); int re = 0; while (ch<'0' || ch>'9') ch=getchar();  
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool input(){
	memset(dist, 0, sizeof(dist)); 
	memset(vis, 0, sizeof(vis));
	N = read();ans = 0;
	for (int i = 1; i <= N; i ++) {
		for (int j = 1; j <= N; j ++) {
			e[i][j] = read();
			if (i == j) e[i][j] = 0x3f3f3f3f;
		}
	} 
	return true;
}
bool solve(){
	T = read();
	while (T --) {
		input();
		for (int i = 1; i <= N; i ++) dist[i] = e[1][i];
			vis[1] = 1;
		for (int i = 2; i <= N; i ++) {
			int k = 0, m = 0x3f3f3f3f;
			for (int j = 1; j <= N; j ++) {
				if (!vis[j] && dist[j] < m) {
					m = dist[j];
					k = j;
				}
			}
			vis[k] = 1;
			ans = ans > dist[k] ? ans : dist[k];
			for (int i = 1; i <= N; i ++) {
				if (!vis[i] && dist[i] > e[k][i]) dist[i] = e[k][i];
			}
		}
		printf("%lld\n",ans);
	}
	return true;
}
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	solve();
	return 0;
} 
