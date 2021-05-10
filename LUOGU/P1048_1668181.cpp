#include <cstdio>
#include <iostream>
using namespace std;
//Product by MiracleEEEE
int T, M, D[105],V[105],Dp[1005];
inline int read_num(){
	char ch = getchar(); int re = 0; bool fl  = 1; if(ch == '-') {fl = 0 ; ch = getchar();}
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return fl ? re : -re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool input(){
	cin >> T; cin >> M;
	for(int i = 1; i <= M ; i++) {
		cin >> D[i] >> V[i];
	}
	return true;
}
bool solve(){
	for(int i = 1; i <= M ; i++) {
		for(int j = T; j >= D[i] ; j--) {
			Dp[j] = max(Dp[j] , Dp[j-D[i]] + V[i]);
		}
	}
	write(Dp[T]);
	return true;
}
int main()
{
	#ifdef LOCAL
	//freopen("TEXT.txt","r",stdin);
//	freopen("OUTPUT.txt","w",stdout);
	#endif
	input();
	solve();
	return 0;
} 