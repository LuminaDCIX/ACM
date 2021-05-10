#include <cstdio>
#include <cstring>
using namespace std;
//Product by MiracleEEEE
char id[2005][10];
int e[2005][2005], dist[2005], vis[2005], n;
inline int read(){
	char ch = getchar(); int re = 0; while (ch<'0' || ch>'9') ch=getchar();  
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool input(){
	memset(e, 0, sizeof(e));
	memset(dist, 0, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i ++) scanf("%s",id[i]);
	for (int i = 1; i <= n; i ++) {
		e[i][i] = 0x3f3f3f3f;
		for (int j = i + 1; j <= n; j ++) {
			for (int k = 0; k < 7; k ++) {
				if (id[i][k] != id[j][k]) {
					e[i][j]++, e[j][i] ++;
				}
			}
		}
	}
	return true;
}
bool solve(){
	while (scanf("%d",&n) && n) {
		input();
		//for (int i = 1; i <= n; i ++,puts("")) 
		//	for (int j = 1; j <= n; j ++) printf("%d ",e[i][j]);
		for (int i = 1; i <= n; i ++) dist[i] = e[1][i];
		vis[1] = 1;
		int ans = 0;
		for (int i = 2; i <= n; i ++) {
			int m = 0x3f3f3f3f, k = 0;
			for (int j = 1; j <= n; j ++) {
				if (!vis[j] && m > dist[j]) {
					m = dist[j];
					k = j;
				}
			}
			vis[k] = 1;
			ans += dist[k];
			for (int j = 1; j <= n; j ++) {
				if (!vis[j] && dist[j] > e[k][j]) {
					dist[j] = e[k][j];
				}
			}
		}
		printf("The highest possible quality is 1/%d.\n",ans);
	}
	return true;
}
int main()
{
	#ifdef LOCAL
	freopen("TEXT.txt","r",stdin);
	freopen("OUTPUT.txt","w",stdout);
	#endif
	solve();
	return 0;
} 
