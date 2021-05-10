#include <cstdio>
#include<iostream>
using namespace std;
//Product by MiracleEEEE
const int MAX = 105 ;
int tr[MAX][MAX],n,dp[MAX][MAX];
inline int read(){char ch = getchar(); int re = 0; bool fl  = 1; if(ch == '-') {fl = 0 ; ch = getchar();}
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return fl ? re : -re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool input(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= i ; j ++) {
			scanf("%d",&tr[i][j]);
		}
	}
	return true;
}

int dfs() {
	for(int i = n - 1; i >= 1; i--){
		for(int j = 1; j <= i ; j++){
			tr[i][j] += max(tr[i+1][j],tr[i+1][j+1]);
		}
	}
}


bool solve(){
	for(int i = 1; i <= n ; i++) dp[n][i] = tr[n][i];
	dfs();
	printf("%d",tr[1][1]);
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
} //123