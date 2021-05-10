#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int,int> pp;
int n , s[100005],k;
pp sum[100005];
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
	for(int i = 1; i <= n ; i++) {
		scanf("%d",&s[i]);
	}
	return true;
}
bool cmp_(pp a, pp b){return a.first < b . first;};
bool solve(){
	while(scanf("%d%d",&n,&k) == 2&&(n || k)) {
		input();s[0] = 0; 		sum[0].first = 0;sum[0].second = 0;
		for(int i = 1; i <= n; i++) sum[i].first = sum[i-1].first + s[i] ,sum[i].second = i;
		sort(sum, sum + n + 1,cmp_);
		for(int i = 1; i <=k ; i++) {
			int l = 1;scanf("%d",&l);
			int p = 0, q = 1,m= s[1],P = 0,Q = 1; int temp = 1 << 30;
			while(q <= n) {
				if(abs( l - abs(sum[q].first - sum[p].first ) ) < temp ) {temp = abs( l - abs(sum[q].first - sum[p].first )); m = abs(sum[q].first - sum[p].first);P= min(sum[q].second,sum[p].second) + 1; Q= max(sum[q].second,sum[p].second);}
				if(abs(sum[q].first - sum[p].first )< l) q++;
				else if(abs(sum[q].first - sum[p].first )> l) p++;
				else break;
				if(p == q) q++;
			}
				printf("%d %d %d\n",m,P,Q);
		}
		
	}//-15 -15 -10 -10 0 2 2 1 4 5
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
}  //reborn