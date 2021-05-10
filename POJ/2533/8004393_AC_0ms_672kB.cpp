#include <cstdio>
#include <iostream>
using namespace std;
int s[1005],n,f[1005]; 
//Product by MiracleEEEE 
inline int read_num(){
	char ch = getchar(); int re = 0; bool fl  = 1; if(ch == '-') {fl = 0 ; ch = getchar();}
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return fl ? re : -re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool input(){
	n = read_num();
	for(int i = 1; i <= n; i++) s[i] = read_num();
	return true;
}
bool solve(){
	f[1] = 1;
	fill(f+1,f+n+1,1);
	for(int i = 1; i <= n ; i++){
		for(int j = i  ;j >= 1 ; j--){
			if(s[j] < s[i]) f[i] = max(f[i] , f[j]+1);
		}//
	}
	int ans = 1;
	for(int i = 1; i <= n ; i++){
		ans = max(ans,f[i]);
	}
	write(ans);
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