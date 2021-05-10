#include <cstdio>
#include <cstring>
using namespace std;
//Product by MiracleEEEE 
int N, K, set[150010],ans,book[50010]; // 1 * n -> eat 2 * n = been eat 3 * n = same
inline int read(){
	char ch = getchar(); int re = 0; while (ch<'0' || ch>'9') ch=getchar();  
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
bool input(){
	N = read(); K = read();
	//printf("%d %d \n", N, K);
	return true;  // a eat b b eat c c eat a
}
int find( int key ) { return set[key] == key ? key : set[key] = find(set[key]);}

void Union ( int x, int y, int d ) { // d == 1 -> the same -> union n * 3 and n * 3, 1 * n and 1 * n, 2 * n and 2 * n // d == 2 -> x eat y -> union same and eat, eat and been eat, been eat and same
	int fx1 = find( x ), fx2 = find( x + N * 1 ), fx3 = find( x + N * 2 );
	int fy1 = find( y ), fy2 = find( y + N * 1 ), fy3 = find( y + N * 2 );
	//printf("fx1 = %d fx2 = %d fx3 = %d\n",fx1,fx2,fx3);
	//printf("fy1 = %d fy2 = %d fy3 = %d\n",fy1,fy2,fy3);
	///for( int i = 1;i <= N; i ++) printf("%d ",book[i]);
	//printf("\n");
	//printf("%d %d",book[x],book[y]);
	if (book[x]!= 0 && book[y]!=0 && (( d == 1 && ( fx1 == fy3 || fx2 == fy3))|| (d == 2 &&  (fx3 == fy3 || fx2 == fy3) ))) {ans ++; return ;}
	 {
		if ( d == 1 ) set[fx1] = fy1, set[fx2] = fy2, set[fx3] = fy3;
		if ( d == 2 ) set[fx1] = fy3, set[fx2] = fy1, set[fx3] = fy2;
		book[x] = book[y] = 1;
	}
	//for( int i = 1;i <= N; i ++) printf("%d ",book[i]);
	//printf("\n");
	//printf("fx1 = %d fx2 = %d fx3 = %d\n",fx1,fx2,fx3);
	//printf("fy1 = %d fy2 = %d fy3 = %d\n",fy1,fy2,fy3);
	// 4 -> 1 3/5/4 
} 
bool solve(){
	for ( int i = 1; i < 150010; i ++ ) set[i] = i; memset( book, 0, sizeof(book) );
	while ( K -- ) {
		int D = read(), A = read(), B = read();
		//printf("%d %d %d ", D, A, B);
		if ( D == 2 && ( A == B )) ans ++;
		else if ( A > N || B > N ) ans ++;
		else Union ( A, B, D );
		//printf("%d\n", ans);
	}
	printf("%d\n", ans);
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
	//system("pause");
	//system("pause");
	return 0;
} 