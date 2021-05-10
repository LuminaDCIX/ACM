#include <cstdio>
using namespace std;
//Product by MiracleEEEE 
inline int read_num(){
	char ch = getchar(); int re = 0; bool fl  = 1; if(ch == '-') {fl = 0 ; ch = getchar();}
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return fl ? re : -re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
int n; long long ans;
struct p{int w, h;};
struct stack{int top; p s[100005]; }l;
long long max (long long a, long long b) {return a > b ? a : b;}
void print() {
	int i = l.top ;
	while( i != 0) {printf("%d ",l.s[i--].h);}
	printf("ans = %d\n",ans);
}
void update( int &w ) { w += l.s[l.top].w ; ans = max ( ans , (long long)l.s[l.top--].h * w);}
bool solve(){
	while ( scanf ("%d", &n) == 1 && n ) {
		l.top = 0; int temp; scanf ("%d", &temp ); l.s[++l.top].h = temp ; l.s[l.top].w = 1 ;ans = temp; n -- ; 
		while ( n -- ) {
			int key, w = 0; scanf ("%d", &key ) ;  ans = max ( ans , key ) ; //printf("%d : ",key);
			while ( l.top && l.s[l.top].h >= key) update( w  );
			l.s[++l.top].h = key , l.s[l.top].w = w + 1;
			//print();
		}
		int w = 0;
		while ( l.top ) update ( w) ;
		printf("%lld\n", ans ) ;
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