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
int n,L,R,kase; __int64 ans;
struct p{long long  t, h, id;};
struct stack{int top; p s[100010]; }l;
__int64 max (__int64 a, __int64 b) {return a > b ? a : b;}
void print() {
	int i = l.top ;
	{printf("%d ",kase);}
	printf("ans = %lld\n",ans);
}
void update( __int64 &w , int &ok) {ok = l.s[l.top].id; w += l.s[l.top].t ;__int64 tmp = ans ; ans = max ( ans , (__int64)l.s[l.top--].h * w);/*printf("kase = %d %I64d w = %I64d ",kase, (__int64)l.s[l.top+1].h * w,w)*/ ;if( tmp != ans) L = l.s[l.top +1].id,R = kase;}
bool solve(){
		scanf ("%d", &n) ;
		l.top = 0; int temp; scanf ("%d", &temp ); l.s[++l.top].h = temp ; l.s[l.top].t = temp ;ans = (__int64)temp * temp; n -- ;l.s[l.top].id = ++kase; L = R = 1;
		while ( n -- ) {
			int key; __int64 w = 0; scanf ("%d",&key ) ;  __int64 tmp = ans ;ans = max ( ans ,(__int64 ) key*key ) ; if(tmp != ans) L = R = kase + 1; //printf("%d : ",key);
			int ok = 0;
			while ( l.top && l.s[l.top].h >= key) update( w, ok );kase++;
			l.s[++l.top].h = key , l.s[l.top].t = w + key;if(!ok)l.s[l.top].id = kase;
			else l.s[l.top].id = ok;
			//print();
		}//6 3 1 6 4 5 2

		__int64 w = 0; int ok = 0;
		while ( l.top ) update ( w , ok) ;
		printf("%I64d\n", ans ) ;
		printf("%d %d\n",L,R);
		return true;
}
int main()
{
	#ifdef LOCAL
	freopen("TEXT.txt","r",stdin);
	//freopen("OUTPUT.txt","w",stdout);
	#endif
	solve();
	return 0;
} 