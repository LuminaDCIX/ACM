#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
const int INF = 0x3f3f3f3f;  
//Product by MiracleEEEE 
inline int read_num(){
	char ch = getchar(); int re = 0; bool fl  = 1; if(ch == '-') {fl = 0 ; ch = getchar();}
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return fl ? re : -re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
struct l{int top ; int s[1000005];}l,r,Max;
int sum [1000005] , n;
bool solve(){
	while( ~ scanf("%d" , &n )) {
			    memset(sum,0,sizeof(sum));
	        Max.top = 0 ; l.top = 0; r.top = 0; Max.s[0] = - INF;  
			while ( n -- ) {
			char temp ;
			getchar() ;
			scanf ("%c",  &temp ) ;
			if ( temp == 'I' ) {
				int key ; scanf("%d", &key ) ;
				l.s[ ++ l.top ] = key ;
				sum[ l.top ] = sum [ l.top - 1] + key ;
				Max.s[ ++ Max.top  ] = max( Max.s[ Max.top - 1 ] , sum[ l.top]) ;
			} else if ( temp == 'D' ) {
				l.top -- ;
				Max.top -- ;
				//Max.s[ Max.top ] = max( Max.s[ Max.top - 1 ] , sum[ l.top]) ;
				
			} else if ( temp == 'L' && l.top != 0 ) {
				int key = l.s[l.top--] ;
				Max.top -- ;
				r.s [ ++ r.top  ] = key ;
				//Max.s[ Max.top ] = max( Max.s[ Max.top - 1 ] , sum[ l.top ]) ;
			} else if ( temp == 'R' && r.top != 0) {
				int key = r.s[r.top--] ;
				l.s [ ++ l.top ] = key ;
				sum [l.top ] = sum [ l.top - 1 ] + key ;
				Max.s[ ++ Max.top  ] = max( Max.s[ Max.top - 1 ] , sum[ l.top]) ;
			} else if ( temp == 'Q' ) {
				int key ; scanf ("%d" , &key ) ;
				printf("%d\n" , Max.s[key]) ;
			}
		}
	
	}
	// 1 2 3 4 5 6 7 8
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
} //123