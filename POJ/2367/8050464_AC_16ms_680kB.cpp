#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
int n;	
//Product by MiracleEEEE 
inline int read(){
	char ch = getchar(); int re = 0; while (ch<'0' || ch>'9') ch=getchar();  
	while( ch >= '0'&& ch <= '9'){re = re * 10 + ch - '0'; ch = getchar();} return re;
}
inline void write(int re){
	if(re < 0) {putchar('-');re = -re;}
	if(re > 9) write(re / 10); putchar(re % 10 + '0');
}
int heads[110],in[110];
struct edge{int to, next;}edges[10005];int tot;
struct que{int s[150050],front, rear;}q;
void add( int x, int y ) {
	edges[++tot].next = heads[x]; edges[tot].to = y; heads[x] = tot;
}
bool input(){
	n = read();
	for ( int i = 1; i <= n ; i++ ) {
		while (1) {
			int temp = read();
			if ( !temp ) break; 
			add( i , temp ); in[temp]++;
		}
	}
	return true;
}
bool solve(){
     //for ( int i = 1;i <= n ; i ++) printf("%d ",in[i]);
	int temp;
	for ( int i = 1;i <= n ; i ++ ) if ( !in[i] ) {	q.s[q.rear++] = i;}
	while ( q.front != q.rear ) {
		int x = q.s[q.front++];
		int i = heads[x];
		printf("%d ",x);
		while ( i ) {
              //printf("i = %d %d %d ",i,edges[i].to,in[edges[i].to]);
			if ( !(--in[edges[i].to]))q.s[q.rear++] = edges[i].to;
			i =  edges[i].next;
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
	//system("pause");
	return 0;
} 
