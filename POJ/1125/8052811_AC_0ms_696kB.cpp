#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
int n,e[105][105];	
//Product by MiracleEEEE 
inline int read(){
	char ch = getchar(); int re = 0; while (ch<'0' || ch>'9') ch=getchar();  
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
void input() {
	for ( int i = 1;i <= n;i ++ ) {
		int temp = read();
		for ( int j = 1; j <= temp; j ++ ) {
			int k = read(), t = read();
			e[i][k] = t;
		}
	}
}
bool solve() {
	while ( scanf("%d", &n) && n ) {
		for (int i = 1; i <= n ;i ++) for ( int j = 1; j <= n;j ++ ) if ( i == j) e[i][j] = 0 ;else e[i][j] = 99999;
		input();
		for ( int k = 1; k <= n ; k++)
			for (int i = 1; i <= n ; i ++ ) 
				for ( int j = 1; j <= n ; j ++ ) if ( e[i][j] > e[i][k] + e[k][j]) e[i][j] = e[i][k] + e[k][j];
		int ans = 0; long long sum = 999999999,ok = 0;
		//for (int i = 1; i <= n ; i ++,puts("")) for (int j = 1; j <= n ; j++) printf("%d ",e[i][j]);
		for (int i = 1; i <= n ; i ++ ) {
			int temp = 0, temok = 1;
			for ( int j = 1; j <= n ; j++ ) if ( e[i][j] != 99999 ) temp = max( temp, e[i][j]); else {temok = 0 ; break;}
			if ( temok && temp < sum ) ans = i, sum = temp,ok = 1;
		}
		if ( ok )printf("%d %lld\n",ans, sum); else printf("disjoint");
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
	//system("pause");
	return 0;
} 
