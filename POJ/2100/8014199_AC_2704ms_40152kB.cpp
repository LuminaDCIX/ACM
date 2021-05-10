#include <cstdio>
#include <iostream>
long long n;
using namespace std; 
struct queue{int front,tair;int s[10000005];}q;
int ans[100000000],cas,Temp;
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
	scanf("%lld",&n);
	return true;
}
bool solve(){
	q.s[q.tair++] = 1;
	long long temp = 1;
	long long i = 1;
	while(i * i <= n ){
		temp += i * i;
	    if ( temp < n) q.s[q.tair++] = i;
		else   { while (temp> n){temp -= 1LL * q.s[q.front] * q.s[q.front]; q.front ++;}q.s[q.tair++] = i;	}
		if(temp == n) {
			cas++;
			ans[Temp++] = q.tair-q.front;
			int k = q.front;
			while(k != q.tair) ans[Temp++] = q.s[k],k++;
			temp -= 1LL * q.s[q.front] * q.s[q.front];
			q.front++; 
		}
		i++;
	}
	printf("%d\n",cas); {
		int i = 0;
		while(ans[i]!=0) {
			cout << ans[i] ;
			int j = i + 1;
			for(; j <= ans[i] +i ; j++) cout<<" " <<ans[j];
			cout << endl;
			i = j;
		}
		
	
	
	}

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
} //hehe