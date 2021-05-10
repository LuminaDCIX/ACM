#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
//Product by MiracleEEEE 
struct dat{int profit, deadline;}data[10010]; 
int n, set[10010],maxt; long long ans;
void init () { for ( int i = 1; i <= maxt; i ++ ) set[i] = i;}
int find ( int t ) { return set[t] == t ? t : set[t] = find(set[t]);}
void unite ( int x, int y ) { int fx = find(x), fy = find(y); if ( fx != fy) set[x] = fy;}
bool C( dat i, dat j ){return i.profit > j.profit;} 
inline int read(){
	char ch = getchar(); int re = 0; while (ch<'0' || ch>'9') ch=getchar();  
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool input(){
	for ( int i = 1; i <= n; i ++ ) data[i].profit = read(), data[i].deadline = read(),maxt = max(maxt,data[i].deadline);
	return true;
}
bool print() { for ( int i = 1;i <= maxt; i ++ ) printf("%d ",set[i]); printf("\n");}
bool solve(){ 
	while ( ~scanf ("%d", &n) ) {
		maxt = 0;input(); ans = 0; init();
		sort ( data + 1, data + n + 1, C );
		for ( int i = 1; i <= n; i ++ ) {
			int t = find ( data[i].deadline );
			if ( t == 0 ) continue; else {
				ans += data[i].profit;
				unite ( t, t - 1 );
				//print();
			} 
		}
		printf("%lld\n", ans);
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