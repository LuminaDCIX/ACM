#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
int n,c[100005],k,maX,ans; long long sum;
//Product by MiracleEEEE 
inline int read(){
	char ch = getchar(); int re = 0; bool fl  = 1; if(ch == '-') {fl = 0 ; ch = getchar();}
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return fl ? re : -re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool input(){
	n = read();
	for(int i = 1; i <= n ; i++){
		c[i] = read();
		sum += c[i];
		maX = max(maX,c[i]);
	}
	k = read();
	return true;
}
bool check(int mid){
	long long cnt = 0;
	for(int i = 1; i <= n ; i++){
		if(c[i] <= mid)continue;
		else cnt += ceil(double(c[i ]- mid) / (k - 1));
	}if(cnt > mid) return false;
	else return true;
}
bool solve(){
	int l = 1 , r = 1000000000,mid;
	if(k == 1) ans = maX;
	else while( r >= l){
		mid = (l + r) / 2;
		if(check(mid)) {r = mid -1; ans = mid;}	
		else l = mid + 1;
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